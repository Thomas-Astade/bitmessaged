//~~ void sendOffer(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::inventory_vector* aVector = (protocol::inventory_vector*)event->Data;
if (VectorsWeGotOffered.find(*aVector) != VectorsWeGotOffered.end())
{
    if (VectorsWeHaveOffered.find(*aVector) == VectorsWeHaveOffered.end())
    {
        VectorsWeHaveOffered.insert(*aVector);
        protocol::inv anOffer;
        anOffer.insert(*VectorsToRequest.begin());
        ACF_sendMessage(MessageReceiver(),toSocket,ev_inv,new protocol::Payload(anOffer.getPayload()));
    }
}