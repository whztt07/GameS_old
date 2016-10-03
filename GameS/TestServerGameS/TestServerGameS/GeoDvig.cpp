
#include "stdafx.h"
/*
#include "GeoDvig.h"
#include "Mechanic.h"
#include "GeoData.h"
#include "WorkFile.h"

 
GeoData GeoDvig::geoData;
Variables *GeoDvig::var;

void GeoDvig::Init(Variables* v){
	
	var = v;
	geoData = WorkFile::ReadGeoData();
}

GeoData GeoDvig::GetGeoData(){
	return geoData;
}

float GeoDvig::GeoHeight(Vector3 vector){

	if (vector.z >= 0 && vector.z < geoData.size_z * 4 && vector.x >= 0 && vector.x < geoData.size_x * 4){
		int tarCube_z = vector.z / 4;
		int tarCube_x = vector.x / 4;
		int tarCell_z = (vector.z - tarCube_z * 4) * 2;
		int tarCell_x = (vector.x - tarCube_x * 4) * 2;
		return geoData.geoCubs[tarCube_x * geoData.size_z + tarCube_z].geoCells[tarCell_x * 8 + tarCell_z].height;
	}
	return 0;

}


void GeoDvig::MovePerson(float dlTime, int i){

	
	
	if (!var->personList[i].root){
		var->personList[i].position.y = 0;
		Vector3 direc = var->personList[i].pathList[0] - var->personList[i].position;
		direc.Normalize();
		float distance = Vector3::Distance(var->personList[i].position, var->personList[i].pathList[0]);
		float movDistance = dlTime * var->personList[i].speed;
		if (distance <= movDistance){
			var->personList[i].position = var->personList[i].pathList[0];
			var->personList[i].pathList.erase(var->personList[i].pathList.begin() + 0);
			var->personList[i].position.y = GeoHeight(var->personList[i].position);
			
			if (var->personList[i].pathList.size() == 0){
				var->personList[i].status = idle;
			}
			else{
				switch (var->personList[i].status){
				case _move:
					var->personList[i].status = r_move;
					break;
				case move_attack:
					var->personList[i].status = r_attack;
					break;
				case move_pickup:
					var->personList[i].status = r_pickup;
					break;
				}
			}
		}
		else{
			var->personList[i].position += direc * movDistance;
			var->personList[i].position.y = GeoHeight(var->personList[i].position);
		}

	}
	
	
}


bool GeoDvig::FallingPerson(float dTime, int i){
	
	int perCube_z = var->personList[i].position.z / 4;
	int perCube_x = var->personList[i].position.x / 4;
	int perCell_z = (var->personList[i].position.z - perCube_z * 4) * 2;
	int perCell_x = (var->personList[i].position.x - perCube_x * 4) * 2;

	int nn = 0, ss = 0, ww = 0, ee = 0;

	if (geoData.geoCubs[perCube_x*geoData.size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].north){
		nn = 1;
	}
	if (geoData.geoCubs[perCube_x*geoData.size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].south){
		ss = 1;
	}
	if (geoData.geoCubs[perCube_x*geoData.size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].west){
		ww = 1;
	}
	if (geoData.geoCubs[perCube_x*geoData.size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].east){
		ee = 1;
	}

	if (ee + ww + nn + ss == 4){
		
		var->personList[i].status = idle;
		
	}
	else{
		if (ee + ww + nn + ss > 1){
			Vector3 direc = Vector3();
			if (ee + ww + nn + ss == 3){

				if (nn == 0){
					direc = Vector3(0, 0, 1);
				}
				if (ss == 0){
					direc = Vector3(0, 0, -1);
				}
				if (ww == 0){
					direc = Vector3(-1, 0, 0);
				}
				if (ee == 0){
					direc = Vector3(1, 0, 0);
				}
			}
			else{
				if (ee + ww + nn + ss == 2){

					if (nn + ww == 2){
						direc = Vector3(1, 0, -1);
					}
					if (nn + ee == 2){
						direc = Vector3(-1, 0, -1);
					}
					if (ss + ww == 2){
						direc = Vector3(1, 0, 1);
					}
					if (ss + ee == 2){
						direc = Vector3(-1, 0, 1);
					}
				}
			}
			var->personList[i].stand = false;
			var->personList[i].needPathUPD = true;
			direc.Normalize();
			var->personList[i].position += direc * dTime;
			var->personList[i].position = Vector3(var->personList[i].position.x, GeoHeight(var->personList[i].position), var->personList[i].position.z);

		}
		else{
			var->personList[i].stand = true;
		}
	}
	bool b = var->personList[i].stand;
	
	return b;
	return false;
}

float GeoDvig::GetAngle(Vector3 vec){		
	float angle = (acosf(vec.z) * 180 / System::Math::PI);
	if (vec.x < 0){
		angle += (180 - angle) * 2;
	}
	return angle;
}

void GeoDvig::NeedPersonPath(int num, Vector3 movePosition){
	
	if (movePosition.z >= 0 && movePosition.z < geoData.size_z * 4 && movePosition.x >= 0 && movePosition.x < geoData.size_x * 4){
		int **ipath;
		ipath = new int*[geoData.size_z * 8];
		for (int i = 0; i < geoData.size_z * 8; i++){
			ipath[i] = new int[geoData.size_x * 8];
			for (int j = 0; j < geoData.size_x * 8; j++){
				ipath[i][j] = -1;
			}
		}
		int tarCube_z = movePosition.z / 4;
		int tarCube_x = movePosition.x / 4;
		int tarCell_z = (movePosition.z - tarCube_z * 4) * 2;
		int tarCell_x = (movePosition.x - tarCube_x * 4) * 2;

		int perCube_z = var->personList[num].position.z / 4;
		int perCube_x = var->personList[num].position.x / 4;
		int perCell_z = (var->personList[num].position.z - perCube_z * 4) * 2;
		int perCell_x = (var->personList[num].position.x - perCube_x * 4) * 2;

		ipath[perCube_z * 8 + perCell_z][perCube_x * 8 + perCell_x] = 0;

		for (int kl = 0; kl < 100; kl++) {
			for (int ci = 0; ci < geoData.size_x; ci++) {
				for (int cj = 0; cj < geoData.size_z; cj++) {
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (ipath[cj * 8 + j][ci * 8 + i] == kl) {
								if (cj == tarCube_z && ci == tarCube_x && j == tarCell_z && i == tarCell_x) {
									i = 100;
									j = 100;
									ci = 100;
									cj = 100;
									kl = 1000;
									break;
								}
								else {
									if ((j > 0 || cj > 0) && ipath[cj * 8 + j - 1][ci * 8 + i] == -1 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j].south) {
										ipath[cj * 8 + j - 1][ci * 8 + i] = kl + 1;
									}
									if (((j < 7 || cj + 1 < geoData.size_z) && ipath[cj * 8 + j + 1][ci * 8 + i] == -1 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j].north)) {
										ipath[cj * 8 + j + 1][ci * 8 + i] = kl + 1;
									}
									if ((i > 0 || ci > 0) && ipath[cj * 8 + j][ci * 8 + i - 1] == -1 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j].west) {
										ipath[cj * 8 + j][ci * 8 + i - 1] = kl + 1;
									}
									if ((i < 7 || ci + 1 < geoData.size_x) && ipath[cj * 8 + j][ci * 8 + i + 1] == -1 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j].east) {
										ipath[cj * 8 + j][ci * 8 + i + 1] = kl + 1;
									}
									if ((i > 0 || ci > 0) && ipath[cj * 8 + j][ci * 8 + i - 1] == kl + 1) {
										if ((j > 0 || cj > 0) && ipath[cj * 8 + j - 1][ci * 8 + i] == kl + 1) {
											if (((j > 0 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j - 1].west) || (j == 0 && !geoData.geoCubs[ci*geoData.size_z + cj - 1].geoCells[i * 8 + 7].west))
												&& ((i > 0 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[(i - 1) * 8 + j].south) || (i == 0 && !geoData.geoCubs[(ci - 1)*geoData.size_z + cj].geoCells[7 * 8 + j].south))){
												ipath[cj * 8 + j - 1][ci * 8 + i - 1] = kl + 1;
											}
										}
										if ((j < 7 || cj + 1 < geoData.size_z) && ipath[cj * 8 + j + 1][ci * 8 + i] == kl + 1) {
											if (((j < 7 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j + 1].west) || (j == 7 && !geoData.geoCubs[ci*geoData.size_z + cj + 1].geoCells[i * 8 + 0].west))
												&& ((i > 0 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[(i - 1) * 8 + j].north) || (i == 0 && !geoData.geoCubs[(ci - 1)*geoData.size_z + cj].geoCells[7 * 8 + j].north))){
												ipath[cj * 8 + j + 1][ci * 8 + i - 1] = kl + 1;
											}
										}
									}
									if ((i < 7 || ci + 1 < geoData.size_x) && ipath[cj * 8 + j][ci * 8 + i + 1] == kl + 1) {
										if ((j > 0 || cj > 0) && ipath[cj * 8 + j - 1][ci * 8 + i] == kl + 1) {
											if (((j > 0 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j - 1].east) || (j == 0 && !geoData.geoCubs[ci*geoData.size_z + cj - 1].geoCells[i * 8 + 7].east))
												&& ((i < 7 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[(i + 1) * 8 + j].south) || (i == 7 && !geoData.geoCubs[(ci + 1)*geoData.size_z + cj].geoCells[0 * 8 + j].south))){
												ipath[cj * 8 + j - 1][ci * 8 + i + 1] = kl + 1;
											}
										}
										if ((j < 7 || cj + 1 < geoData.size_z) && ipath[cj * 8 + j + 1][ci * 8 + i] == kl + 1) {
											if (((j < 7 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[i * 8 + j + 1].east) || (j == 7 && !geoData.geoCubs[ci*geoData.size_z + cj + 1].geoCells[i * 8 + 0].east))
												&& ((i < 7 && !geoData.geoCubs[ci*geoData.size_z + cj].geoCells[(i + 1) * 8 + j].north) || (i == 7 && !geoData.geoCubs[(ci + 1)*geoData.size_z + cj].geoCells[0 * 8 + j].north))){
												ipath[cj * 8 + j + 1][ci * 8 + i + 1] = kl + 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		int cx = tarCube_x * 8 + tarCell_x, cz = tarCube_z * 8 + tarCell_z;
		std::vector<Vector3> vec;
		for (int pl = ipath[cz][cx]; pl > -1; pl--) {
			vec.push_back(Vector3(((float)cx / 2) + 0.25, 0, ((float)cz / 2) + 0.25));
			if (cz > 0 && pl > 0 && ipath[cz - 1][cx] == pl - 1 && !geoData.geoCubs[((int)(cx / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[(cx % 8) * 8 + ((cz - 1) % 8)].north) {
				cz--;
			}
			else{
				if (cz + 1 < (geoData.size_z + 1) * 8 && pl > 0 && ipath[cz + 1][cx] == pl - 1 && !geoData.geoCubs[((int)(cx / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[(cx % 8) * 8 + ((cz + 1) % 8)].south) {
					cz++;
				}
				else{
					if (cx > 0 && pl > 0 && ipath[cz][cx - 1] == pl - 1 && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)(cz / 8)].geoCells[((cx - 1) % 8) * 8 + (cz % 8)].east) {
						cx--;
					}
					else{
						if (cx + 1 < (geoData.size_x + 1) * 8 && pl > 0 && ipath[cz][cx + 1] == pl - 1 && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)(cz / 8)].geoCells[((cx + 1) % 8) * 8 + (cz % 8)].west) {
							cx++;
						}
						else{
							if (cz > 0 && cx > 0 && pl > 0 && ipath[cz - 1][cx - 1] == pl - 1 && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz - 1) % 8)].north && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz - 1) % 8)].east && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)((cz) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz) % 8)].east && !geoData.geoCubs[((int)((cx) / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz - 1) % 8)].north) {
								cx--;
								cz--;
							}
							else{
								if (cz + 1 < (geoData.size_z + 1) * 8 && cx > 0 && pl > 0 && ipath[cz + 1][cx - 1] == pl - 1 && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz + 1) % 8)].south && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz + 1) % 8)].east && !geoData.geoCubs[((int)((cx - 1) / 8))*geoData.size_z + (int)((cz) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz) % 8)].east && !geoData.geoCubs[((int)((cx) / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz + 1) % 8)].south) {
									cx--;
									cz++;
								}
								else{
									if (cx + 1 < (geoData.size_x + 1) * 8 && cz > 0 && pl > 0 && ipath[cz - 1][cx + 1] == pl - 1 && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz - 1) % 8)].north && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz - 1) % 8)].west && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)((cz) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz) % 8)].west && !geoData.geoCubs[((int)((cx) / 8))*geoData.size_z + (int)((cz - 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz - 1) % 8)].north) {
										cz--;
										cx++;
									}
									else{
										if (cx + 1 < (geoData.size_x + 1) * 8 && cz + 1 < (geoData.size_z + 1) * 8 && pl > 0 && ipath[cz + 1][cx + 1] == pl - 1 && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz + 1) % 8)].south && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz + 1) % 8)].west && !geoData.geoCubs[((int)((cx + 1) / 8))*geoData.size_z + (int)((cz) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz) % 8)].west && !geoData.geoCubs[((int)((cx) / 8))*geoData.size_z + (int)((cz + 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz + 1) % 8)].south) {
											cz++;
											cx++;
										}

									}
								}
							}
						}
					}
				}
			}

		}

		vec[0] = Vector3(movePosition.x, 0, movePosition.z);
		vec.erase(vec.end() - 1);
		var->personList[num].pathList.clear();
		for (int i = 0; i < vec.size(); i++){
			var->personList[num].pathList.push_back(vec[vec.size() - 1 - i]);
		}


	}
	
}


void GeoDvig::SetRotation(int i, float rot){
	if (rot >= 360)
		rot -= 360;
	if (rot < 0)
		rot += 360;
	var->personList[i].rotation.y = rot;
}

int GeoDvig::GetIndex(int j){
	for (int i = 0; i < var->personList.size(); i++){
		if (var->personList[i].persID == j){
			return i;
		}
	}
	return -1;
}

int GeoDvig::GetItemIndex(int j){
	for (int i = 0; i < var->dropItemList.size(); i++){
		if (var->dropItemList[i].id == j){
			return i;
		}
	}
	return -1;
}

void GeoDvig::MoveRotation(float dTime, int i){
	Vector3 pos = var->personList[i].position;
	pos.y = 0;
	Vector3 direc = var->personList[i].pathList[0] - pos;
	direc.Normalize();
	float angle = GetAngle(direc);
	if (var->personList[i].rotation.y != angle){
		Rotate(dTime, i, angle);
	}
	else{
		switch (var->personList[i].status){
		case r_move:
			var->personList[i].status = _move;
			break;
		case r_attack:
			var->personList[i].status = move_attack;
			break;
		case r_pickup:
			var->personList[i].status = move_pickup;
			break;
		}
	}
	
}

void GeoDvig::Rotate(float dTime, int i, float angle){
	
	float diffAngle = angle - var->personList[i].rotation.y;
	float dopDiffAngle = fabsf(diffAngle);
	if (dopDiffAngle > 180){
		dopDiffAngle = 360 - 180;
	}
	float rotAngle = var->personList[i].rotationSpeed * dTime;
	if (dopDiffAngle <= rotAngle){
		SetRotation(i, angle);
	}
	else{
		float angleDirec = 1;
		if (diffAngle > 180 || (diffAngle < 0 && diffAngle > -180)){
			angleDirec = -1;
		}
		SetRotation(i, var->personList[i].rotation.y + rotAngle * angleDirec);
	}
}

void GeoDvig::TargetRotation(float dTime, int j){


	Vector3 direc = var->personList[GetIndex(var->personList[j].targetNumber)].position - var->personList[j].position;
	direc.Normalize();
	float angle = GetAngle(direc);


	if (var->personList[j].rotation.y != angle){
		Rotate(dTime, j, angle);
	}
	else{
		var->personList[j].status = attack;
	}
}
	
	
void GeoDvig::TargetDoesRotation(float dTime, int j){
	
	Vector3 direc = var->personList[GetIndex(var->personList[j].targetNumber)].position - var->personList[j].position;
	direc.Normalize();
	float angle = GetAngle(direc);
	if (var->personList[j].rotation.y != angle){
		Rotate(dTime, j, angle);
	}
	
}


void GeoDvig::TargetItemRotation(float dTime, int j){
	
	
	Vector3 direc = var->dropItemList[GetItemIndex(var->personList[j].pickupNumber)].position - var->personList[j].position;
	direc.Normalize();
	float angle = GetAngle(direc);


	if (var->personList[j].rotation.y != angle){
		Rotate(dTime, j, angle);
	}
	else{
		var->personList[j].status = pickup;
	}
	
}*/