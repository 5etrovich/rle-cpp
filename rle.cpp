#include <fstream>
#include <iostream>

void rle(std::istream& input, std::ostream& output){
    char prev_byte, curr_byte;
    unsigned int counter = 1;
    if (!input.get(prev_byte)) {
        return;
    }
    while (input.get(curr_byte)) {
        if (prev_byte == curr_byte && counter < 255) {
            counter++;
        }
        else {
            output << static_cast<unsigned char>(counter) << prev_byte;
            prev_byte = curr_byte;
            counter = 1;
        }
    }
    output << static_cast<unsigned char>(counter) << prev_byte;

}


int main(int argc, char * argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1], std::ios::binary); // загрузить в file файл
    std::ofstream out_file(argv[2], std::ios::binary); // создали файл для выгрузки
    if (!file) {
        std::cerr << "Error: Cannot open input file " << argv[1] << std::endl;
        return 1;
    }
    if (!out_file) {
        std::cerr << "Error: Cannot open output file " << argv[2] << std::endl;
        return 1;
    }
    rle(file, out_file);
    return 0;
}
