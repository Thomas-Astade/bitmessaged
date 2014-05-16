//~~ protocol::Payload& operator=(const protocol::Payload& orig) [Payload] ~~
if (&orig == this)
    return *this;

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

m_Data = orig.m_Data;
m_Data->refcount++;

sem_post(&myDataSemaphore);

return *this;