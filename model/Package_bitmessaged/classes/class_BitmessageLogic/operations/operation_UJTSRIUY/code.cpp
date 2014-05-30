//~~ void storeNewObject(ACF_Message* event) [BitmessageLogic] ~~
protocol::inventory_vector* aVector = (protocol::inventory_vector*)event->Data;
VectorsWeCouldOffer.insert(*aVector);