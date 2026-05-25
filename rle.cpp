#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

void rle(std::istream& input, std::ostream& output) {
    char c;
    if (!input.get(c)) {
        return;   // пустой файл
    }

    auto prev_byte = static_cast<unsigned char>(c);
    uint8_t counter = 1;

    while (input.get(c)) {
        const auto curr_byte = static_cast<unsigned char>(c);
        if (prev_byte == curr_byte && counter < 255) {
            ++counter;
        } else {
            // записываем серию
            output.put(static_cast<char>(counter));
            output.put(static_cast<char>(prev_byte));

            prev_byte = curr_byte;
            counter = 1;
        }
    }

    // последняя серия
    output.put(static_cast<char>(counter));
    output.put(static_cast<char>(prev_byte));
}


void rld(std::istream& input, std::ostream& output) {
    char counter_byte, symbol_byte;
    while (input.get(counter_byte) && input.get(symbol_byte)) {
        auto counter = static_cast<unsigned char>(counter_byte);
        output << std::string(counter, symbol_byte);
    }
}

int main() {
    std::cout << "Выберете что сделать с файлом" << std::endl << "Сжать - 1" << std::endl << "Разжать - 2" << std::endl;
    int choice;
    std::string input, output;
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cerr << "1 или 2\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        std::cout << "Укажите имя сжимаемого файла:" << std::endl;
        std::getline(std::cin, input);
        output = input + ".rle";
    } else if (choice == 2) {
        std::cout << "Укажите имя разжимаемого файла:" << std::endl;
        std::getline(std::cin, input);
        if (input.size() < 4 || input.substr(input.size() - 4) != ".rle") {
            std::cerr << "Error: файл должен иметь расширение .rle\n";
            return 1;
        }
        output = input.substr(0, input.size() - 4);
    }

    std::ifstream file(input, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open input file " << input << '\n';
        return 1;
    }

    std::ofstream out_file(output, std::ios::binary);
    if (!out_file) {
        std::cerr << "Error: Cannot open output file " << output << '\n';
        return 1;
    }
    if (choice == 1) {
        rle(file, out_file);
    }
    else if (choice == 2) {
        rld(file, out_file);
    }
    return 0;
}