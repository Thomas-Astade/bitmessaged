//~~ uint64_t doMHash() [thread] ~~
uint8_t buffer[8+SHA512_DIGEST_LENGTH];

memcpy(&buffer[8], m_initialHash, SHA512_DIGEST_LENGTH);

uint64_t trialValue = (uint64_t)0xffffffffffffffff;
uint64_t nonce = m_offset;

uint8_t resultHash1[SHA512_DIGEST_LENGTH];
uint8_t resultHash2[SHA512_DIGEST_LENGTH];

while (trialValue > m_target)
{
    nonce += m_incval;
    memcpy(buffer, &nonce, 8);
    SHA512(buffer, SHA512_DIGEST_LENGTH + 8, resultHash1);
    SHA512(resultHash1, SHA512_DIGEST_LENGTH, resultHash2);
    memcpy(&trialValue, resultHash2, sizeof(trialValue));
    trialValue = htonll(trialValue);
}
return nonce;
