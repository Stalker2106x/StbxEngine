#ifndef NETWORKMANAGER_HH_
#define NETWORKMANAGER_HH_

namespace stb {

	template <typename TServer, typename TClient>
	struct NetworkManager
	{
		//
		// Client
		//
		void connect(const std::string &ip)
		{
			if (client != nullptr)
			{
				client->disconnect();
				client = nullptr;
			}
			//client = std::make_shared<Client>(self); // INSTANCIATE NEW CLIENT TEMPLATED
			if (client->connectServer(ip) == false) //if it fails, destroy client and redirect
			{
				client = nullptr;
				//Connection failed!!!
			}
		}

		void disconnect()
		{
			if (client != nullptr) //Client already connected
			{
				client->disconnect();
				client = nullptr;
			}
		}


		//
		// Server
		//
		void startServer()
		{
			//server = std::make_shared<Server>(name, atoi(port.c_str()), slots); //INSTANCIATE TEMPLATED SERVER
			if (server == nullptr)
			{
				//Server failed to start!!!
			}
		}

		void stopServer()
		{
			if (server != nullptr) //Server is started
			{
				server->shutdown();
				server = nullptr;
			}
		}

		TServer server;
		TClient client;
	};

}

#endif /* !NETWORKMANAGER_HH_ */