//~~ void sendDisconnected(ACF_Message* event) [OutSocketHandler] ~~
ACF_sendMessage(MessageReceiver(),toConnectionHandler,ev_disconnected,0);
