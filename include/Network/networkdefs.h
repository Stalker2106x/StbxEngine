#ifndef NETWORKDEFS_HH_
#define NETWORKDEFS_HH_

#include <memory>
#include <vector>
#include <deque>

#define DEFAULT_SERVER_SLOTS	2

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

class Packet; //Forward

typedef std::pair<std::shared_ptr<sf::TcpSocket>, ClientInfo> clientNode;
typedef std::vector<clientNode> clientArray;
typedef std::deque<std::shared_ptr<Packet>> packetStack;

#endif /* !NETWORKDEFS_HH_ */