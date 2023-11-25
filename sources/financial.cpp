#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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


//û�� ��å Ŭ����
class YouthPolicy {
private:
	string FieldPolicy;//�о� �Է� �޴� ����
    string RegionPolicy;//���� �Է� �޴� ����
	//char FieldSelect;//�о� ���� ����
	//char RegionSelect; //���� ���� ����
	char Policy;// ��å ����
public:
	void Field();
	void Region();
	void PolicyShow();
};
//���� ���� ���� ����Ʈ
string Region[18] = { "�߾�","����","�λ�","�뱸","��õ","����","����","���","���","����","���","�泲","����","����","���","�泲","����","����" };
//���� ���� �о� ����Ʈ
string Field[5] = { "���ڸ�","�ְ�","����","����","����" };

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
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv"); //���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��
    csvReader.extractAndPrintRowsWithValue("youthPolicy.polyBizSecd", "���", "youthPolicy.polyRlmCd", "���ڸ�", "youthPolicy.polyBizSjnm");
	
}


int main() {
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv"); //���� ��ǻ�Ϳ� ���� ��� �ٲ���� ��

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
