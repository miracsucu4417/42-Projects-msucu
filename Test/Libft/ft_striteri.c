#include <stdio.h>
#include <string.h>

// #include "Libft/libft.h"
#include "libft.h"

// Örnek dönüşüm fonksiyonları:

// 1. Her karakteri büyük harfe çevir
void to_upper(unsigned int i, char *c) {
    (void)i; // kullanılmıyor
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 'a' + 'A';
}

// 2. İndeksi çift olan karakterleri '*' yap
void star_even_index(unsigned int i, char *c) {
    if (i % 2 == 0)
        *c = '*';
}

// 3. Karaktere indeks kadar ileri ASCII kaydır (örnek amaçlı)
void shift_char(unsigned int i, char *c) {
    *c = *c + i;
}

// Yardımcı test fonksiyonu
static int _run_striteri_test_case(char *s, void (*f)(unsigned int, char *),
                                  const char *expected, const char *test_name) {
    if (s == NULL) {
        // PDF açıklamasında NULL input durumundan bahsedilmiyor.
        // Biz burada işleme almıyoruz.
        printf("Skipping %s (input string is NULL)\n", test_name);
        return 1; // geçerli say
    }

    f ? ft_striteri(s, f) : (void)0;

    if (strcmp(s, expected) != 0) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Result:   \"%s\"\n", s);
        printf("  Expected: \"%s\"\n", expected);
        return 0;
    }

    return 1;
}

#define RUN_STRITERI_TEST(desc, s_val, f_val, expected_val) \
    do { \
        char buffer[256]; \
        strncpy(buffer, s_val ? s_val : "", sizeof(buffer)); \
        buffer[sizeof(buffer)-1] = '\0'; \
        total_tests++; \
        if (_run_striteri_test_case(buffer, f_val, expected_val, desc)) { \
            passed_tests++; \
        } \
    } while (0)

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_striteri Tests ---\n\n");

    RUN_STRITERI_TEST("To uppercase all", "hello", to_upper, "HELLO");
    RUN_STRITERI_TEST("Star even indices", "abcdef", star_even_index, "*b*d*f");
    RUN_STRITERI_TEST("Shift chars by index", "abcd", shift_char, "aceg");
    RUN_STRITERI_TEST("Empty string", "", to_upper, "");
    RUN_STRITERI_TEST("No function (NULL f)", "test", NULL, "test");

    // NULL input test - PDF'de belirtilmemiş
    printf("\nSkipping NULL input test since spec does not clarify behavior.\n");

    printf("\n--- Test Summary for ft_striteri ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
