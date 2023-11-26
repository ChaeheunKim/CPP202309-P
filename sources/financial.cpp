#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csv.h" //엑셀 데이터 가져오는 코드
using namespace std;

//기능 1
//데이터는 온통청년 사이트 오픈 API 사용

//TO DO: 세부 기능 1 : 청년 지원 정책 세분화
//청년 정책 클래스

class YouthPolicy {
private:
    string FieldPolicy;//분야 입력 받는 변수
    string RegionPolicy;//지역 입력 받는 변수
    string input;
    //분야 벡터
    vector<string> Fields = { "일자리", "주거", "교육", "복지", "참여" }; 
    //지역 벡터
    vector<string> Regions = { "중앙", "서울", "부산", "대구", "인천", "광주", "대전", "울산", "경기", "강원", "충북", "충남", "전북", "전남", "경북", "경남", "제주", "세종" };
   // 필터링 된 정책 벡터
    vector <string> Policy = {};

//TO DO: 세부 기능 2 : 사용자가 입력한 조건에 맞는 정책 출력
public:
    //유효성 검증 함수
    bool isValid(const string& userInput, const vector<string>& validOptions) {
        return userInput == "0" || find(validOptions.begin(), validOptions.end(), userInput) != validOptions.end();
    }

    // 청년 정책 분야 입력 함수
    void Field() {
            cout << "정책 분야를 선택하세요(종료 시 0)" << endl;
            cout << "일자리/ 주거/ 교육/ 복지/ 참여" << endl;
            cin >> FieldPolicy;  

            while (!isValid(FieldPolicy, Fields)) {
                cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
                cin >> FieldPolicy;
            }
    }

    // 청년 정책 지역 입력 함수
    void Region() {
        cout << "지역을 선택하세요(종료 시 0)" << endl;
        cout << "중앙/서울/부산/대구/인천/광주/대전/울산/경기/강원/충북/충남/전북/전남/경북/경남/제주/세종" << endl;
        cin >> RegionPolicy;   

        while (!isValid(RegionPolicy, Regions)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> RegionPolicy;
        }
    }

    // 입력받은 지역과 분야에 해당하는 정책 출력 함수
    void PolicyShow() {
        CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv"); // 본인 컴퓨터에 따라 경로 바꿔줘야 함

        // 입력받은 분야와 지역을 사용하여 정책을 필터링하고 출력
        csvReader.PrintValue("youthPolicy.polyBizSecd", RegionPolicy, "youthPolicy.polyRlmCd", FieldPolicy, "youthPolicy.polyBizSjnm");
        cout << "자세한 정보를 보고 싶다면 1을 입력하세요" << endl;
        cin >> input;
        if (input == "1")
            csvReader.PrintInfo( RegionPolicy, FieldPolicy);
    }

    // FieldPolicy 값 가져오는 함수
    string getFieldPolicy() const {
        return FieldPolicy;
    }

    // RegionPolicy 값 가져오는 함수
    string getRegionPolicy() const {
        return RegionPolicy;
    }
};


int main() {
    YouthPolicy yp;
    while (true) {
            yp.Field();
            if (yp.getFieldPolicy() == "0")   //0  입력하면 종료
                break;
            yp.Region();
            if (yp.getRegionPolicy() == "0")
                break;
            yp.PolicyShow();


    }

    return 0;
}



