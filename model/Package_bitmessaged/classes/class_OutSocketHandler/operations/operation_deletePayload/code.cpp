//~~ void deletePayload(ACF_Message* event) [OutSocketHandler] ~~
protocol::Payload* aPayload = (protocol::Payload*)event->Data;
delete aPayload;