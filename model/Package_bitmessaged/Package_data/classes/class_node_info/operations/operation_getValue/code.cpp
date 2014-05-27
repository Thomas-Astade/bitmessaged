//~~ int getValue() [node_info] ~~
int ret = 0;

if (sucessfulcount) // a bonus, if we ever where connected to this node
{
    ret += 4;
    if (lastFailedTime == 0) //another bonus, it it never failed
        ret += 2;
    else
        if ((std::time(0) - lastFailedTime) > (60 * 60 *24)) // or if it's long time ago
        ret += 1;
}

if (m_offerCount > 100) // a bonus for offered objects
    ret += 4;

unsigned int successfulBonus = (sucessfulcount/5); 
if (successfulBonus > 5)
    successfulBonus = 5;

if (m_oldObjectCount != 0) // a small malus for nodes that have an incorrect clock
    ret -= 2;
    
if (m_futureObjectCount != 0) // a small malus for nodes that have an incorrect clock
    ret -= 2;

ret += successfulBonus; // this is for nodes which have proven to be reliable

ret -= unsucessfulcount; // unsuccessful tries lower the value

RETURN(ret);