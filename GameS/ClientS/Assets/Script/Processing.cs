using UnityEngine;
using System.Collections;

public class Processing {
	


	static public void Init(MainLogin sc, MyCamera mc){
		Variables.mainLoginScript = sc;
		Variables.myCameraScript = mc;

		UI.Init ();
		Variables.Init ();
		Connection.Init (sc);
		Reset ();

	}

	static public void ProcessButton(string s){
		
		if(s == "AbilityPress"){
			UI.HideMasteryPanel ();
			UI.HideSpellPanel ();
			UI.ShowAbilityPanel ();
		}

		if(s == "AddressPress"){
			UI.HideSettingButtonPanel ();
			UI.ShowSettingWindowPanel ();
		}

		if (s == "AgilityPlusStatsUPPress") {
			int mod = (Variables.base_agility + Variables.statsUPAgility - 10) / 2;
			if (mod < 1)
				mod = 1;
			if (Variables.statsUPFreeCharacteristics >= mod) {
				Variables.statsUPFreeCharacteristics -= mod;
				Variables.statsUPAgility++;
				UI.StatsUPPanelUPD ();
			}
		}
		if (s == "AgilityMinusStatsUPPress") {
			if (Variables.statsUPAgility > 0) {
				int mod = (Variables.base_agility + Variables.statsUPAgility - 11) / 2;
				if (mod < 1)
					mod = 1;
				Variables.statsUPFreeCharacteristics += mod;
				Variables.statsUPAgility--;
				UI.StatsUPPanelUPD ();
			}
		}


		if( s == "CloseSettingPress"){
			UI.HideSettingWindowPanel ();
		}

		if (s == "ConstitutionPlusStatsUPPress") {
			int mod = (Variables.base_constitution + Variables.statsUPConstitution - 10) / 2;
			if (mod < 1)
				mod = 1;
			if (Variables.statsUPFreeCharacteristics >= mod) {
				Variables.statsUPFreeCharacteristics -= mod;
				Variables.statsUPConstitution++;
				UI.StatsUPPanelUPD ();
			}
		}
		if (s == "ConstitutionMinusStatsUPPress") {
			if (Variables.statsUPConstitution > 0) {
				int mod = (Variables.base_constitution + Variables.statsUPConstitution - 11) / 2;
				if (mod < 1)
					mod = 1;
				Variables.statsUPFreeCharacteristics += mod;
				Variables.statsUPConstitution--;
				UI.StatsUPPanelUPD ();
			}
		}


		if (s == "DopStatusPress") {
			UI.PressDopStatusButton ();
		}


		if (s == "ExitConfirmationCancelPress") {
			UI.HideExitConfirmationPanel ();
		}

		if (s == "ExitConfirmationOKPress") {
			UI.HideExitConfirmationPanel ();
			if(!Variables.personList[0].battle){
				if (Variables.gameExitSting == "Exit") {
					Application.Quit ();
				}
				if (Variables.gameExitSting == "Reset") {
					UI.HideGameGUI ();
					UI.ShowPersChoiceGUI ();
					Initializate.Reset ();
					ClearPersChoice ();
					Connection.Send ("NeedPers|");
					Variables.status = "NeedPers";
					Variables.waitAnswerText = "NeedPers|";
				}}
			else{
				UI.WriteGameSystemText ("Вы не можете выйти во время боя!");
			}
		}

		if (s == "ExitLoginPress") {
			Reset ();
			UI.HidePersChoiceGUI ();
			UI.ShowLoginGUI ();
			UI.ClearStatusText ();
		}

		if (s == "ExitPress") {
			Application.Quit ();
		}


		if (s == "GameExitPress") {
			UI.HideGameSystemListButton ();
			Variables.gameExitSting = "Exit";
			UI.ShowExitConfirmationPanel ();
		}

		if (s == "GamePress") {
			if (Variables.persChoiceNumber > -1) {
				string qs = "GamePers|" + Variables.persChoiceList[Variables.persChoiceNumber].id.ToString() + "|";
				Connection.Send (qs);
				Variables.waitAnswerText = qs;
				Variables.status = "GamePers";
				UI.SetPersCreateSystemText ("Подключение...");
			}
		}

		if (s == "GameResetPress") {
			UI.HideGameSystemListButton ();
			Variables.gameExitSting = "Reset";
			UI.ShowExitConfirmationPanel ();
		}

		if (s == "GameSettingPress") {
			UI.HideGameSystemListButton ();
			UI.PressGameSettingButton ();
		}

		if (s == "GameSystemListPress") {
			UI.PressGameSystemListButton ();
		}


		if (s == "InPlacePress") {
			Connection.Send ("ResurrectionInPlace|");
		}

		if (s == "IntelligencePlusStatsUPPress") {
			int mod = (Variables.base_intelligence + Variables.statsUPIntelligence - 10) / 2;
			if (mod < 1)
				mod = 1;
			if (Variables.statsUPFreeCharacteristics >= mod) {
				Variables.statsUPFreeCharacteristics -= mod;
				Variables.statsUPIntelligence++;
				UI.StatsUPPanelUPD ();
			}
		}
		if (s == "IntelligenceMinusStatsUPPress") {
			if (Variables.statsUPIntelligence > 0) {
				int mod = (Variables.base_intelligence + Variables.statsUPIntelligence - 11) / 2;
				if (mod < 1)
					mod = 1;
				Variables.statsUPFreeCharacteristics += mod;
				Variables.statsUPIntelligence--;
				UI.StatsUPPanelUPD ();
			}
		}

		if (s == "InTownPress") {
			Connection.Send ("Resurrection|");
		}

		if (s == "InventoryPress") {
			UI.PressInventoryButton ();
		}


		if(s == "LoginPress"){
			UI.SetStatusText ("Подключение...");
			Connection.SetAddress (UI.GetIPText(), UI.GetPortText());
			Connection.Connect ();
			Variables.waitMees = true;
			Variables.work = true;
			Variables.waitStringMess = "Login|" + UI.GetLoginText() + "|" + UI.GetPassText() + "|";
		}

		if(s == "MasteryPress"){
			UI.ShowMasteryPanel ();
			UI.HideSpellPanel ();
			UI.HideAbilityPanel ();
		}

		if (s == "NewPersPress") {
			UI.HidePersChoiceGUI ();
			UI.ShowPersCreateGUI ();
			UI.SetPersCreateSystemText ("");
			UI.ClearNameInput ();
			UI.CreatePersCreateButton ();
			Variables.persCreateChoiceRaceNumber = 0;
			UI.ClearFocusPersCreateChoiceRaceButton ();
			UI.FocusPersCreateChoiceRaceButton (0);
		}


		if (s == "OKStatsUPPress") {
			Connection.Send ("StatsUP|" + Variables.statsUPStrength + "|" + Variables.statsUPAgility + "|" + Variables.statsUPConstitution + "|" + Variables.statsUPIntelligence + "|"
			+ Variables.statsUPWisdom + "|");
		}


		if (s == "PersCreatePress") {
			UI.SetPersCreateSystemText ("Отправка...");
			string qs = "CreatePers|" + UI.GetNameText () + "|" + Variables.persCreateChoiceRaceNumber.ToString () + "|";
			Connection.Send (qs);
			Variables.waitAnswerText = qs;
			Variables.status = "CreatePers";
		}

		if (s == "PersPlaysClosePress") {
			UI.HidePersPlaysPanel ();
		}


		if(s == "RegistratePress"){
			UI.SetStatusText ("Подключение...");
			Connection.SetAddress (UI.GetIPText(), UI.GetPortText());
			Connection.Connect ();
			Variables.waitMees = true;
			Variables.work = true;
			Variables.waitStringMess = "Registrate|" + UI.GetLoginText() + "|" + UI.GetPassText() + "|";
		}

		if (s == "ResetStatsUPPress") {
			ResetStatsUP ();
			UI.StatsUPPanelUPD ();
		}

		if (s == "ReturnCreatePress") {
			UI.HidePersCreateGUI ();
			UI.ShowPersChoiceGUI ();
		}


		if (s == "ServerLostClosePress") {
			UI.CloseServerLostPanel ();
			Initializate.Reset ();
			UI.HideGameGUI ();
			UI.HidePersChoiceGUI ();
			UI.HidePersCreateGUI ();
			UI.ShowLoginGUI ();
			UI.SetStatusText ("");
		}

		if(s == "SettingPress"){
			UI.PressSettingButton ();
		}

		if (s == "SkillsPress") {
			UI.PressSkillsButton ();
		}

		if(s == "SpellPress"){
			UI.HideMasteryPanel ();
			UI.ShowSpellPanel ();
			UI.HideAbilityPanel ();
		}

		if (s == "StatsUPPress") {
			UI.PressStatsUP ();
			if (UI.GetActiveStatsUPPanel()) {
				ResetStatsUP ();
				UI.StatsUPPanelUPD ();
			}
		}

		if (s == "StatusPress") {
			UI.PressStatusButton ();
		}
		if (s == "StrengthPlusStatsUPPress") {
			int mod = (Variables.base_strength + Variables.statsUPStrength - 10) / 2;
			if (mod < 1)
				mod = 1;
			if (Variables.statsUPFreeCharacteristics >= mod) {
				Variables.statsUPFreeCharacteristics -= mod;
				Variables.statsUPStrength++;
				UI.StatsUPPanelUPD ();
			}
		}
		if (s == "StrengthMinusStatsUPPress") {
			if (Variables.statsUPStrength > 0) {
				int mod = (Variables.base_strength + Variables.statsUPStrength - 11) / 2;
				if (mod < 1)
					mod = 1;
				Variables.statsUPFreeCharacteristics += mod;
				Variables.statsUPStrength--;
				UI.StatsUPPanelUPD ();
			}
		}

		if (s == "WisdomPlusStatsUPPress") {
			int mod = (Variables.base_wisdom + Variables.statsUPWisdom - 10) / 2;
			if (mod < 1)
				mod = 1;
			if (Variables.statsUPFreeCharacteristics >= mod) {
				Variables.statsUPFreeCharacteristics -= mod;
				Variables.statsUPWisdom++;
				UI.StatsUPPanelUPD ();
			}
		}
		if (s == "WisdomMinusStatsUPPress") {
			if (Variables.statsUPWisdom > 0) {
				int mod = (Variables.base_wisdom + Variables.statsUPWisdom - 11) / 2;
				if (mod < 1)
					mod = 1;
				Variables.statsUPFreeCharacteristics += mod;
				Variables.statsUPWisdom--;
				UI.StatsUPPanelUPD ();
			}
		}
	}


