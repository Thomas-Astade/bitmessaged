//~~ void destroy(ACF_Message* event) [OutConnectionHandler] ~~
ACF_sendMessage(MessageReceiver(),event->Source,ev_destroy,0);
theKnowledge.freeNode(myInSocketHandler[event->Source]);
myInSocketHandler.erase(event->Source);