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
            cout << "---------------------------------" << endl;
            cout << "일자리/ 주거/ 교육/ 복지/ 참여" << endl;
            cout << "---------------------------------" << endl;
            cin >> FieldPolicy;  

            while (!isValid(FieldPolicy, Fields)) {
                cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
                cin >> FieldPolicy;
            }
    }

    // 청년 정책 지역 입력 함수
    void Region() {
        cout << "지역을 선택하세요(종료 시 0)" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "중앙부처/서울/부산/대구/인천/광주/대전/울산/경기/강원/충북/충남/전북/전남/경북/경남/제주/세종" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
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
    //금융상품 종류 
    vector<string> FinancialItem = { "청년도약계좌", "예금","적금","대출","금융상품설명"};
    //은행 
    vector<string>  Banks = {"NH농협은행",	"신한은행","우리은행","SC제일은행","하나은행",	 "IBK기업은행",	"KB국민은행","DGB대구은행","BNK부산은행","광주은행","전북은행","BNK경남은행"};
    //예금 종류
    vector<string> Deposit = { "입출금자유예금","정기예금"};
    //적금 종류
    vector<string> saving = { "자유적립식","정액적립식" };
    //금리 종류
    vector<string> interest = {"복리","단리"};
    //금융상품 종류
    vector<string> Finan = { "청년도약계좌","입출금자유예금 ", "정기예금" ,"정액적립식적금","자유적립식적금","단리","복리" };

    
public:
    //유효성 검증 함수
    bool isValid(const string& userInput, const vector<string>& validOptions) {
        return userInput == "0" || find(validOptions.begin(), validOptions.end(), userInput) != validOptions.end();
    }

    //TO DO: 세부 기능 2 : 사용자 상황 맞춤 금융 정보 출력
    // 은행명 입력 함수
    void Bank() {
        cout << "은행을 선택하세요" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "NH농협은행 /신한은행 /우리은행 /SC제일은행 /하나은행 /IBK기업은행 /KB국민은행 /DGB대구은행 /BNK부산은행 /광주은행 /전북은행 /BNK경남은행" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------- " << endl;
        cin >> BankType;

        while (!isValid(BankType, Banks)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> BankType;
        }
    }

    // 금융 상품 입력 함수
    void Item() {
        cout << "금융 상품을 선택하세요(종료 시 0)" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "청년도약계좌/예금/적금/대출/금융상품설명" << endl;
        cout << "-----------------------------------------"<< endl;
        cin >> FinancialType;

        while (!isValid(FinancialType, FinancialItem)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> FinancialType;
        }
    }
    
    //예적금, 대출 정보는 은행연합회 정보 사용(금리 기준 2023.12.20)
    //사용자에게 예금 종류 입력받기
    string userdeposit; //사용자 입력 예금 종류
    void inputdeposit() {
        cout << "알고싶은 예금 종류를 선택하세요(종료 시 0)" << endl;
        cout << "----------------------------------------" << endl;
        cout << "입출금자유예금/ 정기예금" << endl;
        cin >> userdeposit;
       
        //사용자 입력 유효성 검증
        while (!isValid(userdeposit, Deposit)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> userdeposit;
        }      
    }

    //사용자에게 적금 종류 입력받기
    void Saving() {
        cout << "알고싶은 적금 종류를 선택하세요(종료 시 0)" << endl;
        cout << "----------------------------------------" << endl;
        cout << "정액적립식/ 자유적립식" << endl;
        cin >> userdeposit;

        //사용자 입력 유효성 검증
        while (!isValid(userdeposit, saving)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> userdeposit;
        }
    }

    //사용자가 입력한 은행에 맞춘 예적금 세부 정보 출력
    void deposit() {
        string userinterest; //사용자 입력 금리 종류
        //예금
        if (userdeposit == "입출금자유예금") {
            CSVReader csvReader("C:/Users/chee0/Downloads/freedeposit.csv"); // freedeposit.csv 파일, 본인 컴퓨터에 따라 경로 바꿔줘야 함
            Bank();
            csvReader.PrintValue("은행",BankType,"은행",BankType,"상품명");
            csvReader.FreeDeposit(BankType);
        }
        else if (userdeposit == "정기예금") {
            CSVReader csvReader("C:/Users/chee0/Downloads/timedeposit.csv"); // timedeposit.csv 파일, 본인 컴퓨터에 따라 경로 바꿔줘야 함
            Bank();
            csvReader.PrintValue("은행", BankType, "은행", BankType, "상품명");
            csvReader.FreeDeposit(BankType);
        }
        
        //적금
        else if (userdeposit == "정액적립식") {
            CSVReader csvReader("C:/Users/chee0/Downloads/saving.csv"); // saving.csv 파일, 본인 컴퓨터에 따라 경로 바꿔줘야 함
            Bank();
            csvReader.PrintValue("은행", BankType, "은행", BankType, "상품명");
            csvReader.FreeDeposit(BankType);
        }
        else if (userdeposit == "자유적립식") {
            cout << "금리 계산 방법을 선택하세요" << endl;
            cout << "------------------------------" << endl;
            cout << "단리/ 복리" << endl;
            cin >> userinterest;
            //사용자 입력 유효성 검증
            while (!isValid(userinterest, interest)) {
                cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
                cin >> userinterest;
             
            }
            CSVReader csvReader("C:/Users/chee0/Downloads/freesaving.csv"); // freesaving.csv 파일, 본인 컴퓨터에 따라 경로 바꿔줘야 함
            Bank();
            csvReader.PrintValue("은행", BankType, "금리계산방법", userinterest, "상품명");
            csvReader.FreeSaving(BankType, userinterest);
            
        }

    }

    // 입력받은 은행에 맞춘 청년도약계좌 정보 출력 함수
    void FinancialShow() {
        CSVReader csvReader("C:/Users/chee0/Downloads/financial.csv"); // 본인 컴퓨터에 따라 경로 바꿔줘야 함
        Bank();
        csvReader.YouthAccount(BankType);
    }


    void ManualShow() {
        cout << "설명을 원하는 금융 용어를 선택해주세요." << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "청년도약계좌/입출금자유예금/정기예금/정액적립식적금/ 자유적립식적금/ 단리/복리" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cin >> ManuaInput;
        //사용자 입력 유효성 검증
        while (!isValid(ManuaInput, Finan)) {
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            cin >> ManuaInput;
        }
        CSVReader csvReader("C:/Users/chee0/Downloads/Info2.csv"); // 본인 컴퓨터에 따라 경로 바꿔줘야 함
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
    string userinput;
    while (true) {
        cout << "알고싶은 정보의 번호를 입력하세요.(종료 시 0)" << endl;
        cout << "-------------------------------" << endl;
        cout << "1.정책 정보 2.금융상품정보" << endl;
        cout << "-------------------------------" << endl;
        cin >> userinput;
        if (userinput == "0") {
            break; //0 입력 시 종료
        }
        else if (userinput == "1") {
            yp.Field();
            if (yp.getFieldPolicy() == "0")   //0  입력하면 종료
                break;
            yp.Region();
            if (yp.getRegionPolicy() == "0")
                break;
            yp.PolicyShow();
        }
        else if (userinput == "2") {
            yf.Item();
            if (yf.getFinancialType() == "0")
                break;
            else if (yf.getFinancialType() == "청년도약계좌") {
                yf.FinancialShow();  // YouthAccount 함수 호출
            }
            else if (yf.getFinancialType() == "금융상품설명") {
                yf.ManualShow();  // YouthManual 함수 호출
            }
            else if (yf.getFinancialType() == "예금") {
                yf.inputdeposit(); 
                yf.deposit(); //Freedepoist 함수 호출
            }
            else if (yf.getFinancialType() == "적금") {
                yf.Saving();
                yf.deposit(); //Freedepoist 함수 호출
            }
        }
        else {
            cout << "1 또는 2를 입력해주세요" << endl;
        }
    }

    return 0;
}

