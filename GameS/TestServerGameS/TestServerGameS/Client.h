
class GameLogic;

class Client {
	
	//����� ��� ���������� ������� � ������������ ������
	static void Leave(SOCKET);
public:
	//������������� 
	static void Init(GameLogic *game);
	//����� ������� ���������� � ��������� ������
	static unsigned _stdcall ToClient(void *);
	//����� ������������ �-�� ��������
	static const int GetClientCount();
};