#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000
#define LOG_THRESHOLD 999

void compareFiles(FILE* file1, FILE* file2) {
    unsigned char buffer1[BUFFER_SIZE];
    unsigned char buffer2[BUFFER_SIZE];

    int offset = 0;
    int differences = 0;
    int totalDifferences = 0;

    // Read the files in chunks of 100 bytes
    while (1) {
        // Read 100 bytes from each file
        size_t bytesRead1 = fread(buffer1, sizeof(unsigned char), BUFFER_SIZE, file1);
        size_t bytesRead2 = fread(buffer2, sizeof(unsigned char), BUFFER_SIZE, file2);

        if (bytesRead1 != bytesRead2) {
            printf("Files have different sizes.\n");
            return;
        }

        // Compare each byte in the buffers
        for (int i = 0; i < bytesRead1; i++) {
            if (buffer1[i] != buffer2[i]) {
                differences++;
            }
        }

        // Check if the differences threshold is reached
        if (differences > LOG_THRESHOLD) {
            printf("Detected %d differences at offset %08X.\n", differences, offset);
            totalDifferences += differences;
            differences = 0;  // Reset the differences count
        }

        offset += BUFFER_SIZE;

        // Check if end of file is reached
        if (bytesRead1 < BUFFER_SIZE) {
            break;
        }
    }

    printf("Total differences: %d\n", totalDifferences);
}

int main() {
    FILE* file1 = fopen("/home/daniel/Desktop/dump/lv/RAM1.BIN", "rb");
    FILE* file2 = fopen("/home/daniel/Desktop/dump/lv/RAM2.BIN", "rb");

    if (file1 == NULL || file2 == NULL) {
        printf("Failed to open files.\n");
        return 1;
    }

    compareFiles(file1, file2);

    fclose(file1);
    fclose(file2);

    return 0;
}
