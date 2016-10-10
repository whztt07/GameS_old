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
	connection = mysql_real_connect(&mysql, init_data.address.c_str(), init_data.login.c_str(), init_data.password.c_str(), init_data.dataBase.c_str(), 0, 0, 0);
		
}


MSQLConnect::~MSQLConnect(){
		
	mysql_close(connection);
}

MYSQL_RES* MSQLConnect::Query(const string &query){

	
	if (mysql_query(connection, query.c_str())) {
		printf("| %s |", mysql_error(connection));
	}
	return mysql_store_result(connection);	
}

