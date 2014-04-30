//~~ void sendConnected(ACF_Message* event) [OutSocketHandler] ~~
ACF_sendMessage(MessageReceiver(),toConnectionHandler,ev_connected,0);
ACF_sendMessage(MessageReceiver(),toLogic,ev_connected,0);