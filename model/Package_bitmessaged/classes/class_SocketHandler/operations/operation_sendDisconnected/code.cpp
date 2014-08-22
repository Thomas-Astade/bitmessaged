//~~ void sendDisconnected(ACF_Message* event) [SocketHandler] ~~
ACF_sendMessage(MessageReceiver(),toConnectionHandler,ev_disconnected,0);
ACF_sendMessage(MessageReceiver(),toLogic,ev_disconnected,0);
