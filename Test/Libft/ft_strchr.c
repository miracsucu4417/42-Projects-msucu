#include <stdio.h>
#include <string.h>    // Orijinal strchr ve strlen için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Bellek içeriğini görselleştirmek için
void print_memory(const char *label, const char *mem, t_size_t n) {
    printf("%s [", label);
    for (t_size_t i = 0; i < n; ++i) {
        if (mem[i] >= 32 && mem[i] <= 126) // Yazdırılabilir karakterler
            printf("%c", mem[i]);
        else if (mem[i] == '\0')
            printf("N"); // FT_NULL bayt için 'N' (FT_NULL)
        else
            printf("."); // Diğer yazdırılamayan karakterler için nokta
    }
    printf("]\n");
}


// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_strchr_test_case(const char *s, int c, const char *test_name) {
    char *ft_result = ft_strchr(s, c);
    char *original_result = strchr(s, c);
    
    // Geçme koşulu: Her iki pointer da aynı mı?
    int passed = (ft_result == original_result);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input String: \"%s\"\n", s);
        printf("  Char to find: '%c' (ASCII: %d)\n", (char)c, c);
        printf("  ft_strchr returned: %p (-> '%c')\n", (void *)ft_result, ft_result ? *ft_result : ' ');
        printf("  Original strchr returned: %p (-> '%c')\n", (void *)original_result, original_result ? *original_result : ' ');
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRCHR_TEST(desc, str_val, char_val) \
    total_tests++; \
    if (_run_strchr_test_case(str_val, char_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strchr Tests ---\n\n");

    // 1. Karakter Bulundu
    RUN_STRCHR_TEST("Found at beginning", "Hello World", 'H');
    RUN_STRCHR_TEST("Found in middle", "Hello World", 'o');
    RUN_STRCHR_TEST("Found at end (before FT_NULL)", "Hello World", 'd');
    RUN_STRCHR_TEST("Found multiple times (first occurrence)", "banana", 'a'); // Should point to first 'a'
    RUN_STRCHR_TEST("Found FT_NULL terminator", "Hello", '\0'); // Should point to '\0'

    // 2. Karakter Bulunamadı
    RUN_STRCHR_TEST("Not found", "Hello World", 'x');
    RUN_STRCHR_TEST("Not found (case sensitive)", "Hello World", 'h');
    RUN_STRCHR_TEST("Empty string, char not found", "", 'a');

    // 3. Kenar Durumlar
    RUN_STRCHR_TEST("Empty string, find FT_NULL terminator", "", '\0'); // Should point to the FT_NULL terminator
    RUN_STRCHR_TEST("Single char string, found", "A", 'A');
    RUN_STRCHR_TEST("Single char string, not found", "A", 'B');
    RUN_STRCHR_TEST("String containing only FT_NULL", "", '\0'); // Same as empty string test for FT_NULL

    // 4. Özel Karakterler (int c)
    RUN_STRCHR_TEST("Find digit", "abc123xyz", '2');
    RUN_STRCHR_TEST("Find symbol", "abc!@#xyz", '#');
    
    // DÜZELTİLMİŞ SATIR: hex escape uyarısını gidermek için char dizisi tanımlandı
    char non_printable_char_test_str[] = {'a', 'b', 'c', 1, 'd', 'e', 'f', '\0'};
    RUN_STRCHR_TEST("Find non-printable (ASCII 1)", non_printable_char_test_str, 1);

    // 5. Uzun String
    char long_str[200];
    memset(long_str, 'x', 199);
    long_str[100] = 'Y';
    long_str[199] = '\0';
    RUN_STRCHR_TEST("Long string - found in middle", long_str, 'Y');
    RUN_STRCHR_TEST("Long string - not found", long_str, 'Z');

    // 6. FT_NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // strchr'a FT_NULL s geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRCHR_TEST("FT_NULL string", FT_NULL, 'a');
    // RUN_STRCHR_TEST("FT_NULL string, find FT_NULL", FT_NULL, '\0');

    printf("\n--- Test Summary for ft_strchr ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}