//~~ void handleObject(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::object* anObject = (protocol::object*)event->Data;

if (*VectorsToRequest.begin() == anObject->getVector())
    theKnowledge.addObject(*anObject);
