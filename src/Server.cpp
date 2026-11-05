#include <Server.h>
#include <iostream>

void Server::init()
{
	if (listener == nullprt)
	{
		listener = std::make_unique<sf::Tcplistener>();
	}
	if (listener->listen(53000) != sf::Socket::Status::Done)
	{
		std::cout << "Couldn't bind listener to port 53000."
			<< std::endl;
	}
}

void Server::run()
{
	while (running)
	{
		sf::TcpSocket& c_sock = *connections.emplace_back(std::make_unique<sf::TcpSocket>())
			if (listener->accept(c_sock) != sf::Socket::Status::Done)
			{
				connections.pop_back();
				std::cout << "Connection failed on server side" << std::endl;
				continue;
			}
		std::cout << "Client connected @ " << c_sock.getRemotePort() << std::endl;
	}
}