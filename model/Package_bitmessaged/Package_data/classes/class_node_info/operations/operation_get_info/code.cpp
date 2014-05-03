//~~ json_spirit::mObject get_info() [node_info] ~~
json_spirit::mObject obj;

obj["ip"] = inet_ntoa(myAddr.sin_addr);
obj["port"] = (uint64_t)htons(myAddr.sin_port);

if (currentlyInUse > 0)
    obj["last_connected"] = (uint64_t)std::time(0);
else if (lastConnectedTime)
    obj["last_connected"] = lastConnectedTime;

if (lastFailedTime)
    obj["last_failed"] = lastFailedTime;
    
if (unsucessfulcount)
    obj["unsuccessful_count"] = (uint64_t)unsucessfulcount;

if (!m_Agent.empty())
    obj["user_agent"] = m_Agent;

return obj;