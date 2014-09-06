//~~ bool isOld() [object] ~~
uint64_t oTime = getTime() - wiggle_room;
uint64_t now = std::time(0);

bool oldObject;

if (getType() == protocol::message::object)
    oldObject = ((oTime + (6 * 60 *60)) <= now);
else 
    oldObject = ((getType() == protocol::message::pubkey) && ((oTime + maximumKeyAcceptAge) < now)) ||
                   ((getType() != protocol::message::pubkey) && ((oTime + maximumAcceptAge) < now))
                  ;
RETURN(oldObject);