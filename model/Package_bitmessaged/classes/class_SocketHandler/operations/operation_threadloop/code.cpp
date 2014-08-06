//~~ void threadloop() [SocketHandler] ~~
while (1)
{
    try {
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
            theKnowledge.dumpLock();
            printf("detected message type %d\n",messageType);
            printf("expect a message of size: %d\n",messageLen+20);
            theKnowledge.dumpUnlock();
        }
        
        uint8_t rcvbuffer[2000]; //just some buffer
        protocol::wPayload aPayload;
        
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
            
            if (haveRead < 0)
            {
                ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
                ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
                return;
            }
            
            aPayload.push_back(rcvbuffer, haveRead);
            messageLen -= haveRead;
        }
        
        // check the checksum
        if (*((uint32_t*)&buffer[20]) != aPayload.getChecksum())
        {
            ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
            ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
            close(socketfd);
            if (theKnowledge.getDebug())
            {
                theKnowledge.dumpLock();
                printf("WRONG CHECKSUM!\n");
                theKnowledge.dumpUnlock();
            }
            return;
        }

        switch (messageType) {
            case protocol::message::verack:
                ACF_sendMessage(MessageReceiver(),toLogic,ev_verack,0);
                break;
            case protocol::message::version:
                {
                    protocol::version aVersion(aPayload,0);
                    if ((aVersion.getVersion() != 2) && (aVersion.getVersion() != 3)) // at the moment we support only version 2 and 3
                    {
                        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
                        return;
                    }
                    ACF_sendMessage(MessageReceiver(),toLogic,ev_version,new protocol::Payload(aPayload));
                }
                break;
            case protocol::message::addr:
                ACF_sendMessage(MessageReceiver(),toLogic,ev_addr,new protocol::Payload(aPayload));
                break;
            case protocol::message::inv:
                ACF_sendMessage(MessageReceiver(),toLogic,ev_inv,new protocol::Payload(aPayload));
                break;
            case protocol::message::getdata:
                ACF_sendMessage(MessageReceiver(),toLogic,ev_getdata,new protocol::Payload(aPayload));
                break;
            case protocol::message::getpubkey:
            case protocol::message::pubkey:
            case protocol::message::broadcast:
            case protocol::message::msg:
                if (aPayload.size() > 16)
                {
                    protocol::object* anObject = new protocol::object(messageType,aPayload);
                    if (anObject->PowOk())
                        ACF_sendMessage(MessageReceiver(),toLogic,ev_object,anObject);
                    else
                        delete anObject;
                }
                break;
            default:
                break;
        }
        
        if (theKnowledge.getDebug())
        {
            theKnowledge.dumpLock();
            printf("Received Message:\n");
            protocol::wPayload dumpPayload;
            dumpPayload.push_back(buffer,sizeof(buffer));
            dumpPayload.push_back(aPayload);
            dumpPayload.dump();
            theKnowledge.dumpUnlock();
        }
    }
    catch(...)
    {
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
        close(socketfd);
        return;
    }
}