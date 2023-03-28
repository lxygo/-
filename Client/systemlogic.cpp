#include"system.h"
#include"../tcpSocket/tcpSocket.h"
System::System() {
	admin_num = 1;
	users_num = 0;
	packages_num = 0;
	courier_num = 0;
}
void System::Store() {
	ofstream out;
	int i;
	out.open("�û�.txt", ios::out);
	if (out.is_open())
	{
		out << users_num << endl;
		for (i = 0; i <= users_num - 1; i++)
		{
			allusers[i].Storeusers(out);
		}
		out.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
	out.open("���.txt", ios::out);
	if (out.is_open())
	{
		out << packages_num << endl;
		out << not_assgin_num << endl;
		for (i = 0; i <= packages_num - 1; i++)
		{
			allpackages[i].StorePackage(out);
		}
		out << endl;
		for (i = 0; i <= not_assgin_num - 1; i++)
		{
			out << not_assign[i] << " ";
		}
		out << endl;
		out.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
	out.open("����Ա.txt", ios::out);
	if (out.is_open())
	{
		out << admin_num << endl;
		alladmin[0].Storeadmin(out);
		out.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
	out.open("���Ա.txt", ios::out);
	if (out.is_open())
	{
		out << courier_num << endl;
		for (i = 0; i <= courier_num - 1; i++)
		{
			allcouriers[i].Storecour(out);
		}
		out.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
}
void System::Read() {
	ifstream in;
	int i;
	in.open("�û�.txt", ios::in);
	if (in.is_open())
	{
		in >> users_num;
		for (i = 0; i <= users_num - 1; i++)
		{
			Users new_user;
			new_user.Readusers(in);
			allusers.push_back(new_user);
		}
		in.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
	in.open("���.txt", ios::in);
	if (in.is_open())
	{
		in >> packages_num;
		in >> not_assgin_num;
		for (i = 0; i <= packages_num - 1; i++)
		{
			Package new_package;
			new_package.ReadPackage(in);
			allpackages.push_back(new_package);
		}
		for (i = 0; i <= not_assgin_num - 1; i++)
		{
			int num;
			in >> num;
			not_assign.push_back(num);
		}
		in.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
	in.open("����Ա.txt", ios::in);
	if (in.is_open())
	{
		in >> admin_num;
		Administrator new_admin;
		new_admin.Readadmin(in);
		alladmin.push_back(new_admin);
		in.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
	in.open("���Ա.txt", ios::in);
	if (in.is_open())
	{
		in >> courier_num;
		for (i = 0; i <= courier_num - 1; i++)
		{
			Courier new_courier;
			new_courier.Readcour(in);
			allcouriers.push_back(new_courier);
		}
		in.close();
	}
	else
	{
		cout << "�ļ���ʧ��" << endl;
	}
}
int System::Finduser(string user_name) {
	int i;
	for (i = 0; i <= users_num - 1; i++)
	{
		if (user_name.compare(allusers[i].user_name) == 0)
		{
			return i;
		}
	}
	return -1;
}
int System::Findcourier(string courier_name) {
	int i;
	for (i = 0; i <= courier_num - 1; i++)
	{
		if (courier_name.compare(allcouriers[i].user_name) == 0)
		{
			return i;
		}
	}
	return -1;
}
bool System::Log(int order,SOCKET&client_socket) {
	string password;
	bool flag = false;
	int times = 5;
	int judge;
	cout << "����������:";
	cin >> password;
	send(client_socket, password.c_str(), password.length(), 0);
	while (times > 0)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge==1)
		{
			flag = true;
			cout << "��¼�ɹ�" << endl;
			return flag;
		}
		else
		{
			cout << "������󣬻��У�" << times << "�ο��Գ���" << "����������" << endl;
			cin >> password;
			send(client_socket, password.c_str(), password.length(), 0);
			times--;
		}
	}
	return flag;
}
bool System::Courierlog(string id,SOCKET&client_socket) {
	int times = 3;
	string t_password;
	int judge;
	cout << "�������������: ";
	cin >> t_password;
	send(client_socket, t_password.c_str(), t_password.length(), 0);
	while (times > 0)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			return true;
		}
		else
		{
			cout << "����������󣬻���" << times << "�λ���" << endl;
			cout << "���������룺";
			cin >> t_password;
			send(client_socket, t_password.c_str(), t_password.length(), 0);
			times--;
		}
	}
	return false;
}
void System::Send(int sender, int receiver, SOCKET& client_socket) {//sender�Ǽļ��ߵ���ţ�receiver���ռ��ߵ����
	string package_name, note;
	cout << "��������Ҫ���͵Ŀ�����ͣ�";
	cout << "1.��ͨ���(5Ԫ/kg) 2.����Ʒ(8Ԫ/kg) 3.ͼ��(2Ԫ/��)" << endl;
	int choose;
	int judge;
	cin >> choose;
	send(client_socket, (char*)&choose, 4, 0);
	cout << "���������Ŀ��������" ;
	double weight;
	cin >> weight;
	send(client_socket, (char*)&weight, 8, 0);
	if (choose == 1)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			cout << "��������������ƣ�" ;
			cin >> package_name;
			send(client_socket, package_name.c_str(), package_name.length(), 0);
			cout << "���������ı�ע��" ;
			cin >> note;
			send(client_socket, note.c_str(), note.length(), 0);
		}
		else
		{
			cout << "����" << endl;
		}
	}
	else if (choose == 2)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			cout << "��������������ƣ�" ;
			cin >> package_name;
			send(client_socket, package_name.c_str(), package_name.length(), 0);
			cout << "���������ı�ע��" ;
			cin >> note;
			send(client_socket, note.c_str(), note.length(), 0);
		}
		else
		{
			cout << "����" << endl;
		}
	}
	else if (choose == 3)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			cout << "��������������ƣ�";
			cin >> package_name;
			send(client_socket, package_name.c_str(), package_name.length(), 0);
			cout << "���������ı�ע��";
			cin >> note;
			send(client_socket, note.c_str(), note.length(), 0);
		}
		else
		{
			cout << "����" << endl;
		}
	}

}
void System::Receive(int receiver,SOCKET& client_socket) {
	int order;
	bool flag = true;;
	int num1;
	char buf[BUFSIZ] = { 0 };
	recv(client_socket, (char*)&num1, 4, 0);
	if (num1 == 0)
	{
		cout << "û�д����տ�ݡ�" << endl;
		flag = false;
	}
	else
	{
		cout << "��ǩ�տ�ݣ�" << endl;
		for (int i = 0; i <= num1 - 1; i++)
		{
			cout << i + 1 << " :" << endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
		}
	}
	if (flag)
	{
		int  choose = -1;
		cout << "��������Ҫǩ�յĿ����ţ�" ;
		cin >> choose;
		send(client_socket, (char*)&choose, 4, 0);
	}
}
void System::Show(int sender, SOCKET& client_socket)//���Ҹ��û������п����Ϣ
{
	int order;
	int num1, num2, num3;
	string recv_message;
	char buf[BUFSIZ] = { 0 };
	recv(client_socket, (char*)&num1, 4, 0);
	if (num1 == 0)
	{
		cout << "û�д����տ�ݡ�" << endl;
	}
	else
	{
		cout << "�����տ�ݣ�" << endl;
		for (int i = 0; i <= num1 - 1; i++) 
		{
			cout << i + 1 << " :" << endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
		}
	}
	cout << endl;
	recv(client_socket, (char*)&num2, 4, 0);
	if (num2 == 0)
	{
		cout << "û���ѽ��տ�ݡ�" << endl;
	}
	else
	{
		cout << "�ѽ��տ�ݣ�" << endl;
		for (int i = 0; i <= num2 - 1; i++)
		{
			cout << i + 1 << " :" << endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
		}
	}
	cout << endl;
	recv(client_socket, (char*)&num3, 4, 0);
	if (num3 == 0)
	{
		cout << "û�з��͵Ŀ�ݡ�" << endl;
	}
	else
	{
		cout << "�ѷ��Ϳ�ݣ�" << endl;
		for (int i = 0; i <= num3 - 1; i++)
		{
			cout << i + 1 << " :" << endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
		}
	}
	cout << endl;
}
void System::Showbytime(int order,SOCKET &client_socket)const
{
	int i = 0;
	int year, month, day;
	int choose;
	int num = 0;
	char buf[BUFSIZ] = { 0 };
	string recv_message;
	cout << "�������ݷ�����Ӧ��ʱ��(��������)" << endl;
	cout << "�꣺";
	cin >> year;
	cout << "�£�";
	cin >> month;
	cout << "�գ�";
	cin >> day;
	int num1, num2, num3, judge;
	send(client_socket, (char*)&year, 4, 0);
	send(client_socket, (char*)&month, 4, 0);
	send(client_socket, (char*)&day, 4, 0);
	recv(client_socket, (char*)&num1, 4, 0);
	for (i; i <= num1 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			num++;
		}
	}
	if (num == 0)
	{
		cout << "����û���κη��͹����Ŀ�ݡ�" << endl;
	}
	num = 0;
	recv(client_socket, (char*)&num2, 4, 0);
	for (i = 0; i <= num2 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			memset(buf, 0, BUFSIZ);
			num++;
		}
	}
	if (num == 0)
	{
		cout << "����û���κ�ǩ�յĿ�ݡ�" << endl;
	}
	num = 0;
	recv(client_socket, (char*)&num3, 4, 0);
	for (i = 0; i <= num3 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			memset(buf, 0, BUFSIZ);
			num++;
		}
	}
	if (num == 0)
	{
		cout << "����û�мĳ��κο��" << endl;
	}
}
void System::Showbynum(int order,SOCKET& client_socket)
{
	string num;
	int num1 = 0;//��¼��ѯ���Ŀ������
	int choose;
	int num2, num3, num4, judge;
	string recv_message;
	char buf[BUFSIZ] = { 0 };
	cout << "��������Ŀ�ݵ���:" << endl;
	cin >> num;
	send(client_socket, num.c_str(), num.length(), 0);
	int i;
	recv(client_socket, (char*)&num2, 4, 0);
	for (i = 0; i <= num2 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			memset(buf,0,BUFSIZ);
			num1++;
		}
	}
	if (num1 == 0)
	{
		cout << "δ��ѯ����ǩ�տ��" << endl;
	}
	num1 = 0;
	recv(client_socket, (char*)&num3, 4, 0);
	for (i = 0; i <= num3 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			memset(buf, 0, BUFSIZ);
			num1++;
		}
	}
	if (num1 == 0)
	{
		cout << "δ��ѯ����ǩ�տ��" << endl;
	}
	num1 = 0;
	recv(client_socket, (char*)&num4, 4, 0);
	for (i = 0; i <= num4 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			memset(buf, 0, BUFSIZ);
			num1++;
		}
	}
	if (num1 == 0)
	{
		cout << "δ��ѯ���ѷ��Ϳ��" << endl;
	}
}
bool System::Adminlog(SOCKET& client_socket)
{
	int times = 3;
	int judge;
	string password;
	while (times > 0)
	{
		cout << "�������������:";
		cin >> password;
		send(client_socket, password.c_str(), password.length(), 0);
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			cout << "��¼�ɹ�!" << endl;
			return true;
		}
		else
		{
			cout << "������������㻹��" << times << "�λ���" << endl;
			times--;
		}
	}
	return false;

}
void System::Adshowbyuser(SOCKET&client_socket)
{
	string id;
	int order = -1;
	cout << "�������û���id:";
	cin >> id;
	char buf[BUFSIZ];
	send(client_socket, id.c_str(), id.length(), 0);
	recv(client_socket, (char*)&order, 4, 0);
	if (order == -1)
	{
		cout << "δ��ѯ�����û�" << endl;
	}
	else
	{
		memset(buf, 0, BUFSIZ);
		recv(client_socket, buf, BUFSIZ, 0);
		cout << buf << endl;
	}

}
void System::Adshowbyallusers(SOCKET&client_socket)const
{
	int i;
	int num;
	char buf[BUFSIZ] = { 0 };
	recv(client_socket, (char*)&num, 4, 0);
	for (i = 0; i <= num - 1; i++)
	{
		memset(buf, 0, BUFSIZ);
		recv(client_socket, buf, BUFSIZ, 0);
		cout << buf;
		cout << endl;
	}
}
void System::Adshowbyid(SOCKET&client_socket)
{
	int order = -1;
	string id;
	cout << "�������û���id��";
	cin >> id;
	send(client_socket, id.c_str(), id.length(), 0);
	recv(client_socket, (char*)&order, 4, 0);
	if (order == -1)
	{
		cout << "�û�������" << endl;
	}
	else
	{
		Show(order,client_socket);
	}
}
void System::Adshowbytime(SOCKET&client_socket)const
{
	int time[3];
	int num;
	int judge;
	int num1 = 0;
	char buf[BUFSIZ] = { 0 };
	cout << "������Ҫ��ѯ��ʱ�䣨�����գ�" << endl;
	cout << "�꣺";
	cin >> time[0];
	send(client_socket, (char*)&time[0], 4, 0);
	cout << "�£�";
	cin >> time[1];
	send(client_socket, (char*)&time[1], 4, 0);
	cout << "�գ�";
	cin >> time[2];
	send(client_socket, (char*)&time[2], 4, 0);
	recv(client_socket, (char*)&num, 4, 0);
	for (int i = 0; i <= num - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
			num1++;
		}
	}
	if (num1 == 0)
	{
		cout << "����û�п��" << endl;
	}
}
void System::Adshowbynum(SOCKET&client_socket)const
{
	string num;
	int num1 = 0;
	int num2;
	int judge;
	char buf[BUFSIZ] = { 0 };
	string recv_message;
	cout << "������Ҫ��ѯ�Ŀ�ݵ��ţ�";
	cin >> num;
	send(client_socket, num.c_str(), num.length(), 0);
	recv(client_socket, (char*)&num2, 4, 0);
	for (int i = 0; i <= num2 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
			num1++;
		}
	}
	if (num1 == 0)
	{
		cout << "δ��ѯ���ÿ��" << endl;
	}
}
void System::Adshowcourier(SOCKET&client_socket)
{
	cout << "��������Ҫ���еķ���:" << endl;
	cout << "1.��ʾ���п��Ա��Ϣ 2.�û�����ѯ���Ա" << endl;
	int choose;
	int num;
	char buf[BUFSIZ] = { 0 };
	cin >> choose;
	send(client_socket, (char*)&choose, 4, 0);
	if (choose == 1)
	{
		recv(client_socket, (char*)&num, 4, 0);
		if (num == 0)
		{
			cout << "�޿��Ա" << endl;
		}
		else
		{
			for (int i = 0; i <= num - 1; i++)
			{
				memset(buf, 0, BUFSIZ);
				recv(client_socket, buf, BUFSIZ, 0);
				cout << buf;
				cout << endl;
			}
		}
	}
	else if (choose == 2)
	{
		cout << "��������Աid��" ;
		string id;
		int order = -1;
		cin >> id;
		send(client_socket, id.c_str(), id.length(), 0);
		recv(client_socket, (char*)&order, 4, 0);
		if (order == -1)
		{
			cout << "Ϊ��ѯ���ÿ��Ա" << endl;
		}
		else
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf;
			cout << endl;
		}
	}
}
void System::Adshowcollect(SOCKET&client_socket)
{
	cout << "��������Ա��id��" ;
	string id;
	cin >> id;
	send(client_socket, id.c_str(), id.length(), 0);
	int order;
	recv(client_socket, (char*)&order, 4, 0);
	if (order == -1)
	{
		cout << "���û�������" << endl;
	}
	else
	{
		cout << "��ѡ���ѯ�ķ�ʽ��" << endl;
		cout << "1.ȫ����ʾ 2.ʱ���ѯ 3.��ݵ��Ų�ѯ 4.�ļ��� 5.�ռ���" << endl;
		int choose;
		cin >> choose;
		send(client_socket, (char*)&choose, 4, 0);
		if (choose == 1)
		{
			CoSearch(order,client_socket);
		}
		else if (choose == 2)
		{
			Coshowbytime(order,client_socket);
		}
		else if (choose == 3)
		{
			Coshowbynum(order,client_socket);
		}
		else if (choose == 4)
		{
			Coshowbysend(order,client_socket);
		}
		else if (choose == 5)
		{
			Coshowbyreceive(order,client_socket);
		}
	}
}
void System::Addcourier(SOCKET&client_socket)
{
	int order;
	Courier new_courier;
	cout << "��������Ҫ��ӵ�id��" ;
	string id;
	cin >> id;
	send(client_socket, id.c_str(), id.length(), 0);
	recv(client_socket, (char*)&order, 4, 0);
	if (order == -1)
	{
		new_courier.user_name = id;
		cout << "����������������";
		cin >> new_courier.name;
		send(client_socket, new_courier.name.c_str(), new_courier.name.length(), 0);
		cout << "������绰��";
		cin >> new_courier.phone;
		send(client_socket, new_courier.phone.c_str(), new_courier.phone.length(), 0);
		cout << "�������������룺";
		cin >> new_courier.password;
		send(client_socket, new_courier.password.c_str(), new_courier.password.length(), 0);
	}
	else
	{
		cout << "���û�����ע��" << endl;
	}
}
void System::Deletecourier(SOCKET&client_socket)
{
	string id;
	int order;
	cout << "��������Ҫɾ���Ŀ��Աid��";
	cin >> id;
	send(client_socket, id.c_str(), id.length(), 0);
	order = Findcourier(id);
	recv(client_socket, (char*)&order, 4, 0);
	if (order == -1)
	{
		cout << "û�иÿ��Ա" << endl;
	}
}
void System::Assign(SOCKET&client_socket)
{
	int order;
	char buf[BUFSIZ] = { 0 };
	int num;
	int num1, num2;
	recv(client_socket, (char*)&num1, 4, 0);
	if (num1 > 0)
	{
		cout << "��ѡ��Ŀ��Ա:" << endl;
		for (int i = 0; i <= num1 - 1; i++)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
		}
		int choose;
		cout << "��������Ҫ����Ŀ��Ա��";
		cin >> choose;
		send(client_socket, (char*)&choose, 4, 0);
		if (choose >= 0 && choose <= num1)
		{
			cout << "������Ŀ��:" << endl;
			recv(client_socket, (char*)&num2, 4, 0);
			for (int i = 0; i <= num2 - 1; i++)
			{
				cout << i + 1 << " "<<endl;
				memset(buf, 0, BUFSIZ);
				recv(client_socket, buf, BUFSIZ, 0);
				cout << buf << endl;
			}
			cout << "��������Ҫ����Ŀ�ݸ�����";
			cin >> num;
			send(client_socket, (char*)&num, 4, 0);
			int choose1;
			if (num2 != 1 && num <= num2)
			{
				for (int i = 0; i <= num - 1; i++)
				{
					cout << "��������Ҫ����Ŀ����ţ�";
					cin >> choose1;
					send(client_socket, (char*)&choose1, 4, 0);
					num2--;
					if (i != num - 1)
					{
						cout << "������Ŀ��:" << endl;
						for (int i = 0; i <= num2 - 1; i++)
						{
							cout << i + 1 << " "<<endl;
							memset(buf, 0, BUFSIZ);
							recv(client_socket, buf, BUFSIZ, 0);
							cout << buf << endl;
						}
					}
				}
			}
			else if (num == 1 && num2 == 1)
			{
				cout << "�ѷ���" << endl;
			}
			else
			{
				cout << "��Ч����" << endl;
				cin.clear();
				cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
			}

		}
	}
	else
	{
		cout << "�޿��Ա" << endl;
	}
}
void System::Cocollect(int order,SOCKET&client_socket)
{
	int choose;
	int num;
	int choose1;
	int num1, judge;
	char buf[BUFSIZ] = { 0 };
	recv(client_socket, (char*)&num1, 4, 0);
	if (num1 == 0)
	{
		cout << "�޴����տ��" << endl;
	}
	else
	{
		cout << "�����յĿ�ݣ�"<<endl;
		for (int i = 0; i <= num1 - 1; i++)
		{
			cout << i + 1 << ":" << endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
		}
		cout << "��������Ҫ���յĸ���:";
		cin >> num;
		send(client_socket, (char*)&num, 4, 0);
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			for (int i = 0; i <= num - 1; i++)
			{
				cout << "��ѡ����Ҫ���յĿ�ݣ�";
				cin >> choose1;
				send(client_socket, (char*)&choose1, 4, 0);
				num1--;
				if (i != num - 1)
				{
					cout << "�����յĿ�ݣ�" << endl;
					for (int i = 0; i <= num1 - 1; i++)
					{
						cout << i + 1 << ":" << endl;
						memset(buf, 0, BUFSIZ);
						recv(client_socket, buf, BUFSIZ, 0);
						cout << buf << endl;
					}
				}
			}
		}
		else if (judge == 0 && num == 1)
		{
			cout << "������" << endl;
		}
		else
		{
			cout << "��Ч����" << endl;
			cin.clear();
			cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
		}
	}
}
void System::Coshow_not_collect(int order,SOCKET&client_socket)const
{
	int order1;
	char buf[BUFSIZ] = { 0 };
	int num1;
	recv(client_socket, (char*)&num1, 4, 0);
	if (num1 == 0)
	{
		cout << "�޴����տ��" << endl;
	}
	else
	{
		cout << "�����յĿ�ݣ�" << endl;
		for (int i = 0; i <= num1 - 1; i++)
		{
			cout << i + 1 << ":" << endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
		}
	}
}
void System::CoSearch(int order,SOCKET&client_socket)
{
	int order1;
	int num, judge;
	char buf[BUFSIZ] = { 0 };
	recv(client_socket, (char*)&num, 4, 0);
	if (num == 0)
	{
		cout << "�������տ��" << endl;
	}
	else
	{
		cout << "�����յĿ�ݣ�" << endl;
		for (int i = 0; i <= num - 1; i++)
		{
			cout << i + 1 << ":"<<endl;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
		}
	}
	
}
void System::Coshowbynum(int order,SOCKET&client_socket)const
{
	cout << "��������Ҫ��ѯ�Ŀ�ݵ��ţ�";
	string number;
	char buf[BUFSIZ] = { 0 };
	cin >> number;
	send(client_socket, number.c_str(), number.length(), 0);
	int i;
	int order1;
	int num = 0;
	int num1, judge;
	recv(client_socket, (char*)&num1, 4, 0);
	for (i = 0; i <= num1 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
			num++;
		}
	}
	if (num == 0)
	{
		cout << "δ��ѯ���ÿ��" << endl;
	}
}
void System::Coshowbyreceive(int order,SOCKET&client_socket)const
{
	cout << "�������ռ���id" ;
	string id;
	char buf[BUFSIZ] = { 0 };
	cin >> id;
	send(client_socket, id.c_str(), id.length(), 0);
	int i;
	int order1;
	int num = 0;
	int num1, judge;
	recv(client_socket, (char*)&num1, 4, 0);
	for (i = 0; i <= num1 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
			num++;
		}
	}
	if (num == 0)
	{
		cout << "δ��ѯ���ÿ��" << endl;
	}
}
void System::Coshowbysend(int order,SOCKET&client_socket)const
{
	cout << "������ļ���id��";
	string id;
	char buf[BUFSIZ] = { 0 };
	cin >> id;
	send(client_socket, id.c_str(), id.length(), 0);
	int i;
	int order1;
	int num = 0;
	int num1, judge;
	recv(client_socket, (char*)&num1, 4, 0);
	for (i = 0; i <= num1 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
			num++;
		}
	}
	if (num == 0)
	{
		cout << "δ��ѯ���ÿ��" << endl;
	}
}
void System::Coshowbytime(int order,SOCKET&client_socket)const
{
	int time[3];
	char buf[BUFSIZ] = { 0 };
	cout << "������Ҫ��ѯ��ʱ�䣨�����գ�" << endl;
	cout << "�꣺";
	cin >> time[0];
	send(client_socket, (char*)&time[0], 4, 0);
	cout << "�£�";
	cin >> time[1];
	send(client_socket, (char*)&time[1], 4, 0);
	cout << "�գ�";
	cin >> time[2];
	send(client_socket, (char*)&time[2], 4, 0);
	int order1;
	int num = 0;
	int num1, judge;
	recv(client_socket, (char*)&num1, 4, 0);
	for (int i = 0; i <= num1 - 1; i++)
	{
		recv(client_socket, (char*)&judge, 4, 0);
		if (judge == 1)
		{
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			cout << buf << endl;
			num++;
		}
	}
	if (num == 0)
	{
		cout << "����û�������κο��" << endl;
	}
}