//~~ void addNodes(json_spirit::mArray& addr) [node_list] ~~
for (json_spirit::mArray::iterator it = addr.begin(); it != addr.end(); it++)
{
    if ((*it).type() == json_spirit::obj_type)
    {
        node_info aNode((*it).get_obj());
        if (known_nodes.find(aNode.getID()) == known_nodes.end())
            known_nodes[aNode.getID()] = aNode;
    }
}