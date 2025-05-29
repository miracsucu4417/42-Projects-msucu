#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX ve INT_MIN için

// #include "Libft/libft.h" // senin dosya yapına göre bunu seç
#include "libft.h" 

// Yardımcı test fonksiyonu: beklenen string ile dönüş stringini karşılaştırır
static int _run_itoa_test_case(int n, const char *expected_str, const char *test_name) {
    char *ft_result = ft_itoa(n);
    int passed = 1;

    if (ft_result == NULL) {
        printf("❌ FAILED: %s (Returned NULL)\n", test_name);
        passed = 0;
    }
    else {
        if (strcmp(ft_result, expected_str) != 0) {
            printf("❌ FAILED: %s\n", test_name);
            printf("  Input: %d\n", n);
            printf("  ft_itoa returned: \"%s\"\n", ft_result);
            printf("  Expected:         \"%s\"\n", expected_str);
            passed = 0;
        }
    }

    if (ft_result)
        free(ft_result);

    return passed;
}

// Test makrosu
#define RUN_ITOA_TEST(desc, n_val, expected_val) \
    total_tests++; \
    if (_run_itoa_test_case(n_val, expected_val, desc)) { \
        passed_tests++; \
    }

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_itoa Tests ---\n\n");

    // Temel durumlar
    RUN_ITOA_TEST("Zero", 0, "0");
    RUN_ITOA_TEST("Positive single digit", 7, "7");
    RUN_ITOA_TEST("Negative single digit", -5, "-5");
    RUN_ITOA_TEST("Positive multiple digits", 12345, "12345");
    RUN_ITOA_TEST("Negative multiple digits", -9876, "-9876");

    // Kenar durumlar
    RUN_ITOA_TEST("INT_MAX", INT_MAX, "2147483647");
    RUN_ITOA_TEST("INT_MIN", INT_MIN, "-2147483648");

    // Diğer durumlar
    RUN_ITOA_TEST("Negative number ending with zero", -120, "-120");
    RUN_ITOA_TEST("Large positive number", 1000000000, "1000000000");
    RUN_ITOA_TEST("Negative number with many digits", -1000000000, "-1000000000");

    printf("\n--- Test Summary for ft_itoa ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
