#include <stdio.h>
#include <string.h>    // Orijinal strrchr ve strlen için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_strrchr_test_case(const char *s, int c, const char *test_name) {
    char *ft_result = ft_strrchr(s, c);
    char *original_result = strrchr(s, c);
    
    // Geçme koşulu: Her iki pointer da aynı mı?
    int passed = (ft_result == original_result);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input String: \"%s\"\n", s);
        printf("  Char to find: '%c' (ASCII: %d)\n", (char)c, c);
        printf("  ft_strrchr returned: %p (-> '%c')\n", (void *)ft_result, ft_result ? *ft_result : ' ');
        printf("  Original strrchr returned: %p (-> '%c')\n", (void *)original_result, original_result ? *original_result : ' ');
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRRCHR_TEST(desc, str_val, char_val) \
    total_tests++; \
    if (_run_strrchr_test_case(str_val, char_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strrchr Tests ---\n\n");

    // 1. Karakter Bulundu
    RUN_STRRCHR_TEST("Found at end", "Hello World", 'd');
    RUN_STRRCHR_TEST("Found in middle (last 'o')", "Hello World", 'o'); // Should point to last 'o'
    RUN_STRRCHR_TEST("Found at beginning (only one 'H')", "Hello World", 'H'); // Should point to first 'H'
    RUN_STRRCHR_TEST("Found multiple times (last 'a')", "banana", 'a'); // Should point to last 'a'
    RUN_STRRCHR_TEST("Found null terminator", "Hello", '\0'); // Should point to '\0'

    // 2. Karakter Bulunamadı
    RUN_STRRCHR_TEST("Not found", "Hello World", 'x');
    RUN_STRRCHR_TEST("Not found (case sensitive)", "Hello World", 'h');
    RUN_STRRCHR_TEST("Empty string, char not found", "", 'a');

    // 3. Kenar Durumlar
    RUN_STRRCHR_TEST("Empty string, find null terminator", "", '\0'); // Should point to the null terminator
    RUN_STRRCHR_TEST("Single char string, found", "A", 'A');
    RUN_STRRCHR_TEST("Single char string, not found", "A", 'B');
    RUN_STRRCHR_TEST("String containing only null", "", '\0'); // Same as empty string test for null

    // 4. Özel Karakterler (int c)
    RUN_STRRCHR_TEST("Find digit", "abc123xyz123", '3');
    RUN_STRRCHR_TEST("Find symbol", "abc!@#xyz!@#", '#');
    
    // Non-printable karakter (ASCII 1)
    char non_printable_char_test_str[] = {'a', 'b', 'c', 1, 'd', 'e', 'f', 1, 'g', '\0'};
    RUN_STRRCHR_TEST("Find non-printable (ASCII 1)", non_printable_char_test_str, 1);

    // 5. Uzun String
    char long_str[200];
    memset(long_str, 'x', 199);
    long_str[50] = 'Y';
    long_str[150] = 'Y'; // Son Y
    long_str[199] = '\0';
    RUN_STRRCHR_TEST("Long string - found last Y", long_str, 'Y');
    RUN_STRRCHR_TEST("Long string - not found", long_str, 'Z');

    // 6. NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // strrchr'a NULL s geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRRCHR_TEST("NULL string", NULL, 'a');
    // RUN_STRRCHR_TEST("NULL string, find null", NULL, '\0');

    printf("\n--- Test Summary for ft_strrchr ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}