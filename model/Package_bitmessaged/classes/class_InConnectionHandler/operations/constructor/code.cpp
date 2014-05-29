//~~ InConnectionHandler(int port, struct ACF* logicContext, struct ACF* socketContext, data::knowledge& database) [InConnectionHandler] ~~
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

pthread_create(&myThread,&attr,&ThreadEntry,this);