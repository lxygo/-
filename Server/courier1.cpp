#include"system1.h"
Courier::Courier()
{
	money = 0;
	not_collect_num = 0;
	collect_num = 0;
}
void Courier::Changepassword()
{
	string old_password;
	string new_password;
	int times = 3;
	cout << "�����������:";
	cin >> old_password;
	while (times > 0)
	{
		if (old_password.compare(password) == 0)
		{
			cout << "������������:";
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
void Courier::Showmoney()
{
	cout << "�˻��е���" << money;
}
void Courier::Readcour(ifstream& in)
{

	int value;
	in >> user_name;
	in >> name;
	in >> phone;
	in >> money;
	in >> password;
	in >> not_collect_num;
	in >> collect_num;
	for (int i = 0; i <= not_collect_num - 1; i++)
	{
		in >> value;
		not_collect.push_back(value);
	}
	for (int i = 0; i <= collect_num - 1; i++)
	{
		in >> value;
		collect.push_back(value);
	}
}
/*vector<int>not_collect;//δ���յĿ��
vector<int>collect;//�����տ��
int not_collect_num;//δ���յĿ������
int collect_num;//�����յĿ������*/
void Courier::Storecour(ofstream& out)
{
	out << user_name << endl;
	out << name << endl;
	out << phone << endl;
	out << money << endl;
	out << password << endl;
	out << not_collect_num << endl;
	out << collect_num << endl;
	for (int i = 0; i <= not_collect_num - 1; i++)
	{
		out << not_collect[i] << " ";
	}
	out << endl;
	for (int i = 0; i <= collect_num - 1; i++)
	{
		out << collect[i] << " ";
	}
	out << endl;
}