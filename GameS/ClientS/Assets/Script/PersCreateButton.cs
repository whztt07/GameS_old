using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PersCreateButton {
	public PersCreateButton(GameObject go){
		obj = go; 
		image = go.GetComponent<Image>();
		button = go.GetComponent<Button> ();
		text = go.transform.FindChild ("Text").GetComponent<Text> ();

	}

	public Button button;
	public GameObject obj;
	public Image image;
	public Text text;

}
