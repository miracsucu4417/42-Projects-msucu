#include <stdio.h>
#include <ctype.h>     // Orijinal isdigit ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_isdigit_test_case(int input_val, const char *test_name) {
    int ft_result = ft_isdigit(input_val);
    int original_result = isdigit(input_val);
    
    // Geçme koşulu: İkisi de 0 ise VEYA ikisi de sıfır değilse.
    int passed = ((ft_result != 0 && original_result != 0) || (ft_result == 0 && original_result == 0));

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) {
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else {
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_isdigit returned: %d\n", ft_result);
        printf("  Original isdigit returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_ISDIGIT_TEST(desc, val) \
    total_tests++; \
    if (_run_isdigit_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_isdigit Tests ---\n\n");

    // 1. Temel Sayı Karakterleri
    RUN_ISDIGIT_TEST("Digit '0'", '0');
    RUN_ISDIGIT_TEST("Digit '9'", '9');
    RUN_ISDIGIT_TEST("Digit '5'", '5');

    // 2. Sayı Olmayan Alfabetik Karakterler
    RUN_ISDIGIT_TEST("Lowercase 'a'", 'a');
    RUN_ISDIGIT_TEST("Uppercase 'Z'", 'Z');
    RUN_ISDIGIT_TEST("Lowercase 'g'", 'g');

    // 3. Sayı Olmayan Semboller
    RUN_ISDIGIT_TEST("Symbol '!'", '!');
    RUN_ISDIGIT_TEST("Symbol '$'", '$');
    RUN_ISDIGIT_TEST("Symbol '('", '(');

    // 4. Sayı Olmayan Kontrol ve Boşluk Karakterleri
    RUN_ISDIGIT_TEST("Space ' '", ' ');
    RUN_ISDIGIT_TEST("Newline '\\n'", '\n');
    RUN_ISDIGIT_TEST("Tab '\\t'", '\t');
    RUN_ISDIGIT_TEST("FT_NULL char '\\0'", '\0');

    // 5. Sınır Değerler (ASCII Tablosuna göre)
    RUN_ISDIGIT_TEST("ASCII 47 (Before '0')", 47); // '/'
    RUN_ISDIGIT_TEST("ASCII 48 ('0')", 48);
    RUN_ISDIGIT_TEST("ASCII 57 ('9')", 57);
    RUN_ISDIGIT_TEST("ASCII 58 (After '9')", 58); // ':'

    // 6. Genişletilmiş ASCII veya Özel int Değerleri
    RUN_ISDIGIT_TEST("Extended ASCII (int 150)", 150);
    RUN_ISDIGIT_TEST("EOF (int -1)", -1);

    printf("\n--- Test Summary for ft_isdigit ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}