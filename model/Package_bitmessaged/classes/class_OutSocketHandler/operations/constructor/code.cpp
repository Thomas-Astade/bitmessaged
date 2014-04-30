//~~ OutSocketHandler(struct ACF* anACF, sockaddr_in addr, data::knowledge& database) [OutSocketHandler] ~~
theKnowledge.incOutgoingCount();
toConnectionHandler = handler;

sourceAddr.sin_family = AF_INET;
sourceAddr.sin_addr.s_addr = INADDR_ANY;
sourceAddr.sin_port = 0;

pthread_create(&myThread,0,&ThreadEntry,this);