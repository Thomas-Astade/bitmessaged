//~~ void requestObjects(ACF_Message* event) [OutBitmessageLogic] ~~
if (VectorsToRequest.empty()) // nothing to request
    return;
    
protocol::getdata aGet;

aGet.insert(*VectorsToRequest.begin());

ACF_sendMessage(MessageReceiver(),toSocket,ev_getdata,new protocol::Payload(aGet.getPayload()));