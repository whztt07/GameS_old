#include "stdafx.h"

#include <my_global.h>
#include <mysql.h>
#include <stdarg.h>
#include <string>

#include "MSQLConnect.h"
#include "MSQL_init_data.h"

using namespace std;
#pragma comment(lib, "libmysql.lib")



void MSQLConnect::Init(const MSQL_init_data &init_data) {
	
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, init_data.adrres.c_str(), init_data.login.c_str(), init_data.pass.c_str(), init_data.dbase.c_str(), 0, 0, 0);
		
}

//Закрытие соединения и окончание сеанса связи
MSQLConnect::~MSQLConnect(){
		
	mysql_close(connection);
}

//Отправляет запрос и возвращает результат
MYSQL_RES* MSQLConnect::Query(string quer){

	
	if (mysql_query(connection, quer.c_str())) {
		printf("| %s |", mysql_error(connection));
	}
	return mysql_store_result(connection);	
}

