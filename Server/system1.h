#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"../tcpSocket/tcpSocket.h"
using namespace std;
class Users {  //�û���
public:
	string name;//�û�������
	string phone;//�û��ĵ绰
	double money;//�û����
	string address;//�û���ַ
	string user_name;//�û�������֤Ψһ��
	string password;//����
	bool new_users;//�ж��Ƿ������û�
	int send_numbers;	//���͵Ŀ������
	int receive_numbers;//���ܵĿ������
	int not_re_nums;	//δ���յĿ������

	vector<int>send_package;//���͵Ŀ��
	vector<int>not_receive;//δǩ�յĿ��
	vector<int>receive;//���տ��

	Users();
	void Register(string id, SOCKET& client_socket);//ע��
	void Change_password(SOCKET& client_socket);//�޸�����
	void Change_message(SOCKET& client_socket);//�޸ĸ�����Ϣ
	void Add_money(SOCKET& client_socket);//��ֵ
	void Show_money(SOCKET& client_socket)const;//��ѯ���
	void Storeusers(ofstream& out);//����Ϣд���ļ�
	void Readusers(ifstream& in);//��ȡ�û���Ϣ
};
class Package {  //�����
public:
	string package_num;//��ݵ���
	int send_time[6] = { 0 };//����ʱ��
	int receive_time[6] = { 0 };//����ʱ��
	int collect_time[6] = { 0 };//����ʱ��
	double money;//��ݼ۸�
	string package_name;//��������
	string type;//��ݵ�����
	string sender;//�ļ��û�
	string receiver;//�ռ��û�
	bool sign;//ǩ��״̬
	bool collect;//����״̬
	string note;//��ݱ�ע
	Package();
	virtual void Getprice(double weight);
	void StorePackage(ofstream& out);//�洢�����Ϣ
	void ReadPackage(ifstream& in);//��ȡ�����Ϣ
	void SendPackage(string t_sender, string t_receiver, SOCKET& client_socket);//��¼�ļ�ʱ�䣬�ļ��ˣ��ռ��ˣ�ǩ��״̬
	void CollectPackage();
	void ReceivePackage();//��¼ǩ��״̬��ǩ��ʱ��
	void ShowPackage(SOCKET& client_socket)const;//��ѯ���״̬
	void Make_PackageNum();//������ɿ�ݵ���
};
class Fragile :public Package {
public:
	Fragile() :Package() {
		type = "����Ʒ";
	}
	virtual void Getprice(double weight);
};
class Book :public Package {
public:
	Book() :Package() {
		type = "ͼ��";
	}
	virtual void Getprice(double weight);
};
class Normal :public Package {
public:
	Normal() :Package() {
		type = "��ͨ���";
	}
	virtual void Getprice(double weight);
};
class Administrator {  //����Ա��
public:
	string user_name;
	string name;
	string password;
	double money;//�˻����
	vector<int>courier_order;
	Administrator();
	void Changename(SOCKET& client_socket);//�޸Ĺ���Ա����
	void Changepassword(SOCKET& client_socket);//�޸�����
	void Storeadmin(ofstream& out);//�洢��Ϣ
	void Readadmin(ifstream& in);//��ȡ��Ϣ
};
class Courier { //���Ա��
public:
	string user_name;//�û���
	string name;//����
	string phone;//�绰
	double money;//���
	string password;//����
	vector<int>not_collect;//δ���յĿ��
	vector<int>collect;//�����տ��
	int not_collect_num;//δ���յĿ������
	int collect_num;//�����յĿ������

	Courier();
	void Changepassword();
	void Showmoney();
	void Storecour(ofstream& out);
	void Readcour(ifstream& in);
};
class System {
public:
	vector<Users> allusers;//�����û��ļ���
	vector<Package> allpackages;//���п�ݵļ���
	vector<Administrator>alladmin;//���й���Ա�ļ���
	vector<Courier>allcouriers;//���п��Ա�ļ���
	vector<int>not_assign;//δ������Ա�Ŀ��
	int users_num;//�û�����
	int packages_num;//�������
	int admin_num;//����Ա����
	int courier_num;//���Ա������
	int not_assgin_num;//������Ŀ������
	System();
	void Store();//�洢ϵͳ��Ϣ
	void Read();//��ȡϵͳ��Ϣ
	int Finduser(string user_name);//�����û��Ƿ����
	int Findcourier(string courier_name);//���ҿ��Ա�Ƿ����
	bool Log(int order, SOCKET& client_socket);//�Ƿ��¼�ɹ�
	bool Adminlog(SOCKET& client_socket);
	bool Courierlog(string id,SOCKET&client_socket);
	void Send(int sender, int receiver,SOCKET& client_socket);//�ļ�ʱ��״̬�����޸�
	void Receive(int receiver, SOCKET& client_socket);//ǩ��ʱ�������״̬���޸�
	void Show(int sender, SOCKET& client_socket);//��ѯ�û���صĿ��
	void Showbytime(int order, SOCKET& client_socket)const;//�û�ͨ��ʱ��������
	void Showbynum(int order, SOCKET& client_socket);//�û�ͨ����ݵ���������
	void Adshowbyuser(SOCKET&client_socket);//����Աͨ���û�����ѯ�û���Ϣ
	void Adshowbyallusers(SOCKET&client_socket)const;//����Ա��������û�����Ϣ
	void Adshowbyid(SOCKET&client_socket);//����Աͨ���û�������ѯ���
	void Adshowbytime(SOCKET&client_socket)const;//����Աͨ��ʱ���ѯ��ʷ���
	void Adshowbynum(SOCKET&client_sockeet)const;//����Աͨ�����Ž��в�ѯ��ʷ���
	void Adshowcourier(SOCKET&client_socket);//����Ա��ѯ���Ա����Ϣ
	void Adshowcollect(SOCKET& client_socket);//����Ա��ѯ���Ա��������Ϣ
	void Addcourier(SOCKET&client_socket);//��ӿ��Ա
	void Deletecourier(SOCKET&client_socket);//ɾ�����Ա
	void Assign(SOCKET&client_socket);//������
	void Coshow_not_collect(int order,SOCKET&client_socket)const;//���Ա��ѯ�Լ�δ���յĿ��
	void CoSearch(int order,SOCKET&client_socket);//���Ա��ѯ�Լ������յ����п����Ϣ
	void Coshowbysend(int order,SOCKET&client_socket)const;//���Աͨ�������˲�ѯ���
	void Coshowbyreceive(int order,SOCKET&client_socket)const;//���Աͨ�������˲�ѯ���
	void Coshowbytime(int order,SOCKET&client_socket)const;//���Աͨ��ʱ������ѯ�����Ϣ
	void Coshowbynum(int order,SOCKET&client_socket)const;//���Աͨ����ݵ��Ž��п�ݲ�ѯ
	void Cocollect(int order,SOCKET&client_socket);//���Ա���տ��

};
