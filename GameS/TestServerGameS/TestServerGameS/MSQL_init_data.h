#include <string>

using namespace std;

struct MSQL_init_data{
	string address;
	string login; 
	string password; 
	string dataBase;

	MSQL_init_data(string address, string login, string password, string dataBase) : address(address), login(login), password(password), 
		dataBase(dataBase){}
};