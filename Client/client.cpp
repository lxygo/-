#include"../tcpSocket/tcpSocket.h"
#include"../Client/system.h"
using namespace std;
int main()
{
	init_socket();
	bool flag1 = true;
	int choose;
	SOCKET client_socket = creat_client_socket();
	char buf[BUFSIZ] = { 0 };
	string id;
	int order;
	bool flag;
	int service;
	int choose1;//�ֲ�������Ӱ���ⲿ��choose
	System Logsystem;
	cout << "��ӭʹ����������ϵͳ" << endl;
	while (flag1)
	{
		cout << "��ѡ����Ҫ��¼�ķ�ʽ��" << endl;
		cout << "1.ֱ�ӵ�¼ 2.���û�ע�� 3.����Ա��¼ 4.���Ա��¼ 5.�˳�ϵͳ" << endl;
		cin >> choose;//����ѡ��ķ�ʽ
		send(client_socket, (char*)&choose , 4, 0);
		if (choose == 1)
		{
			cout << "����������û���:" ;
			cin >> id;
			send(client_socket, id.c_str(), id.length(), 0);
			recv(client_socket, (char*)&order, 4, 0);
			if (order == -1)
			{
				cout << "δ��ѯ������û�,�����ע��." << endl;
			}
			else
			{
				flag = Logsystem.Log(order,client_socket);
				while (flag)
				{
					cout << "\n��ѡ������Ҫ�ķ���" << endl;
					cout << "1.��ѯ�����Ϣ 2.���Ϳ�� 3.ǩ�տ�� " << endl;
					cout << "4.�޸��˻����� 5.�����˻���ֵ 6.�˻�����ѯ 7.�޸ĸ�����Ϣ 8.�˳�ϵͳ" << endl;
					cin >> service;
					send(client_socket, (char*)&service, 4, 0);
					if (service == 1)
					{
						cout << "��ѡ������Ҫ�Ĳ�ѯ����" << endl;
						cout << "1.��ѯȫ�������Ϣ 2.ͨ��ʱ����в�ѯ 3.ͨ����ݵ��Ž��в�ѯ" << endl;
						cin >> choose1;
						send(client_socket, (char*)&choose1, 4, 0);
						if (choose1 == 1)
						{
							Logsystem.Show(order,client_socket);
						}
						else if (choose1 == 2)
						{
							Logsystem.Showbytime(order,client_socket);
						}
						else if (choose1 == 3)
						{
							Logsystem.Showbynum(order,client_socket);
						}
					}
					else if (service == 2)
					{
						string receiver;
						cout << endl;
						cout << "�������ռ���id��";
						cin >> receiver;
						send(client_socket, receiver.c_str(), receiver.length(), 0);
						int  receive_order;
						recv(client_socket, (char*)&receive_order, 4, 0);
						Logsystem.Send(order, receive_order,client_socket);
					}
					else if (service == 3)
					{
						Logsystem.Receive(order, client_socket);
					}
					else if (service == 4)
					{
						cout << "����������룺" ;
						string old_password;
						string new_password;
						int times = 3;
						int judge;
						cin >> old_password;
						send(client_socket, old_password.c_str(), old_password.length(), 0);
						while (times)
						{
							recv(client_socket, (char*)&judge, 4, 0);
							if (judge == 1)
							{
								cout << "�������µ����룺" ;
								cin >> new_password;
								send(client_socket, new_password.c_str(), new_password.length(), 0);
								break;
							}
							else
							{
								cout << "����������������������룬���ܳ���" << times-- << "��" << endl;
								cout << "����������룺";
								cin >> old_password;
								send(client_socket, old_password.c_str(), old_password.length(),0);
							}
						}
					}
					else if (service == 5)
					{
						double add;
						cout << "�������ֵ�Ľ�";
						cin >> add;
						send(client_socket, (char*)&add, 8, 0);
					}
					else if (service == 6)
					{
						double money;
						recv(client_socket, (char*)&money, 8, 0);
						cout << "��" << money << endl;
					}
					else if (service == 7)
					{
						string name, phone, address;
						cout << "��ѡ�������޸ĵĸ�����Ϣ:" << endl;
						cout << "1.�û����� 2.�û��绰 3.�û���ַ" << endl;
						int choose;
						cin >> choose;
						send(client_socket, (char*)&choose, 4, 0);
						if (choose == 1)
						{
							cout << "�������µ�������" ;
							cin >> name;
							send(client_socket, name.c_str(), name.length(), 0);
						}
						else if (choose == 2)
						{
							cout << "�������µĵ绰���룺";
							cin >> phone;
							send(client_socket, phone.c_str(), phone.length(), 0);
						}
						else if (choose == 3)
						{
							cout << "�������µĵ�ַ��" ;
							cin >> address;
							send(client_socket, address.c_str(), address.length(), 0);
						}
					}
					else if (service == 8)
					{
						flag = false;
						flag1 = false;
					}
					else
					{
						cout << "��Ч����" << endl;
						cin.clear();
						cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
					}
					cout << endl;
				}
			}
		}
		else if (choose == 2)
		{
			cout << "����������Ҫid��" ;
			string id;
			id.clear();
			cin >> id;
			send(client_socket, id.c_str(), id.length(), 0);
			recv(client_socket, (char*)&order, 4, 0);
			if (order == -1)
			{
				Users new_user;
				new_user.Change_message(client_socket);
				new_user.Register(id,client_socket);
				double add;
				cout << "�������ֵ�Ľ�";
				cin >> add;
				send(client_socket, (char*)&add, 8, 0);
				cout << endl;
			}
			else
			{
				cout << "��id��ע��" << endl;
			}
		}
		else if (choose == 3)
		{
			int judge;
			cout << "����������û�����" ;
			cin >> id;
			send(client_socket, id.c_str(), id.length(), 0);
			recv(client_socket, (char*)&judge, 4, 0);
			if (judge == 1)
			{
				flag = Logsystem.Adminlog(client_socket);
				while (flag)
				{
					cout << "\n��ѡ����Ҫ���еķ���:" << endl;
					cout << "1.��ѯĳһ�û���Ϣ  2.��ѯ�����û���Ϣ  3.ͨ���û���ѯ���  4.ͨ��ʱ���ѯ���  5.ͨ����ݵ��Ų�ѯ���" << endl;
					cout << "6.�޸Ĺ���Ա����  7.�޸Ĺ���Ա����  8.������Ա 9.�˳�" << endl;
					cin >> service;
					send(client_socket, (char*)&service, 4, 0);
					if (service == 1)
					{
						Logsystem.Adshowbyuser(client_socket);
					}
					else if (service == 2)
					{
						Logsystem.Adshowbyallusers(client_socket);
					}
					else if (service == 3)
					{
						Logsystem.Adshowbyid(client_socket);
					}
					else if (service == 4)
					{
						Logsystem.Adshowbytime(client_socket);
					}
					else if (service == 5)
					{
						Logsystem.Adshowbynum(client_socket);
					}
					else if (service == 6)
					{
						string name;
						cout << "��������������֣�" ;
						cin >> name;
						send(client_socket, name.c_str(), name.length(), 0);
					}
					else if (service == 7)
					{
						int times = 3;
						int judge;
						string t_password;
						string new_password;
						while (times > 0)
						{
							cout << "��������ľ����룺";
							cin >> t_password;
							send(client_socket, t_password.c_str(), t_password.length(), 0);
							recv(client_socket, (char*)&judge, 4, 0);
							if (judge == 1)
							{
								cout << "�������µ����룺";
								cin >> new_password;
								send(client_socket, new_password.c_str(), new_password.length(), 0);
								break;
							}
							else
							{
								cout << "����������󣬻�������" << times << "��"<<endl;
								times--;
							}
						}
					}
					else if (service == 8)
					{
						cout << "��ѡ����Ҫ���еķ���:"<<endl;
						cout << "1.�鿴���Ա��Ϣ 2.��ѯ�����յĿ����Ϣ 3.��ӿ��Ա 4.ɾ�����Ա 5.�������տ�� " << endl;
						int choose1;
						cin >> choose1;
						send(client_socket, (char*)&choose1, 4, 0);
						if (choose1 == 1)
						{
							Logsystem.Adshowcourier(client_socket);
						}
						else if (choose1 == 2)
						{
							Logsystem.Adshowcollect(client_socket);
						}
						else if (choose1 == 3)
						{
							Logsystem.Addcourier(client_socket);
						}
						else if (choose1 == 4)
						{
							Logsystem.Deletecourier(client_socket);
						}
						else if (choose1 == 5)
						{
							Logsystem.Assign(client_socket);
						}
					}
					else if (service == 9)
					{
						flag = false;
						flag1 = false;
					}
					else
					{
						cout << "��Ч����" << endl;
						cin.clear();
						cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
					}
					cout << endl;
				}
			}
			else
			{
				cout << "���û����ǹ���Ա" << endl;
			}
		}
		else if (choose == 4)
		{
			string id;
			int choose1;
			cout << "����������û�����";
			cin >> id;
			send(client_socket, id.c_str(), id.length(), 0);
			recv(client_socket, (char*)&order, 4, 0);
			if (order != -1)
			{
				flag = Logsystem.Courierlog(id,client_socket);
				while (flag)
				{
					cout << "��ѡ����Ҫ���еķ���"<<endl;
					cout << "1.��ѯ�����յĿ�� 2.��ѯ�������յĿ�� 3.���տ�� 4.��ѯ��� 5.�˳�ϵͳ";
					cout << endl;
					cin >> choose1;
					send(client_socket, (char*)&choose1, 4, 0);
					if (choose1 == 1)
					{
						Logsystem.Coshow_not_collect(order,client_socket);
					}
					else if (choose1 == 2)
					{
						Logsystem.CoSearch(order,client_socket);
					}
					else if (choose1 == 3)
					{
						Logsystem.Cocollect(order,client_socket);
					}
					else if (choose1 == 4)
					{
						int choose2;
						flag = true;
						while (flag)
						{
							cout << "��������Ҫ��ѯ�ķ�ʽ��" << endl;
							cout << "1.��ݵ��Ų�ѯ  2.ʱ���ѯ  3.�ļ��˲�ѯ  4.�ռ��˲�ѯ  5.�˳�" << endl;
							cin >> choose2;
							send(client_socket, (char*)&choose2, 4, 0);
							if (choose2 == 1)
							{
								Logsystem.Coshowbynum(order,client_socket);
							}
							else if (choose2 == 2)
							{
								Logsystem.Coshowbytime(order,client_socket);
							}
							else if (choose2 == 3)
							{
								Logsystem.Coshowbysend(order,client_socket);
							}
							else if (choose2 == 4)
							{
								Logsystem.Coshowbyreceive(order,client_socket);
							}
							else if (choose2 == 5)
							{
								flag = false;
							}
						}
					}
					else if (choose1 == 5)
					{
						flag = false;
						flag1 = false;
					}

				}
			}
		}
		else if (choose == 5)
		{
			flag1 = false;
		}
		else
		{
			cout << "��Ч����" << endl;
			cin.clear();
			cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
		}
	}
	cout << "��л��ʹ�ñ���������ϵͳ" << endl;
	closesocket(client_socket);
	close_socket();
}