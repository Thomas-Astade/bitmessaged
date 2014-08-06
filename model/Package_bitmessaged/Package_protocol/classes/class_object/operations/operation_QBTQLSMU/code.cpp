//~~ bool isActuell() [object] ~~
uint64_t oTime = getTime();
uint64_t now = std::time(0);
bool oldObject = ((getType() == protocol::message::pubkey) && ((oTime + maximumKeyAdvertiseAge) < now)) ||
                   ((getType() != protocol::message::pubkey) && ((oTime + maximumAdvertiseAge) < now))
                  ;
RETURN(!oldObject);