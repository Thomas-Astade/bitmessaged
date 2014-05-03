//~~ void getVersionInfo(ACF_Message* event) [OutBitmessageLogic] ~~
protocol::version aVersion(*((protocol::Payload*)event->Data),0);
theKnowledge.setAgent(nodeID,aVersion.getUserAgent());