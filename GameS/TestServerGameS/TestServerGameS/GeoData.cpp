#include "stdafx.h"

#include <vector>

#include "GeoData.h"
#include "Person.h"
#include "Vector3.h"
#include "Global.h"
using namespace std;

GeoData::GeoData() : size_x(), size_z(){}

GeoData::GeoData(const GeoData &geo) : size_x(geo.size_x), size_z(geo.size_z), geoCubs(geo.geoCubs){}

float GeoData::GeoHeight(const Vector3 &position) const{

	if (position.z >= 0 && position.z < size_z * 4 && position.x >= 0 && position.x < size_x * 4){
		int tarCube_z = position.z / 4;
		int tarCube_x = position.x / 4;
		int tarCell_z = (position.z - tarCube_z * 4) * 2;
		int tarCell_x = (position.x - tarCube_x * 4) * 2;
		return geoCubs[tarCube_x * size_z + tarCube_z].geoCells[tarCell_x * 8 + tarCell_z].height;
	}
	return 0;

}


void GeoData::MovePerson(float deltaTime, Person &person) const{
	
	if (!person.GetRoot()){
		Vector3 position = person.GetPosition();
		position.y = 0;
		Vector3 endPosition = person.GetFirstPath();
		Vector3 direc = endPosition - position;
		direc.Normalize();
		float distance = Vector3::Distance(position, endPosition);
		float movDistance = deltaTime * person.GetSpeed();
		if (distance <= movDistance){
			position = endPosition;
			person.DeleteFirstPath();
			position.y = GeoHeight(position);

			if (person.GetPathListSize() == 0){
				person.SetStatus(idle);
			}
			else{
				switch (person.GetStatus()){
				case _move:
					person.SetStatus(r_move);
					break;
				case move_attack:
					person.SetStatus(r_attack);
					break;
				case move_pickup:
					person.SetStatus(r_pickup);
					break;
				}
			}
		}
		else{
			position += direc * movDistance;
			position.y = GeoHeight(position);
		}
		person.SetPosition(position);
	}
}



bool GeoData::FallingPerson(float dTime, Person &person) const{
	Vector3 position = person.GetPosition();
	int perCube_z = position.z / 4;
	int perCube_x = position.x / 4;
	int perCell_z = (position.z - perCube_z * 4) * 2;
	int perCell_x = (position.x - perCube_x * 4) * 2;

	int nn = 0, ss = 0, ww = 0, ee = 0;

	if (geoCubs[perCube_x*size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].north){
		nn = 1;
	}
	if (geoCubs[perCube_x*size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].south){
		ss = 1;
	}
	if (geoCubs[perCube_x*size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].west){
		ww = 1;
	}
	if (geoCubs[perCube_x*size_z + perCube_z].geoCells[perCell_x * 8 + perCell_z].east){
		ee = 1;
	}
	bool stand = true;
	if (ee + ww + nn + ss == 4){

		person.SetStatus(idle);
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
			stand = false;
			person.SetNeedPathUpdate(true);
			direc.Normalize();
			position += direc * dTime;
			position.y = GeoHeight(position);
			person.SetPosition(position);
		}
	}
	person.SetStand(stand);
	
	return stand;
}

float GeoData::GetAngle(const Vector3 &position) const{
	float angle = (acosf(position.z) * 180 / System::Math::PI);
	if (position.x < 0){
		angle += (180 - angle) * 2;
	}
	return angle;
}


