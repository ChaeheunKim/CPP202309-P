#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; // std 네임스페이스 사용
//엑셀 읽어오는 클래스
class CSVReader {
public:
    CSVReader(const string& filename, char delimiter = ',') : filename_(filename), delimiter_(delimiter) {}

    vector<vector<string>> readData() {
        ifstream in(filename_);
        if (!in.is_open()) {
            cerr << "Failed to open file: " << filename_ << endl;
            return {};
        }

        vector<vector<string>> data;
        string line;
        while (getline(in, line)) {
            vector<string> row = readRow(line);
            if (!row.empty()) {
                data.push_back(row);
            }
        }

        in.close();
        return data;
    }
    //분야,지역 에 맞는 값 출력 함수
    void PrintValue(const string& columnName1, const string& value1,
        const string& columnName2, const string& value2,
        const string& outputColumn) {
        vector<vector<string>> data = readData();
        if (data.empty()) {
            cerr << "Empty data" << endl;
            return;
        }

        // 특정 열 찾기
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

        // 특정 열에 특정 값 갖는 행 출력
        for (size_t i = 1; i < data.size(); ++i) {
            if (columnIndex1 < data[i].size() && columnIndex2 < data[i].size() &&
                data[i][columnIndex1] == value1 && data[i][columnIndex2] == value2) {
                if (outputColumn == "") {
                    for (const auto& cell : data[i]) {
                        cout << "[" << cell << "]" << "\t";
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
                        cout << "[" << data[i][outputIndex] << "]";
                    }
                    else {
                        cerr << "Output column not found" << endl;
                    }
                }
                cout << endl;
            }
        }
    }

    // CSV 파일에서 특정 조건을 만족하는 행을 std::vector에 저장하는 함수
    vector<vector<string>> getInfo(const string& Region, const string& Field) {
        vector<vector<string>> result;

        ifstream file(filename_);
        if (!file.is_open()) {
            cerr << "파일을 열 수 없습니다." << endl;
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

    // CSV 파일에서 특정 조건을 만족하는 행을 출력하는 함수
    void PrintInfo(const string& Region, const string& Field) {
        vector<vector<string>> info = getInfo(Region, Field);

       // 저장된 행들 출력
        for (const auto& row : info) {
            for (const auto& cell : row) {
                cout << "[" << cell << "]" << "\n";
            }
            cout << endl;
        }
    }
private:
    string filename_;
    char delimiter_;

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

