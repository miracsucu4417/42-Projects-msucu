#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Libft header'ını setup'a göre değiştir:
#include "libft.h"

// Yardımcı: Split sonucunu yazdır
void print_split_result(char **arr) {
    if (!arr) {
        printf("  Result: NULL\n");
        return;
    }

    printf("  Result: [");
    for (int i = 0; arr[i]; i++) {
        printf("\"%s\"", arr[i]);
        if (arr[i + 1])
            printf(", ");
    }
    printf("]\n");
}

// Split sonucu beklenen string dizisiyle eşleşiyor mu?
static int arrays_equal(char **actual, const char **expected) {
    if (!actual && !expected)
        return 1;
    if (!actual || !expected)
        return 0;

    int i = 0;
    while (actual[i] && expected[i]) {
        if (strcmp(actual[i], expected[i]) != 0)
            return 0;
        i++;
    }
    return (actual[i] == NULL && expected[i] == NULL);
}

// Test fonksiyonu
static int _run_split_test_case(const char *s, char sep, const char **expected, const char *test_name) {
    char **result = ft_split(s, sep);
    int passed = 1;

    if (!arrays_equal(result, expected)) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input: \"%s\" | Separator: '%c'\n", s ? s : "NULL", sep);
        print_split_result(result);
        passed = 0;
    }

    // Bellek temizliği
    if (result) {
        for (int i = 0; result[i]; i++)
            free(result[i]);
        free(result);
    }

    return passed;
}

#define RUN_SPLIT_TEST(desc, str, sep, expected_arr) \
    total_tests++; \
    if (_run_split_test_case(str, sep, expected_arr, desc)) passed_tests++;

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_split Tests (No empty strings) ---\n\n");

    // Temel ve geçerli testler
    const char *e1[] = {"Hello", "World", NULL};
    RUN_SPLIT_TEST("Basic split on space", "Hello World", ' ', e1);

    const char *e2[] = {"abc", "def", "ghi", NULL};
    RUN_SPLIT_TEST("Comma-separated", "abc,def,ghi", ',', e2);

    const char *e3[] = {"One", "Two", "Four", NULL};
    RUN_SPLIT_TEST("Skip empty between separators", "One-Two--Four", '-', e3);

    const char *e4[] = {NULL};
    RUN_SPLIT_TEST("Empty string input", "", ',', e4);

    const char *e5[] = {"abc", NULL};
    RUN_SPLIT_TEST("No separator", "abc", ',', e5);

    const char *e6[] = {NULL};
    RUN_SPLIT_TEST("Only separators", ";;;;", ';', e6);

    const char *e7[] = {"start", "end", NULL};
    RUN_SPLIT_TEST("Leading/trailing sep", ",start,end,", ',', e7);

    const char *e8[] = {"a", "b", "c", NULL};
    RUN_SPLIT_TEST("Complex: ,a,,b,c,,", ",a,,b,c,,", ',', e8);

    const char *e9[] = {NULL};
    RUN_SPLIT_TEST("NULL input", NULL, ',', NULL);

    printf("\n--- Test Summary for ft_split ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n",
               passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
