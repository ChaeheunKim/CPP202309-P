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
            cout << "---------------------------------" << endl;
            cout << "���ڸ�/ �ְ�/ ����/ ����/ ����" << endl;
            cout << "---------------------------------" << endl;
            cin >> FieldPolicy;  

            while (!isValid(FieldPolicy, Fields)) {
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
                cin >> FieldPolicy;
            }
    }

    // û�� ��å ���� �Է� �Լ�
    void Region() {
        cout << "������ �����ϼ���(���� �� 0)" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "�߾Ӻ�ó/����/�λ�/�뱸/��õ/����/����/���/���/����/���/�泲/����/����/���/�泲/����/����" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
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
    //������ǰ ���� 
    vector<string> FinancialItem = { "û�⵵�����", "����","����","����","������ǰ����"};
    //���� 
    vector<string>  Banks = {"NH��������",	"��������","�츮����","SC��������","�ϳ�����",	 "IBK�������",	"KB��������","DGB�뱸����","BNK�λ�����","��������","��������","BNK�泲����"};
    //���� ����
    vector<string> Deposit = { "�������������","���⿹��"};
    //���� ����
    vector<string> saving = { "����������","����������" };
    //�ݸ� ����
    vector<string> interest = {"����","�ܸ�"};
    //������ǰ ����
    vector<string> Finan = { "û�⵵�����","������������� ", "���⿹��" ,"��������������","��������������","�ܸ�","����" };

    
public:
    //��ȿ�� ���� �Լ�
    bool isValid(const string& userInput, const vector<string>& validOptions) {
        return userInput == "0" || find(validOptions.begin(), validOptions.end(), userInput) != validOptions.end();
    }

    //TO DO: ���� ��� 2 : ����� ��Ȳ ���� ���� ���� ���
    // ����� �Է� �Լ�
    void Bank() {
        cout << "������ �����ϼ���" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "NH�������� /�������� /�츮���� /SC�������� /�ϳ����� /IBK������� /KB�������� /DGB�뱸���� /BNK�λ����� /�������� /�������� /BNK�泲����" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------- " << endl;
        cin >> BankType;

        while (!isValid(BankType, Banks)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> BankType;
        }
    }

    // ���� ��ǰ �Է� �Լ�
    void Item() {
        cout << "���� ��ǰ�� �����ϼ���(���� �� 0)" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "û�⵵�����/����/����/����/������ǰ����" << endl;
        cout << "-----------------------------------------"<< endl;
        cin >> FinancialType;

        while (!isValid(FinancialType, FinancialItem)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> FinancialType;
        }
    }
    
    //������, ���� ������ ���࿬��ȸ ���� ���(�ݸ� ���� 2023.12.20)
    //����ڿ��� ���� ���� �Է¹ޱ�
    string userdeposit; //����� �Է� ���� ����
    void inputdeposit() {
        cout << "�˰���� ���� ������ �����ϼ���(���� �� 0)" << endl;
        cout << "----------------------------------------" << endl;
        cout << "�������������/ ���⿹��" << endl;
        cin >> userdeposit;
       
        //����� �Է� ��ȿ�� ����
        while (!isValid(userdeposit, Deposit)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> userdeposit;
        }      
    }

    //����ڿ��� ���� ���� �Է¹ޱ�
    void Saving() {
        cout << "�˰���� ���� ������ �����ϼ���(���� �� 0)" << endl;
        cout << "----------------------------------------" << endl;
        cout << "����������/ ����������" << endl;
        cin >> userdeposit;

        //����� �Է� ��ȿ�� ����
        while (!isValid(userdeposit, saving)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> userdeposit;
        }
    }

    //����ڰ� �Է��� ���࿡ ���� ������ ���� ���� ���
    void deposit() {
        string userinterest; //����� �Է� �ݸ� ����
        //����
        if (userdeposit == "�������������") {
            CSVReader csvReader("C:/Users/chee0/Downloads/freedeposit.csv"); // freedeposit.csv ����, ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
            Bank();
            csvReader.PrintValue("����",BankType,"����",BankType,"��ǰ��");
            csvReader.FreeDeposit(BankType);
        }
        else if (userdeposit == "���⿹��") {
            CSVReader csvReader("C:/Users/chee0/Downloads/timedeposit.csv"); // timedeposit.csv ����, ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
            Bank();
            csvReader.PrintValue("����", BankType, "����", BankType, "��ǰ��");
            csvReader.FreeDeposit(BankType);
        }
        
        //����
        else if (userdeposit == "����������") {
            CSVReader csvReader("C:/Users/chee0/Downloads/saving.csv"); // saving.csv ����, ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
            Bank();
            csvReader.PrintValue("����", BankType, "����", BankType, "��ǰ��");
            csvReader.FreeDeposit(BankType);
        }
        else if (userdeposit == "����������") {
            cout << "�ݸ� ��� ����� �����ϼ���" << endl;
            cout << "------------------------------" << endl;
            cout << "�ܸ�/ ����" << endl;
            cin >> userinterest;
            //����� �Է� ��ȿ�� ����
            while (!isValid(userinterest, interest)) {
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
                cin >> userinterest;
             
            }
            CSVReader csvReader("C:/Users/chee0/Downloads/freesaving.csv"); // freesaving.csv ����, ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
            Bank();
            csvReader.PrintValue("����", BankType, "�ݸ������", userinterest, "��ǰ��");
            csvReader.FreeSaving(BankType, userinterest);
            
        }

    }

    // �Է¹��� ���࿡ ���� û�⵵����� ���� ��� �Լ�
    void FinancialShow() {
        CSVReader csvReader("C:/Users/chee0/Downloads/financial.csv"); // ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
        Bank();
        csvReader.YouthAccount(BankType);
    }


    void ManualShow() {
        cout << "������ ���ϴ� ���� �� �������ּ���." << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "û�⵵�����/�������������/���⿹��/��������������/ ��������������/ �ܸ�/����" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cin >> ManuaInput;
        //����� �Է� ��ȿ�� ����
        while (!isValid(ManuaInput, Finan)) {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            cin >> ManuaInput;
        }
        CSVReader csvReader("C:/Users/chee0/Downloads/Info2.csv"); // ���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
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
    string userinput;
    while (true) {
        cout << "�˰���� ������ ��ȣ�� �Է��ϼ���.(���� �� 0)" << endl;
        cout << "-------------------------------" << endl;
        cout << "1.��å ���� 2.������ǰ����" << endl;
        cout << "-------------------------------" << endl;
        cin >> userinput;
        if (userinput == "0") {
            break; //0 �Է� �� ����
        }
        else if (userinput == "1") {
            yp.Field();
            if (yp.getFieldPolicy() == "0")   //0  �Է��ϸ� ����
                break;
            yp.Region();
            if (yp.getRegionPolicy() == "0")
                break;
            yp.PolicyShow();
        }
        else if (userinput == "2") {
            yf.Item();
            if (yf.getFinancialType() == "0")
                break;
            else if (yf.getFinancialType() == "û�⵵�����") {
                yf.FinancialShow();  // YouthAccount �Լ� ȣ��
            }
            else if (yf.getFinancialType() == "������ǰ����") {
                yf.ManualShow();  // YouthManual �Լ� ȣ��
            }
            else if (yf.getFinancialType() == "����") {
                yf.inputdeposit(); 
                yf.deposit(); //Freedepoist �Լ� ȣ��
            }
            else if (yf.getFinancialType() == "����") {
                yf.Saving();
                yf.deposit(); //Freedepoist �Լ� ȣ��
            }
        }
        else {
            cout << "1 �Ǵ� 2�� �Է����ּ���" << endl;
        }
    }

    return 0;
}

