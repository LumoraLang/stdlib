#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
int filewrite(const char* path, const char* content) {
    FILE* f = fopen(path, "w");
    if (!f) return -1;
    fputs(content, f);
    fclose(f);
    return 0;
}

int fileappend(const char* path, const char* content) {
    FILE* f = fopen(path, "a");
    if (!f) return -1;
    fputs(content, f);
    fclose(f);
    return 0;
}

char* fileread(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) { return NULL; }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    char* buffer = (char*)malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

int fileexists(const char* path) {
    FILE* f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

int eprintf(const char* s) {
    return fprintf(stderr, "%s", s);
}

char* read_line() {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, stdin);
    if (read != -1 && line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }
    return line;
}

int flush() {
    return fflush(stdout);
}

int getchar() {
    return getchar();
}

int putchar(int c) {
    return putchar(c);
}

int remove_file(const char* path) {
    return remove(path);
}

int rename(const char* old_path, const char* new_path) {
    return rename(old_path, new_path);
}

int copy_file(const char* src, const char* dest) {
    FILE *fsrc = NULL, *fdest = NULL;
    char buffer[4096];
    size_t bytes;
    fsrc = fopen(src, "rb");
    if (!fsrc) return -1;
    fdest = fopen(dest, "wb");
    if (!fdest) {
        fclose(fsrc);
        return -1;
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), fsrc)) > 0) {
        fwrite(buffer, 1, bytes, fdest);
    }

    fclose(fsrc);
    fclose(fdest);
    return 0;
}

int is_directory(const char* path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISDIR(st.st_mode);
    }
    return 0;
}

long long file_size(const char* path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return (long long)st.st_size;
    }
    return -1;
}
