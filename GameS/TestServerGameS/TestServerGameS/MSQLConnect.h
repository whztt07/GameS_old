#include <my_global.h>
#include <mysql.h>
#include <string>

using namespace std;

struct MSQL_init_data;

class MSQLConnect{

	MYSQL *connection;	//Соединение по которому происходит общение	
	MYSQL mysql;		//Переменная нужная для соединения.
public:
	~MSQLConnect();										//Закрытие соединения и окончание сеанса связи
	void		Init(const MSQL_init_data &init_data);	//Создает соединение с базой данных
	MYSQL_RES*	Query(const string &query);				//Отправляет запрос и возвращает результат
};