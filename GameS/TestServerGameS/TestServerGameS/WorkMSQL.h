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
	static void Init(const MSQL_init_data &msql_init_data);
	static string Login(string, string);
	static string Registrate(string, string);
	static string NeedPers(int);
	static string CreatePers(const int&, const string&, const Person&);
	static Person GamePerson(int);
	static vector<Item> GetBaseItem();
	static vector<SpellInfo> GetBaseSpell();
	static vector<Person> GetBasePerson();
};