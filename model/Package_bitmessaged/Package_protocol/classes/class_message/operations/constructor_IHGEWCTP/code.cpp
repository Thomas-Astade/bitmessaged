//~~ message(protocol::message::command_t type, std::tr1::shared_ptr<std::vector<uint8_t> > payload) [message] ~~
unsigned char hash[SHA512_DIGEST_LENGTH];
SHA512(&(*myPayload)[0], (*myPayload).size(), hash);
memcpy(&checksum,hash,sizeof(checksum));