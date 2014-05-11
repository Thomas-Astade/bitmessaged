//~~ void handleObject(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::object* anObject = (protocol::object*)event->Data;

theKnowledge.addObject(*anObject);

if (!VectorsToRequest.empty())
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_request,0);