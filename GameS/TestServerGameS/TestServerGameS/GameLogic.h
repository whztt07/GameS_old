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
	
	CRITICAL_SECTION	gameSection;		//—екци€ дл€ безопасного доступа	
	GeoData				geoData;			// лас геодаты содержащий методы дл€ перемещени€ персонажей	
	PersonHolder		personHolder;		// ласс содержащий в себе массив персонажей и предоставл€ющий методы дл€ работы с ним	
	BasePersonHolder	basePersonHolder;	// ласс содержащий в себе массив базовых персонажей и предоставл€ющий методы дл€ работы с ним
	BaseItemHolder		baseItemHolder;		// ласс содержащий в себе массив предметов и предоставл€ющий методы дл€ работы с ним	
	SpawnPointHolder	spawnPointHolder;	// ласс содержащий в себе массив точек респавна и предоставл€ющий методы дл€ работы с ним
	//DropItemHolder		dropItemHolder;		// ласс содержащий в себе массив выпавших предметов и предоставл€ющий методы дл€ работы с ним
	BaseSpellHolder		baseSpellHolder;	// ласс содержащий в себе массив спелов и предоставл€ющий методы дл€ работы с ним

	
			void				Update();			//ћетод вызываемый дл€ обновлени€ логики	
	static	unsigned _stdcall	RunUpdate(void *pvoid);	//ћетод вызываемый в другом потоке, обновл€ет логику в цикле
	
public:
	
	GameLogic(const MSQL_init_data &msql_init_data);
	
	UpdateData		GetUpdateData();											//ћетод возвращающий дынные необходимые дл€ обновлени€ формы

	const Person&	GetBasePerson(int index);
	void			AddPerson(const Person &newPerson, int type = 1);

	string			ResolutionGamePers(const vector<int> &, int);
	string			NeedUPD(int personId);
	string			NeedUI_UPD(int personId);
	void			Command(const string&, int, const Data&, bool = false);
	void			Exit(int);
	
	void			RunThread();												//ћетод запускающий метод обновлени€ в потоке

};