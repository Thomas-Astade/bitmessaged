//~~ bool isOld() [object] ~~
uint64_t oTime = getTime();
uint64_t now = std::time(0);
bool oldObject = ((getType() == protocol::message::pubkey) && ((oTime + maximumKeyAcceptAge) < now)) ||
                   ((getType() != protocol::message::pubkey) && ((oTime + maximumAcceptAge) < now))
                  ;
RETURN(oldObject);