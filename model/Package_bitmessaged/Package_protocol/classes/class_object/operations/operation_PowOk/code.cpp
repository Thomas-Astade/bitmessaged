//~~ bool PowOk() [object] ~~
uint64_t target;

if (myType == message::object)
{
    uint64_t now = std::time(0);
    uint64_t oTime = getTime() - wiggle_room;
    if (oTime <= now)
        target = myPayload.pow_target_V3(0);
    else
        target = myPayload.pow_target_V3(oTime - now);
}
else
    target = myPayload.pow_target_V2();

uint64_t pow_value = myPayload.pow_value();

RETURN(pow_value <= target);
