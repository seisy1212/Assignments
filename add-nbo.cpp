#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t Open_file(const char* filename) {
    uint32_t number;
    FILE* file = fopen(filename, "rb");
    
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE); 
    }

    size_t read_size = fread(&number, sizeof(number), 1, file);

    
    if (read_size != 1) {
        if (feof(file)) {
            fprintf(stderr, "Error: File %s is too short to read 4 bytes\n", filename);
        } else if (ferror(file)) {
            perror("Error reading file");
        }
        fclose(file);
        exit(EXIT_FAILURE); 
    }

    fclose(file);

    printf("16 bit number=0x%x\n", number);

    uint32_t part1 = (number >> 24) & 0x000000FF;
    uint32_t part2 = (number >> 8) & 0x0000FF00;
    uint32_t part3 = (number << 8) & 0x00FF0000;
    uint32_t part4 = (number << 24) & 0xFF000000;

    uint32_t result = part1 | part2 | part3 | part4;

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t num1 = Open_file(argv[1]);
    uint32_t num2 = Open_file(argv[2]);
    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}

