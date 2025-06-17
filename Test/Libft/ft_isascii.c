#include <stdio.h>
#include <ctype.h>     // Orijinal isascii ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_isascii_test_case(int input_val, const char *test_name) {
    int ft_result = ft_isascii(input_val);
    int original_result = isascii(input_val);
    
    // Geçme koşulu: İkisi de 0 ise VEYA ikisi de sıfır değilse.
    int passed = ((ft_result != 0 && original_result != 0) || (ft_result == 0 && original_result == 0));

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) { // Yazdırılabilir karakter ise
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else { // Int olarak verildiğinde
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_isascii returned: %d\n", ft_result);
        printf("  Original isascii returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_ISASCII_TEST(desc, val) \
    total_tests++; \
    if (_run_isascii_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_isascii Tests ---\n\n");

    // 1. Temel ASCII Karakterler (Harfler, Sayılar, Semboller)
    RUN_ISASCII_TEST("Lowercase 'a'", 'a');
    RUN_ISASCII_TEST("Uppercase 'Z'", 'Z');
    RUN_ISASCII_TEST("Digit '5'", '5');
    RUN_ISASCII_TEST("Symbol '$'", '$');
    RUN_ISASCII_TEST("Space ' '", ' ');
    RUN_ISASCII_TEST("Newline '\\n'", '\n');
    RUN_ISASCII_TEST("FT_NULL char '\\0'", '\0');

    // 2. Sınır Değerler
    RUN_ISASCII_TEST("ASCII Min (0)", 0);
    RUN_ISASCII_TEST("ASCII Max (127)", 127); // DEL karakteri

    // 3. ASCII Olmayan Karakterler (Genişletilmiş ASCII)
    RUN_ISASCII_TEST("Extended ASCII (128)", 128);
    RUN_ISASCII_TEST("Extended ASCII (200)", 200);
    RUN_ISASCII_TEST("Extended ASCII (255)", 255);

    // 4. Özel int Değerleri
    RUN_ISASCII_TEST("EOF (int -1)", -1);
    RUN_ISASCII_TEST("Large positive int (300)", 300); // ASCII aralığı dışında
    RUN_ISASCII_TEST("Large negative int (-100)", -100); // ASCII aralığı dışında

    printf("\n--- Test Summary for ft_isascii ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}