//~~ void getVersionInfo(ACF_Message* event) [BitmessageLogic] ~~
try{
    protocol::version aVersion(*((protocol::Payload*)event->Data),0);
    if (nodeID)
    {
        theKnowledge.setNodeAgent(nodeID,aVersion.getUserAgent());
        theKnowledge.setNodeServices(nodeID,aVersion.getServices());
        m_Protocol_Version = aVersion.getVersion();
        theKnowledge.setNodeVersion(nodeID,m_Protocol_Version);
        
        printf("We connected to a node Version %d (node id %lld)\n",m_Protocol_Version,nodeID);
    }
}
catch (...) //we received a malformated message
{
    disconnect(event);
}