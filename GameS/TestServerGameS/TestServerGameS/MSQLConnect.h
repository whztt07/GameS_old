#include <my_global.h>
#include <mysql.h>
#include <string>

using namespace std;

struct MSQL_init_data;

class MSQLConnect{

	MYSQL *connection;	//���������� �� �������� ���������� �������	
	MYSQL mysql;		//���������� ������ ��� ����������.
public:
	~MSQLConnect();										//�������� ���������� � ��������� ������ �����
	void		Init(const MSQL_init_data &init_data);	//������� ���������� � ����� ������
	MYSQL_RES*	Query(const string &query);				//���������� ������ � ���������� ���������
};