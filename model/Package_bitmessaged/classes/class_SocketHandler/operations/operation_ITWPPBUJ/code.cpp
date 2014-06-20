//~~ void doSend(ACF_Message* event) [SocketHandler] ~~
if (myMessageQueue.empty())
    return;

int ret = myMessageQueue.front().writeTo(socketfd);

if (ret <= 0)
    myMessageQueue.pop_front();

if (!myMessageQueue.empty())
    triggerSend(event);

