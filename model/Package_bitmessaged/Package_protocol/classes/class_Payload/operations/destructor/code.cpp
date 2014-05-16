//~~ ~Payload() [Payload] ~~
while (sem_wait(&myDataSemaphore))
    ;

if (m_Data->refcount == 0)
{
    delete m_Data;
}
else
{
    m_Data->refcount--;
}

sem_post(&myDataSemaphore);