#include "Database.hh"

Database::Database()
{
}

Database::~Database()
{

}

bool Database::connect(std::string ip, const std::string &database, const std::string &user, const std::string &password)
{
	std::string port = "3306";
	if (ip.find(":") != std::string::npos)
	{
		port = ip.substr(ip.find(":") + 1, ip.length() - ip.find(":"));
		ip = ip.substr(0, ip.find(":"));
	}
	/*std::string connectStr = "DRIVER={MySQL ODBC 5.2 ANSI Driver};SERVER=" + ip + "; PORT=" + port +"; DATABASE=" + database + "; USER = " + user + "; PASSWORD = " + password + ";";
	try {
		connection.rlogon(connectStr.c_str());
	} catch (otl_exception& e) {
		return (false);
	}*/
	return (true);
}

void Database::disconnect()
{
	//connection.logoff();
}