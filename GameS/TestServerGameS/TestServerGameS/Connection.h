#include <winsock2.h>  


using namespace std;

class GameLogic;

class Connection {
	
	static SOCKET Socket;	//Соккет для общего приема
	
	static unsigned _stdcall ConnectMy(void *pvoid);	//Метод выполняемый в другом потоке
public:
	
	static void	Init(GameLogic &game);	//Инициализация	
	static int	GetClientCount();		//Метод возвращающий колличество подключенных клиентов
	static void	RunThread();			//Метод запускающий поток
};