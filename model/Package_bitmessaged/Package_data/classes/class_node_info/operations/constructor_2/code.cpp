//~~ node_info(json_spirit::mObject& data) [node_info] ~~
myAddr.sin_family =  AF_INET;

if (data["ip"].type() == json_spirit::str_type)
{
    inet_pton(AF_INET, data["ip"].get_str().c_str(), &myAddr.sin_addr);
}

if (data["port"].type() == json_spirit::int_type)
{
    myAddr.sin_port = htons(data["port"].get_int());
}

if (data["offered_objects"].type() == json_spirit::int_type)
{
    m_offerCount = data["offered_objects"].get_int();
}

if (data["duplicate_offered_objects"].type() == json_spirit::int_type)
{
    m_duplicateOfferCount = data["duplicate_offered_objects"].get_int();
}

if (data["last_connected"].type() == json_spirit::int_type)
{
    lastConnectedTime = data["last_connected"].get_uint64();
}

if (data["last_failed"].type() == json_spirit::int_type)
{
    lastFailedTime = data["last_failed"].get_uint64();
}

if (data["unsuccessful_count"].type() == json_spirit::int_type)
{
    unsucessfulcount = data["unsuccessful_count"].get_int();
}

if (data["successful_count"].type() == json_spirit::int_type)
{
    sucessfulcount = data["successful_count"].get_int();
}

if (data["services"].type() == json_spirit::int_type)
{
    m_Services = data["services"].get_int();
}

if (data["user_agent"].type() == json_spirit::str_type)
{
    m_Agent = data["user_agent"].get_str();
}
