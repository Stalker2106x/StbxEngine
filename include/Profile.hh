#ifndef PROFILE_HH_
#define PROFILE_HH_

#include <map>
#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>
#include <SHA/picosha2.h>
#include "Network/networkdefs.h"

namespace stb {

	//API Defines
#define API_PATH ("http://api.stabax.org/")
#define API_LOGIN_URI ("accounts/?method=login")
#define API_INFO_URI ("accounts/?method=info")
#define API_REGISTER_URI ("accounts/?method=register")

//File Defines
#define CREDENTIALS_PATH ("./credentials.lock")
#define CONFIG_PATH ("./config.cfg")

	class Profile
	{
	public:
		Profile::Profile(const int8_t serverId, const int32_t uid, int8_t state); //Distant profile
		Profile(const std::string &login, const std::string &password); //Client profile
		~Profile();

		static const std::string Profile::cypherProcess(const std::string &msg);

		static bool create(const std::string &login, const std::string &email, const std::string &password);

		static std::pair<std::string, std::string> loadCredentials();
		static void saveCredentials(const std::string &login, const std::string &password);
		static void deleteCredentials();
		static void loadConfig();
		static void saveConfig();

		void setState(ClientState state);
		void setClientId(int8_t id);
		ClientState getState();
		int8_t getClientId();
		std::string &getUsername();
		int32_t getUid();

		static sf::Http http;
		static std::map<std::string, std::string> config;
	private:
		ClientState _state;
		std::string _username;
		int8_t _clientId;
		int32_t _uid;
	};

}

#endif /* PROFILE_HH_ */