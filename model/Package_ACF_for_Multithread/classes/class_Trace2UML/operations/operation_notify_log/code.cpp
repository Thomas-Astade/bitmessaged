//~~ void notify_log(int level, const void* objectPointer, const char* objectName, const char* stateName) [Trace2UML] ~~
while (sem_wait(&msSemaphore))
    ;

if (level > tracelevel && ms_ofile.is_open())
{
    traceTimestamp();
    ms_ofile << objectPointer << ":" << objectName << " note: " << stateName << std::endl;
}

ms_ofile.flush();
sem_post(&msSemaphore);