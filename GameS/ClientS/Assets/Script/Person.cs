using UnityEngine;
using System.Collections;

public class Person {
	public Person (GameObject go){
		obj = go;
		transform = obj.transform;
		battle = false;
		anim = obj.GetComponent<Animator> ();
		curLiveStatus = true;
		collider = obj.GetComponent<CapsuleCollider> ();
	}
	public CapsuleCollider collider;
	public Animator anim;
	public GameObject obj;
	public Transform transform;
	public bool live, battle, corpseSave, resInPlace, curLiveStatus;
	public string name;
	public int id, weaponSlot, bodySlot, animNum;
	public float curMP, maxMP, curHP, maxHP, fillAmountImage, animSpeed;
}
