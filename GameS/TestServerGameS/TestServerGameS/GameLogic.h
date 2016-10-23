#include <windows.h>


#include "GeoData.h"
#include "BasePersonHolder.h"
#include "BaseSpellHolder.h"
#include "BaseItemHolder.h"
#include "SpawnPointHolder.h"
#include "PersonHolder.h"
#include "DropItemHolder.h"

class Data;
class MSQL_init_data;
class UpdateData;

class GameLogic{
	
	CRITICAL_SECTION	gameSection;		//������ ��� ����������� �������	
	GeoData				geoData;			//���� ������� ���������� ������ ��� ����������� ����������	
	PersonHolder		personHolder;		//����� ���������� � ���� ������ ���������� � ��������������� ������ ��� ������ � ���	
	BasePersonHolder	basePersonHolder;	//����� ���������� � ���� ������ ������� ���������� � ��������������� ������ ��� ������ � ���
	BaseItemHolder		baseItemHolder;		//����� ���������� � ���� ������ ��������� � ��������������� ������ ��� ������ � ���	
	SpawnPointHolder	spawnPointHolder;	//����� ���������� � ���� ������ ����� �������� � ��������������� ������ ��� ������ � ���
	DropItemHolder		dropItemHolder;		//����� ���������� � ���� ������ �������� ��������� � ��������������� ������ ��� ������ � ���
	BaseSpellHolder		baseSpellHolder;	//����� ���������� � ���� ������ ������ � ��������������� ������ ��� ������ � ���

			
						
	static	unsigned _stdcall	RunUpdate(void *pvoid);	//����� ���������� � ������ ������, ��������� ������ � �����
	
public:
	
	GameLogic(const MSQL_init_data &msql_init_data);
	
	UpdateData		GetUpdateData();											//����� ������������ ������ ����������� ��� ���������� �����

	const Person&	GetBasePerson(int index);
	void			AddPerson(const Person &newPerson);

	string			ResolutionGamePers(const vector<int> &personIdList, int personId);
	string			NeedUpdate(int personId);
	string			NeedUiUpdate(int personId);
	void			Command(const string &command, int personId, const Data &data, bool fast = false);
	void			Exit(int personId);
	
	void			RunThread();												//����� ���������� ��� ������������ ���������� ������

};