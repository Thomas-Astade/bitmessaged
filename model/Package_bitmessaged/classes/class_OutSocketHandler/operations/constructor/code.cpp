//~~ OutSocketHandler(struct ACF* anACF, sockaddr_in addr, data::knowledge& database, ACF_MessageReceiver* handler, uint64_t theNodeID) [OutSocketHandler] ~~
theKnowledge.incOutgoingCount();
toConnectionHandler = handler;

sourceAddr.sin_family = AF_INET;
sourceAddr.sin_addr.s_addr = INADDR_ANY;
sourceAddr.sin_port = 0;

myLogic = new BitmessageLogic(anACF, database, theNodeID);
myLogic->toSocket = MessageReceiver();
toLogic = myLogic->MessageReceiver();
myLogic->Initialize(0);


pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

pthread_create(&myThread,&attr,&ThreadEntry,this);