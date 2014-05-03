//~~ json_spirit::mObject get_info() [node_info] ~~
json_spirit::mObject obj;

obj["ip"] = inet_ntoa(myAddr.sin_addr);
obj["port"] = (uint64_t)myAddr.sin_port;

if (currentlyInUse > 0)
    obj["last_connected"] = std::time(0);
else
    obj["last_connected"] = lastConnectedTime;

obj["last_failed"] = lastFailedTime;
obj["unsuccessful_count"] = (uint64_t)unsucessfulcount;

return obj;