//~~ void sendDestroyed(ACF_Message* event) [OutBitmessageLogic] ~~
ACF_sendMessage(MessageReceiver(),toSocket,ev_destroyed,0);
