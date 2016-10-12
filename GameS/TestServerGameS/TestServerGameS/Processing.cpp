#include "stdafx.h"
#include <string>

#include "Processing.h"
#include "Account.h"
#include "WorkMSQL.h"
#include "GameLogic.h"
#include "AccountHolder.h"
#include "Data.h"
using namespace std;

AccountHolder Processing::accountList;
GameLogic *Processing::game;

string Processing::Process(string &message, Account &curAccount){
	
	if (CorrectLine(message)){
		string temMess = GetData(message);
		Account copyAccount = curAccount.GetCopyAccount();
		if (copyAccount.GetInfo() == "NeedExit"){
			return "YouKick|";
		}		
		if (temMess == "ConnectUPD"){ return "ConnectUPD|"; }

		if (temMess == "Login"){
			if (copyAccount.GetInfo() == "None"){
				Rem(message);
				string login = GetDataRem(message), pass = GetDataRem(message);
				string retS = WorkMSQL::Login(login, pass);
				curAccount.SetInfo("Login");
				if (retS == "WrongLogin"){
					curAccount.SetLastAnswer("WrongLogin|");
					return "WrongLogin|";
				}
				if (retS == "WrongPass"){
					curAccount.SetLastAnswer("WrongPass|");
					return "WrongPass|";
				}
				if (GetDataRem(retS) == "OK"){

					accountList.AddAccount(curAccount, atoi(GetDataRem(retS).c_str()));
					curAccount.SetLastAnswer("LoginOK|");
					return "LoginOK|";
				}

				return "NULL";
			}
			if (copyAccount.GetInfo() == "Login"){
				return copyAccount.GetLastAnswer();
			}

		}

		if (temMess == "Registrate"){
			if (copyAccount.GetInfo() == "None"){
				Rem(message);
				string login = GetDataRem(message), pass = GetDataRem(message);
				string retS = WorkMSQL::Registrate(login, pass);
				curAccount.SetInfo("Registrate");
				if (retS == "LoginExist"){ curAccount.SetLastAnswer("LoginExist|"); return "LoginExist|"; }
				if (retS == "RegistrateOK"){ curAccount.SetLastAnswer("RegistrateOK|"); return "RegistrateOK|"; }

				return "NULL";
			}
			if (copyAccount.GetInfo() == "Registrate"){
				return copyAccount.GetLastAnswer();
			}
		}


		if (temMess == "NeedPers"){
			if (copyAccount.GetInfo() == "Login" || copyAccount.GetInfo() == "CreatePers" || copyAccount.GetInfo() == "NeedUPD"){
				curAccount.SetInfo("NeedPers");
				string qs = WorkMSQL::NeedPers(copyAccount.GetAccountId());
				curAccount.SetPersonIdList(ParseIntList(qs));
				curAccount.SetLastAnswer(qs);
				return qs;
			}
			if (copyAccount.GetInfo() == "NeedPers"){
				return copyAccount.GetLastAnswer();
			}
		}
		if (temMess == "CreatePers"){
			if (copyAccount.GetInfo() == "CreatePers" && copyAccount.GetLastRequest() == message){
				return copyAccount.GetLastAnswer();
			}
			if (copyAccount.GetInfo() == "NeedPers" || copyAccount.GetInfo() == "CreatePers"){
				curAccount.SetLastRequest(message);
				Rem(message);
				string name = GetDataRem(message);
				int race = atoi(GetDataRem(message).c_str());
				curAccount.SetInfo("CreatePers");
				string qs = WorkMSQL::CreatePers(copyAccount.GetAccountId(), name, game->GetBasePerson(race));
				curAccount.SetLastAnswer(qs);
				return qs;
			}

		}
		if (temMess == "GamePers"){

			if (copyAccount.GetInfo() == "GamePers" && copyAccount.GetLastRequest() == message){
				return copyAccount.GetLastAnswer();
			}
			if (copyAccount.GetInfo() == "NeedPers" || copyAccount.GetInfo() == "GamePers"){
				curAccount.SetLastRequest(message);
				Rem(message);
				int persId = atoi(GetDataRem(message).c_str());
				string sm = game->ResolutionGamePers(copyAccount.GetPersonIdList(), persId);
				if (sm == "PersPlays"){
					curAccount.SetInfo("GamePers");
					string qs = "PersPlays|";
					curAccount.SetLastAnswer(qs);
					return qs;
				}
				if (sm == "PersExist"){
					curAccount.SetPersonId(persId);
					curAccount.SetInfo("GamePers");
					string qs = "GamePersOK|";
					curAccount.SetLastAnswer(qs);
					return qs;
				}
				if (sm == "NewPers"){
					curAccount.SetPersonId(persId);
					curAccount.SetInfo("GamePers");
					game->AddPerson(WorkMSQL::GamePerson(persId));
					string qs = "GamePersOK|";
					curAccount.SetLastAnswer(qs);
					return qs;
				}
			}
		}
		if (temMess == "NeedFirstUPD"){
			if (copyAccount.GetInfo() == "NeedFirstUPD"){
				return copyAccount.GetLastAnswer();
			}
			if (copyAccount.GetInfo() == "GamePers"){
				string qs = game->NeedUpdate(copyAccount.GetPersonId());
				if (qs != "NULL"){
					curAccount.SetInfo("NeedFirstUPD");
					curAccount.SetLastAnswer(qs);
				}
				return qs;
			}
		}
		if (temMess == "NeedUPD"){
			if (copyAccount.GetInfo() == "NeedFirstUPD" || copyAccount.GetInfo() == "NeedUPD"){
				curAccount.SetInfo("NeedUPD");
				string qs = game->NeedUpdate(copyAccount.GetPersonId());
				return qs;
			}
		}
		if (temMess == "NeedUIUPD"){
			if (copyAccount.GetInfo() == "NeedUPD"){
				string qs = game->NeedUiUpdate(copyAccount.GetPersonId());
				return qs;
			}
		}
		if (temMess == "Move" && copyAccount.GetInfo() == "NeedUPD"){
			float x = 0, y = 0, z = 0;
			Rem(message);
			x = atof(GetDataRem(message).c_str());
			y = atof(GetDataRem(message).c_str());
			z = atof(GetDataRem(message).c_str());
			Data data = { x, y, z, 0, 0 };
			game->Command("Move", copyAccount.GetPersonId(), data);
		}
		if (temMess == "UseItem" && copyAccount.GetInfo() == "NeedUPD"){
			int slot;
			Rem(message);
			slot = atoi(GetDataRem(message).c_str());
			Data data = { slot, 0, 0, 0, 0 };
			game->Command("UseItem", copyAccount.GetPersonId(), data);
		}
		if (temMess == "Attack" && copyAccount.GetInfo() == "NeedUPD"){
			int id;
			Rem(message);
			id = atoi(GetDataRem(message).c_str());
			Data data = { id, 0, 0, 0, 0 };
			game->Command("Attack", copyAccount.GetPersonId(), data);
		}

		if (temMess == "StatsUP" && copyAccount.GetInfo() == "NeedUPD"){
			int str = 0, agi = 0, con = 0, intel = 0, wis = 0;
			Rem(message);
			str = atoi(GetDataRem(message).c_str());
			agi = atoi(GetDataRem(message).c_str());
			con = atoi(GetDataRem(message).c_str());
			intel = atoi(GetDataRem(message).c_str());
			wis = atoi(GetDataRem(message).c_str());
			Data data = { str, agi, con, intel, wis };
			game->Command("StatsUP", copyAccount.GetPersonId(), data);
			string qs = "StatsUPOK|";
			return qs;
		}

		if (temMess == "Resurrection" && copyAccount.GetInfo() == "NeedUPD"){
			Data data = { 0, 0, 0, 0, 0};
			game->Command("Resurrection", copyAccount.GetPersonId(), data);
		}

		if (temMess == "ResurrectionInPlace" && copyAccount.GetInfo() == "NeedUPD"){
			Data data = { 0, 0, 0, 0, 0 };
			game->Command("ResurrectionInPlace", copyAccount.GetPersonId(), data);
		}

		if (temMess == "Pickup" && copyAccount.GetInfo() == "NeedUPD"){
			Rem(message);
			int num = atoi(GetDataRem(message).c_str());
			Data data = { num, 0, 0, 0, 0 };
			game->Command("Pickup", copyAccount.GetPersonId(), data);
		}
				
		return "NULL";
	}
	else{
		return "NULL";
	}
	
	return "NULL";
}


