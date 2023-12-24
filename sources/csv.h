#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
int num; //���ǿ� �´� ��å ��ȣ ����
using namespace std; 
unordered_map<string, int> useractivity; //����� �Է� Ƚ��
//���� �о���� Ŭ����
class CSVReader {
public:
    CSVReader(const string& filename, char delimiter = ',') : filename_(filename), delimiter_(delimiter) {}
    // ��õ ��ǰ ���� ����
    vector <string> recommand = {};
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
        int num = 1; // ��å ��ȣ �ʱ�ȭ
        vector<vector<string>> data = readData();
        //������ ��ȿ�� ����
        if (data.empty()) {
            cerr << "Empty data" << endl;
            return;
        }

        // �Է¿� �ش��ϴ� �� ã��
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

        // ����ڰ� �Է��� ���� �´� ����Ʈ ���
        bool found = false; // ���ǿ� �´� ���� ��ǰ ��ȿ�� ����
        for (size_t i = 1; i < data.size(); ++i) {
            if (columnIndex1 < data[i].size() && columnIndex2 < data[i].size() &&
                data[i][columnIndex1] == value1 && data[i][columnIndex2] == value2) {
                found = true;
                if (outputColumn == "") {
                    for (const auto& cell : data[i]) {
                        cout << " [" << cell << "]" << "\t";
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
                        cout << num << "[" << data[i][outputIndex] << "]";
                        num += 1;
                        recommand.push_back(data[i][outputIndex]);
                    }
                    else {
                        cerr << "Output column not found" << endl;
                    }
                }
                cout << endl;
            }
        }
        // �ش��ϴ� ��ǰ�� ���� ��� �޽��� ���
        if (!found) {
            cout << "�ش��ϴ� ��ǰ�� �����ϴ�." << endl;
        }
    }



    // CSV ���Ͽ��� Ư�� ������ �����ϴ� ���� �����ϴ� �Լ�
    vector<vector<string>> getInfo(const string& Region, const string& Field,const int&col1,const int&col2) {
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
                if (tokens.size() >= col2+1 && tokens[col1] == Region && tokens[col2] == Field) {
                    result.push_back(tokens);
                }

                // currentRow �ʱ�ȭ
                currentRow.clear();
            }
        }

        file.close();
        return result;
    }
    //�Է��� �������� �Ǻ��ϴ� �Լ�
    bool isnumber(const std::string& str) {
        std::istringstream iss(str);
        int number;
        iss >> std::noskipws >> number;  
        return iss.eof() && !iss.fail();
    }

    // ���͸� �� ��å �ڼ��� ������ ����ϴ� �Լ�
    void PrintInfo(const string& Region, const string& Field) {
        vector<vector<string>> info = getInfo(Region, Field,2,32);
        int input = 0;
        // ����� ��� ���
        while (true) {
            cout << "�ڼ��� ������ ���� ���� ��å�� ��ȣ�� �Է��ϼ���(������ 0)" << endl;

            string inputStr;
            cin >> inputStr;

            if (inputStr == "0") {
                break;  // 0�� �ԷµǸ� ����
            }

            if (isnumber(inputStr) == true) {
                // stoi�� ����Ͽ� ���ڿ��� ������ ��ȯ
                input = stoi(inputStr);

                if (input >= 1 && input <= info.size()) {
                    useractivity[info[input - 1][4]] += 1;

                    // �Է¹��� ���� ���� ���
                    for (const auto& cell : info[input - 1]) {
                        // ������ �ʿ��� ������ ���
                        if (cell != "-") {
                            if ((&cell - &info[input - 1][0] >= 2) or (&cell - &info[input - 1][0] == 9) or (&cell - &info[input - 1][0] == 32))
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
            }
 else {
    cout << "���ڸ� �Է����ּ���" << endl;
            }
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
            // �� ���� ���� ��� 
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
    
    //����ڰ� �Է��� ���࿡ ���� ������������� ���� ��� �Լ�
    void FreeDeposit(const string& bank) {
            vector<vector<string>> info = GetInfo(bank);
            int input = 0;
                // ����� ��� ���
                while (true) {
                    cout << "�ڼ��� ������ ���� ���� ��å�� ��ȣ�� �Է��ϼ���(������ 0)" << endl;

                    string inputStr;
                    cin >> inputStr;

                    if (inputStr == "0") {
                        break;  // 0�� �ԷµǸ� ����
                    }
                    if (isnumber(inputStr) == true) {
                        // stoi�� ����Ͽ� ���ڿ��� ������ ��ȯ
                        input = stoi(inputStr);

                        if (input >= 1 && input <= info.size()) {
                            useractivity[info[input - 1][4]] += 1;
                            // �Է¹��� ���� ���� ���
                            for (const auto& cell : info[input - 1]) {
                                // ������ �ʿ��� ������ ���
                                if (cell != "") {
                                    if ((&cell - &info[input - 1][0] <= 4) or (&cell - &info[input - 1][0] > 5))
                                        switch (&cell - &info[input - 1][0]) {
                                        case 0:
                                            cout << "�����: [" << cell << "]" << endl;
                                            break;
                                        case 1:
                                            cout << "��ǰ��: [" << cell << "]" << endl;
                                            break;
                                        case 2:
                                            cout << "�⺻ �ݸ�(%): [" << cell << "]" << endl;
                                            break;
                                        case 3:
                                            cout << "�ְ�ݸ�(���ݸ����� %): [" << cell << "]" << endl;
                                            break;
                                        case 4:
                                            cout << "�������޹��: [" << cell << "]" << endl;
                                            break;
                                        case 6:
                                            cout << "���Թ��: [" << cell << "]" << endl;
                                            break;
                                        case 7:
                                            cout << "�������: [" << cell << "]" << endl;
                                            break;
                                        case 8:
                                            cout << "���� ���� ����: [" << cell << "]" << endl;
                                            break;
                                        case 9:
                                            cout << "���� ���: [" << cell << "]" << endl;
                                            break;
                                        case 10:
                                            cout << "Ÿ ���ǻ���: [" << cell << "]" << endl;
                                            break;
                                        case 11:
                                            cout << "�ְ� �ѵ�: [" << cell << "] " << endl;
                                            break;
                                        case 12:
                                            cout << "���������ձݸ�(���� 12���� ����): [" << cell << "] " << endl;
                                            break;
                                        case 13:
                                            cout << "���� ����Ʈ: [" << cell << "] " << endl;
                                            break;
                                        }
                                    cout << endl;
                                }
                            }
                        }
                        else {
                            cout << "�Է��� ��ȣ�� ��ǰ�� �����ϴ�." << endl;
                        }
                    }
                    else { cout << "���ڸ� �Է����ּ���" << endl; }
           }
        }
    
    //����ڰ� �Է��� ���࿡ ���� ������������� ���� ��� �Լ�
    void FreeSaving(const string& bank, const string &interest) {
        vector<vector<string>> info = getInfo(bank,interest,0,13);
        int input = 0;
        // ����� ��� ���
        while (true) {
            cout << "�ڼ��� ������ ���� ���� ��å�� ��ȣ�� �Է��ϼ���(������ 0)" << endl;

            string inputStr;
            cin >> inputStr;

            if (inputStr == "0") {
                break;  // 0�� �ԷµǸ� ����
            }
            if (isnumber(inputStr) == true) {
                // stoi�� ����Ͽ� ���ڿ��� ������ ��ȯ
                input = stoi(inputStr);

                if (input >= 1 && input <= info.size()) {
                    useractivity[info[input - 1][4]] += 1;
                    // �Է¹��� ���� ���� ���
                    for (const auto& cell : info[input - 1]) {
                        // ������ �ʿ��� ������ ���
                        if (cell != "") {
                                switch (&cell - &info[input - 1][0]) {
                                case 0:
                                    cout << "�����: [" << cell << "]" << endl;
                                    break;
                                case 1:
                                    cout << "��ǰ��: [" << cell << "]" << endl;
                                    break;
                                case 2:
                                    cout << "�⺻ �ݸ�(%): [" << cell << "]" << endl;
                                    break;
                                case 3:
                                    cout << "�ְ�ݸ�(���ݸ����� %): [" << cell << "]" << endl;
                                    break;
                                case 5:
                                    cout << "���� �� �ݸ�: [" << cell << "]" << endl;
                                    break;
                                case 6:
                                    cout << "���Թ��: [" << cell << "]" << endl;
                                    break;
                                case 7:
                                    cout << "�������: [" << cell << "]" << endl;
                                    break;
                                case 8:
                                    cout << "���� ���� ����: [" << cell << "]" << endl;
                                    break;
                                case 9:
                                    cout << "���� ���: [" << cell << "]" << endl;
                                    break;
                                case 10:
                                    cout << "Ÿ ���ǻ���: [" << cell << "]" << endl;
                                    break;
                                case 11:
                                    cout << "�ְ� �ѵ�: [" << cell << "] " << endl;
                                    break;
                                case 13:
                                    cout << "���� ����Ʈ: [" << cell << "] " << endl;
                                    break;
                                }
                            cout << endl;
                        }
                    }
                }
                else {
                    cout << "�Է��� ��ȣ�� ��ǰ�� �����ϴ�." << endl;
                }
            }
            else { cout << "���ڸ� �Է����ּ���" << endl; }
        }
    }
    //������ǰ ���� ��� �Լ�
    void FinancialManual(const string& name) {
        vector<vector<string>> info = GetInfo(name);
        // ����� ��� ���
        for (const auto& cell : info[0]) {
            if (cell != "") {
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
    }
    //TO DO: ���α�� 4 ������� �Է¿� ���� ��õ  ���
    void Recommand(){    
        //������� �Է� Ƚ���� ���� ����
        sort(recommand.begin(), recommand.end(),
            [&](const string& a, const string& b) {
                return useractivity[a] > useractivity[b];
            });

        // ��ܿ� ����ڰ� ���� ã�ƺ� ��å/ ������ǰ ���
        if (useractivity[recommand[0]] > 0) {
            cout << " (��õ): " << recommand[0] << endl;
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

