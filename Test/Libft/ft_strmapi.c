#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "Libft/libft.h"
#include "libft.h"

// Örnek dönüşüm fonksiyonları:

// 1. Karakterleri indeksine göre büyük harfe çevir (sadece küçük harfler için)
char to_upper_index(unsigned int i, char c) {
    if (c >= 'a' && c <= 'z')
        return (char)(c - 'a' + 'A');
    return c;
}

// 2. Karakteri indeksin çiftliğine göre değiştir: çift indeksler büyük, tek indeksler küçük yap
char alternate_case(unsigned int i, char c) {
    if (c >= 'a' && c <= 'z') {
        if (i % 2 == 0)
            return (char)(c - 'a' + 'A');
        else
            return c;
    }
    if (c >= 'A' && c <= 'Z') {
        if (i % 2 == 0)
            return c;
        else
            return (char)(c - 'A' + 'a');
    }
    return c;
}

// 3. Karakterin kendisini döndür (fonksiyon etkisiz, sadece kopyalama testi)
char identity(unsigned int i, char c) {
    (void)i; // unused
    return c;
}

// Yardımcı test fonksiyonu
static int _run_strmapi_test_case(const char *s, char (*f)(unsigned int, char),
                                  const char *expected, const char *test_name) {
    char *ft_result = ft_strmapi(s, f);
    int passed = 1;

    if (s == NULL) {
        if (ft_result != NULL) {
            printf("❌ FAILED: %s (Input NULL but result not NULL)\n", test_name);
            passed = 0;
        }
    } else {
        if (ft_result == NULL) {
            printf("❌ FAILED: %s (Returned NULL)\n", test_name);
            passed = 0;
        } else {
            if (strcmp(ft_result, expected) != 0) {
                printf("❌ FAILED: %s\n", test_name);
                printf("  Input: \"%s\"\n", s);
                printf("  ft_strmapi returned: \"%s\"\n", ft_result);
                printf("  Expected:            \"%s\"\n", expected);
                passed = 0;
            }
        }
    }

    if (ft_result)
        free(ft_result);

    return passed;
}

#define RUN_STRMAPI_TEST(desc, s_val, f_val, expected_val) \
    total_tests++; \
    if (_run_strmapi_test_case(s_val, f_val, expected_val, desc)) { \
        passed_tests++; \
    }

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strmapi Tests ---\n\n");

    // Temel testler
    RUN_STRMAPI_TEST("Identity function (copy)", "Hello World!", identity, "Hello World!");
    RUN_STRMAPI_TEST("To uppercase all", "hello", to_upper_index, "HELLO");
    RUN_STRMAPI_TEST("Alternate case on mixed case", "HeLLo", alternate_case, "HeLlO");
    RUN_STRMAPI_TEST("Empty string", "", identity, "");

    // NULL girdi testi - PDF açıklamasında yok ama güvenlik için test
    RUN_STRMAPI_TEST("NULL input string", NULL, identity, NULL);

    printf("\n--- Test Summary for ft_strmapi ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
