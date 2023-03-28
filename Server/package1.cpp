#include"system1.h"
//ʵ��package�ĳ�Ա����
Package::Package() {
	sign = false;
	srand((int)time(0));//��������ӵ�����
	collect = false;
}
void Package::StorePackage(ofstream& out) {
	int i;
	out << package_num << endl;
	for (i = 0; i <= 5; i++)
	{
		out << send_time[i] << " ";
	}
	out << endl;
	for (i = 0; i <= 5; i++)
	{
		out << receive_time[i] << " ";
	}
	out << endl;
	for (i = 0; i <= 5; i++)
	{
		out << collect_time[i] << " ";
	}
	out << endl;
	out << package_name << endl;
	out << sender << endl;
	out << receiver << endl;
	out << sign << endl;
	out << note << endl;
	out << collect << endl;
	out << money << endl;
	out << type << endl;
}
void Package::ReadPackage(ifstream& in) {
	int i;
	in >> package_num;
	for (i = 0; i <= 5; i++)
	{
		in >> send_time[i];
	}
	for (i = 0; i <= 5; i++)
	{
		in >> receive_time[i];
	}
	for (i = 0; i <= 5; i++)
	{
		in >> collect_time[i];
	}
	in >> package_name;
	in >> sender;
	in >> receiver;
	in >> sign;
	in >> note;
	in >> collect;
	in >> money;
	in >> type;
}
void Package::SendPackage(string t_sender, string t_receiver, SOCKET& client_socket) {
	char buf[BUFSIZ] = { 0 };
	receiver = t_receiver;
	sender = t_sender;
	cout << "��������������ƣ�" << endl;
	memset(buf, 0, BUFSIZ);
	recv(client_socket, buf, BUFSIZ, 0);
	package_name = buf;
	cout << "���������ı�ע��" << endl;
	memset(buf, 0, BUFSIZ);
	recv(client_socket, buf, BUFSIZ, 0);
	note = buf;
	tm time1;
	time_t sendtime = time(0);
	localtime_s(&time1, &sendtime);
	send_time[0] = time1.tm_year + 1900;
	send_time[1] = time1.tm_mon + 1;
	send_time[2] = time1.tm_mday;
	send_time[3] = time1.tm_hour;
	send_time[4] = time1.tm_min;
	send_time[5] = time1.tm_sec;
}
void Package::CollectPackage()
{
	time_t collecttime = time(0);
	tm time1;
	localtime_s(&time1, &collecttime);
	collect_time[0] = time1.tm_year + 1900;
	collect_time[1] = time1.tm_mon + 1;
	collect_time[2] = time1.tm_mday;
	collect_time[3] = time1.tm_hour;
	collect_time[4] = time1.tm_min;
	collect_time[5] = time1.tm_sec;
	collect = true;
}
void Package::ReceivePackage() {
	time_t receivetime = time(0);
	tm time1;
	localtime_s(&time1, &receivetime);
	receive_time[0] = time1.tm_year + 1900;
	receive_time[1] = time1.tm_mon + 1;
	receive_time[2] = time1.tm_mday;
	receive_time[3] = time1.tm_hour;
	receive_time[4] = time1.tm_min;
	receive_time[5] = time1.tm_sec;
	sign = true;
}
void Package::ShowPackage(SOCKET& client_socket)const
{
	string send_message;
	cout << "��ݵ��ţ�" << package_num << endl;
	send_message = "��ݵ��ţ�" + package_num + "\n";
	cout << "������ƣ�" << endl;
	send_message = send_message + "������ƣ�" + package_name + "\n";
	cout << "�ļ��ˣ�" << sender << endl;
	send_message = send_message + "�ļ��ˣ�" + sender + "\n";
	cout << "�ռ��ˣ�" << receiver << endl;
	send_message = send_message + "�ռ��ˣ�" + receiver + "\n";
	cout << "��ݽ�" << money << endl;
	send_message = send_message + "��ݽ�" +to_string(money) + "\n";
	cout << "��ݱ�ע��" << note << endl;
	send_message = send_message + "��ݱ�ע��" + note + "\n";
	if (collect)
	{
		cout << "������" << endl;
		send_message = send_message + "������" + "\n";
		cout << "�ļ�ʱ�䣺" << send_time[0] << "��" << send_time[1] << "��" << send_time[2] << "�� " << send_time[3] << ":" << send_time[4] << ":" << send_time[5] << endl;
		send_message = send_message + "�ļ�ʱ�䣺" + to_string(send_time[0]) + "��" + to_string(send_time[1]) + "��" + to_string(send_time[2]) + "��" + to_string(send_time[3]) + ":" + to_string(send_time[4]) + ":" + to_string(send_time[5]) + "\n";
		cout << "����ʱ�䣺" << collect_time[0] << "��" << collect_time[1] << "��" << collect_time[2] << "�� " << collect_time[3] << ":" << collect_time[4] << ":" << collect_time[5] << endl;
		send_message = send_message + "����ʱ�䣺" + to_string(collect_time[0]) + "��" + to_string(collect_time[1]) + "��" + to_string(collect_time[2]) + "��" + to_string(collect_time[3]) + ":" + to_string(collect_time[4]) + ":" + to_string(collect_time[5]) + "\n";
	}
	else if (collect == false)
	{
		cout << "������" << endl;
		send_message = send_message + "������" + "\n";
		cout << "�ļ�ʱ�䣺" << send_time[0] << "��" << send_time[1] << "��" << send_time[2] << "�� " << send_time[3] << ":" << send_time[4] << ":" << send_time[5] << endl;
		send_message = send_message + "�ļ�ʱ�䣺" + to_string(send_time[0]) + "��" + to_string(send_time[1]) + "��" + to_string(send_time[2]) + "��" + to_string(send_time[3]) + ":" + to_string(send_time[4]) + ":" + to_string(send_time[5]) + "\n";
	}
	if (sign)
	{
		cout << "��ǩ�� " << endl;
		send_message = send_message + "��ǩ��" + "\n";
		cout << "�ļ�ʱ�䣺" << send_time[0] << "��" << send_time[1] << "��" << send_time[2] << "�� " << send_time[3] << ":" << send_time[4] << ":" << send_time[5] << endl;
		send_message = send_message + "�ļ�ʱ�䣺" + to_string(send_time[0]) + "��" + to_string(send_time[1]) + "��" + to_string(send_time[2]) + "��" + to_string(send_time[3]) + ":" + to_string(send_time[4]) + ":" + to_string(send_time[5]) + "\n";
		cout << "ǩ��ʱ�䣺" << receive_time[0] << "��" << receive_time[1] << "��" << receive_time[2] << "�� " << receive_time[3] << ":" << receive_time[4] << ":" << receive_time[5] << endl;
		send_message = send_message + "ǩ��ʱ�䣺" + to_string(receive_time[0]) + "��" + to_string(receive_time[1]) + "��" + to_string(receive_time[2]) + "��" + to_string(receive_time[3]) + ":" + to_string(receive_time[4]) + ":" + to_string(receive_time[5]) + "\n";
	}
	else if ((sign == false) && (collect == true))
	{
		cout << "��ǩ��" << endl;
		send_message = send_message + "��ǩ��" + "\n";
		cout << "�ļ�ʱ�䣺" << send_time[0] << "��" << send_time[1] << "��" << send_time[2] << "�� " << send_time[3] << ":" << send_time[4] << ":" << send_time[5] << endl;
		send_message = send_message + "�ļ�ʱ�䣺" + to_string(send_time[0]) + "��" + to_string(send_time[1]) + "��" + to_string(send_time[2]) + "��" + to_string(send_time[3]) + ":" + to_string(send_time[4]) + ":" + to_string(send_time[5]) + "\n";
	}
	send(client_socket, send_message.c_str(), send_message.length(), 0);
}
void Package::Make_PackageNum() {
	package_num = 'L';
	for (int i = 0; i <= 10; i++)
	{
		package_num = package_num + (char)(rand() % 10 + 48);
	}
}
void Package::Getprice(double weight) {
	money = weight * 15;
}
void Fragile::Getprice(double weight) {
	money = weight * 8;
}
void Book::Getprice(double weight) {
	money = weight * 2;
}
void Normal::Getprice(double weight) {
	money = weight * 5;
}
