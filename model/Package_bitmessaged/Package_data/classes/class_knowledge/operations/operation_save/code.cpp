//~~ void save() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
json_spirit::mObject obj;
obj["known_nodes"] = known_node_list.get_info();

sem_post(&mySemaphore);

std::string filename = std::string(getenv ("HOME")) + "/" + ".bitmessaged.json";
std::ofstream os( filename.c_str() );
write( obj, os, json_spirit::pretty_print );
os.close();