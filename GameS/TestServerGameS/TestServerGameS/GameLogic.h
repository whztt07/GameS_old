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
	//������ ��� ����������� �������
	CRITICAL_SECTION gameSection;
	//���� ������� ���������� ������ ��� ����������� ����������
	GeoData geoData;
	//����� ���������� ��� ���������� ������
	void Update();
	//����� ���������� � ������ ������, ��������� ������ � �����
	static unsigned _stdcall RunUpdate(void*);

	//����� ���������� � ���� ������ ���������� � ��������������� ������ ��� ������ � ���
	PersonHolder personHolder;
	//����� ���������� � ���� ������ ������� ���������� � ��������������� ������ ��� ������ � ���
	BasePersonHolder basePersonHolder;
	//����� ���������� � ���� ������ ��������� � ��������������� ������ ��� ������ � ���
	BaseItemHolder baseItemHolder;
	//����� ���������� � ���� ������ ����� �������� � ��������������� ������ ��� ������ � ���
	SpawnPointHolder spawnPointHolder;
	//����� ���������� � ���� ������ �������� ��������� � ��������������� ������ ��� ������ � ���
	//DropItemHolder dropItemHolder;
	//����� ���������� � ���� ������ ������ � ��������������� ������ ��� ������ � ���
	BaseSpellHolder baseSpellHolder;

public:
	
	GameLogic(const MSQL_init_data&);
	//����� ������������ ������ ����������� ��� ���������� �����
	UpdateData GetUpdateData();

	const Person& GetBasePerson(const int&);
	void AddPerson(const Person&, int = 1);

	string ResolutionGamePers(const vector<int>&, const int&);
	string NeedUPD(const int&);
	string NeedUI_UPD(const int&);
	void Command(string, const int&, const Data&, bool = true);
	void Exit(const int&);
	//����� ����������� ����� ���������� � ������
	void RunThread();

};