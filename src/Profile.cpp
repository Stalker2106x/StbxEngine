#include <JSON/json.hpp>
#include "Profile.hh"

using namespace stb;

using json = nlohmann::json;
sf::Http Profile::http;
std::map<std::string, std::string> Profile::config; //Public access instance user profile;

//Generic instance user
Profile::Profile(const std::string &login, const std::string &password)
{
	sf::Http::Request request;
	sf::Http::Response response;
	std::string pass_hash;

	picosha2::hash256_hex_string(password, pass_hash);
	http.setHost(API_PATH);
	request.setMethod(sf::Http::Request::Post);
	request.setField("Content-Type", "application/x-www-form-urlencoded");
	request.setUri(API_LOGIN_URI);
	request.setBody("USER_LOGIN="+login+"&USER_PASSWORD="+pass_hash);

	_uid = -1;
	response = http.sendRequest(request);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		json userData;

		try {
			userData = json::parse(response.getBody());
		} catch (...) {
			std::cerr << "JSON ERROR";
		}
		_uid = userData["USER_ID"].get<int32_t>();
		_username = userData["USER_DISPLAYNAME"].get<std::string>();
		_state = ClientState::Disconnected;
	}
	else
	{
		throw (std::exception("BAD_LOGIN"));
	}
}

//Retrieve remote user profile
Profile::Profile(const int8_t clientId, const int32_t uid, int8_t state)
{
	sf::Http::Request request;
	sf::Http::Response response;

	_clientId = clientId;
	_username = "{unknown}";
	http.setHost(API_PATH);
	request.setMethod(sf::Http::Request::Post);
	request.setField("Content-Type", "application/x-www-form-urlencoded");
	request.setUri(API_INFO_URI);
	request.setBody("USER_ID=" + std::to_string(uid));

	response = http.sendRequest(request);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		json userData;

		try {
			userData = json::parse(response.getBody());
		}
		catch (...) {
			std::cerr << "JSON ERROR";
		}
		_uid = uid;
		_username = userData["USER_DISPLAYNAME"].get<std::string>();
	}
	else
	{
		std::cerr << "UID:" << uid << " COULD NOT BE RETRIEVED";
	}
	_state = static_cast<ClientState>(state);
}

Profile::~Profile()
{

}

const std::string Profile::cypherProcess(const std::string &msg)
{
	char key = 'X';
	std::string output = msg;

	for (size_t i = 0; i < msg.size(); i++)
		output[i] = msg[i] ^ key;
	return (output);
}

bool Profile::create(const std::string &login, const std::string &email, const std::string &password)
{
	sf::Http::Request request;
	sf::Http::Response response;
	std::string pass_hash;

	picosha2::hash256_hex_string(password, pass_hash);
	http.setHost(API_PATH);
	request.setMethod(sf::Http::Request::Post);
	request.setField("Content-Type", "application/x-www-form-urlencoded");
	request.setUri(API_REGISTER_URI);
	request.setBody("USER_LOGIN=" + login + "&USER_EMAIL=" + email + "&USER_PASSWORD=" + pass_hash);

	response = http.sendRequest(request);
	if (response.getStatus() != sf::Http::Response::Ok)
	{
		throw (std::exception("Error"));
	}
	return (true);
}

std::pair<std::string, std::string> Profile::loadCredentials()
{
	std::ifstream file(CREDENTIALS_PATH, std::ifstream::in);
	std::pair<std::string, std::string> credentials;

	if (!file.good())
	{
		throw(std::exception("BAD FILE"));
	}
	std::getline(file, credentials.first);
	std::getline(file, credentials.second);
	file.close();
	credentials.second = cypherProcess(credentials.second);
	return (credentials);
}

void Profile::saveCredentials(const std::string &login, const std::string &password)
{
	std::ofstream file(CREDENTIALS_PATH, std::ofstream::out | std::ofstream::trunc);
	std::string passwordCypher = cypherProcess(password);

	if (!file.good())
	{
		throw(std::exception("BAD FILE"));
	}
	file << login << "\n" << passwordCypher;
	file.close();
}

void Profile::deleteCredentials()
{
	if (remove(CREDENTIALS_PATH))
	{
		throw(std::exception("FILE NOT DELETED"));
	}
}

void Profile::loadConfig()
{
	std::ifstream file(CONFIG_PATH, std::ifstream::in);
	std::string buffer;

	if (!file.good())
	{
		return; //No config
	}
	while (std::getline(file, buffer))
	{
		config.emplace(buffer.substr(0, buffer.find('=')), buffer.substr(buffer.find('=') + 1, buffer.size() - buffer.find('=')));
	}
	file.close();
}

void Profile::saveConfig()
{
	std::ofstream file(CONFIG_PATH, std::ofstream::out | std::ofstream::trunc);

	if (!file.good())
	{
		throw(std::exception("BAD FILE"));
	}
	for (std::map<std::string, std::string>::iterator it = config.begin(); it != config.end(); it++)
	{
		file << (it)->first + "=" + (it)->second << "\n";
	}
	file.close();
}

void Profile::setState(ClientState state)
{
	_state = state;
}

void Profile::setClientId(int8_t id)
{
	_clientId = id;
}

int8_t Profile::getClientId()
{
	return (_clientId);
}

ClientState Profile::getState()
{
	return (_state);
}
std::string &Profile::getUsername()
{
	return (_username);
}

int32_t Profile::getUid()
{
	return (_uid);
}