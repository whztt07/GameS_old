using UnityEngine;
using System.Collections;
using System.Diagnostics;

public class MainLogin : MonoBehaviour {
	public GameObject persChoiseButtonPrefab;
	public GameObject persCreateButtonPrefab;
	public GameObject testPrefab;
	public GameObject personPerfab;
	public GameObject buttonPrefab;
	public GameObject dropItemPrefab;
	public GameObject masteryPrefab;
	public GameObject spellPrefab;
	public GameObject imagePrefab; //255, 150, 150, 255
	public LayerMask personMask, moveMask, dropItemMask;
	public int lostConnectTime = 10;
	public bool showAllPosts = false;
	// Use this for initialization
	void Start () {
		Processing.Init (this.gameObject.GetComponent<MainLogin>(), this.gameObject.GetComponent<MyCamera>());
	}

	public void ButtonS(string s){
		Processing.ProcessButton (s);
	}

	// Update is called once per frame
	void Update () {
		//Stopwatch sw = new Stopwatch ();
		//sw.Start ();
		float dTime = Time.deltaTime;
		//for (int i = 0; i < 1; i++)
		//	Instantiate (testPrefab,Vector3.zero,Quaternion.Euler(Vector3.zero));
		ClickUPD();
		if (Processing.Work ()) {
			Processing.UPDConnect (dTime);
			UI.UIUpd (dTime);
			AnimationC.AnimationUPD ();
		}

		//sw.Stop ();
//		print ("res:"+sw.ElapsedMilliseconds.ToString ());
	}

	public void PrintS(string s){
		print (s);
	}

	public void PersChoice(int i){
		Processing.PersChoice (i);

	}

	public void PersCreateChoiceRace(int i){
		Processing.PersCreateChoiceRace (i);
	}

public void ClickUPD(){
		bool messageReady = false;
		float dTime = Time.deltaTime;
		string str = "";
		if (!UnityEngine.EventSystems.EventSystem.current.IsPointerOverGameObject ()) {
			
			if (Input.GetMouseButtonUp (0)) {
				Ray _ray = Camera.main.ScreenPointToRay (Input.mousePosition);
				RaycastHit hit;
				if (Physics.Raycast (_ray, out hit, Mathf.Infinity, personMask)) {
					
					for (int i = 0; i < Variables.personList.Count; i++) {
						if (Variables.personList [i].obj == hit.transform.gameObject) {
							
							if (Variables.persTargetNumber == Variables.personList [i].id && i != 0 && Variables.personList[i].live) {
								str = "Attack|" + Variables.persTargetNumber + "|";
								messageReady = true;	

							} else {
								Variables.persTargetNumber = Variables.personList [i].id;

							}
							break;
						}
					}

				} else if (Physics.Raycast (_ray, out hit, Mathf.Infinity, dropItemMask)) {

					for (int i = 0; i < Variables.dropItemList.Count; i++) {
						if (Variables.dropItemList [i].obj == hit.transform.gameObject) {
							
							str = "Pickup|" + Variables.dropItemList [i].id + "|";
							messageReady = true;
							break;
						}
					}

				} else {


					if (Physics.Raycast (_ray, out hit, Mathf.Infinity, moveMask)) {
						str = "Move|" + hit.point.x + "|" + hit.point.y + "|" + hit.point.z + "|";
						messageReady = true;	

					}
				
				}
			}
		} else {
			if (Input.GetMouseButtonUp (1)) {
				if (Variables.curPosType == "Inventory") {
					Connection.Send ("UseItem|" + Variables.curPosNum + "|");
				}
			}
		}
		if (messageReady) {
			
			Connection.Send (str);
		
		}

	}

	public void EndDrag(){
		//PrintS ("END");
	}
	public void BeginDragInventoryButton(int i){
		//PrintS ("BEGIN" + i);
	}

	public void EnterInventoryButton(int i){
		//PrintS ("ENTER" + i);
		Variables.curPosType = "Inventory";
		Variables.curPosNum = i;
	}
	public void ExitInventoryButton(){
		//PrintS ("EXIT");
		Variables.curPosType = "";
		Variables.curPosNum = -1;
	}


}