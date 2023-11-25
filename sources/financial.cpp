#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//기능 1
//TO DO: 세부 기능 1 : 청년 지원 정책 세분화
//데이터는 온통청년 사이트 오픈 API 사용 예정

//엑셀 데이터 읽는 클래스




class CSVReader {
public:
    CSVReader(const std::string& filename, char delimiter = ',') : filename_(filename), delimiter_(delimiter) {}

    std::vector<std::vector<std::string>> readData() {
        std::ifstream in(filename_);
        if (!in.is_open()) {
            std::cerr << "Failed to open file: " << filename_ << std::endl;
            return {};
        }

        std::vector<std::vector<std::string>> data;
        std::string line;
        while (std::getline(in, line)) {
            std::vector<std::string> row = readRow(line);
            if (!row.empty()) {
                data.push_back(row);
            }
        }

        in.close();
        return data;
    }

    void extractAndPrintRowsWithValue(const std::string& columnName1, const std::string& value1,
        const std::string& columnName2, const std::string& value2,
        const std::string& outputColumn) {
        std::vector<std::vector<std::string>> data = readData();
        if (data.empty()) {
            std::cerr << "Empty data" << std::endl;
            return;
        }

        // Find the index of the specified columns
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
            std::cerr << "One or both columns not found" << std::endl;
            return;
        }

        // Print rows with the specified values in the specified columns
        for (size_t i = 1; i < data.size(); ++i) {  // Skip header row
            if (columnIndex1 < data[i].size() && columnIndex2 < data[i].size() &&
                data[i][columnIndex1] == value1 && data[i][columnIndex2] == value2) {
                if (outputColumn == "") {
                    for (const auto& cell : data[i]) {
                        std::cout << "[" << cell << "]" << "\t";
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
                        std::cout << "[" << data[i][outputIndex] << "]";
                    }
                    else {
                        std::cerr << "Output column not found" << std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }
    }

private:
    std::string filename_;
    char delimiter_;

    std::vector<std::string> readRow(const std::string& line) {
        std::stringstream ss(line);
        std::vector<std::string> row;

        std::string cell;
        while (std::getline(ss, cell, delimiter_)) {
            row.push_back(cell);
        }

        return row;
    }
};


//청년 정책 클래스
class YouthPolicy {
private:
	string FieldPolicy;//분야 입력 받는 변수
    string RegionPolicy;//지역 입력 받는 변수
	//char FieldSelect;//분야 구분 변수
	//char RegionSelect; //지역 구분 변수
	char Policy;// 정책 변수
public:
	void Field();
	void Region();
	void PolicyShow();
};
//선택 가능 지역 리스트
string Region[18] = { "중앙","서울","부산","대구","인천","광주","대전","울산","경기","강원","충북","충남","전북","전남","경북","경남","제주","세종" };
//선택 가능 분야 리스트
string Field[5] = { "일자리","주거","교육","복지","참여" };

//청년 정책 분야 입력 함수
void YouthPolicy::Field() {
	string FieldPolicy;
	cout << "정책 분야를 선택하세요(종료 시 0)" << endl;
	cout << "일자리/ 주거/ 교육/ 복지/ 참여" << endl;
	cin >> FieldPolicy;
}
//청년 정책 지역 입력 함수
void YouthPolicy::Region() {
	string RegionPolicy;
	cout << "지역을 선택하세요(종료 시 0)" << endl;
	cout << "중앙/서울/부산/대구/인천/광주/대전/울산/경기/강원/충북/충남/전북/전남/경북/경남/제주/세종" << endl;
	cin >> RegionPolicy;
}

//입력받은 지역과 분야에 해당하는 정책 출력 함수
void YouthPolicy::PolicyShow() {
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv"); //본인 컴퓨터에 따라 경로 바꿔줘야 함
    csvReader.extractAndPrintRowsWithValue("youthPolicy.polyBizSecd", "경기", "youthPolicy.polyRlmCd", "일자리", "youthPolicy.polyBizSjnm");
	
}


int main() {
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv"); //본인 컴퓨터에 따라 경로 바꿔줘야 함

	YouthPolicy yp;
	while (true) {
        string FieldPolicy;
        string RegionPolicy;
        yp.Field();
        yp.Region();
        if (FieldPolicy == "0" || RegionPolicy == "0") {
            break;
        }

        yp.PolicyShow();
        
	
	}
    return 0;
}
