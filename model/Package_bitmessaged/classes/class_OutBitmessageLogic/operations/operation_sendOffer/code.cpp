//~~ void sendOffer(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::inventory_vector* aVector = (protocol::inventory_vector*)event->Data;

protocol::inv anOffer;

if (VectorsWeGotOffered.find(*aVector) != VectorsWeGotOffered.end())
{
    if (VectorsWeHaveOffered.find(*aVector) == VectorsWeHaveOffered.end())
    {
        VectorsWeHaveOffered.insert(*aVector);
        anOffer.insert(*VectorsToRequest.begin());
    }
}

while ((anOffer.size() < 100) && (!VectorsWeCouldOffer.empty()))
{
    if (VectorsWeHaveOffered.find(*VectorsWeCouldOffer.begin()) == VectorsWeHaveOffered.end())
    {
        VectorsWeHaveOffered.insert(*VectorsWeCouldOffer.begin());
        anOffer.insert(*VectorsWeCouldOffer.begin());
    }
    VectorsWeCouldOffer.erase(VectorsWeCouldOffer.begin());
}

if (!anOffer.empty())
    ACF_sendMessage(MessageReceiver(),toSocket,ev_inv,new protocol::Payload(anOffer.getPayload()));