	static public void UPDConnect (float dTime){
		while (true) {
			string s = Connection.GetConnectData ();
			if (s != "NoneData") {
				if (s != "ConnectUPD|") {
					Process (s);
				}
				Variables.lastUpd = 0;
			} else {
				break;
			}
		}
	
		if (Connection.GetConnect ()) {
			if (Variables.waitMees) {
				UI.SetStatusText ("Отправка...");
				Variables.waitMees = false;
				Connection.Send (Variables.waitStringMess);

				Variables.status = GetDat (Variables.waitStringMess);
				Variables.waitAnswerText = Variables.waitStringMess;
			}
			Variables.lastUpd += dTime;
			Variables.lastSend += dTime;
			if (Variables.lastUpd > Variables.mainLoginScript.lostConnectTime) {
				UI.ServerLost ();
				UI.SetStatusText ("Не удалось отправить!");
				Reset ();
			} else {
				if (Variables.status == "NeedUPD") {
					Connection.Send("NeedUIUPD|");
					ReSend ();
				}
				if (Variables.lastUpd > 2 && Variables.lastUpd < 7 && Variables.lastSend > 0.5) {
					ReSend ();
				} else {
					if (Variables.lastUpd > 7 && Variables.lastSend > 0.1) {
						ReSend ();
					}
				}
			}
		} else {
			Variables.lastUpd += dTime;
			if (Variables.lastUpd > 10) {
				UI.SetStatusText ("Не удалось подключиться!");
				Reset ();
			}
		}

	}

