//~~ void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) [addV2Object] ~~
std::vector<unsigned char> ivector = paramList.getBytestring(0);
paramList.verifyEnd(1);

protocol::wPayload p;
p.push_back(&ivector[0],ivector.size());
protocol::object o(m_Type,p);

if (!o.PowOk())
    throw(girerr::error("Your POW nonce is not correct"));
    
if (!o.isActuell())
    throw(girerr::error("the time of the object is not correct"));

database->addObject(0,o);

std::vector<unsigned char> myBytes(32);
memcpy(&myBytes[0],o.getVector().getData(),32);

*retvalP = xmlrpc_c::value_bytestring(myBytes);
