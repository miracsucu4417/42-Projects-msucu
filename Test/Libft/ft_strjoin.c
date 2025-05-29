#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Kendi libft include'ına göre düzenle
#include "libft.h"  // veya "Libft/libft.h"

// Yardımcı fonksiyon: Belleği görsel olarak incelemek için
void print_memory(const char *label, const char *mem, size_t n) {
    printf("%s [", label);
    for (size_t i = 0; i < n; ++i) {
        if (mem[i] >= 32 && mem[i] <= 126)
            printf("%c", mem[i]);
        else if (mem[i] == '\0')
            printf("N"); // Null byte
        else
            printf(".");
    }
    printf("]\n");
}

// Test fonksiyonu
static int _run_strjoin_test_case(const char *s1, const char *s2,
                                  const char *expected_result, const char *test_name) {
    char *result = ft_strjoin(s1, s2);
    int passed = 1;

    if (expected_result == NULL) {
        if (result != NULL) {
            printf("❌ FAILED: %s (Expected NULL, got non-NULL)\n", test_name);
            passed = 0;
        }
    } else {
        if (result == NULL) {
            printf("❌ FAILED: %s (Expected \"%s\", got NULL)\n", test_name, expected_result);
            passed = 0;
        } else if (strcmp(result, expected_result) != 0 || strlen(result) != strlen(expected_result)) {
            printf("❌ FAILED: %s\n", test_name);
            printf("  s1: \"%s\", s2: \"%s\"\n", s1, s2);
            printf("  Result:   \"%s\"\n", result);
            printf("  Expected: \"%s\"\n", expected_result);
            passed = 0;
        }
    }

    if (result) free(result);
    return passed;
}

#define RUN_STRJOIN_TEST(desc, s1_val, s2_val, expected_val) \
    total_tests++; \
    if (_run_strjoin_test_case(s1_val, s2_val, expected_val, desc)) passed_tests++;

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strjoin Tests ---\n\n");

    // Temel testler
    RUN_STRJOIN_TEST("Normal join", "Hello", "World", "HelloWorld");
    RUN_STRJOIN_TEST("Empty s1", "", "World", "World");
    RUN_STRJOIN_TEST("Empty s2", "Hello", "", "Hello");
    RUN_STRJOIN_TEST("Both empty", "", "", "");

    // Uzun stringler
    RUN_STRJOIN_TEST("Long strings", "aaaaaaaaaa", "bbbbbbbbbb", "aaaaaaaaaabbbbbbbbbb");

    // NULL testleri (standart strjoin bu durumda davranış tanımsızdır ama biz test için NULL'ı da kontrol ediyoruz)
    RUN_STRJOIN_TEST("s1 is NULL", NULL, "World", NULL);
    RUN_STRJOIN_TEST("s2 is NULL", "Hello", NULL, NULL);
    RUN_STRJOIN_TEST("Both NULL", NULL, NULL, NULL);

    // Null karakter içeren test (görünmez karakter olabilir ama strcmp onu dikkate almaz çünkü ilk null'da durur)
    char s1_with_null[] = {'a', 'b', '\0', 'c'}; // C string olarak sadece "ab"
    char s2_with_null[] = {'x', 'y', '\0', 'z'}; // C string olarak sadece "xy"
    RUN_STRJOIN_TEST("String with internal nulls", s1_with_null, s2_with_null, "abxy");

    printf("\n--- Test Summary for ft_strjoin ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
