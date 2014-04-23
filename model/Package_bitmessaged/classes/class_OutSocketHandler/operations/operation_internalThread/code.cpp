//~~ void internalThread() [OutSocketHandler] ~~
socketfd = socket(AF_INET, SOCK_STREAM, 0);

if (socketfd < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    return;
}

if (connect(socketfd, (struct sockaddr *)&myAddr, sizeof(myAddr)) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}


ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_connected,0);

while (1)
{
    sleep(1);
}