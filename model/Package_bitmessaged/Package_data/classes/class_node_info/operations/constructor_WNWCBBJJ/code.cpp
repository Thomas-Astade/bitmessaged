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
