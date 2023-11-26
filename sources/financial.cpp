#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csv.h" //���� ������ �������� �ڵ�
using namespace std;

//��� 1
//�����ʹ� ����û�� ����Ʈ ���� API ���

//TO DO: ���� ��� 1 : û�� ���� ��å ����ȭ
//û�� ��å Ŭ����

class YouthPolicy {
private:
    string FieldPolicy;//�о� �Է� �޴� ����
    string RegionPolicy;//���� �Է� �޴� ����
    string input;
    //�о� ����
    vector<string> Fields = { "���ڸ�", "�ְ�", "����", "����", "����" }; 
    //���� ����
    vector<string> Regions = { "�߾�", "����", "�λ�", "�뱸", "��õ", "����", "����", "���", "���", "����", "���", "�泲", "����", "����", "���", "�泲", "����", "����" };
   // ���͸� �� ��å ����
    vector <string> Policy = {};

//TO DO: ���� ��� 2 : ����ڰ� �Է��� ���ǿ� �´� ��å ���
public:
    //��ȿ�� ���� �Լ�
    bool isValid(const string& userInput, const vector<string>& validOptions) {
        return userInput == "0" || find(validOptions.begin(), validOptions.end(), userInput) != validOptions.end();
    }

    // û�� ��å �о� �Է� �Լ�
    void Field() {
            cout << "��å �о߸� �����ϼ���(���� �� 0)" << endl;
            cout << "���ڸ�/ �ְ�/ ����/ ����/ ����" << endl;
            cin >> FieldPolicy;  

            while (!isValid(FieldPolicy, Fields)) {
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
                cin >> FieldPolicy;
            }
    }

    // û�� ��å ���� �Է� �Լ�
    void Region() {
        cout << "������ �����ϼ���(���� �� 0)" << endl;
        cout << "�߾�/����/�λ�/�뱸/��õ/����/����/���/���/����/���/�泲/����/����/���/�泲/����/����" << endl;
        cin >> RegionPolicy;   

        while (!isValid(RegionPolicy, Regions)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> RegionPolicy;
        }
    }

    // �Է¹��� ������ �о߿� �ش��ϴ� ��å ��� �Լ�
    void PolicyShow() {
        CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv"); // ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��

        // �Է¹��� �о߿� ������ ����Ͽ� ��å�� ���͸��ϰ� ���
        csvReader.PrintValue("youthPolicy.polyBizSecd", RegionPolicy, "youthPolicy.polyRlmCd", FieldPolicy, "youthPolicy.polyBizSjnm");
        cout << "�ڼ��� ������ ���� �ʹٸ� 1�� �Է��ϼ���" << endl;
        cin >> input;
        if (input == "1")
            csvReader.PrintInfo( RegionPolicy, FieldPolicy);
    }

    // FieldPolicy �� �������� �Լ�
    string getFieldPolicy() const {
        return FieldPolicy;
    }

    // RegionPolicy �� �������� �Լ�
    string getRegionPolicy() const {
        return RegionPolicy;
    }
};


int main() {
    YouthPolicy yp;
    while (true) {
            yp.Field();
            if (yp.getFieldPolicy() == "0")   //0  �Է��ϸ� ����
                break;
            yp.Region();
            if (yp.getRegionPolicy() == "0")
                break;
            yp.PolicyShow();


    }

    return 0;
}



