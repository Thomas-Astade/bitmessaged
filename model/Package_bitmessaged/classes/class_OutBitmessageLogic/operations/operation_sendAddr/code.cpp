//~~ void sendAddr(ACF_Message* event) [OutBitmessageLogic] ~~
std::vector<data::node_info> nodes = theKnowledge.getNodesToProvideToOthers();
protocol::addr aAddr(nodes);
ACF_sendMessage(MessageReceiver(),toSocket,ev_addr,new protocol::Payload(aAddr.getPayload()));