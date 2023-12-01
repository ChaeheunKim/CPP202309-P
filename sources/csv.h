#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
int num; //조건에 맞는 정책 번호 변수
using namespace std; 
//엑셀 읽어오는 클래스
class CSVReader {
public:
    CSVReader(const string& filename, char delimiter = ',') : filename_(filename), delimiter_(delimiter) {}
    // 필터링 된 정책 벡터
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

            // 큰 텍스트 블록을 묶은 경우 처리
            if (isInsideQuotes(currentRow)) {
                continue;
            }

            vector<string> row = readRow(currentRow);
            if (!row.empty()) {
                data.push_back(row);
            }

            // currentRow 초기화
            currentRow.clear();
        }

        in.close();
        return data;
    }

    //사용자가 입력한 조건에 맞는 정책 출력 함수
    void PrintValue(const string& columnName1, const string& value1,
        const string& columnName2, const string& value2,
        const string& outputColumn) {
        int num = 1;
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
    // 필터링 된 정책 자세한 정보를 출력하는 함수
    void PrintInfo(const string& Region, const string& Field) {
        vector<vector<string>> info = getInfo(Region, Field);
        int input;
        cout << "자세한 정보를 보고 싶은 정책의 번호를 입력하세요(없으면 0)" << endl;
        cin >> input;
        // 저장된 행들 출력
        if (input!=0)
            // 출력할 행이 있는지 확인
            if (input >= 1 && input <= Policy.size()) {
                // 보고싶은 정책 제세한 정보 출력
                for (const auto& cell : info[input - 1]) {
                    cout << "[" << cell << "]" << "\t";
                }
                cout << endl;
            }
            else {
                cout << "입력한 번호의 정책이 존재하지 않습니다." << endl;
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
        return count % 2 != 0;  // 따옴표 개수가 홀수이면 따옴표 안에 있다고 판단
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