	static void Process(string s){
		Variables.dataText = s;
		string temS = GetDat ();
		if (temS == "ConnectLost") {
			if(Connection.GetConnect()){
				UI.SetStatusText ("");
				UI.ServerLost ();
			}
			else{
				UI.SetStatusText ("Не удалось соединиться с сервером!");
			}


			Reset ();
			return;
		}
		if (temS == "Port") {
			Rem ();
			Connection.SetPort (int.Parse(GetDat()));
			Connection.SetConnect (true);
			return;
		}
		if (temS == "LoginExist" && Variables.status == "Registrate") {
			UI.SetStatusText ("Логин занят!");
			Reset ();
			return;
		}
		if (temS == "RegistrateOK" && Variables.status == "Registrate") {
			
			UI.SetStatusText ("Регистрация успешна!");
			Reset ();
			return;
		}
		if (temS == "WrongLogin" && Variables.status == "Login") {
			
			UI.SetStatusText ("Неправильный Логин!");
			Reset ();
			return;
		}
		if (temS == "WrongPass" && Variables.status == "Login") {
			
			UI.SetStatusText ("Неправильный пароль!");
			Reset ();
			return;
		}
		if (temS == "LoginOK" && Variables.status == "Login") {
			UI.HideLoginGUI ();
			UI.ShowPersChoiceGUI ();
			ClearPersChoice ();
			Connection.Send ("NeedPers|");
			Variables.status = "NeedPers";
			Variables.waitAnswerText = "NeedPers|";
			return;
		}
		if (temS == "Pers" && Variables.status == "NeedPers") {
			Variables.status = "Wait";
			UI.HideReceiptSystemPanel ();
			Variables.needPersActive = true;
			Rem ();
			int n = int.Parse(GetDatRem ());
			if (n != 0) {
				for(int i = 0; i < n; i++){
					Variables.persChoiceList.Add (new PersChoice (int.Parse(GetDatRem ()), GetDatRem (), int.Parse(GetDatRem ())));
				}
				UI.CreatePersChoiceButton ();
			}
			return;
		}
		if (temS == "NameExist" && Variables.status == "CreatePers") {
			Variables.status = "Wait";
			UI.SetPersCreateSystemText ("Имя уже занято!");
			return;
		}
		if (temS == "CreatePersOK" && Variables.status == "CreatePers") {
			UI.HidePersCreateGUI ();
			UI.ShowPersChoiceGUI ();
			ClearPersChoice ();
			Connection.Send ("NeedPers|");
			Variables.status = "NeedPers";
			Variables.waitAnswerText = "NeedPers|";
			return;
		}
		if (temS == "GamePersOK" && Variables.status == "GamePers") {
			Connection.Send ("NeedFirstUPD|");
			Variables.status = "NeedFirstUPD";
			Variables.waitAnswerText = "NeedFirstUPD|";
			return;
		}
		if (temS == "PersPlays" && Variables.status == "GamePers") {
			UI.ShowPersPlaysPanel ();
			Variables.status = "Wait";
			return;
		}
		if (temS == "AllUPD" && Variables.status == "NeedFirstUPD") {
			Variables.status = "Loading";
			UI.HidePersChoiceGUI ();
			UI.ShowGameGUI ();
			Initializate.Loading ();
			Connection.Send ("NeedUPD|");
			Variables.status = "NeedUPD";
			Variables.waitAnswerText = "NeedUPD|";
			return;
		}
		if (temS == "AllUPD" && Variables.status == "NeedUPD"){
			Rem ();
			Initializate.Processing ();
			return;
		}
		if (temS == "UIUPD" && Variables.status == "NeedUPD"){
			Rem ();
			UI.UIUpd ();
			return;
		}
		if (temS == "StatsUPOK" && Variables.status == "NeedUPD") {
			UI.HideStatsUPPanel ();
			return;
		}
	}

