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
	
	CRITICAL_SECTION	gameSection;		//—екци€ дл€ безопасного доступа	
	GeoData				geoData;			// лас геодаты содержащий методы дл€ перемещени€ персонажей	
	PersonHolder		personHolder;		// ласс содержащий в себе массив персонажей и предоставл€ющий методы дл€ работы с ним	
	BasePersonHolder	basePersonHolder;	// ласс содержащий в себе массив базовых персонажей и предоставл€ющий методы дл€ работы с ним
	BaseItemHolder		baseItemHolder;		// ласс содержащий в себе массив предметов и предоставл€ющий методы дл€ работы с ним	
	SpawnPointHolder	spawnPointHolder;	// ласс содержащий в себе массив точек респавна и предоставл€ющий методы дл€ работы с ним
	DropItemHolder		dropItemHolder;		// ласс содержащий в себе массив выпавших предметов и предоставл€ющий методы дл€ работы с ним
	BaseSpellHolder		baseSpellHolder;	// ласс содержащий в себе массив спелов и предоставл€ющий методы дл€ работы с ним

			
						
	static	unsigned _stdcall	RunUpdate(void *pvoid);	//ћетод вызываемый в другом потоке, обновл€ет логику в цикле
	
public:
	
	GameLogic(const MSQL_init_data &msql_init_data);
	
	UpdateData		GetUpdateData();											//ћетод возвращающий дынные необходимые дл€ обновлени€ формы

	const Person&	GetBasePerson(int index);
	void			AddPerson(const Person &newPerson);

	string			ResolutionGamePers(const vector<int> &personIdList, int personId);
	string			NeedUpdate(int personId);
	string			NeedUiUpdate(int personId);
	void			Command(const string &command, int personId, const Data &data, bool fast = false);
	void			Exit(int personId);
	
	void			RunThread();												//ћетод вызываемый дл€ бесконечного обновлени€ логики

};