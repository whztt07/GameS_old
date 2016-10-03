using UnityEngine;
using System.Collections;

public class MyCamera : MonoBehaviour {
	public Camera _camera;
	Transform cameraTransform,thisTransform;
	const float rad= 0.01745329251f;
	float distanse = 9,rotat_y=20,rotat_x=0;
	public float speedRot=3;
	bool keyDown = false;


	// Use this for initialization
	void Start () {
		if (!_camera) {
			_camera = Camera.main;		
		}
		cameraTransform = _camera.transform;

	}

	// Update is called once per frame
	void Update () {
		if (Variables.personList.Count > 0) {
			thisTransform = Variables.personList [0].transform;
			distanse += Input.GetAxis ("Mouse ScrollWheel") * speedRot;
			if (distanse > 9) {
				distanse = 9;
			}
			if (distanse < 1) {
				distanse = 1;
			}
			if (Input.GetMouseButtonDown (1) && !UnityEngine.EventSystems.EventSystem.current.IsPointerOverGameObject ()) {
				keyDown = true;
			}
			if (Input.GetMouseButtonUp (1)) {
				keyDown = false;
			}
			if (keyDown) {
				rotat_y = cameraTransform.rotation.eulerAngles.x - Input.GetAxis ("Mouse Y") * speedRot;
				if (rotat_y > 85 && rotat_y <= 180) {
					rotat_y = 85;
				}
				if (rotat_y > 180 && rotat_y < 275) {
					rotat_y = 275;
				}
				rotat_x = cameraTransform.rotation.eulerAngles.y + Input.GetAxis ("Mouse X") * speedRot;
			}
			cameraTransform.rotation = Quaternion.Euler (rotat_y, rotat_x, 0);
			cameraTransform.position = new Vector3 (thisTransform.position.x - distanse * Mathf.Sin (cameraTransform.rotation.eulerAngles.y * rad) * Mathf.Cos (cameraTransform.rotation.eulerAngles.x * rad), thisTransform.position.y + distanse * Mathf.Sin (cameraTransform.rotation.eulerAngles.x * rad), thisTransform.position.z - distanse * Mathf.Cos (cameraTransform.rotation.eulerAngles.y * rad) * Mathf.Cos (cameraTransform.rotation.eulerAngles.x * rad));
		}
	}

	public void Reset(){
		cameraTransform.position = new Vector3 (0, 1, -10);
		cameraTransform.rotation = Quaternion.Euler (Vector3.zero);
	}
}
