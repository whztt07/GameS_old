using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class PersChoiceButton  {
	public PersChoiceButton(GameObject go){
		obj = go; 
		image = go.GetComponent<Image>();
		button = go.GetComponent<Button> ();
		nameText = go.transform.FindChild ("NameText").GetComponent<Text> ();
		raceText = go.transform.FindChild ("RaceText").GetComponent<Text> ();
	}

	public Button button;
	public GameObject obj;
	public Image image;
	public Text nameText, raceText;
}
