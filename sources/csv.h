#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
int num; //���ǿ� �´� ��å ��ȣ ����
using namespace std; 
//���� �о���� Ŭ����
class CSVReader {
public:
    CSVReader(const string& filename, char delimiter = ',') : filename_(filename), delimiter_(delimiter) {}
    // ���͸� �� ��å ����
    vector <string> Policy = {};
    //���� ���� �о����
    vector<vector<string>> readData() {
        ifstream in(filename_);
        if (!in.is_open()) {
            cerr << "Failed to open file: " << filename_ << endl;
            return {};
        }

        vector<vector<string>> data;
        string line;
        string currentRow;
        while (getline(in, line)) {
            currentRow += line;

            // ū �ؽ�Ʈ ����� ���� ��� ó��
            if (isInsideQuotes(currentRow)) {
                continue;
            }

            vector<string> row = readRow(currentRow);
            if (!row.empty()) {
                data.push_back(row);
            }

            // currentRow �ʱ�ȭ
            currentRow.clear();
        }

        in.close();
        return data;
    }

    //����ڰ� �Է��� ���ǿ� �´� ��å ��� �Լ�
    void PrintValue(const string& columnName1, const string& value1,
        const string& columnName2, const string& value2,
        const string& outputColumn) {
        int num = 1;
        vector<vector<string>> data = readData();
        if (data.empty()) {
            cerr << "Empty data" << endl;
            return;
        }

        // Ư�� �� ã��
        int columnIndex1 = -1;
        int columnIndex2 = -1;
        for (size_t i = 0; i < data[0].size(); ++i) {
            if (data[0][i] == columnName1) {
                columnIndex1 = static_cast<int>(i);
            }
            if (data[0][i] == columnName2) {
                columnIndex2 = static_cast<int>(i);
            }
        }

        if (columnIndex1 == -1 || columnIndex2 == -1) {
            cerr << "One or both columns not found" << endl;
            return;
        }

        // Ư�� ���� Ư�� �� ���� �� ���
        for (size_t i = 1; i < data.size(); ++i) {
            if (columnIndex1 < data[i].size() && columnIndex2 < data[i].size() &&
                data[i][columnIndex1] == value1 && data[i][columnIndex2] == value2) {
                if (outputColumn == "") {
                    for (const auto& cell : data[i]) {
                        cout <<" [" << cell << "]" << "\t";
                    }
                }
                else {
                    int outputIndex = -1;
                    for (size_t j = 0; j < data[0].size(); ++j) {
                        if (data[0][j] == outputColumn) {
                            outputIndex = static_cast<int>(j);
                            break;
                        }
                    }

                    if (outputIndex != -1) {
                        cout << num<< "[" << data[i][outputIndex] << "]";
                        num += 1;
                        Policy.push_back(data[i][outputIndex]);
                    }
                    else {
                        cerr << "Output column not found" << endl;
                    }
                }
                cout << endl;
            }
        }
    }



    // CSV ���Ͽ��� Ư�� ������ �����ϴ� ���� std::vector�� �����ϴ� �Լ�
    vector<vector<string>> getInfo(const string& Region, const string& Field) {
        vector<vector<string>> result;

        ifstream file(filename_);
        if (!file.is_open()) {
            cerr << "������ �� �� �����ϴ�." << endl;
            return result;
        }

        std::string line;
        string currentRow;
        bool issideQuotes = false;
        while (getline(file, line)) {
            currentRow += line;
            // ū �ؽ�Ʈ ����� ���� ��� ó��
            issideQuotes = isInsideQuotes(currentRow);

            // ū �ؽ�Ʈ ����� ������ ��
            if (!issideQuotes) {
                vector<string> tokens;
                istringstream iss(currentRow);
                string token;

                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                // Ư�� ������ �����ϴ� ������ Ȯ��
                if (tokens.size() >= 33 && tokens[2] == Region && tokens[32] == Field) {
                    result.push_back(tokens);
                }

                // currentRow �ʱ�ȭ
                currentRow.clear();
            }
        }

        file.close();
        return result;
    }

