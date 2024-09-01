#include <assert.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define PREFIX "_"
#define NEEDLE ";;; `"

#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"

int main(int argc, char *argv[]) {
    int fd, outfd;
    uint64_t argv_1_len;
    size_t st_size;
    char *content, *outfile_name, *needle;
    struct stat stat;

    assert(argc == 2);
    fd = open(argv[1], O_RDONLY);
    assert(fd != -1);

    assert(fstat(fd, &stat) != -1);

    st_size = (size_t)stat.st_size;
    content = mmap(NULL, st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    assert(content != (void *)-1);

    for (needle = content; needle < content + st_size; needle++) {
        if (memcmp(needle, NEEDLE, sizeof NEEDLE - 1) == 0) {
            char *start, *start_abs;
            char *full;
            uint64_t len;
            FILE *pstdout;
            struct {
                uint64_t size;
                uint64_t capacity;
                char *heap_buffer;
                char linebuffer[1024];
            } inbuffer = {
                .size = 0,
                .capacity = 1024,
                .heap_buffer = malloc(inbuffer.capacity),
                .linebuffer = {0}};
            start_abs = needle;
            needle += sizeof NEEDLE - 1;
            start = needle;
            while (*needle != '`') {
                needle++;
            }
            len = (uint64_t)(needle - start);
            full = malloc(len + 1);
            memcpy(full, start, len);
            full[len] = 0;
            pstdout = popen(full, "r");
            assert(pstdout != NULL);
            while (fgets(inbuffer.linebuffer, sizeof inbuffer.linebuffer, pstdout) != 0) {
                uint64_t linebuffer_strlen = strlen(inbuffer.linebuffer);
                if (inbuffer.size + linebuffer_strlen > inbuffer.capacity) {
                    inbuffer.capacity *= 2;
                    inbuffer.heap_buffer = realloc(inbuffer.heap_buffer, inbuffer.capacity);
                }
                memcpy(inbuffer.heap_buffer + inbuffer.size, inbuffer.linebuffer, linebuffer_strlen);
                inbuffer.size += linebuffer_strlen;
            }
            memmove(start_abs + inbuffer.size, needle + 1, /* right */ st_size - (/* left */ (size_t)(content - needle) + 1));
            st_size -= len + sizeof NEEDLE;
            st_size += inbuffer.size;
            memcpy(start_abs, inbuffer.heap_buffer, inbuffer.size);
            free(inbuffer.heap_buffer);
            free(full);
            pclose(pstdout);
        }
    }
    argv_1_len = strlen(argv[1]);
    outfile_name = malloc(argv_1_len + sizeof PREFIX);
    memcpy(outfile_name, PREFIX, sizeof PREFIX - 1);
    memcpy(outfile_name + sizeof PREFIX - 1, argv[1], argv_1_len);
    outfile_name[argv_1_len + sizeof PREFIX - 1] = 0;

    outfd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, stat.st_mode);
    assert(write(outfd, content, st_size) != -1);

    assert(munmap(content, st_size) != -1);
    close(outfd);
    close(fd);

    free(outfile_name);

    return EXIT_SUCCESS;
}
