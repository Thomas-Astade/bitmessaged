//~~ void initConnections(ACF_Message* event) [OutConnectionHandler] ~~
for (unsigned int i = 0; i < OutSocketLimit; i++)
{
    if (theKnowledge.getOutgoingCount() >= OutSocketLimit)
        break;
    data::node_info node;
    if (theKnowledge.getNode(node))
    {
        OutSocketHandler* aHandler = 
            new OutSocketHandler(MessageReceiver_base.myACF, node.getAddr(),
            theKnowledge, MessageReceiver());
        myOutSocketHandler[aHandler] = node.getID();
        aHandler->Initialize(0);
    }
    else
        break;
}