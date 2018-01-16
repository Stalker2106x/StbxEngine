#ifndef PACKET_HH_
#define PACKET_HH_

#include <vector>
#include <memory>
#include <SFML/Network.hpp>
#include "networkdefs.h"

namespace stb {

	class Packet
	{
	public:

		struct Code {
			enum Client {		//Client packet for disconnect/errors
				COk = 101,		//Generic aknowledge response
				CInfo,
				Ready,
				Message,
				Drop
			};
			enum Describe {		//Describe an object
				Client = 201,	//Describe client (version, ...)
				Player,			//Describe player (server id, stabax login...)
				Server			//Describe server (version, name, slots...)
			};
			enum Event {		//Event packet for board events
				Trigger = 301,  //Trigger an event for current player of turn
			};
			enum Handshake {	//Exchange connection data
				Welcome = 401,	//Contains connected ID
				Accept,			//Accept connection
				Query			//Query command on client app
			};
			enum Player {		//Player packet to operate on players
				Alter = 501,	//Alter player stats
				Move,			//Move following orientation
				RTD,			//Roll the dice result
				Use				//Use item
			};
			enum Server {		//Server packet for close/errors
				SOk = 601,		//Generic aknowledge response
				SInfo,
				Start,
				Mismatch,		//Mismatch between client and server versions
				Full			//Server full error
			};
		};

		Packet(int16_t packetCode, int8_t senderId, bool serverSide);
		Packet(std::shared_ptr<sf::Packet> packet, bool serverSide);
		~Packet();

		template<typename T>
		T getData()
		{
			T var;

			(*_data) >> var;
			return (var);
		}

		//Send already packed packet
		static sf::Socket::Status send(sf::TcpSocket &sender, const Packet &packet)
		{
			return (sender.send(*packet._data));
		}

		//Basic packet
		static sf::Socket::Status send(sf::TcpSocket &sender, int16_t packetCode)
		{
			sf::Packet packet;

			packet << packetCode;
			return (sender.send(packet));
		}

		//Sending aggregate
		template<typename T>
		static void aggregate(sf::Packet &packet, T arg)
		{
			packet << arg;
		}
		template<typename T, typename ... Args>
		static void aggregate(sf::Packet &packet, T arg, Args ... args)
		{
			packet << arg;
			aggregate(packet, args...);
		}
		template<typename T, typename ... Args>
		static sf::Socket::Status send(sf::TcpSocket &sender, int16_t packetCode, T arg, Args ... args)
		{
			sf::Packet packet;

			packet << packetCode;
			aggregate(packet, arg, args...);
			return (sender.send(packet));
		}
		//Basic broadcast to multiple clients
		static void broadcast(clientArray &clients, int16_t packetCode, int8_t emitter)
		{
			for (uint8_t i = 0; i < clients.size(); i++)
			{
				if (clients[i].first == nullptr || clients[i].second.id == emitter)
					continue;
				sf::Packet packet;

				packet << packetCode;
				clients[i].first->send(packet);
			}
		}
		//Broadcast to multiple clients
		template<typename T, typename ... Args>
		static void broadcast(clientArray &clients, int16_t packetCode, int8_t emitter, T arg, Args ... args)
		{
			for (uint8_t i = 0; i < clients.size(); i++)
			{
				if (clients[i].first == nullptr || clients[i].second.id == emitter)
					continue;
				sf::Packet packet;

				packet << packetCode;
				aggregate(packet, arg, args...);
				clients[i].first->send(packet);
			}
		}

		//insert in packet
		template <typename T>
		Packet &operator<<(T data)
		{
			(*_data) << data;
			return (*this);
		}

		//extract from packet
		template <typename T>
		Packet &operator>>(T data)
		{
			(*_data) >> data;
			return (*this);
		}

		int16_t code;
		int8_t clientId;
	protected:
		std::shared_ptr<sf::Packet> _data;
	};

}

#endif /* !PACKET_HH_ */