//~~ uint32_t getChecksum() [Payload] ~~
uint32_t ret;

unsigned char hash[SHA512_DIGEST_LENGTH];
SHA512(&m_Data->at(0), m_Data->size(), hash);
memcpy(&ret,hash,sizeof(ret));

RETURN(ret);