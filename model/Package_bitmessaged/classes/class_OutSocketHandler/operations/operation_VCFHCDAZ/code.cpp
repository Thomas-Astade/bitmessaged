//~~ void dumpSend() [OutSocketHandler] ~~
printf("%s:%d -> ",
    inet_ntoa(sourceAddr.sin_addr),
    htons(sourceAddr.sin_port)
    );

printf("%s:%d\n",
    inet_ntoa(destAddr.sin_addr),
    htons(destAddr.sin_port)
    );