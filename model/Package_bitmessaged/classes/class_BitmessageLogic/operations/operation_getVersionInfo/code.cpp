//~~ void getVersionInfo(ACF_Message* event) [BitmessageLogic] ~~
protocol::version aVersion(*((protocol::Payload*)event->Data),0);
if (nodeID)
{
    theKnowledge.setNodeAgent(nodeID,aVersion.getUserAgent());
    theKnowledge.setNodeServices(nodeID,aVersion.getServices());
}
