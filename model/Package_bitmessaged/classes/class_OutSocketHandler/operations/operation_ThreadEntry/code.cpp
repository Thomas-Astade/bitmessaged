//~~ void* ThreadEntry(void* context) [OutSocketHandler] ~~
OutSocketHandler* me = (OutSocketHandler*)context;
me->internalThread();
return 0;