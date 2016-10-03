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

string Processing::Process(string mess, Account &account){
	
	if (CorrectLine(mess)){
		string temMess = GetData(mess);
		Account *acc = account.GetCopy();
		if (acc->GetDopInfo() == "NeedExit"){
			return "YouKick|";
		}		
		if (temMess == "ConnectUPD"){ return "ConnectUPD|"; }

		if (temMess == "Login"){
			if (acc->GetDopInfo() == "None"){
				Rem(mess);
				string login = GetDataRem(mess), pass = GetDataRem(mess);
				string retS = WorkMSQL::Login(login, pass);
				account.SetDopInfo("Login");
				if (retS == "WrongLogin"){
					account.SetLastAnswer("WrongLogin|");
					return "WrongLogin|";
				}
				if (retS == "WrongPass"){
					account.SetLastAnswer("WrongPass|");
					return "WrongPass|";
				}
				if (GetDataRem(retS) == "OK"){

					accountList.AddAccount(account, atoi(GetDataRem(retS).c_str()));
					account.SetLastAnswer("LoginOK|");
					return "LoginOK|";
				}

				return "NULL";
			}
			if (acc->GetDopInfo() == "Login"){
				return acc->GetLastAnswer();
			}

		}

		if (temMess == "Registrate"){
			if (acc->GetDopInfo() == "None"){
				Rem(mess);
				string login = GetDataRem(mess), pass = GetDataRem(mess);
				string retS = WorkMSQL::Registrate(login, pass);
				account.SetDopInfo("Registrate");
				if (retS == "LoginExist"){ account.SetLastAnswer("LoginExist|"); return "LoginExist|"; }
				if (retS == "RegistrateOK"){ account.SetLastAnswer("RegistrateOK|"); return "RegistrateOK|"; }

				return "NULL";
			}
			if (acc->GetDopInfo() == "Registrate"){
				return acc->GetLastAnswer();
			}
		}


		if (temMess == "NeedPers"){
			if (acc->GetDopInfo() == "Login" || acc->GetDopInfo() == "CreatePers" || acc->GetDopInfo() == "NeedUPD"){
				account.SetDopInfo("NeedPers");
				string qs = WorkMSQL::NeedPers(acc->GetAccNum());
				account.SetPersIdList(ParseIntList(qs));
				account.SetLastAnswer(qs);
				return qs;
			}
			if (acc->GetDopInfo() == "NeedPers"){
				return acc->GetLastAnswer();
			}
		}
		if (temMess == "CreatePers"){
			if (acc->GetDopInfo() == "CreatePers" && acc->GetLastRequest() == mess){
				return acc->GetLastAnswer();
			}
			if (acc->GetDopInfo() == "NeedPers" || acc->GetDopInfo() == "CreatePers"){
				account.SetLastRequest(mess);
				Rem(mess);
				string name = GetDataRem(mess);
				int race = atoi(GetDataRem(mess).c_str());
				account.SetDopInfo("CreatePers");
				string qs = WorkMSQL::CreatePers(acc->GetAccNum(), name, game->GetBasePerson(race));
				account.SetLastAnswer(qs);
				return qs;
			}

		}
		if (temMess == "GamePers"){

			if (acc->GetDopInfo() == "GamePers" && acc->GetLastRequest() == mess){
				return acc->GetLastAnswer();
			}
			if (acc->GetDopInfo() == "NeedPers" || acc->GetDopInfo() == "GamePers"){
				account.SetLastRequest(mess);
				Rem(mess);
				int persId = atoi(GetDataRem(mess).c_str());
				string sm = game->ResolutionGamePers(acc->GetPersIdList(), persId);
				if (sm == "PersPlays"){
					account.SetDopInfo("GamePers");
					string qs = "PersPlays|";
					account.SetLastAnswer(qs);
					return qs;
				}
				if (sm == "PersExist"){
					account.SetPersNum(persId);
					account.SetDopInfo("GamePers");
					string qs = "GamePersOK|";
					account.SetLastAnswer(qs);
					return qs;
				}
				if (sm == "NewPers"){
					account.SetPersNum(persId);
					account.SetDopInfo("GamePers");
					game->AddPerson(WorkMSQL::GamePerson(persId));
					string qs = "GamePersOK|";
					account.SetLastAnswer(qs);
					return qs;
				}
			}
		}
		if (temMess == "NeedFirstUPD"){
			if (acc->GetDopInfo() == "NeedFirstUPD"){
				return acc->GetLastAnswer();
			}
			if (acc->GetDopInfo() == "GamePers"){
				string qs = game->NeedUPD(acc->GetPersNum());
				if (qs != "NULL"){
					account.SetDopInfo("NeedFirstUPD");
					account.SetLastAnswer(qs);
				}
				return qs;
			}
		}
		if (temMess == "NeedUPD"){
			if (acc->GetDopInfo() == "NeedFirstUPD" || acc->GetDopInfo() == "NeedUPD"){
				account.SetDopInfo("NeedUPD");
				string qs = game->NeedUPD(acc->GetPersNum());
				return qs;
			}
		}
		if (temMess == "NeedUIUPD"){
			if (acc->GetDopInfo() == "NeedUPD"){
				string qs = game->NeedUI_UPD(acc->GetPersNum());
				return qs;
			}
		}
		if (temMess == "Move" && acc->GetDopInfo() == "NeedUPD"){
			float x = 0, y = 0, z = 0;
			Rem(mess);
			x = atof(GetDataRem(mess).c_str());
			y = atof(GetDataRem(mess).c_str());
			z = atof(GetDataRem(mess).c_str());
			Data data = { x, y, z, 0, 0 };
			game->Command("Move", acc->GetPersNum(), data);
		}
		if (temMess == "UseItem" && acc->GetDopInfo() == "NeedUPD"){
			int slot;
			Rem(mess);
			slot = atoi(GetDataRem(mess).c_str());
			Data data = { slot, 0, 0, 0, 0 };
			game->Command("UseItem", acc->GetPersNum(), data);
		}
		if (temMess == "Attack" && acc->GetDopInfo() == "NeedUPD"){
			int id;
			Rem(mess);
			id = atoi(GetDataRem(mess).c_str());
			Data data = { id, 0, 0, 0, 0 };
			game->Command("Attack", acc->GetPersNum(), data);
		}

		if (temMess == "StatsUP" && acc->GetDopInfo() == "NeedUPD"){
			int str = 0, agi = 0, con = 0, intel = 0, wis = 0;
			Rem(mess);
			str = atoi(GetDataRem(mess).c_str());
			agi = atoi(GetDataRem(mess).c_str());
			con = atoi(GetDataRem(mess).c_str());
			intel = atoi(GetDataRem(mess).c_str());
			wis = atoi(GetDataRem(mess).c_str());
			Data data = { str, agi, con, intel, wis };
			game->Command("StatsUP", acc->GetPersNum(), data);
			string qs = "StatsUPOK|";
			return qs;
		}

		if (temMess == "Resurrection" && acc->GetDopInfo() == "NeedUPD"){
			Data data = { 0, 0, 0, 0, 0};
			game->Command("Resurrection", acc->GetPersNum(), data);
		}

		if (temMess == "ResurrectionInPlace" && acc->GetDopInfo() == "NeedUPD"){
			Data data = { 0, 0, 0, 0, 0 };
			game->Command("ResurrectionInPlace", acc->GetPersNum(), data);
		}

		if (temMess == "Pickup" && acc->GetDopInfo() == "NeedUPD"){
			Rem(mess);
			int num = atoi(GetDataRem(mess).c_str());
			Data data = { num, 0, 0, 0, 0 };
			game->Command("Pickup", acc->GetPersNum(), data);
		}
				
		return "NULL";
	}
	else{
		return "NULL";
	}
	
	return "NULL";
}


string Processing::GetData(string dat){

	int g = dat.find('|');
	return dat.substr(0, g);
}

void Processing::Rem(string &s){

	int g = s.find('|');
	s = s.substr(g + 1);
}

string Processing::GetDataRem(string &s){

	int g = s.find('|');
	string k = s.substr(0, g);
	s = s.substr(g + 1);
	return k;
}

bool Processing::CorrectLine(string s){
	int ko = 0;
	while (!s.empty()){
		ko++;
		int g = s.find('|');
		if (g < 0 || ko >100){
			return false;
		}

		s = s.substr(g + 1);

	}
	return true;
}

void Processing::Init(GameLogic *_game){
	game = _game;	
}

const int Processing::GetClientCount(){
	return accountList.GetClientCount();
}

void Processing::Leave(const Account &acc){
	
	game->Exit(acc.GetPersNum());
	accountList.Leave(acc);
}


vector<int> Processing::ParseIntList(string s){
	Rem(s);
	int n = atoi(GetDataRem(s).c_str());
	vector<int> vec;
	for (int i = 0; i < n; i++){
		int nn = atoi(GetDataRem(s).c_str());
		vec.push_back(nn);
		Rem(s);
		Rem(s);
	}
	return vec;
}