    // ���͸� �� ��å �ڼ��� ������ ����ϴ� �Լ�
    void PrintInfo(const string& Region, const string& Field) {
        vector<vector<string>> info = getInfo(Region, Field);
        int input=0;
        cout << "�ڼ��� ������ ���� ���� ��å�� ��ȣ�� �Է��ϼ���(������ 0)" << endl;
        cin >> input;
        // ����� ��� ���
        while (input != 0) {
            // ����� ���� �ִ��� Ȯ��
            if (input >= 1 && input <= Policy.size()) {
                // �Է¹��� ���� ���� ���
                for (const auto& cell : info[input - 1]) {
                    // ������ �ʿ��� ������ ���
                    if (cell != "-") {
                        if ((&cell - &info[input - 1][0] >= 2) or (&cell - &info[input - 1][0]==9) or (&cell - &info[input - 1][0] == 32))
                            switch (&cell - &info[input - 1][0]) {
                            case 2:
                                cout << "����: [" << cell << "]" << endl;
                                break;
                            case 3:
                                cout << "��� �� ����ü ����: [" << cell << "]" << endl;
                                break;
                            case 4:
                                cout << "��å��: [" << cell << "]" << endl;
                                break;
                            case 5:
                                cout << "��å �Ұ�: [" << cell << "]" << endl;
                                break;
                            case 6:
                                cout << "���� ����: [" << cell << "]" << endl;
                                break;
                            case 7:
                                cout << "���� �Ը�: [" << cell << "]" << endl;
                                break;
                            case 8:
                                cout << "�����Ⱓ: [" << cell << "]" << endl;
                                break;
                            case 10:
                                cout << "�����û�Ⱓ: [" << cell << "]" << endl;
                                break;
                            case 11:
                                cout << "����: [" << cell << "]" << endl;
                                break;
                            case 12:
                                cout << "���� ���: [" << cell << "]" << endl;
                                break;
                            case 13:
                                cout << "��� ����: [" << cell << "]" << endl;
                                break;
                            case 14:
                                cout << "Ưȭ �о�: [" << cell << "]" << endl;
                                break;
                            case 15:
                                cout << "�з� ���: [" << cell << "]" << endl;
                                break;
                            case 16:
                                cout << "������ �� �ҵ�����: [" << cell << "]" << endl;
                                break;
                            case 17:
                                cout << "�߰��ܼ� ����: [" << cell << "]" << endl;
                                break;
                            case 18:
                                cout << "���� ���� ���: [" << cell << "]" << endl;
                                break;
                            case 19:
                                cout << "��û ����: [" << cell << "]" << endl;
                                break;
                            case 20:
                                cout << "���� ����: [" << cell << "]" << endl;
                                break;
                            case 21:
                                cout << "�ɻ� ��ǥ: [" << cell << "]" << endl;
                                break;
                            case 22:
                                cout << "��û ����Ʈ �ּ�: [" << cell << "]" << endl;
                                break;
                            case 23:
                                cout << "���� ����Ʈ URL1: [" << cell << "]" << endl;
                                break;
                            case 24:
                                cout << "���� ����Ʈ URL1 : [" << cell << "]" << endl;
                                break;
                            case 25:
                                cout << "�ְ� ��ó : [" << cell << "]" << endl;
                                break;
                            case 26:
                                cout << "�ְ���ó ����� �̸� : [" << cell << "]" << endl;
                                break;
                            case 27:
                                cout << "�ְ���ó ����� ����ó : [" << cell << "]" << endl;
                                break;
                            case 28:
                                cout << "������ : [" << cell << "]" << endl;
                                break;
                            case 29:
                                cout << "���� ����� �̸� : [" << cell << "]" << endl;
                                break;
                            case 30:
                                cout << "���� ����� ����ó : [" << cell << "]" << endl;
                                break;
                            case 31:
                                cout << "��Ÿ���� : [" << cell << "]" << endl;
                                break;
                           }
                        cout << endl;
                    }
         
                }
            }
            // ��� ��ȣ�� �Է����� ��� ���� ���
            else {
                cout << "�Է��� ��ȣ�� ��å�� �������� �ʽ��ϴ�." << endl;
            }
            cout << "�ڼ��� ������ ���� ���� ��å�� ��ȣ�� �Է��ϼ���(������ 0)" << endl;
            cin >> input;
        }
    }
    //Ư�� ���� ���� ������� ���� ��������
    vector<vector<string>> GetInfo(const string& bank) {
        vector<vector<string>> result;

        ifstream file(filename_);
        if (!file.is_open()) {
            cerr << "������ �� �� �����ϴ�." << endl;
            return result;
        }

        std::string line;
        string currentRow;
        bool issideQuotes = false;
        while (getline(file, line)) {
            currentRow += line;
            // ū �ؽ�Ʈ ����� ���� ��� ó��
            issideQuotes = isInsideQuotes(currentRow);

            // ū �ؽ�Ʈ ����� ������ ��
            if (!issideQuotes) {
                vector<string> tokens;
                istringstream iss(currentRow);
                string token;

                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                // Ư�� ������ �����ϴ� ������ Ȯ��
                if (tokens[0] == bank) {
                    result.push_back(tokens);
                }

                // currentRow �ʱ�ȭ
                currentRow.clear();
            }
        }

        file.close();
        return result;
    }
    //����ڰ� �Է��� ���࿡ ���� û�⵵����� ���� ��� �Լ�
    void YouthAccount( const string& value) {
        vector<vector<string>> info = GetInfo(value);
        // ����� ��� ���
        for (const auto& cell : info[0]) {
            //     // �� ���� ���� ��� 
          switch (&cell - &info[0][0]){
                    case 0:
                        cout << "�����: [" << cell << "]" << endl;
                        break;
                    case 1:
                        cout << "�⺻ �ݸ�(3�� ����): [" << cell << "]" << endl;
                        break;
                    case 2:
                        cout << "�ҵ� ���ݸ�: [" << cell << "]" << endl;
                        break;
                    case 3:
                        cout << "���ݴ㺸�밡��ݸ�(�����Ͻû�ȯ����): [" << cell << "]" << endl;
                        break;
                    case 4:
                        cout << "���ݴ㺸�밡��ݸ�(�ѵ�����): [" << cell << "]" << endl;
                        break;
                    case 5:
                        cout << "���ݴ㺸�밡��ݸ�(���Ⱑ���ѵ�): [" << cell << "]" << endl;
                        break;
                    case 6:
                        cout << "���ະ ���ݸ�: [" << cell << "]" << endl;
                        break;
                    case 8:
                        cout << "���� �� �ݸ�: [" << cell << "]" << endl;
                        break;
                    case 9:
                        cout << "�������: [" << cell << "]" << endl;
                        break;
                    case 10:
                        cout << "��Ÿ ���ǻ���: [" << cell << "]" << endl;
                        break;
                    case 11:
                        cout << "���� ��ũ: [" << cell << "]" << endl;
                        break;


                    }
          cout << endl;
                }

            }
    //����ڰ� �Է��� ���࿡ ���� û�⵵����� ���� ��� �Լ�
    void FinancialManual(const string& name) {
        vector<vector<string>> info = GetInfo(name);
        // ����� ��� ���
        for (const auto& cell : info[0]) {
            // �� ���� ���� ��� 
            switch (&cell - &info[0][0]) {
            case 1:
                cout << cell << endl;
                break;
            case 2:
                cout << "���� ����: [" << cell << "]" << endl;
                break;
            case 3:
                cout << "�ҵ� ����: [" << cell << "]" << endl;
                break;
            case 4:
                cout << "�Ⱓ: [" << cell << "]" << endl;
                break;
            case 5:
                cout << "�� ���Ա�: [" << cell << "]" << endl;
                break;
            case 6:
                cout << "���� ������: [" << cell << "]" << endl;
                break;
            case 7:
                cout << "��Ÿ ����: [" << cell << "]" << endl;
                break;
            case 8:
                cout << "���� URL: [" << cell << "]" << endl;
                break;
            }
            cout << endl;
        }
    }
        
    
    
private:
    string filename_;
    char delimiter_;
    //����ǥ �ȿ� ��ǥ�� ���� ����� ó��
    bool isInsideQuotes(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '"') {
                count++;
            }
        }
        return count % 2 != 0;  // ����ǥ ������ Ȧ���̸� ����ǥ �ȿ� �ִٰ� �Ǵ�
    }
    // ��ǥ�� �����Ͽ� �� �б�(csv ����)
    vector<string> readRow(const string& line) {
        stringstream ss(line);
        vector<string> row;

        string cell;
        while (getline(ss, cell, delimiter_)) {

        row.push_back(cell);
        }

        return row;
    }
};

