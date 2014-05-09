//~~ int getValue() [node_info] ~~
int ret = 0;

if (sucessfulcount) // a bonus, if we ever where connected to this node
{
    ret += 64;
    if (lastFailedTime == 0) //another bonus, it it never failed
        ret += 8;
    else
        if ((std::time(0) - lastFailedTime) > (60 * 60 *24)) // or if it's long time ago
        ret += 4;
}

unsigned int successfulBonus = sucessfulcount;
if (successfulBonus > 10)
    successfulBonus = 10;
    
ret += successfulBonus; // this is for nodes which have proven to be reliable

ret -= unsucessfulcount; // unsuccessful tries lower the value

RETURN(ret);