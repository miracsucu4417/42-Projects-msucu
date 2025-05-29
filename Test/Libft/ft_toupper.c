#include <stdio.h>
#include <ctype.h>     // Orijinal toupper ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_toupper_test_case(int input_val, const char *test_name) {
    int ft_result = ft_toupper(input_val);
    int original_result = toupper(input_val);
    
    // Geçme koşulu: Dönüş değerlerinin tam olarak aynı olması
    int passed = (ft_result == original_result);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) { // Yazdırılabilir karakter ise
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else { // Int olarak verildiğinde
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_toupper returned: '%c' (ASCII: %d)\n", (char)ft_result, ft_result);
        printf("  Original toupper returned: '%c' (ASCII: %d)\n", (char)original_result, original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_TOUPPER_TEST(desc, val) \
    total_tests++; \
    if (_run_toupper_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_toupper Tests ---\n\n");

    // 1. Temel Küçük Harfler
    RUN_TOUPPER_TEST("Lowercase 'a'", 'a');
    RUN_TOUPPER_TEST("Lowercase 'z'", 'z');
    RUN_TOUPPER_TEST("Lowercase 'm'", 'm');

    // 2. Temel Büyük Harfler (Değişmemeli)
    RUN_TOUPPER_TEST("Uppercase 'A'", 'A');
    RUN_TOUPPER_TEST("Uppercase 'Z'", 'Z');
    RUN_TOUPPER_TEST("Uppercase 'M'", 'M');

    // 3. Rakamlar (Değişmemeli)
    RUN_TOUPPER_TEST("Digit '0'", '0');
    RUN_TOUPPER_TEST("Digit '9'", '9');

    // 4. Semboller (Değişmemeli)
    RUN_TOUPPER_TEST("Symbol '!'", '!');
    RUN_TOUPPER_TEST("Symbol '@'", '@');
    RUN_TOUPPER_TEST("Symbol '{'", '{'); // 'z'den sonra
    RUN_TOUPPER_TEST("Symbol '['", '['); // 'Z'den sonra

    // 5. Boşluk ve Kontrol Karakterleri (Değişmemeli)
    RUN_TOUPPER_TEST("Space ' '", ' ');
    RUN_TOUPPER_TEST("Newline '\\n'", '\n');
    RUN_TOUPPER_TEST("Tab '\\t'", '\t');
    RUN_TOUPPER_TEST("Null char '\\0'", '\0');

    // 6. Sınır Değerler (ASCII Tablosuna göre)
    // Küçük harf aralığının hemen dışındakiler
    RUN_TOUPPER_TEST("ASCII 96 ('`' - before 'a')", 96);
    RUN_TOUPPER_TEST("ASCII 97 ('a')", 97);
    RUN_TOUPPER_TEST("ASCII 122 ('z')", 122);
    RUN_TOUPPER_TEST("ASCII 123 ('{' - after 'z')", 123);

    // Büyük harf aralığının hemen dışındakiler
    RUN_TOUPPER_TEST("ASCII 64 ('@' - before 'A')", 64);
    RUN_TOUPPER_TEST("ASCII 65 ('A')", 65);
    RUN_TOUPPER_TEST("ASCII 90 ('Z')", 90);
    RUN_TOUPPER_TEST("ASCII 91 ('[' - after 'Z')", 91);

    // 7. Genişletilmiş ASCII veya Özel int Değerleri
    // toupper/tolower C'de `unsigned char` veya EOF ile çağrıldığında tanımlıdır.
    // Diğer int değerleri için UB olabilir ama çoğu implementasyonda kendi değerini döndürür.
    RUN_TOUPPER_TEST("Extended ASCII (150)", 150);
    RUN_TOUPPER_TEST("Negative (EOF -1)", -1);
    RUN_TOUPPER_TEST("Large positive int (300)", 300);

    printf("\n--- Test Summary for ft_toupper ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}