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
	//—екци€ дл€ безопасного доступа
	CRITICAL_SECTION gameSection;
	// лас геодаты содержащий методы дл€ перемещени€ персонажей
	GeoData geoData;
	//ћетод вызываемый дл€ обновлени€ логики
	void Update();
	//ћетод вызываемый в другом потоке, обновл€ет логику в цикле
	static unsigned _stdcall RunUpdate(void*);

	// ласс содержащий в себе массив персонажей и предоставл€ющий методы дл€ работы с ним
	PersonHolder personHolder;
	// ласс содержащий в себе массив базовых персонажей и предоставл€ющий методы дл€ работы с ним
	BasePersonHolder basePersonHolder;
	// ласс содержащий в себе массив предметов и предоставл€ющий методы дл€ работы с ним
	BaseItemHolder baseItemHolder;
	// ласс содержащий в себе массив точек респавна и предоставл€ющий методы дл€ работы с ним
	SpawnPointHolder spawnPointHolder;
	// ласс содержащий в себе массив выпавших предметов и предоставл€ющий методы дл€ работы с ним
	//DropItemHolder dropItemHolder;
	// ласс содержащий в себе массив спелов и предоставл€ющий методы дл€ работы с ним
	BaseSpellHolder baseSpellHolder;

public:
	
	GameLogic(const MSQL_init_data&);
	//ћетод возвращающий дынные необходимые дл€ обновлени€ формы
	UpdateData GetUpdateData();

	const Person& GetBasePerson(const int&);
	void AddPerson(const Person&, int = 1);

	string ResolutionGamePers(const vector<int>&, const int&);
	string NeedUPD(const int&);
	string NeedUI_UPD(const int&);
	void Command(string, const int&, const Data&, bool = true);
	void Exit(const int&);
	//ћетод запускающий метод обновлени€ в потоке
	void RunThread();

};