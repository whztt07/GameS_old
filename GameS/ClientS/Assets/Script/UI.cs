using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class UI  {
	
	static  InputField loginInput, passInput, ipInput, portInput, nameInput;
	static  GameObject settingWindowPanel, settingButtonPanel, serverLostPanel, loginGUI, persChoiceGUI, receiptSystemPanel, maxPersPanel, persCreateGUI, gameGUI,
	skillsPanel, exitConfirmationPanel, gameSystemListPanel, targetPanel, inventoryPanel, statusPanel, dopStatusPanel, gameSettingPanel, persPlaysPanel, statsUPPanel,
	resurrectionPanel, inPlaceButton, masteryPanel, abilityPanel, spellPanel;
	static  Transform persChoiceTransform, persChoiceCreateTransform;
	static  Text statusText, persCreateSystemText, gameSystemText, attackText, attackSpeedText, critChanceText, critRateText, evasionText, accuracyText, speedText,
	freeCharacteristicsText, strengthText, agilityText, constitutionText, intelligenceText, wisdomText, modStrengthText, modAgilityText, modConstitutionText, modIntelligenceText,
	modWisdomText, saveReactionText, saveWillText, savePersistenceText, saveDeathText, complexitySpellText, complexityAbilityText, invisibleText, detectionText, concentrationText, 
	failSpellChanceText, rotationSpeedText, visibleRangeText, attackRangeText, recoveryHPText, recoveryMPText, regenerationHPInBattleText, regenerationHPOutBattleText,
	regenerationMPInBattleText, regenerationMPOutBattleText, resistanceFireText, resistanceColdText, resistanceNegativeText, resistanceSlashText, resistancePierceText, resistanceCrushText,
	strengthStatsUPText, agilityStatsUPText, constitutionStatsUPText, intelligenceStatsUPText, wisdomStatsUPText, modStrengthStatsUPText, modAgilityStatsUPText, modConstitutionStatsUPText,
	modIntelligenceStatsUPText, modWisdomStatsUPText, freeCharacteristicsStatsUPText, namePersonPanelText, hpBarPersonPanelText, mpBarPersonPanelText, nameStatusPanelText, 
	characteristicPointText, abilityPointText, spellPointText, mpBarStatusPanelText, hpBarStatusPanelText, weightBarStatusPanelText, weightBarInventoryPanelText,
	weightBarPercentInventoryPanelText, targetPanelText;
	static Image hpBarPersonPanelImage, mpBarPersonPanelImage, mpBarStatusPanelImage, hpBarStatusPanelImage, weightBarStatusPanelImage, weaponSlotImage, bodySlotImage,
	weightBarInventoryPanelImage, hpBarTargetPanelImage;
	static float gameSystemTextTime;
	static string uiUpdString;

	static public void Init(){
		
	
		loginInput = GameObject.Find ("LoginInputField").GetComponent<InputField> ();
		passInput = GameObject.Find ("PassInputField").GetComponent<InputField> ();
		ipInput = GameObject.Find ("IPInputField").GetComponent<InputField> ();
		portInput = GameObject.Find ("PortInputField").GetComponent<InputField> ();
		nameInput = GameObject.Find ("NameInputField").GetComponent<InputField> ();
			
		receiptSystemPanel = GameObject.Find ("ReceiptSystemPanel");
		maxPersPanel = GameObject.Find ("MaxPersPanel");
		loginGUI = GameObject.Find ("LoginGUI");
		persChoiceGUI = GameObject.Find ("PersChoiceGUI");
		settingWindowPanel = GameObject.Find ("SettingWindowPanel");
		settingButtonPanel = GameObject.Find ("SettingButtonPanel");
		serverLostPanel = GameObject.Find ("ServerLostPanel");
		persCreateGUI = GameObject.Find ("PersCreateGUI");
		gameGUI = GameObject.Find ("GameGUI");
		skillsPanel = GameObject.Find ("SkillsPanel");
		exitConfirmationPanel = GameObject.Find ("ExitConfirmationPanel");
		gameSystemListPanel = GameObject.Find ("GameSystemListPanel");
		targetPanel = GameObject.Find ("TargetPanel");
		inventoryPanel = GameObject.Find ("InventoryPanel");
		statusPanel = GameObject.Find ("StatusPanel");
		dopStatusPanel = GameObject.Find ("DopStatusPanel");
		gameSettingPanel = GameObject.Find ("GameSettingPanel");
		persPlaysPanel = GameObject.Find ("PersPlaysPanel");
		statsUPPanel = GameObject.Find ("StatsUPPanel");
		resurrectionPanel = GameObject.Find ("ResurrectionPanel"); 
		inPlaceButton = GameObject.Find ("InPlaceButton");
		masteryPanel = GameObject.Find ("MasteryPanel");
		abilityPanel = GameObject.Find ("AbilityPanel");
		spellPanel = GameObject.Find ("SpellPanel");

		statusText = GameObject.Find ("StatusText").GetComponent<Text> ();
		persCreateSystemText = GameObject.Find ("PersCreateSystemText").GetComponent<Text> ();
		gameSystemText = GameObject.Find ("GameSystemText").GetComponent<Text> ();
		attackText = GameObject.Find ("AttackDataText").GetComponent<Text> ();
		attackSpeedText = GameObject.Find ("AttackSpeedDataText").GetComponent<Text> ();
		critChanceText = GameObject.Find ("CritChanceDataText").GetComponent<Text> ();
		critRateText = GameObject.Find ("CritRateDataText").GetComponent<Text> ();
		evasionText = GameObject.Find ("EvasionDataText").GetComponent<Text> ();
		accuracyText = GameObject.Find ("AccuracyDataText").GetComponent<Text> ();
		speedText = GameObject.Find ("SpeedDataText").GetComponent<Text> ();
		freeCharacteristicsText = GameObject.Find ("FreeCharacteristicsDataText").GetComponent<Text> ();
		strengthText = GameObject.Find ("StrengthDataText").GetComponent<Text> ();
		agilityText = GameObject.Find ("AgilityDataText").GetComponent<Text> ();
		constitutionText = GameObject.Find ("ConstitutionDataText").GetComponent<Text> ();
		intelligenceText = GameObject.Find ("IntelligenceDataText").GetComponent<Text> ();
		wisdomText = GameObject.Find ("WisdomDataText").GetComponent<Text> ();
		modStrengthText = GameObject.Find ("ModStrengthDataText").GetComponent<Text> ();
		modAgilityText = GameObject.Find ("ModAgilityDataText").GetComponent<Text> ();
		modConstitutionText = GameObject.Find ("ModConstitutionDataText").GetComponent<Text> ();
		modIntelligenceText = GameObject.Find ("ModIntelligenceDataText").GetComponent<Text> ();
		modWisdomText = GameObject.Find ("ModWisdomDataText").GetComponent<Text> ();
		saveReactionText = GameObject.Find ("SaveReactionDataText").GetComponent<Text> ();
		saveWillText = GameObject.Find ("SaveWillDataText").GetComponent<Text> ();
		savePersistenceText = GameObject.Find ("SavePersistenceDataText").GetComponent<Text> ();
		saveDeathText = GameObject.Find ("SaveDeathDataText").GetComponent<Text> ();
		complexitySpellText = GameObject.Find ("ComplexitySpellDataText").GetComponent<Text> ();
		complexityAbilityText = GameObject.Find ("ComplexityAbilityDataText").GetComponent<Text> ();
		invisibleText = GameObject.Find ("InvisibleDataText").GetComponent<Text> ();
		detectionText = GameObject.Find ("DetectionDataText").GetComponent<Text> ();
		concentrationText = GameObject.Find ("ConcentrationDataText").GetComponent<Text> ();
		failSpellChanceText = GameObject.Find ("FailSpellChanceDataText").GetComponent<Text> ();
		rotationSpeedText = GameObject.Find ("RotationSpeedDataText").GetComponent<Text> ();
		visibleRangeText = GameObject.Find ("VisibleRangeDataText").GetComponent<Text> ();
		attackRangeText = GameObject.Find ("AttackRangeDataText").GetComponent<Text> ();
		recoveryHPText = GameObject.Find ("RecoveryHPDataText").GetComponent<Text> ();
		recoveryMPText = GameObject.Find ("RecoveryMPDataText").GetComponent<Text> ();
		regenerationHPInBattleText = GameObject.Find ("RegenerationHPInBattleDataText").GetComponent<Text> ();
		regenerationHPOutBattleText = GameObject.Find ("RegenerationHPOutBattleDataText").GetComponent<Text> ();
		regenerationMPInBattleText = GameObject.Find ("RegenerationMPInBattleDataText").GetComponent<Text> ();
		regenerationMPOutBattleText = GameObject.Find ("RegenerationMPOutBattleDataText").GetComponent<Text> ();
		resistanceFireText = GameObject.Find ("ResistanceFireDataText").GetComponent<Text> ();
		resistanceColdText = GameObject.Find ("ResistanceColdDataText").GetComponent<Text> ();
		resistanceNegativeText = GameObject.Find ("ResistanceNegativeDataText").GetComponent<Text> ();
		resistanceSlashText = GameObject.Find ("ResistanceSlashDataText").GetComponent<Text> ();
		resistancePierceText = GameObject.Find ("ResistancePierceDataText").GetComponent<Text> ();
		resistanceCrushText = GameObject.Find ("ResistanceCrushDataText").GetComponent<Text> ();
		strengthStatsUPText = GameObject.Find ("StrengthStatsUPDataText").GetComponent<Text> ();
		agilityStatsUPText = GameObject.Find ("AgilityStatsUPDataText").GetComponent<Text> ();
		constitutionStatsUPText = GameObject.Find ("ConstitutionStatsUPDataText").GetComponent<Text> ();
		intelligenceStatsUPText = GameObject.Find ("IntelligenceStatsUPDataText").GetComponent<Text> ();
		wisdomStatsUPText = GameObject.Find ("WisdomStatsUPDataText").GetComponent<Text> ();
		modStrengthStatsUPText = GameObject.Find ("ModStrengthStatsUPDataText").GetComponent<Text> ();
		modAgilityStatsUPText = GameObject.Find ("ModAgilityStatsUPDataText").GetComponent<Text> ();
		modConstitutionStatsUPText = GameObject.Find ("ModConstitutionStatsUPDataText").GetComponent<Text> ();
		modIntelligenceStatsUPText = GameObject.Find ("ModIntelligenceStatsUPDataText").GetComponent<Text> ();
		modWisdomStatsUPText = GameObject.Find ("ModWisdomStatsUPDataText").GetComponent<Text> ();
		freeCharacteristicsStatsUPText = GameObject.Find ("FreeCharacteristicsStatsUPDataText").GetComponent<Text> ();
		namePersonPanelText = GameObject.Find ("NamePersonPanelText").GetComponent<Text> ();
		hpBarPersonPanelText = GameObject.Find ("HPBarPersonPanelText").GetComponent<Text> ();
		mpBarPersonPanelText = GameObject.Find ("MPBarPersonPanelText").GetComponent<Text> ();
		nameStatusPanelText = GameObject.Find ("MPBarPersonPanelText").GetComponent<Text> (); 
		characteristicPointText = GameObject.Find ("CharacteristicPointDataText").GetComponent<Text> (); 
		abilityPointText = GameObject.Find ("AbilityPointDataText").GetComponent<Text> (); 
		spellPointText = GameObject.Find ("SpellPointDataText").GetComponent<Text> (); 
		mpBarStatusPanelText = GameObject.Find ("MPBarStatusPanelText").GetComponent<Text> (); 
		hpBarStatusPanelText = GameObject.Find ("HPBarStatusPanelText").GetComponent<Text> (); 
		weightBarStatusPanelText = GameObject.Find ("WeightBarStatusPanelText").GetComponent<Text> (); 
		weightBarInventoryPanelText = GameObject.Find ("WeightBarInventoryPanelText").GetComponent<Text> (); 
		weightBarPercentInventoryPanelText = GameObject.Find ("WeightBarPercentInventoryPanelText").GetComponent<Text> (); 
		targetPanelText = GameObject.Find ("NameTargetPanelText").GetComponent<Text> (); 


		hpBarPersonPanelImage = GameObject.Find ("HPBarPersonPanelImage").GetComponent<Image> ();
		mpBarPersonPanelImage = GameObject.Find ("MPBarPersonPanelImage").GetComponent<Image> ();
		mpBarStatusPanelImage = GameObject.Find ("MPBarStatusPanelImage").GetComponent<Image> (); 
		hpBarStatusPanelImage = GameObject.Find ("HPBarStatusPanelImage").GetComponent<Image> (); 
		weightBarStatusPanelImage = GameObject.Find ("WeightBarStatusPanelImage").GetComponent<Image> (); 
		weaponSlotImage = GameObject.Find ("WeaponInventoryButton").GetComponent<Image> (); 
		bodySlotImage = GameObject.Find ("BodyInventoryButton").GetComponent<Image> ();
		weightBarInventoryPanelImage = GameObject.Find ("WeightBarInventoryPanelImage").GetComponent<Image> ();
		hpBarTargetPanelImage = GameObject.Find ("HPBarTargetPanelImage").GetComponent<Image> ();


		persChoiceTransform = GameObject.Find ("PersChoicePanel").transform;
		persChoiceCreateTransform = GameObject.Find ("PersChoiceCreatePanel").transform;
		Variables.inventoryButtonPanelTransform = GameObject.Find ("InventoryButtonPanel").transform;
		Variables.buffPanelTransform = GameObject.Find ("BuffPanel").transform;
		Variables.debuffPanelTransform = GameObject.Find ("DebuffPanel").transform;
		Variables.contentMasteryTransform = GameObject.Find ("ContentMastery").transform;
		Variables.contentAbilityTransform = GameObject.Find ("ContentAbility").transform;
		Variables.contentSpellTransform = GameObject.Find ("ContetntSpell").transform;

		settingButtonPanel.SetActive (false);
		settingWindowPanel.SetActive (false);
		serverLostPanel.SetActive (false);
		persChoiceGUI.SetActive (false);
		maxPersPanel.SetActive (false);
		persCreateGUI.SetActive (false);
		gameGUI.SetActive (false);
		skillsPanel.SetActive (false);
		exitConfirmationPanel.SetActive (false);
		gameSystemListPanel.SetActive (false);
		targetPanel.SetActive (false);
		inventoryPanel.SetActive (false);
		statusPanel.SetActive (false);
		dopStatusPanel.SetActive (false);
		gameSettingPanel.SetActive (false);
		persPlaysPanel.SetActive (false);
		statsUPPanel.SetActive (false);
		resurrectionPanel.SetActive (false);
		inPlaceButton.SetActive (false);
		abilityPanel.SetActive (false);
		spellPanel.SetActive (false);
	}
	static public void WriteGameSystemText(string s){
		gameSystemText.text = s;
		gameSystemTextTime = 5f;
	}
	static public void PressStatusButton (){
		statusPanel.SetActive (!statusPanel.activeSelf);
	}
	static public void PressInventoryButton (){
		inventoryPanel.SetActive (!inventoryPanel.activeSelf);
	}
	static public void PressSkillsButton (){
		skillsPanel.SetActive (!skillsPanel.activeSelf);
	}
	static public void PressGameSystemListButton (){
		gameSystemListPanel.SetActive (!gameSystemListPanel.activeSelf);
	}
	static public void HideGameSystemListButton (){
		gameSystemListPanel.SetActive (false);
	}
	static public void ShowExitConfirmationPanel (){
		exitConfirmationPanel.SetActive (true);
	}
	static public void HideExitConfirmationPanel (){
		exitConfirmationPanel.SetActive (false);
	}
	static public void PressGameSettingButton (){
		gameSettingPanel.SetActive (!gameSettingPanel.activeSelf);
	}

	static public void PressSettingButton (){
		settingButtonPanel.SetActive (!settingButtonPanel.activeSelf);
	}
	static public void ShowInPlaceButton(){
		inPlaceButton.SetActive (true);
	}
	static public void HideInPlaceButton(){
		inPlaceButton.SetActive (false);
	}
	static public void ShowResurrectionPanel(){
		resurrectionPanel.SetActive (true);
	}
	static public void HideResurrectionPanel(){
		resurrectionPanel.SetActive (false);
	}
	static public void ShowSettingWindowPanel (){
		settingWindowPanel.SetActive (true);
	}

	static public void HideSettingButtonPanel (){
		settingButtonPanel.SetActive (false);
	}

	static public void HideSettingWindowPanel (){
		settingWindowPanel.SetActive (false);
	}

	static public void SetStatusText (string s){
		statusText.text = s;
	}
	static public void ClearStatusText (){
		statusText.text = "";
	}

	static public string GetLoginText (){
		return loginInput.text;
	}

	static public string GetPassText (){
		return passInput.text;
	}
	static public string GetIPText (){
		return ipInput.text;
	}
	static public string GetPortText (){
		return portInput.text;
	}

	static public void ServerLost (){
		serverLostPanel.SetActive (true);
	}
	static public void CloseServerLostPanel(){
		serverLostPanel.SetActive (false);
	}

	static public void ShowLoginGUI (){
		loginGUI.SetActive (true);
	}
	static public void ShowPersChoiceGUI (){
		persChoiceGUI.SetActive (true);
	}
	static public void HideMasteryPanel(){
		masteryPanel.SetActive (false);
	}
	static public void ShowMasteryPanel(){
		masteryPanel.SetActive (true);
	}
	static public void HideAbilityPanel(){
		abilityPanel.SetActive (false);
	}
	static public void ShowAbilityPanel(){
		abilityPanel.SetActive (true);
	}
	static public void HideSpellPanel(){
		spellPanel.SetActive (false);
	}
	static public void ShowSpellPanel(){
		spellPanel.SetActive (true);
	}
	static public void HideLoginGUI (){
		loginGUI.SetActive (false);
	}
	static public void HidePersChoiceGUI (){
		persChoiceGUI.SetActive (false);
	}
	static public void HideReceiptSystemPanel(){
		receiptSystemPanel.SetActive (false);
	}
	static public void PressDopStatusButton(){
		dopStatusPanel.SetActive (!dopStatusPanel.activeSelf);
	}
	static public void PressStatsUP(){
		statsUPPanel.SetActive (!statsUPPanel.activeSelf);
	}
	static public void HideStatsUPPanel(){
		statsUPPanel.SetActive (false);
	}
	static public bool GetActiveStatsUPPanel(){
		return statsUPPanel.activeSelf;
	}
	static public void HidePersCreateGUI (){
		persCreateGUI.SetActive (false);
	}
	static public void ShowPersCreateGUI (){
		persCreateGUI.SetActive (true);
	}
	static public void ShowGameGUI (){
		gameGUI.SetActive (true);
	}
	static public void HideGameGUI (){
		gameGUI.SetActive (false);
	}
	static public void ShowPersPlaysPanel (){
		persPlaysPanel.SetActive (true);
	}
	static public void HidePersPlaysPanel (){
		persPlaysPanel.SetActive (false);
	}
	static public void SetPersCreateSystemText (string s){
		persCreateSystemText.text = s;
	}
	static public string GetNameText (){
		return nameInput.text;
	}
	static public void ClearNameInput (){
		nameInput.text = "";
	}
	static public void CreatePersCreateButton (){
		if (Variables.raceList.Count != Variables.persCreateChoiceRaceButtonList.Count) {
			for (int i = 0; i < Variables.raceList.Count; i++) {
				Variables.persCreateChoiceRaceButtonList.Add (new PersCreateButton(GameObject.Instantiate(
					Variables.mainLoginScript.persCreateButtonPrefab, Vector3.zero, Quaternion.Euler(Vector3.zero)) as GameObject));
				Variables.persCreateChoiceRaceButtonList [i].obj.transform.SetParent (persChoiceCreateTransform);
				int ii = i;
				Variables.persCreateChoiceRaceButtonList [i].button.onClick.AddListener(delegate {	Variables.mainLoginScript.PersCreateChoiceRace(ii);});
				Variables.persCreateChoiceRaceButtonList [i].text.text = Variables.raceList [i];
			}
		}
	}

	static public void CreatePersChoiceButton (){
		for (int i = 0; i < Variables.persChoiceList.Count; i++) {
			Variables.persChoiceButtonList.Add(new PersChoiceButton(GameObject.Instantiate(
				Variables.mainLoginScript.persChoiseButtonPrefab, Vector3.zero, Quaternion.Euler(Vector3.zero)) as GameObject));

			Variables.persChoiceButtonList[i].obj.transform.SetParent(persChoiceTransform);
			int ii = i;
			Variables.persChoiceButtonList[i].button.onClick.AddListener(delegate {	Variables.mainLoginScript.PersChoice(ii);});
			Variables.persChoiceButtonList [i].nameText.text = Variables.persChoiceList [i].name;
			Variables.persChoiceButtonList [i].raceText.text = Variables.raceList[Variables.persChoiceList [i].race];
		}
	}
	static public void FocusPersChoiceButton (int j){
		
		Variables.persChoiceButtonList [j].image.color = new Color (0.5f, 0.5f, 0.5f);
	}
	static public void ClearFocusPersChoiceButton (){
		for (int i = 0; i < Variables.persChoiceButtonList.Count; i++) {
			Variables.persChoiceButtonList [i].image.color = Color.white;
		}
	}
	static public void FocusPersCreateChoiceRaceButton (int j){

		Variables.persCreateChoiceRaceButtonList [j].image.color = new Color (0.5f, 0.5f, 0.5f);
	}
	static public void ClearFocusPersCreateChoiceRaceButton (){
		for (int i = 0; i < Variables.persCreateChoiceRaceButtonList.Count; i++) {
			Variables.persCreateChoiceRaceButtonList [i].image.color = Color.white;
		}
	}
	static public void StatsUPPanelUPD(){
		freeCharacteristicsStatsUPText.text = Variables.statsUPFreeCharacteristics.ToString();
		int str = Variables.statsUPStrength + Variables.strength, agi = Variables.statsUPAgility + Variables.agility, con = Variables.statsUPConstitution + Variables.consitution,
		intel = Variables.statsUPIntelligence + Variables.intelligence, wis = Variables.statsUPWisdom + Variables.wisdom;
		strengthStatsUPText.text = (Variables.statsUPStrength + Variables.base_strength).ToString () + " (" + str + ")";
		agilityStatsUPText.text = (Variables.statsUPAgility + Variables.base_agility).ToString () + " (" + agi + ")";
		constitutionStatsUPText.text = (Variables.statsUPConstitution + Variables.base_constitution).ToString () + " (" + con + ")";
		intelligenceStatsUPText.text = (Variables.statsUPIntelligence + Variables.base_intelligence).ToString () + " (" + intel + ")";
		wisdomStatsUPText.text = (Variables.statsUPWisdom + Variables.base_wisdom).ToString () + " (" + wis + ")";
		modStrengthStatsUPText.text = ((str - 10) / 2.0f).ToString ();
		modAgilityStatsUPText.text = ((agi - 10) / 2.0f).ToString ();
		modConstitutionStatsUPText.text = ((con - 10) / 2.0f).ToString ();
		modIntelligenceStatsUPText.text = ((intel - 10) / 2.0f).ToString ();
		modWisdomStatsUPText.text = ((wis - 10) / 2.0f).ToString ();
	}

	static public void UIUpd(float dTime){
		gameSystemTextTime -= dTime;
		if (gameSystemTextTime <= 0) {
			gameSystemTextTime = 0;
			gameSystemText.text = "";
		}

		if (Variables.personList.Count > 0) {
			namePersonPanelText.text = Variables.personList [0].name;
			nameStatusPanelText.text = Variables.personList [0].name;
			string s = ((int)(Variables.personList [0].curHP + 0.5f)).ToString() + "/" + ((int)(Variables.personList [0].maxHP + 0.5f)).ToString();
			hpBarPersonPanelText.text = s;
			hpBarStatusPanelText.text = s;
			s = ((int)(Variables.personList [0].curMP + 0.5f)).ToString() + "/" + ((int)(Variables.personList [0].maxMP + 0.5f)).ToString();
			mpBarPersonPanelText.text = s;
			mpBarStatusPanelText.text = s;
			float f = Variables.personList [0].curHP / Variables.personList [0].maxHP;
			hpBarPersonPanelImage.fillAmount = f;
			hpBarStatusPanelImage.fillAmount = f;
			f = Variables.personList [0].curMP / Variables.personList [0].maxMP;
			mpBarPersonPanelImage.fillAmount = f;
			mpBarStatusPanelImage.fillAmount = f;

			int j = -1;
			if (Variables.persTargetNumber != -1) {
				for (int i = 0; i < Variables.personList.Count; i++) {
					if (Variables.persTargetNumber == Variables.personList [i].id) {
						j = i;
						break;
					}
				}
				if (j == -1) {
					Variables.persTargetNumber = -1;
					targetPanel.SetActive (false);
				} else {
					targetPanel.SetActive (true);

					targetPanelText.text = Variables.personList [j].name;
					hpBarTargetPanelImage.fillAmount = Variables.personList [j].fillAmountImage;

				}
			}
		}


	}

	static public void UIUpd(){
		if (uiUpdString != Variables.dataText) {
			uiUpdString = Variables.dataText;
			Variables.base_strength = int.Parse(GetDatRem ());
			Variables.base_agility = int.Parse(GetDatRem ());
			Variables.base_constitution = int.Parse(GetDatRem ());
			Variables.base_intelligence = int.Parse(GetDatRem ());
			Variables.base_wisdom = int.Parse(GetDatRem ());
			Variables.strength = int.Parse(GetDatRem ());
			Variables.agility = int.Parse(GetDatRem ());
			Variables.consitution = int.Parse(GetDatRem ());
			Variables.intelligence = int.Parse(GetDatRem ());
			Variables.wisdom = int.Parse(GetDatRem ());
			strengthText.text = Variables.strength + " (" + Variables.base_strength + ")";
			agilityText.text = Variables.agility + " (" + Variables.base_agility + ")";
			constitutionText.text = Variables.consitution + " (" + Variables.base_constitution + ")";
			intelligenceText.text = Variables.intelligence + " (" + Variables.base_intelligence + ")";
			wisdomText.text = Variables.wisdom + " (" + Variables.base_wisdom + ")";


			modStrengthText.text = float.Parse(GetDatRem ()).ToString();
			modAgilityText.text = float.Parse(GetDatRem ()).ToString();
			modConstitutionText.text = float.Parse(GetDatRem ()).ToString();
			modIntelligenceText.text = float.Parse(GetDatRem ()).ToString();
			modWisdomText.text = float.Parse(GetDatRem ()).ToString();
			attackText.text = float.Parse(GetDatRem ()).ToString() + "-" + float.Parse(GetDatRem ()).ToString();
			attackSpeedText.text = GetDatRem ();
			critChanceText.text = GetDatRem () + "%";
			critRateText.text = "x" + GetDatRem ();
			evasionText.text = float.Parse(GetDatRem ()).ToString();
			accuracyText.text = float.Parse(GetDatRem ()).ToString();
			speedText.text = float.Parse(GetDatRem ()).ToString();
			saveReactionText.text = float.Parse(GetDatRem ()).ToString();
			savePersistenceText.text = float.Parse(GetDatRem ()).ToString();
			saveWillText.text = float.Parse(GetDatRem ()).ToString();
			saveDeathText.text = float.Parse(GetDatRem ()).ToString();
			complexitySpellText.text = float.Parse(GetDatRem ()).ToString();
			complexityAbilityText.text = float.Parse(GetDatRem ()).ToString();
			invisibleText.text = float.Parse(GetDatRem ()).ToString();
			detectionText.text = float.Parse(GetDatRem ()).ToString();
			concentrationText.text = float.Parse(GetDatRem ()).ToString();
			failSpellChanceText.text = GetDatRem () + "%";
			rotationSpeedText.text = float.Parse(GetDatRem ()).ToString() + "°";
			visibleRangeText.text = float.Parse(GetDatRem ()).ToString();
			attackRangeText.text = float.Parse(GetDatRem ()).ToString();
			recoveryHPText.text = GetDatRem () + "%";
			recoveryMPText.text = GetDatRem () + "%";
			regenerationHPOutBattleText.text = float.Parse(GetDatRem ()).ToString();
			regenerationMPOutBattleText.text = float.Parse(GetDatRem ()).ToString();
			regenerationHPInBattleText.text = float.Parse(GetDatRem ()).ToString();
			regenerationMPInBattleText.text = float.Parse(GetDatRem ()).ToString();
			resistanceSlashText.text = GetDatRem ();
			resistanceCrushText.text = GetDatRem ();
			resistancePierceText.text = GetDatRem ();
			resistanceFireText.text = GetDatRem ();
			resistanceColdText.text = GetDatRem ();
			resistanceNegativeText.text = GetDatRem ();
			Variables.freeCharacteristics = int.Parse(GetDatRem ());
			freeCharacteristicsText.text = Variables.freeCharacteristics.ToString();
			Variables.curWeight = float.Parse(GetDatRem ());
			Variables.maxWeight = float.Parse(GetDatRem ());

			string s = ((int)(Variables.curWeight * 100/Variables.maxWeight)).ToString() + "%";
			weightBarStatusPanelText.text = s;
			weightBarPercentInventoryPanelText.text = s;
			weightBarInventoryPanelText.text = Variables.curWeight + "/" + Variables.maxWeight;

			float amo = Variables.curWeight / Variables.maxWeight;
			weightBarStatusPanelImage.fillAmount = amo;
			weightBarInventoryPanelImage.fillAmount = amo;

			characteristicPointText.text = GetDatRem ();
			abilityPointText.text = GetDatRem ();
			spellPointText.text = GetDatRem ();

			Variables.personList[0].weaponSlot = int.Parse(GetDatRem ());
			Variables.personList[0].bodySlot = int.Parse(GetDatRem ());
			if (Variables.personList[0].weaponSlot > -1) {
				weaponSlotImage.sprite = 
					Variables.buttonListScript.buttonInfoList [Variables.personList[0].weaponSlot + Variables.weaponOffset].image;
			} else {
				weaponSlotImage.sprite = Variables.buttonListScript.buttonInfoList [0].image;
			}
			if (Variables.personList[0].bodySlot > -1) {
				bodySlotImage.sprite = 
					Variables.buttonListScript.buttonInfoList [Variables.personList[0].bodySlot + Variables.weaponOffset].image;
			} else {
				bodySlotImage.sprite = Variables.buttonListScript.buttonInfoList [0].image;
			}
			for (int i = 0; i < 20; i++) {
				Variables.inventoryButtonList[i].item = int.Parse(GetDatRem ());
				Variables.inventoryButtonList[i].count = int.Parse(GetDatRem ());
				if (Variables.inventoryButtonList [i].item > -1) {
					Variables.inventoryButtonObjectList [i].buttonImage.sprite = 
						Variables.buttonListScript.buttonInfoList [Variables.inventoryButtonList [i].item + Variables.weaponOffset].image;
				} else {
					Variables.inventoryButtonObjectList [i].buttonImage.sprite = Variables.buttonListScript.buttonInfoList [0].image;
				}
			}
			for (int i = 0; i < 10; i++) {
				int type = int.Parse(GetDatRem ());

				if (type == -1) {
					Variables.buffObjectList [i].obj.SetActive (false);
				} else {
					Variables.buffObjectList [i].obj.SetActive (true);
					Variables.buffObjectList [i].image.sprite = Variables.buffListScript.buffList [GetBuffIndex (type)].image;
				}
			}
			for (int i = 0; i < 10; i++) {
				int type = int.Parse(GetDatRem ());

				if (type == -1) {
					Variables.debuffObjectList [i].obj.SetActive (false);
				} else {
					Variables.debuffObjectList [i].obj.SetActive (true);
					Variables.debuffObjectList [i].image.sprite = Variables.buffListScript.buffList [GetBuffIndex (type)].image;
				}
			}
		}
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

	static int GetBuffIndex(int num){
		for (int i = 0; i < Variables.buffListScript.buffList.Count; i++) {

			if (Variables.buffListScript.buffList [i].type == num) {
				return i;
			}

		}
		return -1;
	}
}
