//~~ OutSocketHandler(struct ACF* anACF, sockaddr_in addr, data::knowledge& database, ACF_MessageReceiver* handler) [OutSocketHandler] ~~
theKnowledge.incOutgoingCount();
toConnectionHandler = handler;

sourceAddr.sin_family = AF_INET;
sourceAddr.sin_addr.s_addr = INADDR_ANY;
sourceAddr.sin_port = 0;

myLogic = new OutBitmessageLogic(anACF, database);
myLogic->toSocket = MessageReceiver();
toLogic = myLogic->MessageReceiver();
myLogic->Initialize(0);

pthread_create(&myThread,0,&ThreadEntry,this);