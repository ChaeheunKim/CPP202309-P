#include <iostream>
using namespace std;

//��� 1
//TO DO: ���� ��� 1 : û�� ���� ��å ����ȭ
//�����ʹ� ����û�� ����Ʈ ���� API ��� ����

//û�� ��å Ŭ����
class YouthPolicy {
private:
	char FieldPolicy;
	char RegionPolicy;
	char FieldSelect;//�о� ���� ����
	char RegionSelect; //���� ���� ����
	char Policy;// ��å ����
public:
	void Field();
	void Region();
	void PolicyShow();
};

//û�� ��å �о� �Է� �Լ�
void YouthPolicy::Field() {
	char FieldPolicy;
	cout << "��å �о߸� �����ϼ���(���� �� 0)" << endl;
	cout << "�о� ��ü/ ���ڸ�/ �ְ�/ ����/ ����.��ȭ/ ����.�Ǹ�" << endl;
	cin >> FieldPolicy;
}
//û�� ��å ���� �Է� �Լ�
void YouthPolicy::Region() {
	char RegionPolicy;
	cout << "������ �����ϼ���(���� �� 0)" << endl;
	cout << "���� ��ü/�߾�/����/�λ�/�뱸/��õ/����/����/���/���/����/���/�泲/����/����/���/�泲/����/����" << endl;
	cin >> RegionPolicy;
}

//�Է¹��� ������ �о߿� �ش��ϴ� ��å ��� �Լ�
void YouthPolicy::PolicyShow() {
	if ((FieldPolicy == "�о� ��ü") && (RegionSelect == "���� ��ü")) {
		cout << Policy << endl;  //��� ��å ���
	}
	else if ((FieldPolicy == "�о� ��ü") && (RegionSelect == RegionPolicy)) {
		//Policy = //�����Ϳ��� ����ڰ� ������ ������ �ش��ϴ� ��å
		cout << Policy << endl;
	}
	else if ((FieldPolicy == FieldPolicy) && (RegionSelect == "���� ��ü")) {
		//Policy = //�����Ϳ��� ����ڰ� ������ �о߿� �ش��ϴ� ��å
		cout << Policy << endl;
	}
	else if ((FieldSelect == FieldPolicy) && (RegionSelect == RegionPolicy)) {
		//Policy = //�����Ϳ��� ����ڰ� ������ ������ �о߿�  ��� �ش��ϴ� ��å
		cout << Policy << endl;
	}
}
int main() {
	YouthPolicy yp;
	while (true) {
		yp.Field();
		yp.Region();
		yp.PolicyShow();
		if ((FieldPolicy == 0) or (RegionPoicly == 0))
			break;
	}
}
