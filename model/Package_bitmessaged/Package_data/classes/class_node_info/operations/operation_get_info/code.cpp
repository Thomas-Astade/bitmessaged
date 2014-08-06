//~~ json_spirit::mObject get_info() [node_info] ~~
json_spirit::mObject obj;

obj["ip"] = inet_ntoa(myAddr.sin_addr);
obj["port"] = (uint64_t)htons(myAddr.sin_port);
obj["value"] = getValue();

if (lastConnectedTime)
    obj["last_connected"] = lastConnectedTime;

if (lastFailedTime)
    obj["last_failed"] = lastFailedTime;
    
if (m_offerCount)
    obj["offered_objects"] = (uint64_t)m_offerCount;
    
if (m_oldObjectCount)
    obj["old_objects"] = (uint64_t)m_oldObjectCount;
    
if (m_Version)
    obj["protocol_version"] = (uint64_t)m_Version;
    
if (m_futureObjectCount)
    obj["future_objects"] = (uint64_t)m_futureObjectCount;
    
if (m_duplicateOfferCount)
    obj["duplicate_offered_objects"] = (uint64_t)m_duplicateOfferCount;
    
if (unsucessfulcount)
    obj["unsuccessful_count"] = (uint64_t)unsucessfulcount;

if (sucessfulcount)
    obj["successful_count"] = (uint64_t)sucessfulcount;

if (m_Services)
    obj["services"] = m_Services;

if (!m_Agent.empty())
    obj["user_agent"] = m_Agent;

return obj;