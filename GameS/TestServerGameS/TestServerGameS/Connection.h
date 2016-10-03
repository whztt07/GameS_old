#include <winsock2.h>  


using namespace std;

class GameLogic;

class Connection {
	//Соккет для общего приема
	static SOCKET Socket;
	//Метод выполняемый в другом потоке
	static unsigned _stdcall ConnectMy(void*);
public:
	//Инициализация
	static void Init(GameLogic *game);
	//Метод возвращающий колличество подключенных клиентов
	static const int GetClientCount();
	//Метод запускающий поток
	static void RunThread();
};