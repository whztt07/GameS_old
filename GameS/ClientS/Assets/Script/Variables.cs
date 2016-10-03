using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;

public class Variables  {
	static public void Init(){

		buttonListScript = GameObject.Find ("ButtonListObject").GetComponent<ButtonList> ();
		buffListScript = GameObject.Find ("BuffListObject").GetComponent<BuffList> ();
		terrainObj = GameObject.Find ("Terrain");
		persChoiceList = new List<PersChoice> ();
		persChoiceButtonList = new List<PersChoiceButton> ();
		persCreateChoiceRaceButtonList = new List<PersCreateButton> ();
		raceList = new List<string> ();
		personList = new List<Person> ();
		temporaryPersonIdList = new List<int> ();
		temporaryItemIdList = new List<int> ();
		inventoryButtonList = new List<InventoryButton> ();
		inventoryButtonObjectList = new List<PanelButton> ();
		buffObjectList = new List<BuffObject> (); 
		debuffObjectList = new List<BuffObject> (); 
		dropItemList = new List<DropItem> ();
		weaponOffset = 1;
		masteryOffset = 16;
		abilityOffset = 26;
		spellOffset = 51;
		persTargetNumber = -1;

		raceList.Add ("Человек");
		raceList.Add ("Эльф");
		raceList.Add ("Орк");

		terrainObj.SetActive (false);
	}
	static public List<BuffObject> buffObjectList, debuffObjectList;
	static public List<InventoryButton> inventoryButtonList;
	static public List<PanelButton> inventoryButtonObjectList;
	static public bool waitMees, work, needPersActive;
	static public string waitStringMess, dataText, waitAnswerText, status, gameExitSting, curPosType;
	static public MainLogin mainLoginScript;
	static public MyCamera myCameraScript;
	static public BuffList buffListScript;
	static public ButtonList buttonListScript;
	static public float lastUpd, lastSend, curWeight, maxWeight;
	static public int persChoiceNumber, persCreateChoiceRaceNumber, statsUPStrength, statsUPAgility, statsUPConstitution, statsUPIntelligence, statsUPWisdom,
	statsUPFreeCharacteristics, freeCharacteristics, base_strength, base_agility, base_constitution, base_intelligence, base_wisdom, strength, agility, consitution,
	intelligence, wisdom, weaponOffset, curPosNum, masteryOffset, abilityOffset, spellOffset, persTargetNumber;
	static public List<PersChoice> persChoiceList;
	static public List<PersChoiceButton> persChoiceButtonList;
	static public List<string> raceList;
	static public List<PersCreateButton> persCreateChoiceRaceButtonList;
	static public List<DropItem> dropItemList;
	static public GameObject terrainObj;
	static public List<Person> personList;
	static public List<int> temporaryPersonIdList, temporaryItemIdList; 
	static public Transform inventoryButtonPanelTransform, buffPanelTransform, debuffPanelTransform, contentMasteryTransform, contentAbilityTransform, contentSpellTransform;
}
