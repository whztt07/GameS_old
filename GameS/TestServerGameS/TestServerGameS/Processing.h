
#include <vector>
#include <string>

#include <windows.h>

#include "AccountHolder.h"

class GameLogic;

using namespace std;



class Processing {
	
	static AccountHolder	accountList;	
	static GameLogic		*game;

	static string		GetData(const string &message);
	static void			Rem(string &message);
	static string		GetDataRem(string &message);
	static bool			CorrectLine(const string &message);
	static vector<int>	ParseIntList(const string &message);
public:
	static void			Init(GameLogic &game);
	static string		Process(string &message, Account &curAccount);
	static void			Leave(const Account &account);
	static int			GetClientCount();
};