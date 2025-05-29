#include <stdio.h>
#include <ctype.h>     // Orijinal tolower ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_tolower_test_case(int input_val, const char *test_name) {
    int ft_result = ft_tolower(input_val);
    int original_result = tolower(input_val);
    
    // Geçme koşulu: Dönüş değerlerinin tam olarak aynı olması
    int passed = (ft_result == original_result);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) { // Yazdırılabilir karakter ise
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else { // Int olarak verildiğinde
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_tolower returned: '%c' (ASCII: %d)\n", (char)ft_result, ft_result);
        printf("  Original tolower returned: '%c' (ASCII: %d)\n", (char)original_result, original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_TOLOWER_TEST(desc, val) \
    total_tests++; \
    if (_run_tolower_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_tolower Tests ---\n\n");

    // 1. Temel Büyük Harfler
    RUN_TOLOWER_TEST("Uppercase 'A'", 'A');
    RUN_TOLOWER_TEST("Uppercase 'Z'", 'Z');
    RUN_TOLOWER_TEST("Uppercase 'M'", 'M');

    // 2. Temel Küçük Harfler (Değişmemeli)
    RUN_TOLOWER_TEST("Lowercase 'a'", 'a');
    RUN_TOLOWER_TEST("Lowercase 'z'", 'z');
    RUN_TOLOWER_TEST("Lowercase 'm'", 'm');

    // 3. Rakamlar (Değişmemeli)
    RUN_TOLOWER_TEST("Digit '0'", '0');
    RUN_TOLOWER_TEST("Digit '9'", '9');

    // 4. Semboller (Değişmemeli)
    RUN_TOLOWER_TEST("Symbol '!'", '!');
    RUN_TOLOWER_TEST("Symbol '@'", '@');
    RUN_TOLOWER_TEST("Symbol '{'", '{'); // 'z'den sonra
    RUN_TOLOWER_TEST("Symbol '['", '['); // 'Z'den sonra

    // 5. Boşluk ve Kontrol Karakterleri (Değişmemeli)
    RUN_TOLOWER_TEST("Space ' '", ' ');
    RUN_TOLOWER_TEST("Newline '\\n'", '\n');
    RUN_TOLOWER_TEST("Tab '\\t'", '\t');
    RUN_TOLOWER_TEST("Null char '\\0'", '\0');

    // 6. Sınır Değerler (ASCII Tablosuna göre)
    // Büyük harf aralığının hemen dışındakiler
    RUN_TOLOWER_TEST("ASCII 64 ('@' - before 'A')", 64);
    RUN_TOLOWER_TEST("ASCII 65 ('A')", 65);
    RUN_TOLOWER_TEST("ASCII 90 ('Z')", 90);
    RUN_TOLOWER_TEST("ASCII 91 ('[' - after 'Z')", 91);

    // Küçük harf aralığının hemen dışındakiler
    RUN_TOLOWER_TEST("ASCII 96 ('`' - before 'a')", 96);
    RUN_TOLOWER_TEST("ASCII 97 ('a')", 97);
    RUN_TOLOWER_TEST("ASCII 122 ('z')", 122);
    RUN_TOLOWER_TEST("ASCII 123 ('{' - after 'z')", 123);

    // 7. Genişletilmiş ASCII veya Özel int Değerleri
    RUN_TOLOWER_TEST("Extended ASCII (150)", 150);
    RUN_TOLOWER_TEST("Negative (EOF -1)", -1);
    RUN_TOLOWER_TEST("Large positive int (300)", 300);

    printf("\n--- Test Summary for ft_tolower ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}