//~~ void handleObject(ACF_Message* event) [BitmessageLogic] ~~
protocol::object* anObject = (protocol::object*)event->Data;

theKnowledge.addObject(nodeID,*anObject);