void GeoData::NeedPersonPath(Person &person, const Vector3 &movePosition) const{
	
	Vector3 position = person.GetPosition();
	if (movePosition.z >= 0 && movePosition.z < size_z * 4 && movePosition.x >= 0 && movePosition.x < size_x * 4){
		int **ipath;
		ipath = new int*[size_z * 8];
		for (int i = 0; i < size_z * 8; i++){
			ipath[i] = new int[size_x * 8];
			for (int j = 0; j < size_x * 8; j++){
				ipath[i][j] = -1;
			}
		}
		int tarCube_z = movePosition.z / 4;
		int tarCube_x = movePosition.x / 4;
		int tarCell_z = (movePosition.z - tarCube_z * 4) * 2;
		int tarCell_x = (movePosition.x - tarCube_x * 4) * 2;

		int perCube_z = position.z / 4;
		int perCube_x = position.x / 4;
		int perCell_z = (position.z - perCube_z * 4) * 2;
		int perCell_x = (position.x - perCube_x * 4) * 2;

		ipath[perCube_z * 8 + perCell_z][perCube_x * 8 + perCell_x] = 0;

		for (int kl = 0; kl < 100; kl++) {
			for (int ci = 0; ci < size_x; ci++) {
				for (int cj = 0; cj < size_z; cj++) {
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
									if ((j > 0 || cj > 0) && ipath[cj * 8 + j - 1][ci * 8 + i] == -1 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j].south) {
										ipath[cj * 8 + j - 1][ci * 8 + i] = kl + 1;
									}
									if (((j < 7 || cj + 1 < size_z) && ipath[cj * 8 + j + 1][ci * 8 + i] == -1 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j].north)) {
										ipath[cj * 8 + j + 1][ci * 8 + i] = kl + 1;
									}
									if ((i > 0 || ci > 0) && ipath[cj * 8 + j][ci * 8 + i - 1] == -1 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j].west) {
										ipath[cj * 8 + j][ci * 8 + i - 1] = kl + 1;
									}
									if ((i < 7 || ci + 1 < size_x) && ipath[cj * 8 + j][ci * 8 + i + 1] == -1 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j].east) {
										ipath[cj * 8 + j][ci * 8 + i + 1] = kl + 1;
									}
									if ((i > 0 || ci > 0) && ipath[cj * 8 + j][ci * 8 + i - 1] == kl + 1) {
										if ((j > 0 || cj > 0) && ipath[cj * 8 + j - 1][ci * 8 + i] == kl + 1) {
											if (((j > 0 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j - 1].west) || (j == 0 && !geoCubs[ci*size_z + cj - 1].geoCells[i * 8 + 7].west))
												&& ((i > 0 && !geoCubs[ci*size_z + cj].geoCells[(i - 1) * 8 + j].south) || (i == 0 && !geoCubs[(ci - 1)*size_z + cj].geoCells[7 * 8 + j].south))){
												ipath[cj * 8 + j - 1][ci * 8 + i - 1] = kl + 1;
											}
										}
										if ((j < 7 || cj + 1 < size_z) && ipath[cj * 8 + j + 1][ci * 8 + i] == kl + 1) {
											if (((j < 7 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j + 1].west) || (j == 7 && !geoCubs[ci*size_z + cj + 1].geoCells[i * 8 + 0].west))
												&& ((i > 0 && !geoCubs[ci*size_z + cj].geoCells[(i - 1) * 8 + j].north) || (i == 0 && !geoCubs[(ci - 1)*size_z + cj].geoCells[7 * 8 + j].north))){
												ipath[cj * 8 + j + 1][ci * 8 + i - 1] = kl + 1;
											}
										}
									}
									if ((i < 7 || ci + 1 < size_x) && ipath[cj * 8 + j][ci * 8 + i + 1] == kl + 1) {
										if ((j > 0 || cj > 0) && ipath[cj * 8 + j - 1][ci * 8 + i] == kl + 1) {
											if (((j > 0 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j - 1].east) || (j == 0 && !geoCubs[ci*size_z + cj - 1].geoCells[i * 8 + 7].east))
												&& ((i < 7 && !geoCubs[ci*size_z + cj].geoCells[(i + 1) * 8 + j].south) || (i == 7 && !geoCubs[(ci + 1)*size_z + cj].geoCells[0 * 8 + j].south))){
												ipath[cj * 8 + j - 1][ci * 8 + i + 1] = kl + 1;
											}
										}
										if ((j < 7 || cj + 1 < size_z) && ipath[cj * 8 + j + 1][ci * 8 + i] == kl + 1) {
											if (((j < 7 && !geoCubs[ci*size_z + cj].geoCells[i * 8 + j + 1].east) || (j == 7 && !geoCubs[ci*size_z + cj + 1].geoCells[i * 8 + 0].east))
												&& ((i < 7 && !geoCubs[ci*size_z + cj].geoCells[(i + 1) * 8 + j].north) || (i == 7 && !geoCubs[(ci + 1)*size_z + cj].geoCells[0 * 8 + j].north))){
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
			if (cz > 0 && pl > 0 && ipath[cz - 1][cx] == pl - 1 && !geoCubs[((int)(cx / 8))*size_z + (int)((cz - 1) / 8)].geoCells[(cx % 8) * 8 + ((cz - 1) % 8)].north) {
				cz--;
			}
			else{
				if (cz + 1 < (size_z + 1) * 8 && pl > 0 && ipath[cz + 1][cx] == pl - 1 && !geoCubs[((int)(cx / 8))*size_z + (int)((cz + 1) / 8)].geoCells[(cx % 8) * 8 + ((cz + 1) % 8)].south) {
					cz++;
				}
				else{
					if (cx > 0 && pl > 0 && ipath[cz][cx - 1] == pl - 1 && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)(cz / 8)].geoCells[((cx - 1) % 8) * 8 + (cz % 8)].east) {
						cx--;
					}
					else{
						if (cx + 1 < (size_x + 1) * 8 && pl > 0 && ipath[cz][cx + 1] == pl - 1 && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)(cz / 8)].geoCells[((cx + 1) % 8) * 8 + (cz % 8)].west) {
							cx++;
						}
						else{
							if (cz > 0 && cx > 0 && pl > 0 && ipath[cz - 1][cx - 1] == pl - 1 && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)((cz - 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz - 1) % 8)].north && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)((cz - 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz - 1) % 8)].east && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)((cz) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz) % 8)].east && !geoCubs[((int)((cx) / 8))*size_z + (int)((cz - 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz - 1) % 8)].north) {
								cx--;
								cz--;
							}
							else{
								if (cz + 1 < (size_z + 1) * 8 && cx > 0 && pl > 0 && ipath[cz + 1][cx - 1] == pl - 1 && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)((cz + 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz + 1) % 8)].south && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)((cz + 1) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz + 1) % 8)].east && !geoCubs[((int)((cx - 1) / 8))*size_z + (int)((cz) / 8)].geoCells[((cx - 1) % 8) * 8 + ((cz) % 8)].east && !geoCubs[((int)((cx) / 8))*size_z + (int)((cz + 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz + 1) % 8)].south) {
									cx--;
									cz++;
								}
								else{
									if (cx + 1 < (size_x + 1) * 8 && cz > 0 && pl > 0 && ipath[cz - 1][cx + 1] == pl - 1 && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)((cz - 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz - 1) % 8)].north && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)((cz - 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz - 1) % 8)].west && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)((cz) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz) % 8)].west && !geoCubs[((int)((cx) / 8))*size_z + (int)((cz - 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz - 1) % 8)].north) {
										cz--;
										cx++;
									}
									else{
										if (cx + 1 < (size_x + 1) * 8 && cz + 1 < (size_z + 1) * 8 && pl > 0 && ipath[cz + 1][cx + 1] == pl - 1 && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)((cz + 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz + 1) % 8)].south && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)((cz + 1) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz + 1) % 8)].west && !geoCubs[((int)((cx + 1) / 8))*size_z + (int)((cz) / 8)].geoCells[((cx + 1) % 8) * 8 + ((cz) % 8)].west && !geoCubs[((int)((cx) / 8))*size_z + (int)((cz + 1) / 8)].geoCells[((cx) % 8) * 8 + ((cz + 1) % 8)].south) {
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
		vector<Vector3> pathList;
		for (int i = 0; i < vec.size(); i++){
			pathList.push_back(vec[vec.size() - 1 - i]);
		}
		person.SetPathList(pathList);

	}

}

