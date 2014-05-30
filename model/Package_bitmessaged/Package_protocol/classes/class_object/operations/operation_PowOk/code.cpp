//~~ bool PowOk() [object] ~~
uint64_t pow_value = myPayload.pow_value();
uint64_t target = myPayload.pow_target();

RETURN(pow_value <= target);
