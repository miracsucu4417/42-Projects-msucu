#include <stdio.h>
#include <ctype.h>     // Orijinal isalnum ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_isalnum_test_case(int input_val, const char *test_name) {
    int ft_result = ft_isalnum(input_val);
    int original_result = isalnum(input_val);
    
    // Geçme koşulu: İkisi de 0 ise VEYA ikisi de sıfır değilse.
    // (Orijinal isalnum'un da 1024 gibi değerler döndürebileceğini unutma)
    int passed = ((ft_result != 0 && original_result != 0) || (ft_result == 0 && original_result == 0));

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) { // Yazdırılabilir karakter ise
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else { // Int olarak verildiğinde
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_isalnum returned: %d\n", ft_result);
        printf("  Original isalnum returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_ISALNUM_TEST(desc, val) \
    total_tests++; \
    if (_run_isalnum_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_isalnum Tests ---\n\n");

    // 1. Temel Alfabetik Karakterler (Küçük Harf)
    RUN_ISALNUM_TEST("Lowercase 'a'", 'a');
    RUN_ISALNUM_TEST("Lowercase 'z'", 'z');
    RUN_ISALNUM_TEST("Lowercase 'm'", 'm');

    // 2. Temel Alfabetik Karakterler (Büyük Harf)
    RUN_ISALNUM_TEST("Uppercase 'A'", 'A');
    RUN_ISALNUM_TEST("Uppercase 'Z'", 'Z');
    RUN_ISALNUM_TEST("Uppercase 'M'", 'M');

    // 3. Temel Sayı Karakterleri
    RUN_ISALNUM_TEST("Digit '0'", '0');
    RUN_ISALNUM_TEST("Digit '9'", '9');
    RUN_ISALNUM_TEST("Digit '5'", '5');

    // 4. Alfanumerik Olmayan Semboller
    RUN_ISALNUM_TEST("Symbol '!'", '!');
    RUN_ISALNUM_TEST("Symbol '@'", '@');
    RUN_ISALNUM_TEST("Symbol '#'", '#');
    RUN_ISALNUM_TEST("Symbol '$'", '$');

    // 5. Alfanumerik Olmayan Boşluk ve Kontrol Karakterleri
    RUN_ISALNUM_TEST("Whitespace ' '", ' ');
    RUN_ISALNUM_TEST("Newline '\\n'", '\n');
    RUN_ISALNUM_TEST("Tab '\\t'", '\t');
    RUN_ISALNUM_TEST("Null char '\\0'", '\0');

    // 6. Sınır Değerler (ASCII Tablosuna göre)
    RUN_ISALNUM_TEST("ASCII 47 (Before '0')", 47); // '/'
    RUN_ISALNUM_TEST("ASCII 48 ('0')", 48);
    RUN_ISALNUM_TEST("ASCII 57 ('9')", 57);
    RUN_ISALNUM_TEST("ASCII 58 (After '9')", 58); // ':'
    RUN_ISALNUM_TEST("ASCII 64 (Before 'A')", 64); // '@'
    RUN_ISALNUM_TEST("ASCII 65 ('A')", 65);
    RUN_ISALNUM_TEST("ASCII 90 ('Z')", 90);
    RUN_ISALNUM_TEST("ASCII 91 (After 'Z')", 91); // '['
    RUN_ISALNUM_TEST("ASCII 96 (Before 'a')", 96); // '`'
    RUN_ISALNUM_TEST("ASCII 97 ('a')", 97);
    RUN_ISALNUM_TEST("ASCII 122 ('z')", 122);
    RUN_ISALNUM_TEST("ASCII 123 (After 'z')", 123); // '{'

    // 7. Genişletilmiş ASCII veya Özel int Değerleri
    RUN_ISALNUM_TEST("Extended ASCII (int 150)", 150);
    RUN_ISALNUM_TEST("EOF (int -1)", -1);

    printf("\n--- Test Summary for ft_isalnum ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}