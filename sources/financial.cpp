#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
using namespace std;

//��� 1
//TO DO: ���� ��� 1 : û�� ���� ��å ����ȭ
//�����ʹ� ����û�� ����Ʈ ���� API ��� ����

//���� ������ �д� Ŭ����
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
    //Ư�� ���� �ش��ϴ� ������ ���� �ϴ� �Լ�
    void extractAndPrintRowsWithValue(const std::string& columnName, const std::string& value) {
        std::vector<std::vector<std::string>> data = readData();
        if (data.empty()) {
            std::cerr << "Empty data" << std::endl;
            return;
        }

        // Ư�� �� �ε��� ã��
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

        // Ư���� �� �ִ� �� ���
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
//û�� ��å Ŭ����
class YouthPolicy {
private:
	char FieldPolicy;//�о� �Է� �޴� ����
	char RegionPolicy;//���� �Է� �޴� ����
	char FieldSelect;//�о� ���� ����
	char RegionSelect; //���� ���� ����
	char Policy;// ��å ����
public:
	void Field();
	void Region();
	void PolicyShow();
};

//û�� ��å �о� �Է� �Լ�
void YouthPolicy::Field() {
	string FieldPolicy;
	cout << "��å �о߸� �����ϼ���(���� �� 0)" << endl;
	cout << "���ڸ�/ �ְ�/ ����/ ����/ ����" << endl;
	cin >> FieldPolicy;
}
//û�� ��å ���� �Է� �Լ�
void YouthPolicy::Region() {
	string RegionPolicy;
	cout << "������ �����ϼ���(���� �� 0)" << endl;
	cout << "�߾�/����/�λ�/�뱸/��õ/����/����/���/���/����/���/�泲/����/����/���/�泲/����/����" << endl;
	cin >> RegionPolicy;
}

//�Է¹��� ������ �о߿� �ش��ϴ� ��å ��� �Լ�
void YouthPolicy::PolicyShow() {
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv");
	//if ((FieldSelect == FieldPolicy) && (RegionSelect == RegionPolicy)) {
		//Policy = //�����Ϳ��� ����ڰ� ������ ������ �о߿�  ��� �ش��ϴ� ��å
		csvReader.extractAndPrintRowsWithValue("youthPolicy.polyBizSecd", "����");
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
