//~~ void destroy(ACF_Message* event) [OutConnectionHandler] ~~
ACF_sendMessage(MessageReceiver(),event->Source,ev_destroy,0);
