
class GameLogic;

class Client {
	
	//Метод для отключения клиента и освобождения памяти
	static void Leave(SOCKET);
public:
	//Инициализация 
	static void Init(GameLogic *game);
	//Метод который вызывается в отдельном потоке
	static unsigned _stdcall ToClient(void *);
	//Метод возвращающий к-во клиентов
	static const int GetClientCount();
};