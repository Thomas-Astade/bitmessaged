//~~ std::string getContentHash() [object] ~~
uint8_t hash[MD5_DIGEST_LENGTH];

if ((myType == protocol::message::object) && myPayload.size() > 20)
{
    MD5((*myPayload)+20, myPayload.size()-20, hash);
    RETURN(std::string((char*)hash,MD5_DIGEST_LENGTH));
} else if ((myType != protocol::message::object) && myPayload.size() > 16)
{
    MD5((*myPayload)+16, myPayload.size()-16, hash);
    RETURN(std::string((char*)hash,MD5_DIGEST_LENGTH));
}

RETURN(std::string());