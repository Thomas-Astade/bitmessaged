//~~ Payload(const protocol::Payload& orig) [Payload] ~~
while (sem_wait(&myDataSemaphore))
    ;

m_Data = orig.m_Data;
m_Data->refcount++;

sem_post(&myDataSemaphore);