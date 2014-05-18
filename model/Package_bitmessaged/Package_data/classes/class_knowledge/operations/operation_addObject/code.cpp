//~~ void addObject(const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
if (collectedObjects.find(object.getVector()) == collectedObjects.end())
{
    struct tm *tmp;
    time_t t;
    char nowstr[200];
    char ostr[200];

    t = getTime();
    tmp = localtime(&t);
    strftime(nowstr, sizeof(nowstr), "%a, %d %b %y %T %z",tmp);

    t = object.getTime();
    tmp = localtime(&t);
    strftime(ostr, sizeof(ostr), "%a, %d %b %y %T %z",tmp);

    if ((getTime() - object.getTime()) < ((2*24*60*60) + 600))
    {   //only if less than 2 days old
        collectedObjects[object.getVector()] = object;
        std::pair<uint64_t, protocol::inventory_vector> aPair(getTime(), object.getVector());
        receivedTimes.push_back(aPair);
        printf("Add object                   now: %s object %s\n", nowstr, ostr);
        printf("      %s: ",object.getTypeStr().c_str());
        for (int i = 0; i < 32; i++)
        {
            printf("%02x",object.getVector()[i]);
        }
        printf("\n");
    }
    else
    {
        printf("FAIL: to old object received now: %s object %s\n", nowstr, ostr);
        printf("      %s: ",object.getTypeStr().c_str());
        for (int i = 0; i < 32; i++)
        {
            printf("%02x",object.getVector()[i]);
        }
        printf("\n");
    }
}

sem_post(&mySemaphore);