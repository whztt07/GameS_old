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

	
			void				Update();			//����� ���������� ��� ���������� ������	
	static	unsigned _stdcall	RunUpdate(void *pvoid);	//����� ���������� � ������ ������, ��������� ������ � �����
	
public:
	
	GameLogic(const MSQL_init_data &msql_init_data);
	
	UpdateData		GetUpdateData();											//����� ������������ ������ ����������� ��� ���������� �����

	const Person&	GetBasePerson(int index);
	void			AddPerson(const Person &newPerson, int type = 1);

	string			ResolutionGamePers(const vector<int> &, int);
	string			NeedUPD(int personId);
	string			NeedUI_UPD(int personId);
	void			Command(const string&, int, const Data&, bool = false);
	void			Exit(int);
	
	void			RunThread();												//����� ����������� ����� ���������� � ������

};