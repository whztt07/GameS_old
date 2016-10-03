using UnityEngine;
using System.Collections;

public class AnimationC{

	public static void AnimationUPD(){

		for (int i = 0; i < Variables.personList.Count; i++) {
			if (Variables.personList [i].curLiveStatus != Variables.personList [i].live) {
				Variables.personList [i].curLiveStatus = Variables.personList [i].live;
				if (Variables.personList [i].live) {
					Variables.personList [i].collider.center = new Vector3 (0, 0.9f, 0);
					Variables.personList [i].collider.direction = 1;
				} else {
					Variables.personList [i].collider.center = new Vector3 (0, 0, -0.9f);
					Variables.personList [i].collider.direction = 2;
				}
			}
			switch (Variables.personList [i].animNum) {

			case 0: 
				Variables.personList [i].anim.speed = 1;
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", false);			
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", false);
				break;
			case 1: 
				Variables.personList [i].anim.speed = Variables.personList [i].animSpeed; //2.4f *
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", true);
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", false);
				break;
			case 2: 
				Variables.personList [i].anim.speed = Variables.personList [i].animSpeed; //2.563125f *
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", false);
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", true);
				Variables.personList [i].anim.SetBool ("WarIdle", false);			
				break;
			case 3: 
				Variables.personList [i].anim.speed = 2.267f * Variables.personList [i].animSpeed;
				Variables.personList [i].anim.SetBool ("Attack", true);
				Variables.personList [i].anim.SetBool ("Run", false);			
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", false);
				break;
			case 4: 
				Variables.personList [i].anim.speed = 3.333f * Variables.personList [i].animSpeed;
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", false);			
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", true);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", false);
				break;
			case 5: 
				Variables.personList [i].anim.speed = 2.2f * Variables.personList [i].animSpeed;
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", false);			
				Variables.personList [i].anim.SetBool ("BowA", true);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", false);
				break;
			case 6: 
				Variables.personList [i].anim.speed = 1;
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", false);			
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", true);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", false);
				break;
			case 7: 
				Variables.personList [i].anim.speed = 1;
				Variables.personList [i].anim.SetBool ("Attack", false);
				Variables.personList [i].anim.SetBool ("Run", false);			
				Variables.personList [i].anim.SetBool ("BowA", false);
				Variables.personList [i].anim.SetBool ("Cast", false);
				Variables.personList [i].anim.SetBool ("Dead", false);
				Variables.personList [i].anim.SetBool ("Walk", false);
				Variables.personList [i].anim.SetBool ("WarIdle", true);
				break;
			default:
				break;
			}

		}

	}

}
