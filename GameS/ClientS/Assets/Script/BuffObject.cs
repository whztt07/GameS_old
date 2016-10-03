using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class BuffObject {

	public BuffObject (GameObject go){
		obj = go;
		image = obj.GetComponent<Image> ();
		transform = obj.transform;
	}

	public GameObject obj;
	public Image image;
	public Transform transform;
}
