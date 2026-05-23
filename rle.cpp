#include <fstream>
#include <iostream>

/**
 * @brief Выполняет сжатие RLE (Run-Length Encoding) из входного потока в выходной.
 *
 * Алгоритм: читает побайтово, считает количество повторяющихся подряд байт.
 * Как только встречается другой байт или счётчик достигает 255,
 * записывает в выходной поток пару (счётчик, байт).
 *
 * @param input  входной бинарный поток
 * @param output выходной бинарный поток
 */
void rle(std::istream& input, std::ostream& output) {
    char prev_byte, curr_byte;
    unsigned int counter = 1;   // счётчик повторений текущего байта

    // читаем первый байт; если файл пуст, выходим
    if (!input.get(prev_byte)) {
        return;
    }

    // обрабатываем остальные байты
    while (input.get(curr_byte)) {
        // если байт совпадает с предыдущим и счётчик ещё не достиг 255
        if (prev_byte == curr_byte && counter < 255) {
            ++counter;
        } else {
            // записываем накопленную пару (счётчик, байт)
            output << static_cast<unsigned char>(counter) << prev_byte;
            // начинаем новую последовательность
            prev_byte = curr_byte;
            counter = 1;
        }
    }
    // записываем последнюю пару
    output << static_cast<unsigned char>(counter) << prev_byte;
}

int main(int argc, char* argv[]) {
    // проверяем аргументы командной строки
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // открываем входной файл в бинарном режиме
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open input file " << argv[1] << std::endl;
        return 1;
    }

    // открываем выходной файл в бинарном режиме
    std::ofstream out_file(argv[2], std::ios::binary);
    if (!out_file) {
        std::cerr << "Error: Cannot open output file " << argv[2] << std::endl;
        return 1;
    }

    // выполняем сжатие
    rle(file, out_file);

    return 0;
}