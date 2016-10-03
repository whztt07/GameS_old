using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class PanelButton {

	public PanelButton(GameObject go){
		obj = go; transform = obj.transform; button = obj.GetComponent<Button> (); eventTrigger = obj.GetComponent<EventTrigger> (); buttonImage = obj.GetComponent<Image> ();
		cooldownImage = obj.GetComponentInChildren <Image> ();
	}

	public GameObject obj;
	public Transform transform;
	public Image buttonImage, cooldownImage;
	public Button button;
	public EventTrigger eventTrigger;

}
