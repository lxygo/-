#include"../tcpSocket/tcpSocket.h"
#include"../Server/system1.h"
using namespace std;
int main()
{
	init_socket();
	bool flag = true;
	SOCKET server_socket = creat_server_socket();
	char buf[BUFSIZ] = { 0 };
	int choose1;//�ֲ�������Ӱ���ⲿ��choose
	cout << "wait client" << endl;
	SOCKET client_socket = accept(server_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		err("accept");
	}//���ͨ�ŵ�����

	cout << "��ӭʹ����������ϵͳ" << endl;
	System Logsystem;
	Logsystem.Read();
	string id;
	string password;
	int order = -1;//���
	int service;//ѡ��ķ���ʽ
	int choose;
	int i;
	bool flag1 = true;

	while (flag1)
	{
		cout << "��ѡ����Ҫ��¼�ķ�ʽ��" << endl;
		cout << "1.ֱ�ӵ�¼ 2.���û�ע�� 3.����Ա��¼ 4.���Ա��¼ 5.�˳�ϵͳ" << endl;
		recv(client_socket,(char*)&choose, 4, 0);
		cout << choose;//������
		if (choose == 1)
		{
			cout << "����������û���:";
			memset(buf, 0, BUFSIZ);
			recv(client_socket,buf, BUFSIZ, 0);
			id = buf;
			order = Logsystem.Finduser(id);
			send(client_socket, (char*)&order,4, 0);
			if (order == -1)
			{
				cout << "δ��ѯ������û�,�����ע��" << endl;
			}
			else
			{
				flag = Logsystem.Log(order,client_socket);
				while (flag)
				{
					cout << "\n��ѡ������Ҫ�ķ���" << endl;
					cout << "1.��ѯ�����Ϣ 2.���Ϳ�� 3.ǩ�տ�� " << endl;
					cout << "4.�޸��˻����� 5.�����˻���ֵ 6.�˻�����ѯ 7.�޸ĸ�����Ϣ 8 �˳�ϵͳ" << endl;
					recv(client_socket, (char*)&service, 4, 0);
					cout << service << endl;//hsuchu
					if (service == 1)
					{
						cout << "��ѡ������Ҫ�Ĳ�ѯ����" << endl;
						cout << "1.��ѯȫ�������Ϣ 2.ͨ��ʱ����в�ѯ 3.ͨ����ݵ��Ž��в�ѯ" << endl;
						recv(client_socket, (char*)&choose1, 4, 0);
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
						memset(buf, 0, BUFSIZ);
						recv(client_socket, buf, BUFSIZ, 0);
						receiver = buf;
						int  receive_order;
						receive_order = Logsystem.Finduser(receiver);
						send(client_socket, (char*)&receive_order, 4, 0);
						Logsystem.Send(order, receive_order, client_socket);
					}
					else if (service == 3)
					{
						Logsystem.Receive(order, client_socket);
					}
					else if (service == 4)
					{
						Logsystem.allusers[order].Change_password(client_socket);
					}
					else if (service == 5)
					{
						Logsystem.allusers[order].Add_money(client_socket);
					}
					else if (service == 6)
					{
						Logsystem.allusers[order].Show_money(client_socket);
					}
					else if (service == 7)
					{
						Logsystem.allusers[order].Change_message(client_socket);
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
			cout << "����������Ҫid��";
			string id;
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			id = buf;
			order = Logsystem.Finduser(id);
			send(client_socket, (char*)&order, 4, 0);
			if (order == -1)
			{
				Users new_user;
				new_user.Change_message(client_socket);
				new_user.Register(id,client_socket);
				new_user.Add_money(client_socket);
				order = Logsystem.users_num;
				Logsystem.allusers.push_back(new_user);
				Logsystem.users_num++;
			}
			else
			{
				cout << "��id��ע��" << endl;
			}
		}
		else if (choose == 3)
		{
			int judge;
			cout << "����������û�����";
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			id = buf;
			if (id.compare(Logsystem.alladmin[0].user_name) == 0)
			{
				judge = 1;
				send(client_socket, (char*)&judge, 4, 0);
				flag = Logsystem.Adminlog(client_socket);
				while (flag)
				{
					cout << "\n��ѡ����Ҫ���еķ���:" << endl;
					cout << "1.��ѯĳһ�û���Ϣ  2.��ѯ�����û���Ϣ  3.ͨ���û���ѯ���  4.ͨ��ʱ���ѯ���  5.ͨ����ݵ��Ų�ѯ���" << endl;
					cout << "6.�޸Ĺ���Ա����  7.�޸Ĺ���Ա����  8.������Ա 9.�˳�" << endl;
					recv(client_socket, (char*)&service, 4, 0);
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
						Logsystem.alladmin[0].Changename(client_socket);
					}
					else if (service == 7)
					{
						Logsystem.alladmin[0].Changepassword(client_socket);
					}
					else if (service == 8)
					{
						cout << "��ѡ����Ҫ���еķ���:";
						cout << "1.�鿴���Ա��Ϣ 2.��ѯ�����յĿ����Ϣ 3.��ӿ��Ա 4.ɾ�����Ա 5.�������տ�� " << endl;
						int choose1;
						recv(client_socket, (char*)&choose1, 4, 0);
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
				judge = 0;
				send(client_socket, (char*)&judge, 4, 0);
				cout << "���û����ǹ���Ա" << endl;
			}
		}
		else if (choose == 4)
		{
			string id;
			int choose1;
			cout << "����������û�����";
			memset(buf, 0, BUFSIZ);
			recv(client_socket, buf, BUFSIZ, 0);
			id = buf;
			order = Logsystem.Findcourier(id);
			send(client_socket, (char*)&order, 4, 0);
			if (order != -1)
			{
				flag = Logsystem.Courierlog(id,client_socket);
				while (flag)
				{
					cout << "��¼�ɹ�����ӭ����" << endl;
					cout << "��ѡ����Ҫ���еķ���";
					cout << "1.��ѯ�����յĿ�� 2.��ѯ�������յĿ�� 3.���տ�� 4.��ѯ��� 5.�˳�ϵͳ";
					cout << endl;
					recv(client_socket, (char*)&choose1, 4, 0);
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
							recv(client_socket, (char*)&choose2, 4, 0);
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
	Logsystem.Store();
	cout << "��л��ʹ�ñ���������ϵͳ" << endl;
	closesocket(client_socket);
	closesocket(server_socket);
	close_socket();
}