	static string GetDat(){
		string s = "";
		if (Variables.dataText != " ") {
			s = Variables.dataText.Substring (0, Variables.dataText.IndexOf ("|"));
		}
		return s;
	}
	static string GetDat(string mess){
		
		string s = "";
		if (mess != " ") {
			s = mess.Substring (0, mess.IndexOf ("|"));
		}
		return s;
	}

	static void Rem(){
		Variables.dataText= Variables.dataText.Substring(Variables.dataText.IndexOf("|")+1);
	}
	static string GetDatRem(){
		string sl = "";
		if (Variables.dataText != " ") {
			sl = Variables.dataText.Substring (0, Variables.dataText.IndexOf ("|"));

			Variables.dataText = Variables.dataText.Substring (Variables.dataText.IndexOf ("|") + 1);
		}
		return sl;
	}

	static public bool Work(){
		return Variables.work;
	}

	static void Reset(){

		Variables.persChoiceNumber = -1;
		Variables.work = false;
		Variables.waitMees = false;
		Variables.needPersActive = false;
		Variables.status = "None";
		Variables.lastSend = 0;
		Variables.lastUpd = 0;
		Connection.Reset ();
	}

	static void ResetStatsUP(){
		Variables.statsUPFreeCharacteristics = Variables.freeCharacteristics;
		Variables.statsUPStrength = 0;
		Variables.statsUPAgility = 0;
		Variables.statsUPConstitution = 0;
		Variables.statsUPIntelligence = 0;
		Variables.statsUPWisdom = 0;
	}

	static void ReSend(){
		Variables.lastSend = 0;
		if (Variables.status == "Wait" || Variables.status == "Loading") {
			Connection.Send ("ConnectUPD|");
		} else {
			Connection.Send (Variables.waitAnswerText);
		}
	}
	static public void PersChoice(int j){
		Variables.persChoiceNumber = j;
		Variables.mainLoginScript.PrintS (j.ToString ());
		UI.ClearFocusPersChoiceButton ();
		UI.FocusPersChoiceButton (j);
	}
	static void ClearPersChoice(){
		Variables.persChoiceList.Clear ();
		for (int i = 0; i < Variables.persChoiceButtonList.Count; i++) {
			GameObject.Destroy (Variables.persChoiceButtonList [i].obj);
		}
		Variables.persChoiceButtonList.Clear ();
		
	}

	static public void PersCreateChoiceRace(int j){

	}
}
