
class GameLogic;

class Client {
	
public:
	
	static void					Init(GameLogic &game);	//������������� 	
	static unsigned _stdcall	ToClient(void *pvoid);	//����� ������� ���������� � ��������� ������	
	static int					GetClientCount();		//����� ������������ �-�� ��������
};