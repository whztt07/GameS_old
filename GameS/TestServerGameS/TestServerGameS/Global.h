#pragma once
//Параметры Mastery
#define MASTERY_COUNT 10
#define MASTERY_MAX_LVL 5
#define MASTERY_EXP_ARRAY  0, 20, 30, 20, 70, 60, 100

#define SPELL_COUNT 44
#define ABILITY_COUNT 20
#define BUFF_COUNT 10
#define DEBUFF_COUNT 10

#define INVENTORY_SIZE 20
//Время после которого связь с клентом закрывается в милисекундах
#define MAX_WAIT_CLIENT_TIME 10000
//Порт с которого начинается поиск свободного для клиента
#define BEGIN_PORT 11001
//Размер буффера для приходящих сообщений от клиентов
#define CLIENT_BUFFER_SIZE 1024
//Порт на который приходят все запросы на подключение
#define MAIN_PORT    11000


#define NPC_PATROL_RANGE 5
#define NPC_SPAWN_RANGE 5


enum PersonStatus{
	idle = 0,
	r_move = 1,
	_move = 2,
	r_walk = 3,
	walk = 4,
	r_attack = 5,
	move_attack = 6,
	attack = 7,
	r_cast = 8,
	move_cast = 9,
	cast = 10,
	useItem = 11,
	r_pickup = 12,
	move_pickup = 13,
	pickup = 14,
	res = 15,
	dropitem = 16,
	r_dialog = 17,
	move_dialog = 18,
	dialog = 19,
	answer = 20,
	statsUp = 21,
	learn = 22,
	dead = 23,
	resplace = 24
};

enum AnimationStatus{
	animIdle = 0,
	animRun = 1,
	animWalk = 2,
	animAttack = 3,
	animCast = 4,
	animRangeAttack = 5,
	animDead = 6,
	animWarIdle = 7
};

