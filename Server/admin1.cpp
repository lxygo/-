#include"system1.h"

//ʵ�ֹ���Ա��ĺ���
Administrator::Administrator() {
	money = 0;
}
void Administrator::Changename(SOCKET& client_socket)
{
	char buf[BUFSIZ] = { 0 };
	cout << "���������������" << endl;
	recv(client_socket, buf, BUFSIZ, 0);
	name = buf;
}
void Administrator::Changepassword(SOCKET& client_socket)
{
	int times = 3;
	int judge;
	string t_password;
	char buf[BUFSIZ] = { 0 };
	while (times > 0)
	{
		cout << "��������ľ�����:";
		memset(buf, 0, BUFSIZ);
		recv(client_socket, buf, BUFSIZ, 0);
		t_password = buf;
		if (t_password.compare(password) == 0)
		{
			judge = 1;
			send(client_socket, (char*)&judge, 4, 0);
			cout << "�������µ�����:";
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			password = buf;
			break;
		}
		else
		{
			judge = 0;
			send(client_socket, (char*)&judge, 4, 0);
			cout << "����������󣬻�������" << times << "��";
			times--;
		}
	}
}
void Administrator::Readadmin(ifstream& in)
{
	in >> user_name;
	in >> name;
	in >> password;
	in >> money;
}
void Administrator::Storeadmin(ofstream& out)
{
	out << user_name << endl;
	out << name << endl;
	out << password << endl;
	out << money << endl;
}