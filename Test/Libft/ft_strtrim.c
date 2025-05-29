#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Libft header'ını setup'a göre ayarla
#include "libft.h"  // veya "Libft/libft.h"

// Test helper
static int _run_strtrim_test_case(const char *s1, const char *set,
                                   const char *expected, const char *test_name) {
    char *result = ft_strtrim(s1, set);
    int passed = 1;

    if (expected == NULL) {
        if (result != NULL) {
            printf("❌ FAILED: %s (Expected NULL, got non-NULL)\n", test_name);
            passed = 0;
        }
    } else {
        if (result == NULL) {
            printf("❌ FAILED: %s (Expected \"%s\", got NULL)\n", test_name, expected);
            passed = 0;
        } else if (strcmp(result, expected) != 0) {
            printf("❌ FAILED: %s\n", test_name);
            printf("  s1: \"%s\"\n  set: \"%s\"\n", s1, set);
            printf("  Result:   \"%s\"\n", result);
            printf("  Expected: \"%s\"\n", expected);
            passed = 0;
        }
    }

    if (result) free(result);
    return passed;
}

#define RUN_STRTRIM_TEST(desc, s1_val, set_val, expected_val) \
    total_tests++; \
    if (_run_strtrim_test_case(s1_val, set_val, expected_val, desc)) passed_tests++;

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strtrim Tests ---\n\n");

    // Temel testler
    RUN_STRTRIM_TEST("Trim spaces", "  Hello World  ", " ", "Hello World");
    RUN_STRTRIM_TEST("Trim tabs and newlines", "\t\nHello\n\t", "\n\t", "Hello");
    RUN_STRTRIM_TEST("Trim punctuation", "..!?Hello!?!.", ".!?", "Hello");
    RUN_STRTRIM_TEST("No trim needed", "Hello", "xyz", "Hello");
    RUN_STRTRIM_TEST("All trimmed", "!!!!", "!", "");
    RUN_STRTRIM_TEST("Empty input string", "", "abc", "");
    RUN_STRTRIM_TEST("Empty set", "  Hello  ", "", "  Hello  ");

    // NULL kontrolleri
    RUN_STRTRIM_TEST("s1 is NULL", NULL, "abc", NULL);
    RUN_STRTRIM_TEST("set is NULL", "abc", NULL, NULL);
    RUN_STRTRIM_TEST("Both NULL", NULL, NULL, NULL);

    // Karışık karakter seti
    RUN_STRTRIM_TEST("Multiple trim chars", "abcHelloabc", "abc", "Hello");
    RUN_STRTRIM_TEST("Only leading trim", "+++Hello", "+", "Hello");
    RUN_STRTRIM_TEST("Only trailing trim", "Hello$$$", "$", "Hello");

    printf("\n--- Test Summary for ft_strtrim ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n",
               passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
