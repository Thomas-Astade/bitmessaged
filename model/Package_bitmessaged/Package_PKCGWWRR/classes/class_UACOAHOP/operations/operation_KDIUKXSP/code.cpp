int const addend(paramList.getInt(0));
int const adder(paramList.getInt(1));
paramList.verifyEnd(2);
*retvalP = xmlrpc_c::value_int(addend + adder);
