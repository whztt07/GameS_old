#include <my_global.h>
#include <mysql.h>
#include <string>

using namespace std;

struct MSQL_init_data;

class MSQLConnect{
	//Соединение по которому происходит общение
	MYSQL *connection;
	//Переменная нужная для соединения.
	MYSQL mysql;
public:
	void Init(const MSQL_init_data&);
	~MSQLConnect();
	MYSQL_RES* Query(string quer);
};