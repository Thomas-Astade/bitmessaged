//~~ std::set<protocol::inventory::vector> getObjects(uint64_t minTime, uint64_t maxTime) [knowledge] ~~
std::set<protocol::inventory_vector> ret;

if (maxTime < minTime)
    return ret;

while (sem_wait(&mySemaphore))
    ;
    
for (std::list<std::pair<uint64_t, protocol::inventory_vector> >::iterator it = receivedTimes.begin();
     it != receivedTimes.end(); it++)
{
    if ((*it).first > maxTime)
        break;
    if ((*it).first >= minTime)
        ret.insert((*it).second);
}
sem_post(&mySemaphore);

return ret;