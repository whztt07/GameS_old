#include <string>

using namespace std;

struct MSQL_init_data{
	MSQL_init_data(string _adrres, string _login, string _pass, string _dbase) : adrres(_adrres), login(_login), pass(_pass), dbase(_dbase){}
	string adrres, login, pass, dbase;
};