float GeoData::GetRotation(float angle) const{
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return angle;
}


void GeoData::Rotate(float deltaTime, float angle, Person &person) const{

	float diffAngle = angle - person.GetRotation();
	float dopDiffAngle = fabsf(diffAngle);
	if (dopDiffAngle > 180){
		dopDiffAngle = 360 - 180;
	}
	float rotAngle = person.GetRotationSpeed() * deltaTime;
	if (dopDiffAngle <= rotAngle){
		person.SetRotation(GetRotation(angle));
	}
	else{
		float angleDirec = 1;
		if (diffAngle > 180 || (diffAngle < 0 && diffAngle > -180)){
			angleDirec = -1;
		}
		person.SetRotation(GetRotation(person.GetRotation() + rotAngle * angleDirec));
	}
}

void GeoData::MoveRotation(float deltaTime, Person &person) const{
	Vector3 pos = person.GetPosition();
	pos.y = 0;
	Vector3 direc = person.GetFirstPath() - pos;
	direc.Normalize();
	float angle = GetAngle(direc);
	if (person.GetRotation() != angle){
		Rotate(deltaTime, angle, person);
	}
	else{
		switch (person.GetStatus()){
		case r_move:
			person.SetStatus(_move);
			break;
		case r_attack:
			person.SetStatus(move_attack);
			break;
		case r_pickup:
			person.SetStatus(move_pickup);
			break;
		}
	}

}

void GeoData::SetSizeX(int newSizeX){
	size_x = newSizeX;
}

void GeoData::SetSizeZ(int newSizeZ){
	size_z = newSizeZ;
}

void GeoData::AddGeoCub(const GeoCube &newGeoCub){
	geoCubs.push_back(newGeoCub);
}