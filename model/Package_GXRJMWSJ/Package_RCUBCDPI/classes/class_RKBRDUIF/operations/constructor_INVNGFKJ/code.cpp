//~~ thread(unsigned int offset, unsigned int incval, uint64_t target, char* initialHash) [thread] ~~
pthread_create( &context, NULL, (void* (*)(void*))&thread::threadLoop, this);