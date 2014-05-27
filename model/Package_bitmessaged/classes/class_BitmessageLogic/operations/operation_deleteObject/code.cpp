//~~ void deleteObject(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::object* anObject = (protocol::object*)event->Data;
delete anObject;