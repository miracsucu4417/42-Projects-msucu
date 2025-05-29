#include <stdio.h>
#include <ctype.h>     // Orijinal isprint ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_isprint_test_case(int input_val, const char *test_name) {
    int ft_result = ft_isprint(input_val);
    int original_result = isprint(input_val);
    
    // Geçme koşulu: İkisi de 0 ise VEYA ikisi de sıfır değilse.
    int passed = ((ft_result != 0 && original_result != 0) || (ft_result == 0 && original_result == 0));

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) { // Yazdırılabilir karakter ise
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else { // Int olarak verildiğinde
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_isprint returned: %d\n", ft_result);
        printf("  Original isprint returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_ISPRINT_TEST(desc, val) \
    total_tests++; \
    if (_run_isprint_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_isprint Tests ---\n\n");

    // 1. Temel Yazdırılabilir Karakterler
    RUN_ISPRINT_TEST("Space ' '", ' ');
    RUN_ISPRINT_TEST("Digit '0'", '0');
    RUN_ISPRINT_TEST("Lowercase 'a'", 'a');
    RUN_ISPRINT_TEST("Uppercase 'Z'", 'Z');
    RUN_ISPRINT_TEST("Symbol '!'", '!');
    RUN_ISPRINT_TEST("Symbol '~'", '~');

    // 2. Yazdırılabilir Olmayan Kontrol Karakterleri
    RUN_ISPRINT_TEST("Null char '\\0'", '\0');
    RUN_ISPRINT_TEST("Tab '\\t'", '\t');
    RUN_ISPRINT_TEST("Newline '\\n'", '\n');
    RUN_ISPRINT_TEST("Backspace (ASCII 8)", 8);
    RUN_ISPRINT_TEST("Vertical Tab (ASCII 11)", 11);
    RUN_ISPRINT_TEST("Form Feed (ASCII 12)", 12);
    RUN_ISPRINT_TEST("Carriage Return (ASCII 13)", 13);
    RUN_ISPRINT_TEST("Unit Separator (ASCII 31)", 31); // ' ' (boşluk)'tan hemen önce

    // 3. Yazdırılabilir Karakterlerin Sınırları
    RUN_ISPRINT_TEST("ASCII 31 (Before Space)", 31); // Unit Separator
    RUN_ISPRINT_TEST("ASCII 32 (Space)", 32);
    RUN_ISPRINT_TEST("ASCII 126 ('~')", 126);
    RUN_ISPRINT_TEST("ASCII 127 (DEL)", 127); // Delete karakteri, yazdırılamaz

    // 4. ASCII Aralığı Dışındaki int Değerleri
    RUN_ISPRINT_TEST("Extended ASCII (128)", 128);
    RUN_ISPRINT_TEST("Large positive int (200)", 200);
    RUN_ISPRINT_TEST("EOF (int -1)", -1);
    RUN_ISPRINT_TEST("Large negative int (-50)", -50);

    printf("\n--- Test Summary for ft_isprint ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}