//~~ void deleteObject(ACF_Message* event) [OutSocketHandler] ~~
protocol::object* anObject = (protocol::object*)event->Data;
delete anObject;