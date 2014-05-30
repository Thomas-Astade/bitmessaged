//~~ uint64_t pow_target(int pow_per_byte = 320, int pow_extra_bytes = 14000) [Payload] ~~
const uint64_t two_63 = (uint64_t)(0x8000000000000000);
uint64_t divisor;
uint64_t target;

divisor = ((m_Data->size() + (uint64_t) pow_extra_bytes) *
           pow_per_byte);

/* We need to divide 2⁶⁴ by divisor. We can't represent 2⁶⁴ in
 * a 64-bit variable so instead we divide 2⁶³ by the divisor
 * twice and add the result */
target = two_63 / divisor * 2;
/* If the fractional part of the result would be greater than
 * or equal to a half then we would get an extra 1 when we
 * multiply by two */
if ((two_63 % divisor) * 2 >= divisor)
        target++;

return target;
