//~~ uint32_t getChecksum() [Payload] ~~
uint32_t ret;

unsigned char hash[SHA512_DIGEST_LENGTH];
SHA512(&VECTOR[0], VECTOR.size(), hash);
memcpy(&ret,hash,sizeof(ret));

RETURN(ret);