#include <stdio.h>
#include <fcntl.h>    // open
#include <unistd.h>   // close, read, lseek
#include <string.h>
#include <stdlib.h>

// #include "Libft/libft.h"
#include "libft.h"

#define TEST_FILENAME "test.txt"

// Dosyanın içeriğini oku, buffer'a yaz, sonuna FT_NULL ekle
static char *read_file_content(const char *filename, t_size_t *out_size) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return FT_NULL;

    // Dosya boyutunu öğren
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        close(fd);
        return FT_NULL;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        close(fd);
        return FT_NULL;
    }

    char *buffer = malloc(size + 1);
    if (!buffer) {
        close(fd);
        return FT_NULL;
    }

    st_size_t read_bytes = read(fd, buffer, size);
    if (read_bytes != size) {
        free(buffer);
        close(fd);
        return FT_NULL;
    }

    buffer[size] = '\0';
    if (out_size) *out_size = size;

    close(fd);
    return buffer;
}

// Test fonksiyonu: dosyaya karakterler yaz, içeriği kontrol et
static int _run_putchar_fd_test_case(const char *chars_to_write, const char *expected_content, const char *test_name) {
    int fd = open(TEST_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        printf("❌ FAILED: %s (Cannot open test file)\n", test_name);
        return 0;
    }

    // Karakterleri yaz
    for (t_size_t i = 0; chars_to_write[i] != '\0'; i++) {
        ft_putchar_fd(chars_to_write[i], fd);
    }

    close(fd);

    // Dosyayı okuyup içeriği kontrol et
    t_size_t size = 0;
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

#define RUN_PUTCHAR_FD_TEST(desc, chars, expected) \
    total_tests++; \
    if (_run_putchar_fd_test_case(chars, expected, desc)) { \
        passed_tests++; \
    }

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_putchar_fd Tests ---\n\n");

    RUN_PUTCHAR_FD_TEST("Write single char 'A'", "A", "A");
    RUN_PUTCHAR_FD_TEST("Write multiple chars 'Hello'", "Hello", "Hello");
    RUN_PUTCHAR_FD_TEST("Write empty string", "", "");
    RUN_PUTCHAR_FD_TEST("Write special chars '\\n\\0!'", "\n\0!", "\n"); // \0 sadece string sonlandırıcı, dosyada yazılmaz, beklenen "\n"

    printf("\n--- Test Summary for ft_putchar_fd ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
