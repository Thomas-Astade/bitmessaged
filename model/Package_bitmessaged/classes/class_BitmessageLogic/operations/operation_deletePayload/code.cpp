//~~ void deletePayload(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::Payload* aPayload = (protocol::Payload*)event->Data;
delete aPayload;