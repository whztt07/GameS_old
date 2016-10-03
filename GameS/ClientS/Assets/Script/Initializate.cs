using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;
public class Initializate  {
	static bool _init = false;
	static public void Init(){
		if (!_init) {
			_init = true;



			for (int i = 0; i < 20; i++) {
				Variables.inventoryButtonList.Add (new InventoryButton ());

				Variables.inventoryButtonObjectList.Add (new PanelButton (GameObject.Instantiate (Variables.mainLoginScript.buttonPrefab) as GameObject));
				Variables.inventoryButtonObjectList [i].transform.SetParent (Variables.inventoryButtonPanelTransform);


				int ii = i;
				EventTrigger.TriggerEvent t = new EventTrigger.TriggerEvent();
				t.AddListener(delegate  {	Variables.mainLoginScript.BeginDragInventoryButton(ii);});
				Variables.inventoryButtonObjectList[i].eventTrigger.triggers.Add(new EventTrigger.Entry{callback = t
						,	eventID = EventTriggerType.BeginDrag});

				t = new EventTrigger.TriggerEvent();
				t.AddListener(delegate {	Variables.mainLoginScript.EndDrag();});
				Variables.inventoryButtonObjectList[i].eventTrigger.triggers.Add (new EventTrigger.Entry{ 
					callback = t , 
					eventID = EventTriggerType.EndDrag});

				t = new EventTrigger.TriggerEvent();
				t.AddListener(delegate {	Variables.mainLoginScript.EnterInventoryButton(ii);});
				Variables.inventoryButtonObjectList[i].eventTrigger.triggers.Add (new EventTrigger.Entry{ 
					callback = t , 
					eventID = EventTriggerType.PointerEnter});

				t = new EventTrigger.TriggerEvent();
				t.AddListener(delegate {	Variables.mainLoginScript.ExitInventoryButton();});
				Variables.inventoryButtonObjectList[i].eventTrigger.triggers.Add (new EventTrigger.Entry{ 
					callback = t , 
					eventID = EventTriggerType.PointerExit});
				


			}
			for (int i = 0; i < 20; i++) {
				

				Variables.buffObjectList.Add (new BuffObject (GameObject.Instantiate (Variables.mainLoginScript.imagePrefab) as GameObject));
				Variables.debuffObjectList.Add (new BuffObject (GameObject.Instantiate (Variables.mainLoginScript.imagePrefab) as GameObject));

				Variables.buffObjectList [i].transform.SetParent (Variables.buffPanelTransform);
				Variables.debuffObjectList [i].transform.SetParent (Variables.debuffPanelTransform);
				Variables.debuffObjectList [i].image.color = new Color (255, 150, 150);
				Variables.buffObjectList [i].obj.SetActive (false);
				Variables.debuffObjectList [i].obj.SetActive (false);

			}


		}
	}
	static public void Loading(){
		Variables.terrainObj.SetActive (true);
		Variables.personList.Add (new Person (GameObject.Instantiate (Variables.mainLoginScript.personPerfab, Vector3.zero, Quaternion.Euler (Vector3.zero)) as GameObject));
		Init ();
		Rem ();
		Processing ();
	}

