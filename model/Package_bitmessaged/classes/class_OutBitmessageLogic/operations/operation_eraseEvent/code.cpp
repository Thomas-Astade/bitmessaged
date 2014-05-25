//~~ void eraseEvent(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::inventory_vector* aVector = (protocol::inventory_vector*)event->Data;
delete aVector;