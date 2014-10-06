//~~ void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) [getV3Objects] ~~
std::vector<xmlrpc_c::value> arrayData;

std::set<protocol::inventory_vector> objects = database->getObjects(3);

for (std::set<protocol::inventory_vector>::iterator it = objects.begin(); it != objects.end(); it++)
{
    protocol::object anObject = database->getObject(*it);
    if (m_Type == anObject.getObjectType())
    {
        std::vector<unsigned char> myBytes(32);
        memcpy(&myBytes[0],(*it).getData(),32);
        arrayData.push_back(xmlrpc_c::value_bytestring(myBytes));
    }
}

*retvalP = xmlrpc_c::value_array(arrayData);
