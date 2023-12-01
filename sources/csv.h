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
        while (getline(file, line)) {
            istringstream iss(line);
            string token;
            vector<string> tokens;

            while (getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() >= 33 && tokens[2] == Region && tokens[32] == Field) {
                result.push_back(tokens);
            }
        }

        file.close();
        return result;
    }
    // ���͸� �� ��å �ڼ��� ������ ����ϴ� �Լ�
    void PrintInfo(const string& Region, const string& Field) {
        vector<vector<string>> info = getInfo(Region, Field);
        int input;
        cout << "�ڼ��� ������ ���� ���� ��å�� ��ȣ�� �Է��ϼ���(������ 0)" << endl;
        cin >> input;
        // ����� ��� ���
        if (input!=0)
            // ����� ���� �ִ��� Ȯ��
            if (input >= 1 && input <= Policy.size()) {
                // ������� ��å ������ ���� ���
                for (const auto& cell : info[input - 1]) {
                    cout << "[" << cell << "]" << "\t";
                }
                cout << endl;
            }
            else {
                cout << "�Է��� ��ȣ�� ��å�� �������� �ʽ��ϴ�." << endl;
            }
        }
    }
    
        
    
private:
    string filename_;
    char delimiter_;

    bool isInsideQuotes(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '"') {
                count++;
            }
        }
        return count % 2 != 0;  // ����ǥ ������ Ȧ���̸� ����ǥ �ȿ� �ִٰ� �Ǵ�
    }

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

