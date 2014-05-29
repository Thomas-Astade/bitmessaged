//~~ void* ThreadEntry(void* context) [InConnectionHandler] ~~
InConnectionHandler* me = (InConnectionHandler*)context;
me->internalThread();
return 0;