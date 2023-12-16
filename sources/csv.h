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
    //엑셀 파일 읽어오기
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
        string currentRow;
        bool issideQuotes = false;
        while (getline(file, line)) {
            currentRow += line;
            // 큰 텍스트 블록을 묶은 경우 처리
            issideQuotes = isInsideQuotes(currentRow);

            // 큰 텍스트 블록이 끝났을 때
            if (!issideQuotes) {
                vector<string> tokens;
                istringstream iss(currentRow);
                string token;

                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                // 특정 조건을 만족하는 행인지 확인
                if (tokens.size() >= 33 && tokens[2] == Region && tokens[32] == Field) {
                    result.push_back(tokens);
                }

                // currentRow 초기화
                currentRow.clear();
            }
        }

        file.close();
        return result;
    }

    // 필터링 된 정책 자세한 정보를 출력하는 함수
    void PrintInfo(const string& Region, const string& Field) {
        vector<vector<string>> info = getInfo(Region, Field);
        int input=0;
        cout << "자세한 정보를 보고 싶은 정책의 번호를 입력하세요(없으면 0)" << endl;
        cin >> input;
        // 저장된 행들 출력
        while (input != 0) {
            // 출력할 행이 있는지 확인
            if (input >= 1 && input <= Policy.size()) {
                // 입력받은 행의 열들 출력
                for (const auto& cell : info[input - 1]) {
                    // 열에서 필요한 정보만 출력
                    if (cell != "-") {
                        if ((&cell - &info[input - 1][0] >= 2) or (&cell - &info[input - 1][0]==9) or (&cell - &info[input - 1][0] == 32))
                            switch (&cell - &info[input - 1][0]) {
                            case 2:
                                cout << "지역: [" << cell << "]" << endl;
                                break;
                            case 3:
                                cout << "기관 및 지자체 구분: [" << cell << "]" << endl;
                                break;
                            case 4:
                                cout << "정책명: [" << cell << "]" << endl;
                                break;
                            case 5:
                                cout << "정책 소개: [" << cell << "]" << endl;
                                break;
                            case 6:
                                cout << "지원 내용: [" << cell << "]" << endl;
                                break;
                            case 7:
                                cout << "지원 규모: [" << cell << "]" << endl;
                                break;
                            case 8:
                                cout << "사업운영기간: [" << cell << "]" << endl;
                                break;
                            case 10:
                                cout << "사업신청기간: [" << cell << "]" << endl;
                                break;
                            case 11:
                                cout << "연령: [" << cell << "]" << endl;
                                break;
                            case 12:
                                cout << "전공 요건: [" << cell << "]" << endl;
                                break;
                            case 13:
                                cout << "취업 상태: [" << cell << "]" << endl;
                                break;
                            case 14:
                                cout << "특화 분야: [" << cell << "]" << endl;
                                break;
                            case 15:
                                cout << "학력 요건: [" << cell << "]" << endl;
                                break;
                            case 16:
                                cout << "거주지 및 소득조건: [" << cell << "]" << endl;
                                break;
                            case 17:
                                cout << "추가단서 사항: [" << cell << "]" << endl;
                                break;
                            case 18:
                                cout << "참여 제한 대상: [" << cell << "]" << endl;
                                break;
                            case 19:
                                cout << "신청 절차: [" << cell << "]" << endl;
                                break;
                            case 20:
                                cout << "제출 서류: [" << cell << "]" << endl;
                                break;
                            case 21:
                                cout << "심사 발표: [" << cell << "]" << endl;
                                break;
                            case 22:
                                cout << "신청 사이트 주소: [" << cell << "]" << endl;
                                break;
                            case 23:
                                cout << "참고 사이트 URL1: [" << cell << "]" << endl;
                                break;
                            case 24:
                                cout << "참고 사이트 URL1 : [" << cell << "]" << endl;
                                break;
                            case 25:
                                cout << "주관 부처 : [" << cell << "]" << endl;
                                break;
                            case 26:
                                cout << "주관부처 담당자 이름 : [" << cell << "]" << endl;
                                break;
                            case 27:
                                cout << "주관부처 담당자 연락처 : [" << cell << "]" << endl;
                                break;
                            case 28:
                                cout << "운영기관명 : [" << cell << "]" << endl;
                                break;
                            case 29:
                                cout << "운영기관 담당자 이름 : [" << cell << "]" << endl;
                                break;
                            case 30:
                                cout << "운영기관 담당자 연락처 : [" << cell << "]" << endl;
                                break;
                            case 31:
                                cout << "기타사항 : [" << cell << "]" << endl;
                                break;
                           }
                        cout << endl;
                    }
         
                }
            }
            // 벗어난 번호를 입력했을 경우 오류 출력
            else {
                cout << "입력한 번호의 정책이 존재하지 않습니다." << endl;
            }
            cout << "자세한 정보를 보고 싶은 정책의 번호를 입력하세요(없으면 0)" << endl;
            cin >> input;
        }
    }
    //특정 은행 정보 희망계좌 정보 가져오기
    vector<vector<string>> GetInfo(const string& bank) {
        vector<vector<string>> result;

        ifstream file(filename_);
        if (!file.is_open()) {
            cerr << "파일을 열 수 없습니다." << endl;
            return result;
        }

        std::string line;
        string currentRow;
        bool issideQuotes = false;
        while (getline(file, line)) {
            currentRow += line;
            // 큰 텍스트 블록을 묶은 경우 처리
            issideQuotes = isInsideQuotes(currentRow);

            // 큰 텍스트 블록이 끝났을 때
            if (!issideQuotes) {
                vector<string> tokens;
                istringstream iss(currentRow);
                string token;

                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                // 특정 조건을 만족하는 행인지 확인
                if (tokens[0] == bank) {
                    result.push_back(tokens);
                }

                // currentRow 초기화
                currentRow.clear();
            }
        }

        file.close();
        return result;
    }
    //사용자가 입력한 은행에 따른 청년도약계좌 정보 출력 함수
    void YouthAccount( const string& value) {
        vector<vector<string>> info = GetInfo(value);
        // 저장된 행들 출력
        for (const auto& cell : info[0]) {
            //     // 각 열의 정보 출력 
          switch (&cell - &info[0][0]){
                    case 0:
                        cout << "은행명: [" << cell << "]" << endl;
                        break;
                    case 1:
                        cout << "기본 금리(3년 고정): [" << cell << "]" << endl;
                        break;
                    case 2:
                        cout << "소득 우대금리: [" << cell << "]" << endl;
                        break;
                    case 3:
                        cout << "적금담보대가산금리(만기일시상환대출): [" << cell << "]" << endl;
                        break;
                    case 4:
                        cout << "적금담보대가산금리(한도대출): [" << cell << "]" << endl;
                        break;
                    case 5:
                        cout << "적금담보대가산금리(대출가능한도): [" << cell << "]" << endl;
                        break;
                    case 6:
                        cout << "은행별 우대금리: [" << cell << "]" << endl;
                        break;
                    case 8:
                        cout << "만기 후 금리: [" << cell << "]" << endl;
                        break;
                    case 9:
                        cout << "우대조건: [" << cell << "]" << endl;
                        break;
                    case 10:
                        cout << "기타 유의사항: [" << cell << "]" << endl;
                        break;
                    case 11:
                        cout << "참고 링크: [" << cell << "]" << endl;
                        break;


                    }
          cout << endl;
                }

            }
    //사용자가 입력한 은행에 따른 청년도약계좌 정보 출력 함수
    void FinancialManual(const string& name) {
        vector<vector<string>> info = GetInfo(name);
        // 저장된 행들 출력
        for (const auto& cell : info[0]) {
            // 각 열의 정보 출력 
            switch (&cell - &info[0][0]) {
            case 1:
                cout << cell << endl;
                break;
            case 2:
                cout << "연령 조건: [" << cell << "]" << endl;
                break;
            case 3:
                cout << "소득 조건: [" << cell << "]" << endl;
                break;
            case 4:
                cout << "기간: [" << cell << "]" << endl;
                break;
            case 5:
                cout << "월 납입금: [" << cell << "]" << endl;
                break;
            case 6:
                cout << "정부 지원금: [" << cell << "]" << endl;
                break;
            case 7:
                cout << "기타 사항: [" << cell << "]" << endl;
                break;
            case 8:
                cout << "참고 URL: [" << cell << "]" << endl;
                break;
            }
            cout << endl;
        }
    }
        
    
    
private:
    string filename_;
    char delimiter_;
    //따옴표 안에 쉼표가 있을 경우의 처리
    bool isInsideQuotes(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '"') {
                count++;
            }
        }
        return count % 2 != 0;  // 따옴표 개수가 홀수이면 따옴표 안에 있다고 판단
    }
    // 쉼표로 구분하여 행 읽기(csv 파일)
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

