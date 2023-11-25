#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

    // ... (다른 함수들은 여기에)

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

int main() {
    CSVReader csvReader("C:/Users/chee0/Downloads/youth_data.csv");
    std::ifstream in("C:/Users/chee0/Downloads/youth_data.csv", std::ios::binary);
    // Read and print the entire CSV data
    std::vector<std::vector<std::string>> data = csvReader.readData();
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << "[" << cell << "]" << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
