//~~ void dumpSend() [SocketHandler] ~~
printf("me -> %s:%d\n",
    inet_ntoa(destAddr.sin_addr),
    htons(destAddr.sin_port)
    );