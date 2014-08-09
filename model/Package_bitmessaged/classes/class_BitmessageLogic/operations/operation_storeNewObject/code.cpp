//~~ void storeNewObject(ACF_Message* event) [BitmessageLogic] ~~
protocol::inventory_vector* aVector = (protocol::inventory_vector*)event->Data;

protocol::object o = theKnowledge.getObject(aVector);

if ((m_Protocol_Version == 3) && (o.getType() == protocol::message::object))
    VectorsWeCouldOffer.insert(*aVector);
else if ((m_Protocol_Version == 2) && (o.getType() != protocol::message::object))
    VectorsWeCouldOffer.insert(*aVector);