//~~ void notifyConnections(ACF_Message* event) [InConnectionHandler] ~~
protocol::inventory_vector* aVector = (protocol::inventory_vector*)event->Data;
for (std::map<ACF_MessageReceiver*, uint64_t>::iterator it = myInSocketHandler.begin(); it != myInSocketHandler.end(); it++)
{
    ACF_sendMessage(MessageReceiver(),(*it).first,ev_newObject,new protocol::inventory_vector(*aVector));
}