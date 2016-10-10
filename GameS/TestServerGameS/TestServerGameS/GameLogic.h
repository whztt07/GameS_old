#include <windows.h>


#include "GeoData.h"
#include "BasePersonHolder.h"
#include "BaseSpellHolder.h"
#include "BaseItemHolder.h"
#include "SpawnPointHolder.h"
#include "PersonHolder.h"

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
	//DropItemHolder		dropItemHolder;		//����� ���������� � ���� ������ �������� ��������� � ��������������� ������ ��� ������ � ���
	BaseSpellHolder		baseSpellHolder;	//����� ���������� � ���� ������ ������ � ��������������� ������ ��� ������ � ���

	
			void				UpdateClientData();				
	static	unsigned _stdcall	RunUpdate(void *pvoid);	//����� ���������� � ������ ������, ��������� ������ � �����
	
public:
	
	GameLogic(const MSQL_init_data &msql_init_data);
	
	UpdateData		GetUpdateData();											//����� ������������ ������ ����������� ��� ���������� �����

	const Person&	GetBasePerson(int index);
	void			AddPerson(const Person &newPerson, int personType = 1);

	string			ResolutionGamePers(const vector<int> &personIdList, int personId);
	string			NeedUPD(int personId);
	string			NeedUI_UPD(int personId);
	void			Command(const string &command, int personId, const Data &data, bool fast = false);
	void			Exit(int personId);
	
	void			RunThread();												//����� ���������� ��� ������������ ���������� ������

};