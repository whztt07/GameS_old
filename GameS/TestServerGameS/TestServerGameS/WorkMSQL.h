#include <string>
#include <vector>
class Person;
class MSQL_init_data;
class MSQLConnect;
class Item;
class SpellInfo;
class Person;
class Player;
using namespace std;
class WorkMSQL{
		
	static MSQLConnect msql_connect;
public:
	static void					Init(const MSQL_init_data &msql_init_data);
	static string				Login(const string &login, const string &password);
	static string				Registrate(const string &login, const string &pasword);
	static string				NeedPers(int accountId);
	static string				CreatePers(int accountId, const string &name, const Person &basePerson);
	static Person				GamePerson(int personId);
	static vector<Item>			GetBaseItem();
	static vector<SpellInfo>	GetBaseSpell();
	static vector<Person>		GetBasePerson();
};