
#include <vector>
#include <string>

#include <windows.h>

#include "AccountHolder.h"

class GameLogic;

using namespace std;



class Processing {
	
	static AccountHolder accountList;
	
	static GameLogic *game;
	static string GetData(string);
	static void Rem(string&);
	static string GetDataRem(string&);
	static bool CorrectLine(string);
	static vector<int> ParseIntList(string);
public:
	static void Init(GameLogic *_game);
	static string Process(string, Account&);
	static void Leave(const Account&);
	static const int GetClientCount();
};