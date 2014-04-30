//~~ void initialConnections(ACF_Message* event) [OutConnectionHandler] ~~
for (unsigned int i = 0; i < OutSocketLimit; i++)
{
    data::node_info node;
    if (theKnowledge.getNode(node))
    {
        OutSocketHandler* aHandler = 
            new OutSocketHandler(MessageReceiver_base.myACF, node.getAddr(), theKnowledge);
        aHandler->Initialize(0);
    }
    else
        break;
}