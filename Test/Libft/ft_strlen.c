#include <stdio.h>
#include <string.h>    // Orijinal strlen ile karşılaştırmak için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_strlen_test_case(const char *s, const char *test_name) {
    size_t ft_len = ft_strlen(s);
    size_t original_len = strlen(s);
    
    int passed = (ft_len == original_len);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input String: \"%s\"\n", s);
        printf("  ft_strlen returned: %zu\n", ft_len);
        printf("  Original strlen returned: %zu\n", original_len);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRLEN_TEST(desc, val) \
    total_tests++; \
    if (_run_strlen_test_case(val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strlen Tests ---\n\n");

    // 1. Temel Stringler
    RUN_STRLEN_TEST("Normal string", "Hello World!");
    RUN_STRLEN_TEST("Empty string", "");
    RUN_STRLEN_TEST("Single character string", "A");
    RUN_STRLEN_TEST("String with numbers and symbols", "123!@#$abc");
    RUN_STRLEN_TEST("String with spaces", "   This has spaces   ");

    // 2. Özel Karakterler İçeren Stringler
    RUN_STRLEN_TEST("String with newline", "Line1\nLine2");
    RUN_STRLEN_TEST("String with tab", "Tab\tTest");
    RUN_STRLEN_TEST("String with null char in middle (should stop at null)", "Null\0CharInMiddle");
    RUN_STRLEN_TEST("String with unicode-like chars (if system supports)", "你好世界"); // Bu karakterler birden fazla bayt olabilir, strlen bayt sayısını verir.

    // 3. Uzun String
    char long_str[1000];
    for (int i = 0; i < 999; ++i) {
        long_str[i] = 'X';
    }
    long_str[999] = '\0';
    RUN_STRLEN_TEST("Long string (999 chars)", long_str);

    // 4. Kenar Durum: NULL String (Bu durum genellikle undefined behavior'dır,
    // ancak bazı test süitleri veya projeler bunu da kontrol edebilir.
    // Fonksiyonun NULL input'u nasıl ele alacağını burada görmeliyiz.
    // Normalde strlen NULL input'u işleyemez ve segfault verir.)
    // ft_strlen'in pdf'inde NULL input'u nasıl ele alacağı belirtilmemiş.
    // Orijinal strlen, NULL pointer ile çağrıldığında segfault verir.
    // Bu yüzden bu testi yorum satırı olarak bırakıyorum, çalıştırmak segfault'a yol açabilir.
    // RUN_STRLEN_TEST("NULL string (EXPECT SEGFAULT or crash if not handled)", NULL);


    printf("\n--- Test Summary for ft_strlen ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}