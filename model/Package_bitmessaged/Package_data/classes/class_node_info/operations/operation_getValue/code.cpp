//~~ int getValue() [node_info] ~~
int ret = 0;

if (lastConnectedTime) // a bonus, if we ever where connected to this node
{
    ret += 64;
    if ((currentlyInUse > 0) || (std::time(0) - lastConnectedTime) < 600) // some extra bonus, if we where connected resently
        ret += 16;
    if (lastFailedTime == 0) //another bonus, it it never failed
        ret += 8;
    else
        if ((std::time(0) - lastFailedTime) > (60 * 60 *24)) // or if it's long time ago
        ret += 4;
}

ret -= unsucessfulcount; // unsuccessful tries lower the value

RETURN(ret);