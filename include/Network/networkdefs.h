#ifndef NETWORKDEFS_HH_
#define NETWORKDEFS_HH_

#include <memory>
#include <vector>
#include <deque>
#include <functional>

namespace stb {

#define DEFAULT_SERVER_SLOTS	2

	//Struct defining version
	struct VersionInfo {
		int major;
		int minor;
		int build;
		VersionInfo() {}
		VersionInfo(int ma, int mi, int b)
		{
			major = ma;
			minor = mi;
			build = b;
		}
	};

	//Enum defining client possible states
	enum ClientState {
		Disconnected,
		Connecting,
		Connected,
		Ready
	};

	//Struct containing client info
	struct ClientInfo {
		int8_t id;
		bool autoHandle;
		bool host;
		int32_t uid;
		ClientState state;
		ClientInfo(int aid)
		{
			id = aid;
			autoHandle = false;
			host = false;
			uid = -1;
			state = Disconnected;
		}
	};

	//Struct containing server info
	struct ServerInfo {
		std::string name;
		int8_t slots;
		ServerInfo(std::string n, int8_t s = DEFAULT_SERVER_SLOTS)
		{
			name = n;
			slots = s;
		}
	};

	class Packet; //Forward
	class ClientHandler;

	typedef std::pair<std::shared_ptr<sf::TcpSocket>, ClientInfo> clientNode;
	typedef std::vector<clientNode> clientArray;
	typedef std::deque<std::shared_ptr<Packet>> packetStack;

	typedef std::function<void(std::shared_ptr<Packet>)>  packetFunctor;
	typedef std::map<int16_t, packetFunctor> packetFunctorMap;
}

#endif /* !NETWORKDEFS_HH_ */