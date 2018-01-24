#ifndef NETWORKMANAGER_HH_
#define NETWORKMANAGER_HH_

namespace stb {

	template <typename TServer, typename TClient>
	struct NetworkManager
	{
		//
		// Client
		//
		void startClient()
		{

		}

		void stopClient()
		{

		}


		//
		// Server
		//
		void startServer()
		{

		}

		void stopServer()
		{

		}

		TServer server;
		TClient client;
	};

}

#endif /* !NETWORKMANAGER_HH_ */