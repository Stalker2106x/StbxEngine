#ifndef DATABASE_HH_
#define DATABASE_HH_

#include <string>
#include <memory>

/*OTL Library load
#define OTL_ODBC
#include "SQL/otlv4.h"*/

class Database
{
public:
	Database();
	~Database();

	bool connect(std::string ip, const std::string &database, const std::string &user, const std::string &password = "");
	void disconnect();

	//otl_connect connection;
};

#endif /* !DATABASE_HH_ */