// PID: 730660144
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_LINES_CAPACITY 8
#define INITIAL_LINE_CAPACITY 128

char* readline();
char** readlines(int* num_lines);
void printlines(char** lines, int num_lines);
void freelines(char** lines, int num_lines);
int cmp(const void* a, const void* b);

int main() {
    int line_total = 0;
    char** all_lines = readlines(&line_total);
    qsort(all_lines, line_total, sizeof(char*), cmp);
    printlines(all_lines, line_total);
    freelines(all_lines, line_total);
    return 0;
}

char* readline() {
    int buf_size = INITIAL_LINE_CAPACITY;
    char* text = malloc(buf_size);
    if (!text) {
        fprintf(stderr, "Memory error\n");
        exit(1);
    }

    int i = 0;
    int character;
    while ((character = getchar()) != EOF) {
        if (i + 1 >= buf_size) {
            buf_size *= 2;
            text = realloc(text, buf_size);
            if (!text) {
                fprintf(stderr, "Memory error\n");
                exit(1);
            }
        }
        text[i++] = character;
        if (character == '\n') break;
    }

    if (i == 0 && character == EOF) {
        free(text);
        return NULL;
    }

    text[i] = '\0';
    return text;
}

char** readlines(int* num_lines) {
    int size = INITIAL_LINES_CAPACITY;
    char** storage = malloc(size * sizeof(char*));
    if (!storage) {
        fprintf(stderr, "Memory error\n");
        exit(1);
    }

    *num_lines = 0;
    char* current;
    while ((current = readline()) != NULL) {
        if (*num_lines >= size) {
            size *= 2;
            storage = realloc(storage, size * sizeof(char*));
            if (!storage) {
                fprintf(stderr, "Memory error\n");
                exit(1);
            }
        }
        storage[*num_lines] = current;
        (*num_lines)++;
    }
    return storage;
}

void printlines(char** lines, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        printf("%s", lines[i]);
    }
}

void freelines(char** lines, int num_lines) {
    for (int j = 0; j < num_lines; j++) {
        free(lines[j]);
    }
    free(lines);
}

int cmp(const void* a, const void* b) {
    const char* first = *(const char**)a;
    const char* second = *(const char**)b;
    return strcmp(first, second);
}