	static public void Processing(){
		
		Variables.personList [0].id = int.Parse (GetDatRem ());
		Variables.personList [0].name = GetDatRem ();
		Variables.personList [0].live = int.Parse (GetDatRem ()) != 0;
		Variables.personList [0].corpseSave = int.Parse (GetDatRem ()) != 0;
		Variables.personList [0].resInPlace = int.Parse (GetDatRem ()) != 0;
		if (!Variables.personList [0].live) {
			UI.ShowResurrectionPanel ();
			if (!Variables.personList [0].corpseSave) {
				Variables.personList [0].obj.SetActive (false);
				UI.HideInPlaceButton ();
			} else {
				if (Variables.personList [0].resInPlace) {
					UI.ShowInPlaceButton ();
				} else {
					UI.HideInPlaceButton ();
				}
			}
		} else {
			Variables.personList [0].obj.SetActive (true);
			UI.HideResurrectionPanel ();
		}
		Variables.personList [0].transform.position = new Vector3 (float.Parse (GetDatRem ()), float.Parse (GetDatRem ()), float.Parse (GetDatRem ()));
		Variables.personList [0].transform.rotation = Quaternion.Euler (new Vector3 (0, float.Parse (GetDatRem ()), 0));
		Variables.personList [0].curHP = float.Parse (GetDatRem ());
		Variables.personList [0].maxHP = float.Parse (GetDatRem ());
		Variables.personList [0].curMP = float.Parse (GetDatRem ());
		Variables.personList [0].maxMP = float.Parse (GetDatRem ());
		Variables.personList [0].fillAmountImage = Variables.personList [0].curHP / Variables.personList [0].maxHP;
		Variables.personList [0].animNum = int.Parse(GetDatRem ());
		Variables.personList [0].animSpeed = float.Parse (GetDatRem ());

		int targetNum = int.Parse(GetDatRem ());
		if (Variables.persTargetNumber == -1) {
			Variables.persTargetNumber = targetNum;
		}
		int number = int.Parse (GetDatRem ());
		Variables.temporaryPersonIdList.Clear ();
		for (int i = 0; i < number; i++) {
			int _id = int.Parse (GetDatRem ());
			Variables.temporaryPersonIdList.Add (_id);
			string _name = GetDatRem ();
			bool _live = int.Parse (GetDatRem ()) != 0;
			float _x = float.Parse (GetDatRem ()), _y = float.Parse (GetDatRem ()), _z = float.Parse (GetDatRem ()), _rot_y = float.Parse (GetDatRem ());
			int _index = -1;
			for (int i2 = 1; i2 < Variables.personList.Count; i2++) {
				if (Variables.personList [i2].id == _id) {
					_index = i2;
					break;
				}
			}
			if (_index > 0) {
				Variables.personList [_index].transform.position = new Vector3 (_x, _y, _z);
				Variables.personList [_index].transform.rotation = Quaternion.Euler (new Vector3 (0, _rot_y, 0));
			} else {
				Variables.personList.Add (new Person (GameObject.Instantiate (Variables.mainLoginScript.personPerfab, new Vector3 (_x, _y, _z),
					Quaternion.Euler (new Vector3 (0, _rot_y, 0))) as GameObject));
				_index = Variables.personList.Count-1;
			}
			Variables.personList [_index].id = _id;
			Variables.personList [_index].name = _name;
			Variables.personList [_index].live = _live;
			Variables.personList [_index].fillAmountImage = float.Parse (GetDatRem ());
			Variables.personList [_index].animNum = int.Parse(GetDatRem ());
			Variables.personList [_index].animSpeed = float.Parse (GetDatRem ());
		}
		for (int i = 1; i < Variables.personList.Count; i++) {
			if (!Variables.temporaryPersonIdList.Contains (Variables.personList [i].id)) {
				GameObject.Destroy (Variables.personList [i].obj);
				Variables.personList.RemoveAt (i);
				i--;
			}
		}


		number = int.Parse (GetDatRem ());
		Variables.temporaryItemIdList.Clear ();
		for (int i = 0; i < number; i++) {
			int _id = int.Parse (GetDatRem ());
			Variables.temporaryItemIdList.Add (_id);
			float _x = float.Parse (GetDatRem ()), _y = float.Parse (GetDatRem ()), _z = float.Parse (GetDatRem ());
			int _index = -1;
			for (int i2 = 0; i2 < Variables.dropItemList.Count; i2++) {
				if (Variables.dropItemList [i2].id == _id) {
					_index = i2;
					break;
				}
			}
			if (_index == -1) {							
				Variables.dropItemList.Add (new DropItem (GameObject.Instantiate (Variables.mainLoginScript.dropItemPrefab, new Vector3 (_x, _y, _z),
					Quaternion.Euler (Vector3.zero)) as GameObject));
				_index = Variables.dropItemList.Count-1;
			}
			Variables.dropItemList [_index].id = _id;
		}
		for (int i = 0; i < Variables.dropItemList.Count; i++) {
			if (!Variables.temporaryItemIdList.Contains (Variables.dropItemList [i].id)) {
				GameObject.Destroy (Variables.dropItemList [i].obj);
				Variables.dropItemList.RemoveAt (i);
				i--;
			}
		}

	}

	static public void Reset (){
		Variables.terrainObj.SetActive (false);
		for (int i = 0; i < Variables.personList.Count; i++) {
			GameObject.Destroy (Variables.personList [i].obj);
		}
		Variables.personList.Clear ();
		for (int i = 0; i < Variables.dropItemList.Count; i++) {
			GameObject.Destroy (Variables.dropItemList [i].obj);
		}
		Variables.dropItemList.Clear ();
		Variables.myCameraScript.Reset ();
	}

	static string GetDat(){
		string s = "";
		if (Variables.dataText != " ") {
			s = Variables.dataText.Substring (0, Variables.dataText.IndexOf ("|"));
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
}