string Processing::GetData(const string &message){
	return message.substr(0, message.find('|'));
}

void Processing::Rem(string &message){
	message = message.substr(message.find('|') + 1);
}

string Processing::GetDataRem(string &message){

	int g = message.find('|');
	string k = message.substr(0, g);
	message = message.substr(g + 1);
	return k;
}

bool Processing::CorrectLine(const string &message){
	int ko = 0;
	string copyMessage = message;
	while (!copyMessage.empty()){
		ko++;
		int g = copyMessage.find('|');
		if (g < 0 || ko >100){
			return false;
		}
		copyMessage = copyMessage.substr(g + 1);

	}
	return true;
}

void Processing::Init(GameLogic &game){
	Processing::game = &game;	
}

int Processing::GetClientCount(){
	return accountList.GetClientCount();
}

void Processing::Leave(const Account &account){
	
	game->Exit(account.GetPersonId());
	accountList.Leave(account);
}


vector<int> Processing::ParseIntList(const string &message){
	string copyMessage = message;
	Rem(copyMessage);
	int n = atoi(GetDataRem(copyMessage).c_str());
	vector<int> vec;
	for (int i = 0; i < n; i++){
		int nn = atoi(GetDataRem(copyMessage).c_str());
		vec.push_back(nn);
		Rem(copyMessage);
		Rem(copyMessage);
	}
	return vec;
}