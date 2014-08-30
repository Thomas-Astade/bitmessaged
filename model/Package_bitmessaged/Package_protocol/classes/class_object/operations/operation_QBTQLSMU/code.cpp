//~~ bool isActuell() [object] ~~
uint64_t oTime = getTime();
uint64_t now = std::time(0);

bool oldObject;

if (getType() == protocol::message::object)
    oldObject = (oTime <= now);
else 
    oldObject = ((getType() == protocol::message::pubkey) && ((oTime + maximumKeyAdvertiseAge) < now)) ||
                   ((getType() != protocol::message::pubkey) && ((oTime + maximumAdvertiseAge) < now))
                  ;

bool futureObject;

if (getType() == protocol::message::object)
    futureObject = (oTime > (now + (60 * 60 * 24 * 28)));
else 
    futureObject = (oTime > now);

RETURN(!oldObject && !futureObject);