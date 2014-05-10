//~~ inventory_vector getVector() [Payload] ~~
unsigned char hash1[SHA512_DIGEST_LENGTH];
unsigned char hash2[SHA512_DIGEST_LENGTH];
SHA512(&VECTOR[0], VECTOR.size(), hash1);
SHA512(hash1, sizeof(hash1), hash2);

RETURN(inventory_vector(hash2));