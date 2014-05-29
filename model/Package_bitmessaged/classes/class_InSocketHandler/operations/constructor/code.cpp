//~~ InSocketHandler(struct ACF* anACF, sockaddr_in addr, data::knowledge& database, ACF_MessageReceiver* handler, int fd) [InSocketHandler] ~~
socketfd = fd;

theKnowledge.incIncommingCount();
toConnectionHandler = handler;

myLogic = new BitmessageLogic(anACF, database);
myLogic->toSocket = MessageReceiver();
toLogic = myLogic->MessageReceiver();
myLogic->Initialize(0);

pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

pthread_create(&myThread,&attr,&ThreadEntry,this);