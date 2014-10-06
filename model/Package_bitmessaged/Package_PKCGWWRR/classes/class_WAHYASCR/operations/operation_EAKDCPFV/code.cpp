//~~ void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) [getV2Object] ~~
std::vector<unsigned char> ivector = paramList.getBytestring(0);
paramList.verifyEnd(1);

if (ivector.size() != 32)
    throw(girerr::error("a inventory vector has to contain 32 bytes"));

protocol::inventory_vector v(&ivector[0]);
protocol::object o = database->getObject(v);

if (!o.isValid())
    throw(girerr::error("there is no such object"));

protocol::Payload p(o.getPayload());

std::vector<unsigned char> myBytes(p.size());
memcpy(&myBytes[0],*p,p.size());

*retvalP = xmlrpc_c::value_bytestring(myBytes);