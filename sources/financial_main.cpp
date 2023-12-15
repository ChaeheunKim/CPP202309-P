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
    vector<string> Regions = { "�߾Ӻ�ó", "����", "�λ�", "�뱸", "��õ", "����", "����", "���", "���", "����", "���", "�泲", "����", "����", "���", "�泲", "����", "����" };
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
        cout << "�߾Ӻ�ó/����/�λ�/�뱸/��õ/����/����/���/���/����/���/�泲/����/����/���/�泲/����/����" << endl;
        cin >> RegionPolicy;   

        while (!isValid(RegionPolicy, Regions)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> RegionPolicy;
        }
    }
    //TO DO: ���� ��� 3 : �ڼ��� ���� ���
    // �Է¹��� ������ �о߿� �ش��ϴ� ��å ��� �Լ�
    void PolicyShow() {
        CSVReader csvReader("C:/Users/chee0/Downloads/download/YouthData.csv"); // ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��

        // �Է¹��� �о߿� ������ ����Ͽ� ��å�� ���͸��ϰ� ���
        csvReader.PrintValue("youthPolicy.polyBizSecd", RegionPolicy, "youthPolicy.polyRlmCd", FieldPolicy, "youthPolicy.polyBizSjnm");
        csvReader.PrintInfo(RegionPolicy, FieldPolicy);
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
//��� 2 : ���� �� ������ǰ ���� ���
//TO DO: ���� ��� 1: �� ����� ���� ���� �� ����ȭ
//�� ����� Ȩ������ ���� ����(�ݸ� ���� 2023.12.03)
class YouthFinancial {
private:
    string FinancialType;//������ǰ ���� �Է� �޴� ����
    string BankType;//���� �Է� �޴� ����
    string input;
    string ManuaInput; // ���ϴ� ��ǰ ���� �Է� �޴� ����
    //������ǰ ���� ����
    vector<string> FinancialItem = { "û�⵵�����", "û���������", "��Ÿ������ǰ","������ǰ����"};
    //���� ����
    vector<string>  Banks = {"NH��������",	"��������","�츮����","SC��������","�ϳ�����",	 "IBK�������",	"KB��������","DGB�뱸����","BNK�λ�����","��������","��������","BNK�泲����"};


    
public:
    //��ȿ�� ���� �Լ�
    bool isValid(const string& userInput, const vector<string>& validOptions) {
        return userInput == "0" || find(validOptions.begin(), validOptions.end(), userInput) != validOptions.end();
    }
//TO DO: ���� ��� 2 : ����� ��Ȳ ���� ���� ���� ���
    // ����� �Է� �Լ�
    void Bank() { 
        cout << "������ �����ϼ���(���� �� 0)" << endl;
        cout << "NH�������� /�������� /�츮���� /SC�������� /�ϳ����� /IBK������� /KB�������� /DGB�뱸���� /BNK�λ����� /�������� /�������� /BNK�泲����" << endl;
        cin >> BankType;

        while (!isValid(BankType,Banks)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> BankType;
        }
    }

    // ���� ��ǰ �Է� �Լ�
    void Item() {
        cout << "���� ��ǰ�� �����ϼ���(���� �� 0)" << endl;
        cout << "û�⵵����� /û��������� /��Ÿ������ǰ/������ǰ����" << endl;
        cin >> FinancialType;

        while (!isValid(FinancialType, FinancialItem)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> FinancialType;
        }
        // �Է¹��� ��ǰ�� ���� ���� ��� 
        if (FinancialType == "û�⵵�����" || FinancialType=="û���������") {
            //���� �Է¹ޱ�
            YouthFinancial Bank();
            CSVReader csvReader("C:/Users/chee0/Downloads/financial.csv"); // ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
            csvReader.YouthAccount(BankType);
        }
        else if (FinancialType == "������ǰ����") {
            YouthFinancial Manualshow();
        }
    }
   

    void ManualShow() {
            cout << "������ ���ϴ� ��ǰ�� �����ּ���." << endl;
            cout << "û�⵵�����/û���������/��Ÿ������ǰ" << endl;
            cin >> ManuaInput;
            CSVReader csvReader("C:/Users/chee0/Downloads/info.csv");
            csvReader.FinancialManual(ManuaInput);
    }


    // BankType �� �������� �Լ�
    string getBankType() const {
        return BankType;
    }

    // FinancialType �� �������� �Լ�
    string getFinancialType() const {
        return FinancialType;
    }
};



int main() {
    YouthPolicy yp;
    YouthFinancial yf;
    while (true) {
            yp.Field();
            if (yp.getFieldPolicy() == "0")   //0  �Է��ϸ� ����
                break;
            yp.Region();
            if (yp.getRegionPolicy() == "0")
                break;
            yp.PolicyShow();
            yf.Item();
            if (yf.getFinancialType() == "0")
              break;

    }

    return 0;
}



