//~~ void dumpLock()() [knowledge] ~~
while (sem_wait(&dumpSemaphore))
    ;
