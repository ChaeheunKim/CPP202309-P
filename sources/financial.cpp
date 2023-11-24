#include <iostream>
using namespace std;

//기능 1
//TO DO: 세부 기능 1 : 청년 지원 정책 세분화
//데이터는 온통청년 사이트 오픈 API 사용 예정

//청년 정책 클래스
class YouthPolicy {
private:
	char FieldPolicy;
	char RegionPolicy;
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
	char FieldPolicy;
	cout << "정책 분야를 선택하세요(종료 시 0)" << endl;
	cout << "분야 전체/ 일자리/ 주거/ 교육/ 복지.문화/ 참여.권리" << endl;
	cin >> FieldPolicy;
}
//청년 정책 지역 입력 함수
void YouthPolicy::Region() {
	char RegionPolicy;
	cout << "지역을 선택하세요(종료 시 0)" << endl;
	cout << "지역 전체/중앙/서울/부산/대구/인천/광주/대전/울산/경기/강원/충북/충남/전북/전남/경북/경남/제주/세종" << endl;
	cin >> RegionPolicy;
}

//입력받은 지역과 분야에 해당하는 정책 출력 함수
void YouthPolicy::PolicyShow() {
	if ((FieldPolicy == "분야 전체") && (RegionSelect == "지역 전체")) {
		cout << Policy << endl;  //모든 정책 출력
	}
	else if ((FieldPolicy == "분야 전체") && (RegionSelect == RegionPolicy)) {
		//Policy = //데이터에서 사용자가 선택한 지역에 해당하는 정책
		cout << Policy << endl;
	}
	else if ((FieldPolicy == FieldPolicy) && (RegionSelect == "지역 전체")) {
		//Policy = //데이터에서 사용자가 선택한 분야에 해당하는 정책
		cout << Policy << endl;
	}
	else if ((FieldSelect == FieldPolicy) && (RegionSelect == RegionPolicy)) {
		//Policy = //데이터에서 사용자가 선택한 지역과 분야에  모두 해당하는 정책
		cout << Policy << endl;
	}
}
int main() {
	YouthPolicy yp;
	while (true) {
		yp.Field();
		yp.Region();
		yp.PolicyShow();
		if ((FieldPolicy == 0) or (RegionPoicly == 0))
			break;
	}
}
