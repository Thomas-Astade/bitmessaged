//~~ void sendOffer(ACF_Message* event) [BitmessageLogic] ~~
protocol::inv anOffer;

while ((anOffer.size() < 50) && (!VectorsWeCouldOffer.empty()))
{
    if (VectorsWeHaveOffered.find(*VectorsWeCouldOffer.begin()) == VectorsWeHaveOffered.end())
    {
        VectorsWeHaveOffered.insert(*VectorsWeCouldOffer.begin());
        anOffer.insert(*VectorsWeCouldOffer.begin());
    }
    VectorsWeCouldOffer.erase(VectorsWeCouldOffer.begin());
}

if (!anOffer.empty())
{
    ACF_sendMessage(MessageReceiver(),toSocket,ev_inv,new protocol::Payload(anOffer.getPayload()));
    if (m_Protocol_Version == 3)
        printf("Offer some objects\n");
}
