//~~ void destroy(ACF_Message* event) [InConnectionHandler] ~~
ACF_sendMessage(MessageReceiver(),event->Source,ev_destroy,0);
myInSocketHandler.erase(event->Source);