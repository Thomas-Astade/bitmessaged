//~~ void* ThreadEntry(void* context) [OutSocketHandler] ~~
InSocketHandler* me = (InSocketHandler*)context;
me->internalThread();
return 0;