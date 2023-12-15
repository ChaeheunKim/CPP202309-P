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
    vector<string> Regions = { "중앙부처", "서울", "부산", "대구", "인천", "광주", "대전", "울산", "경기", "강원", "충북", "충남", "전북", "전남", "경북", "경남", "제주", "세종" };
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
        cout << "중앙부처/서울/부산/대구/인천/광주/대전/울산/경기/강원/충북/충남/전북/전남/경북/경남/제주/세종" << endl;
        cin >> RegionPolicy;   

        while (!isValid(RegionPolicy, Regions)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> RegionPolicy;
        }
    }
    //TO DO: 세부 기능 3 : 자세한 정보 출력
    // 입력받은 지역과 분야에 해당하는 정책 출력 함수
    void PolicyShow() {
        CSVReader csvReader("C:/Users/chee0/Downloads/download/YouthData.csv"); // 본인 컴퓨터에 따라 경로 바꿔줘야 함

        // 입력받은 분야와 지역을 사용하여 정책을 필터링하고 출력
        csvReader.PrintValue("youthPolicy.polyBizSecd", RegionPolicy, "youthPolicy.polyRlmCd", FieldPolicy, "youthPolicy.polyBizSjnm");
        csvReader.PrintInfo(RegionPolicy, FieldPolicy);
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
//기능 2 : 은행 별 금융상품 정보 출력
//TO DO: 세부 기능 1: 각 은행사 정보 수집 후 세분화
//각 은행사 홈페이지 정보 참고(금리 기준 2023.12.03)
class YouthFinancial {
private:
    string FinancialType;//금융상품 종류 입력 받는 변수
    string BankType;//은행 입력 받는 변수
    string input;
    string ManuaInput; // 원하는 상품 설명 입력 받는 변수
    //금융상품 종류 벡터
    vector<string> FinancialItem = { "청년도약계좌", "청년희망적금", "기타금융상품","금융상품설명"};
    //은행 벡터
    vector<string>  Banks = {"NH농협은행",	"신한은행","우리은행","SC제일은행","하나은행",	 "IBK기업은행",	"KB국민은행","DGB대구은행","BNK부산은행","광주은행","전북은행","BNK경남은행"};


    
public:
    //유효성 검증 함수
    bool isValid(const string& userInput, const vector<string>& validOptions) {
        return userInput == "0" || find(validOptions.begin(), validOptions.end(), userInput) != validOptions.end();
    }
//TO DO: 세부 기능 2 : 사용자 상황 맞춤 금융 정보 출력
    // 은행명 입력 함수
    void Bank() { 
        cout << "은행을 선택하세요(종료 시 0)" << endl;
        cout << "NH농협은행 /신한은행 /우리은행 /SC제일은행 /하나은행 /IBK기업은행 /KB국민은행 /DGB대구은행 /BNK부산은행 /광주은행 /전북은행 /BNK경남은행" << endl;
        cin >> BankType;

        while (!isValid(BankType,Banks)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> BankType;
        }
    }

    // 금융 상품 입력 함수
    void Item() {
        cout << "금융 상품을 선택하세요(종료 시 0)" << endl;
        cout << "청년도약계좌 /청년희망적금 /기타금융상품/금융상품설명" << endl;
        cin >> FinancialType;

        while (!isValid(FinancialType, FinancialItem)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> FinancialType;
        }
        // 입력받은 상품에 맞춘 정보 출력 
        if (FinancialType == "청년도약계좌" || FinancialType=="청년희망적금") {
            //은행 입력받기
            YouthFinancial Bank();
            CSVReader csvReader("C:/Users/chee0/Downloads/financial.csv"); // 본인 컴퓨터에 따라 경로 바꿔줘야 함
            csvReader.YouthAccount(BankType);
        }
        else if (FinancialType == "금융상품설명") {
            YouthFinancial Manualshow();
        }
    }
   

    void ManualShow() {
            cout << "설명을 원하는 상품을 적어주세요." << endl;
            cout << "청년도약계좌/청년희망적금/기타금융상품" << endl;
            cin >> ManuaInput;
            CSVReader csvReader("C:/Users/chee0/Downloads/info.csv");
            csvReader.FinancialManual(ManuaInput);
    }


    // BankType 값 가져오는 함수
    string getBankType() const {
        return BankType;
    }

    // FinancialType 값 가져오는 함수
    string getFinancialType() const {
        return FinancialType;
    }
};



int main() {
    YouthPolicy yp;
    YouthFinancial yf;
    while (true) {
            yp.Field();
            if (yp.getFieldPolicy() == "0")   //0  입력하면 종료
                break;
            yp.Region();
            if (yp.getRegionPolicy() == "0")
                break;
            yp.PolicyShow();
            yf.Item();
            if (yf.getFinancialType() == "0")
              break;

    }

    return 0;
}



