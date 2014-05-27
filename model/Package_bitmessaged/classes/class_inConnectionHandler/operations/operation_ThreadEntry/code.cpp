//~~ void* ThreadEntry(void* context) [inConnectionHandler] ~~
inConnectionHandler* me = (inConnectionHandler*)context;
me->internalThread();
return 0;