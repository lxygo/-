#include"system.h"

//ʵ�ֹ���Ա��ĺ���
Administrator::Administrator() {
	money = 0;
}
void Administrator::Changename()
{
	cout << "���������������" << endl;
	cin >> name;
}
void Administrator::Changepassword()
{
	int times = 3;
	string t_password;
	while (times > 0)
	{
		cout << "��������ľ�����:";
		cin >> t_password;
		if (t_password.compare(password) == 0)
		{
			cout << "�������µ�����:";
			cin >> password;
			break;
		}
		else
		{
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