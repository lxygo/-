#include"system.h"
//ʵ��users�ĳ�Ա����
Users::Users() {
	new_users = true;
	money = 0;
	send_numbers = 0;
	receive_numbers = 0;
	not_re_nums = 0;
}
void Users::Register(string id,SOCKET& client_socket) {
	user_name = id;
	new_users = false;
	string tpassword;
	int judge;
	while (true)
	{
		cout << "������������룺" ;
		cin >> password;
		send(client_socket, password.c_str(), password.length(), 0);
		cout << "���ٴ�����������룺";
		cin >> tpassword;
		send(client_socket, tpassword.c_str(), tpassword.length(), 0);
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			break;
		}
		else
		{
			cout << "���������������������" << endl;
		}
	}
}
void Users::Change_password() {
	cout << "�����������" << endl;
	string old_password;
	string new_password;
	int times = 3;
	cin >> old_password;
	while (times)
	{
		if (old_password.compare(password) == 0)
		{
			cout << "�������µ�����" << endl;
			cin >> new_password;
			while (new_password.compare(password) == 0)
			{
				cout << "�������벻���ظ�,����������" << endl;
				cin >> new_password;
			}
			password = new_password;
			break;
		}
		else
		{
			cout << "����������������������룬���ܳ���" << times-- << "��" << endl;
			cin >> old_password;
		}
	}
}
void Users::Change_message(SOCKET& client_socket) {
	int judge;
	recv(client_socket, (char*)&judge, 4, 0);
	if (judge == 1)
	{
		cout << "�������û�������";
		cin >> name;
		send(client_socket, name.c_str(), name.length(), 0);
		cout << "�������û��绰��";
		cin >> phone;
		send(client_socket, phone.c_str(), phone.length(), 0);
		cout << "�������û���ַ��";
		cin >> address;
		send(client_socket, address.c_str(), address.length(), 0);
	}
	else
	{
		cout << "��ѡ�������޸ĵĸ�����Ϣ:" << endl;
		cout << "1.�û����� 2.�û��绰 3.�û���ַ" << endl;
		int choose;
		cin >> choose;
		send(client_socket, (char*)&choose, 4, 0);
		if (choose == 1)
		{
			cout << "�������µ�����" << endl;
			cin >> name;
			send(client_socket, name.c_str(), name.length(), 0);
		}
		else if (choose == 2)
		{
			cout << "�������µĵ绰����" << endl;
			cin >> phone;
			send(client_socket, phone.c_str(), phone.length(), 0);
		}
		else if (choose == 3)
		{
			cout << "�������µĵ�ַ" << endl;
			cin >> address;
			send(client_socket, address.c_str(), address.length(), 0);
		}
	}
}
void Users::Add_money() {
	double add;
	cout << "�������ֵ�Ľ��" << endl;
	cin >> add;
	money = money + add;
}
void Users::Show_money()const {
	cout << "���:" << money << endl;
}
void Users::Storeusers(ofstream& out) {
	out << user_name << endl;
	out << password << endl;
	out << name << endl;
	out << phone << endl;
	out << address << endl;
	out << money << endl;
	out << new_users << endl;
	out << send_numbers << endl;	//���͵Ŀ������
	out << receive_numbers << endl;//���ܵĿ������
	out << not_re_nums << endl;
	int i;
	for (i = 0; i <= send_numbers - 1; i++)
	{
		out << send_package[i] << " ";
	}
	out << endl;
	for (i = 0; i <= receive_numbers - 1; i++)
	{
		out << receive[i] << " ";
	}
	out << endl;
	for (i = 0; i <= not_re_nums - 1; i++)
	{
		out << not_receive[i] << " ";
	}
	out << endl;
}
void Users::Readusers(ifstream& in) {
	in >> user_name;
	in >> password;
	in >> name;
	in >> phone;
	in >> address;
	in >> money;
	in >> new_users;
	in >> send_numbers;	//���͵Ŀ������
	in >> receive_numbers;//���ܵĿ������
	in >> not_re_nums;
	int order, i;
	for (i = 0; i <= send_numbers - 1; i++)
	{
		in >> order;
		send_package.push_back(order);
	}
	for (i = 0; i <= receive_numbers - 1; i++)
	{
		in >> order;
		receive.push_back(order);
	}
	for (i = 0; i <= not_re_nums - 1; i++)
	{
		in >> order;
		not_receive.push_back(order);
	}
}

