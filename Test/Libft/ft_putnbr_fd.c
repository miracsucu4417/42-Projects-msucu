#include <stdio.h>
#include <fcntl.h>    // open
#include <unistd.h>   // close, read, lseek
#include <string.h>
#include <stdlib.h>

// #include "Libft/libft.h"
#include "libft.h"

#define TEST_FILENAME "test.txt"

// Dosya içeriğini oku ve null-terminated string olarak döndür
static char *read_file_content(const char *filename, size_t *out_size) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return NULL;

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        close(fd);
        return NULL;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        close(fd);
        return NULL;
    }

    char *buffer = malloc(size + 1);
    if (!buffer) {
        close(fd);
        return NULL;
    }

    ssize_t read_bytes = read(fd, buffer, size);
    if (read_bytes != size) {
        free(buffer);
        close(fd);
        return NULL;
    }

    buffer[size] = '\0';
    if (out_size) *out_size = size;

    close(fd);
    return buffer;
}

// Test fonksiyonu: dosyaya ft_putnbr_fd ile yaz, içeriği kontrol et
static int _run_putnbr_fd_test_case(int number, const char *expected_content, const char *test_name) {
    int fd = open(TEST_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        printf("❌ FAILED: %s (Cannot open test file)\n", test_name);
        return 0;
    }

    ft_putnbr_fd(number, fd);

    close(fd);

    size_t size = 0;
    char *content = read_file_content(TEST_FILENAME, &size);
    if (!content) {
        printf("❌ FAILED: %s (Cannot read test file)\n", test_name);
        return 0;
    }

    int passed = 1;
    if (strcmp(content, expected_content) != 0) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Written content: \"%s\"\n", content);
        printf("  Expected content:\"%s\"\n", expected_content);
        passed = 0;
    }

    free(content);
    return passed;
}

#define RUN_PUTNBR_FD_TEST(desc, num, expected) \
    total_tests++; \
    if (_run_putnbr_fd_test_case(num, expected, desc)) { \
        passed_tests++; \
    }

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_putnbr_fd Tests ---\n\n");

    RUN_PUTNBR_FD_TEST("Write zero", 0, "0");
    RUN_PUTNBR_FD_TEST("Write positive number", 12345, "12345");
    RUN_PUTNBR_FD_TEST("Write negative number", -6789, "-6789");
    RUN_PUTNBR_FD_TEST("Write INT_MAX", 2147483647, "2147483647");
    RUN_PUTNBR_FD_TEST("Write INT_MIN", -2147483648, "-2147483648");

    printf("\n--- Test Summary for ft_putnbr_fd ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
