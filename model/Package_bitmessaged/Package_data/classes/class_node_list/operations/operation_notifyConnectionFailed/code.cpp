//~~ void notifyConnectionFailed(uint64_t id) [node_list] ~~
#ifdef _TRACE_
    char buffer[50];
    sprintf(buffer,"%ld",id);
    Trace2UML::notify_log(5,this,"node_list",buffer);
#endif

if (known_nodes.find(id) == known_nodes.end())
    return;

node_info node = known_nodes[id];
node.ConnectionFailed();
known_nodes[id] = node;
