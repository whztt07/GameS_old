#include <winsock2.h>  


using namespace std;

class GameLogic;

class Connection {
	//������ ��� ������ ������
	static SOCKET Socket;
	//����� ����������� � ������ ������
	static unsigned _stdcall ConnectMy(void*);
public:
	//�������������
	static void Init(GameLogic *game);
	//����� ������������ ����������� ������������ ��������
	static const int GetClientCount();
	//����� ����������� �����
	static void RunThread();
};