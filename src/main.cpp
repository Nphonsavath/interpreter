#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>

std::string read_file_contents(const std::string& filename);
int isDigit(int character);

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    int ret_val = 0;
    int equal_counter = 0;
    int line = 1;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        std::string file_contents = read_file_contents(argv[2]);
	
	for (std::size_t i = 0; i < file_contents.size(); i++) {
		if (isDigit(file_contents[i])) {
			std::string result = "";
			while (isDigit(file_contents[i])) {
				result += file_contents[i];
					i += 1;
			}
			std::string resultFloat = result + ".0";
			if (file_contents[i] != '.') {
				std::cout << "NUMBER " << result << " " << resultFloat << std::endl;
			} else {
				result += '.';
				i += 1;
				while (isDigit(file_contents[i])) {
					result += file_contents[i];
					i += 1;
				}
				double number = std::stod(result);
				if (std::fmod(number, 1.0) == 0.0) {
					std::cout << "NUMBER " << result << " " << resultFloat << std::endl;
				} else {
					std::cout << "NUMBER " << result << " " << std::fixed << std::setprecision(1) << result << std::endl;
					//std::cout << "NUMBER " << result << " " << result << std::endl;
				}
			}
			i -= 1;
		} else { 
			switch (file_contents[i]) { 
				case '(': 
					std::cout << "LEFT_PAREN ( null" << std::endl; break;
				case ')': 
					std::cout << "RIGHT_PAREN ) null" << std::endl; break;
				case '{':
					std::cout << "LEFT_BRACE { null" << std::endl; break;
				case '}':
					std::cout << "RIGHT_BRACE } null" << std::endl; break;
				case '*':
					std::cout << "STAR * null" << std::endl; break;
				case '.':
					std::cout << "DOT . null" << std::endl; break;
				case ',':
					std::cout << "COMMA , null" << std::endl; break;
				case '+':
					std::cout << "PLUS + null" << std::endl; break;
				case '-':
					std::cout << "MINUS - null" << std::endl; break;
				case ';':
					std::cout << "SEMICOLON ; null" << std::endl; break;
				case '=':
					if (file_contents[i+1] == '=') {
						std::cout << "EQUAL_EQUAL == null" << std::endl;
						i += 1;
					} else {
						std::cout << "EQUAL = null" << std::endl;
					}
					break;
				case '!':
					if (file_contents[i+1] == '=') {
						std::cout << "BANG_EQUAL != null" << std::endl;
						i += 1;
					} else {
						std::cout << "BANG ! null" << std::endl;
					}
					break;
				case '<':
					if (file_contents[i+1] == '=') {
						std::cout << "LESS_EQUAL <= null" << std::endl;
						i += 1;
					} else {
						std::cout << "LESS < null" << std::endl;
					}
					break;
				case '>':
					if (file_contents[i+1] == '=') {
						std::cout << "GREATER_EQUAL >= null" << std::endl;
						i += 1;
					} else {
						std::cout << "GREATER > null" << std::endl;
					}
					break;
				case '/':
					if (file_contents[i+1] == '/') {
						//i += 1;
						while (i < file_contents.size() && file_contents[i+1] != '\n') {
							i++;
						}
					} else {
						std::cout << "SLASH / null" << std::endl;
					}
					break;
				case ' ':
				case '\r':
				case '\t': 
					break;
				case '\n':
					line++;
					break;
				case '\"':
					{
					std::string result = "";
					while (i < file_contents.size() && file_contents[i+1] != '\"') {
						result += file_contents[i+1];
						i += 1;
					}
					if (i == file_contents.size()) { 
						std::cerr << "[line " << line << "] Error: Unterminated string." << std::endl;
						ret_val = 65;
					} else {
						i += 1;
						std::cout << "STRING \"" << result << "\" " << result << std::endl;
					}
					break;
					}
				default:
					std::cerr << "[line " << line << "] Error: Unexpected character: " << file_contents[i] << std::endl;
					ret_val = 65;
					break;
				}
			}
		} 
		std::cout << "EOF  null" << std::endl;
		return ret_val;
    } else {
	std::cerr << "Unknown command: " << command << std::endl;
	return 1;
	}
}

std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

int isDigit(int character) {
	return character >= '0' && character <= '9';
}
