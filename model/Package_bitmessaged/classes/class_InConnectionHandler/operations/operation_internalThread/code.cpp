//~~ void internalThread() [InConnectionHandler] ~~
int one = 1, client_fd;
struct sockaddr_in svr_addr, cli_addr;
socklen_t sin_len = sizeof(cli_addr);

int sock = socket(AF_INET, SOCK_STREAM, 0);
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

svr_addr.sin_family = AF_INET;
svr_addr.sin_addr.s_addr = INADDR_ANY;
svr_addr.sin_port = htons(m_port);

bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr));
listen(sock, 5);

for (;;)
{
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    if (InSocketLimit > theKnowledge.getIncommingCount())
    {
        InSocketHandler* aHandler = new InSocketHandler(m_SocketContext, cli_addr, 
                        theKnowledge, MessageReceiver(), client_fd);
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_register,aHandler->MessageReceiver());
        aHandler->Initialize(0);
    }
    else
        close(client_fd);
}