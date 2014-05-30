//~~ uint64_t pow_value() [Payload] ~~
uint8_t initial_hash[8 + SHA512_DIGEST_LENGTH];
uint8_t hash1[SHA512_DIGEST_LENGTH];
uint8_t hash2[SHA512_DIGEST_LENGTH];
uint64_t pow_value;

/* Initial hash is nonce + hash(rest of the data) */
memcpy(initial_hash, &m_Data->operator[](0), 8);
SHA512(&m_Data->operator[](8), m_Data->size() - 8, initial_hash + 8);

/* Get the result hash into hash2 */
SHA512(initial_hash, sizeof initial_hash, hash1);
SHA512(hash1, sizeof hash1, hash2);

/* The POW value is the first 8 bytes of that as a big-endian
 * number */
memcpy(&pow_value, hash2, sizeof pow_value);

return htonll(pow_value);
