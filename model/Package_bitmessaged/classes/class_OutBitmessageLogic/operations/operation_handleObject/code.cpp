//~~ void handleObject(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::object* anObject = (protocol::object*)event->Data;

if (*VectorsToRequest.begin() == anObject->getVector())
    printf("correct object received\n");
else
    printf("WRONG object received\n");
