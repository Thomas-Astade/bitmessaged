//~~ OutSocketHandler(struct ACF* anACF, sockaddr_in addr) [OutSocketHandler] ~~
socketfd = socket(AF_INET, SOCK_STREAM, 0);
pthread_create(&myThread,0,&ThreadEntry,this);