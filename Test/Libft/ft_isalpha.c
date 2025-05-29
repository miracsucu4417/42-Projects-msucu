#include <stdio.h>
#include <ctype.h>     // Orijinal isalpha ile karşılaştırmak için
#include "libft.h" // Kendi libft.h dosyan için

// İç yardımcı fonksiyon: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_isalpha_test_case(int input_val, const char *test_name) {
    int ft_result = ft_isalpha(input_val);
    int original_result = isalpha(input_val);
    
    // Geçme koşulu: İkisi de 0 ise VEYA ikisi de sıfır değilse.
    // (Orijinal isalpha'nın 1024 gibi değerler döndürebileceğini unutma)
    int passed = ((ft_result != 0 && original_result != 0) || (ft_result == 0 && original_result == 0));

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        if (input_val >= 0 && input_val <= 127) { // Yazdırılabilir karakter ise
            printf("  Input: '%c' (ASCII: %d)\n", (char)input_val, input_val);
        } else { // Int olarak verildiğinde
            printf("  Input: %d\n", input_val);
        }
        printf("  ft_isalpha returned: %d\n", ft_result);
        printf("  Original isalpha returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_ISALPHA_TEST(desc, val) \
    total_tests++; \
    if (_run_isalpha_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_isalpha Tests ---\n\n");

    // 1. Temel Alfabetik Karakterler (Küçük Harf)
    RUN_ISALPHA_TEST("Lowercase 'a'", 'a');
    RUN_ISALPHA_TEST("Lowercase 'z'", 'z');
    RUN_ISALPHA_TEST("Lowercase 'm'", 'm');

    // 2. Temel Alfabetik Karakterler (Büyük Harf)
    RUN_ISALPHA_TEST("Uppercase 'A'", 'A');
    RUN_ISALPHA_TEST("Uppercase 'Z'", 'Z');
    RUN_ISALPHA_TEST("Uppercase 'M'", 'M');

    // 3. Alfabetik Olmayan Karakterler (Sayılar)
    RUN_ISALPHA_TEST("Digit '0'", '0');
    RUN_ISALPHA_TEST("Digit '9'", '9');
    RUN_ISALPHA_TEST("Digit '5'", '5');

    // 4. Alfabetik Olmayan Karakterler (Semboller)
    RUN_ISALPHA_TEST("Symbol '!'", '!');
    RUN_ISALPHA_TEST("Symbol '@'", '@');
    RUN_ISALPHA_TEST("Symbol '#'", '#');
    RUN_ISALPHA_TEST("Symbol '$'", '$');

    // 5. Alfabetik Olmayan Karakterler (Boşluk ve Kontrol Karakterleri)
    RUN_ISALPHA_TEST("Whitespace ' '", ' ');
    RUN_ISALPHA_TEST("Newline '\\n'", '\n');
    RUN_ISALPHA_TEST("Tab '\\t'", '\t');
    RUN_ISALPHA_TEST("Null char '\\0'", '\0');

    // 6. Sınır Değerler (ASCII Tablosuna göre)
    RUN_ISALPHA_TEST("ASCII 64 ('@')", 64);
    RUN_ISALPHA_TEST("ASCII 65 ('A')", 65);
    RUN_ISALPHA_TEST("ASCII 90 ('Z')", 90);
    RUN_ISALPHA_TEST("ASCII 91 ('[')", 91);
    RUN_ISALPHA_TEST("ASCII 96 ('`')", 96);
    RUN_ISALPHA_TEST("ASCII 97 ('a')", 97);
    RUN_ISALPHA_TEST("ASCII 122 ('z')", 122);
    RUN_ISALPHA_TEST("ASCII 123 ('{')", 123);

    // 7. Genişletilmiş ASCII veya Özel int Değerleri
    RUN_ISALPHA_TEST("Extended ASCII (int 150)", 150);
    RUN_ISALPHA_TEST("EOF (int -1)", -1);

    printf("\n--- Test Summary for ft_isalpha ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}