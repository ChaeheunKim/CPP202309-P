#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
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
        if (in.fail()) {
            std::cerr << "File not found" << std::endl;
            return {};
        }

        std::vector<std::vector<std::string>> data;
        while (in.good()) {
            std::vector<std::string> row = readRow(in);
            if (!row.empty()) {
                data.push_back(row);
            }
        }

        in.close();
        return data;
    }
    //특정 값에 해당하는 데이터 추출 하는 함수
    void extractAndPrintRowsWithValue(const std::string& columnName, const std::string& value) {
        std::vector<std::vector<std::string>> data = readData();
        if (data.empty()) {
            std::cerr << "Empty data" << std::endl;
            return;
        }

        // 특정 열 인덱스 찾기
        int columnIndex = -1;
        for (size_t i = 0; i < data[0].size(); ++i) {
            if (data[0][i] == columnName) {
                columnIndex = static_cast<int>(i);
                break;
            }
        }

        if (columnIndex == -1) {
            std::cerr << "Column not found" << std::endl;
            return;
        }

        // 특정한 값 있는 열 출력
        for (size_t i = 1; i < data.size(); ++i) {  // Skip header row
            if (columnIndex < data[i].size() && data[i][columnIndex] == value) {
                for (const auto& cell : data[i]) {
                    std::cout << "[" << cell << "]" << "\t";
                }
                std::cout << std::endl;
            }
        }
    }

private:
    std::string filename_;
    char delimiter_;

    std::vector<std::string> readRow(std::istream& in) {
        std::stringstream ss;
        bool inquotes = false;
        std::vector<std::string> row;

        while (in.good()) {
            char c = in.get();
            if (!inquotes && c == '"') {
                inquotes = true;
            }
            else if (inquotes && c == '"') {
                if (in.peek() == '"') {
                    ss << (char)in.get();
                }
                else {
                    inquotes = false;
                }
            }
            else if (!inquotes && c == delimiter_) {
                row.push_back(ss.str());
                ss.str("");
            }
            else if (!inquotes && (c == '\r' || c == '\n')) {
                if (in.peek() == '\n') {
                    in.get();
                }
                row.push_back(ss.str());
                return row;
            }
            else {
                ss << c;
            }
        }

        return row;
    }
};
//청년 정책 클래스
class YouthPolicy {
private:
	char FieldPolicy;//분야 입력 받는 변수
	char RegionPolicy;//지역 입력 받는 변수
	char FieldSelect;//분야 구분 변수
	char RegionSelect; //지역 구분 변수
	char Policy;// 정책 변수
public:
	void Field();
	void Region();
	void PolicyShow();
};

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
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv");
	//if ((FieldSelect == FieldPolicy) && (RegionSelect == RegionPolicy)) {
		//Policy = //데이터에서 사용자가 선택한 지역과 분야에  모두 해당하는 정책
		csvReader.extractAndPrintRowsWithValue("youthPolicy.polyBizSecd", "광주");
        csvReader.extractAndPrintRowsWithValue("FieldPolicy", "youthPolicy.polyRlmCd");
	//}
}
int main() {
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv");



	YouthPolicy yp;
	while (true) {
        string FieldPolicy;
        string RegionPolicy;
        
		yp.Field();
		yp.Region();
		yp.PolicyShow();
		if ((FieldPolicy == "0") or (RegionPolicy == "0"))
			break;
	}
    return 0;
}
