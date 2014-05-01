//~~ void internalThread() [OutSocketHandler] ~~
socketfd = socket(AF_INET, SOCK_STREAM, 0);

if (socketfd < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

if (connect(socketfd, (struct sockaddr *)&destAddr, sizeof(destAddr)) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

socklen_t len = sizeof(sourceAddr);

if (getsockname(socketfd, (struct sockaddr *) &sourceAddr, &len) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_connected,0);

while (1)
{
    uint8_t buffer[24];

    int ret = recv(socketfd, &buffer, sizeof(buffer), MSG_WAITALL);

    if (ret == 0)
    {
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
        return;
    }
    
    if (ret < (int)sizeof(buffer))
    {
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
        return;
    }
    
    protocol::message::command_t messageType = protocol::message::unknown;
    
    for (unsigned int search = protocol::message::version;
        search < protocol::message::unknown; search++)
    {
        if (memcmp(buffer, comand_defines[search], 16) == 0)
        {
            messageType = (protocol::message::command_t)search;
            break;
        }
    }
    
    printf("detected message type %d\n",messageType);
    
    uint32_t messageLen = htonl(*((uint32_t*)&buffer[16]));
    
    if (messageLen > (200 * 1024 * 1024)) // we do not accapt messages longer than 200 MByte
    {
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
        close(socketfd);
        return;
    }

    if (theKnowledge.getDebug())
    {
        printf("expect a message of size: %d\n",messageLen+20);
    }
    
    uint8_t rcvbuffer[2000]; //just some buffer
    protocol::Payload aPayload;
    
    while (messageLen)
    {
        unsigned int read = messageLen;
        
        if (read > sizeof(rcvbuffer))
            read = sizeof(rcvbuffer);
            
        int haveRead = recv(socketfd, &rcvbuffer, read, 0);

        if (haveRead == 0)
        {
            ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
            return;
        }
        
        if (read < 0)
        {
            ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
            ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
            return;
        }
        
        aPayload.push_back(rcvbuffer, haveRead);
        messageLen -= haveRead;
    }
    
    switch (messageType) {
        case protocol::message::verack:
            ACF_sendMessage(MessageReceiver(),toLogic,ev_verack,0);
            break;
        case protocol::message::version:
            ACF_sendMessage(MessageReceiver(),toLogic,ev_version,0);
            break;
        default:
            break;
    }
    
    if (*((uint32_t*)&buffer[20]) != aPayload.getChecksum())
    {
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
        close(socketfd);
        return;
    }
    
    if (theKnowledge.getDebug())
    {
        printf("Received Message:\n");
        protocol::Payload dumpPayload;
        dumpPayload.push_back(buffer,sizeof(buffer));
        dumpPayload.push_back(aPayload);
        dumpPayload.dump();
    }
}