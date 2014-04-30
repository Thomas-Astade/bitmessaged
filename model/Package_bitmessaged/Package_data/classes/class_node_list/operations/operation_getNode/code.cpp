//~~ bool getNode(data::node_info& info) [node_list] ~~
if (known_nodes.empty())
    RETURN(false);
    
data::node_info& res = (*known_nodes.begin()).second;

if (res.isInUse())
    RETURN(false);

res.incUse();

info = res;

RETURN(true);