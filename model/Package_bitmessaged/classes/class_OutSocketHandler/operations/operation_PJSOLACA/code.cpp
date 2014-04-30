//~~ void sendConnected(ACF_Message* event) [OutSocketHandler] ~~
ACF_sendMessage(MessageReceiver(),toConnectionHandler,ev_connected,0);
