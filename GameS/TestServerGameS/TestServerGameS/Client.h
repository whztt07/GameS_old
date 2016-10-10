
class GameLogic;

class Client {
	
public:
	
	static void					Init(GameLogic &game);	//Инициализация 	
	static unsigned _stdcall	ToClient(void *pvoid);	//Метод который вызывается в отдельном потоке	
	static int					GetClientCount();		//Метод возвращающий к-во клиентов
};