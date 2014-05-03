//~~ void save() [knowledge] ~~
json_spirit::mObject obj;
obj["known_nodes"] = known_node_list.get_info();

std::string filename = std::string(getenv ("HOME")) + "/" + ".bitmessaged.json";
std::ofstream os( filename.c_str() );
write( obj, os, json_spirit::pretty_print );
os.close();