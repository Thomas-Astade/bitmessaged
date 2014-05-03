//~~ void load() [knowledge] ~~
std::string filename = std::string(getenv ("HOME")) + "/" + ".bitmessaged.json";
std::ifstream is( filename.c_str() );
json_spirit::mValue value;
read( is, value );

if (value.type() == json_spirit:: obj_type)
{
    json_spirit::mValue value1 = value.get_obj()["known_nodes"];
    if (value1.type() == json_spirit:: array_type)
    {
        known_node_list.addNodes(value1.get_array());
    }
}
