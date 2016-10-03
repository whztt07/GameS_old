
#include "stdafx.h"


#include "AI.h"


/*
Variables *AI::var;
void AI::Init(Variables *va){
	var = va;
}*/

/*
void AI::AIUPD(){
	EnterCriticalSection(&var->varSection);
	int persCount = var->personList.size();
	for (int i = 0; i < persCount; i++){
		
		int target = var->personList[i].targetNumber;
		int type = var->personList[i].persType;
		if (type == 2 && target != -1 && var->personList[i].status == idle) {
			var->personList[i].data = { target, 0, 0, 0, 0 };
			var->personList[i].command = "Attack";
			
		}
	}
	LeaveCriticalSection(&var->varSection);
}*/