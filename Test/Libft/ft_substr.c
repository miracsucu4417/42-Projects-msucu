#include <stdio.h>
#include <string.h>    // strlen, strcmp, memcmp için
#include <stdlib.h>    // malloc, free için

// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Bellek içeriğini görselleştirmek için (MAIN'DEN ÖNCE TANIMLANDI)
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
static int _run_substr_test_case(const char *s, unsigned int start, t_size_t len, 
                                  const char *expected_result_str, const char *test_name) {
    char *ft_result = FT_NULL;
    int passed = 1; // Varsayılan olarak geçer

    ft_result = ft_substr(s, start, len);

    // Beklenen sonuç FT_NULL ise (malloc hatası bekleniyorsa veya s FT_NULL ise)
    if (expected_result_str == FT_NULL) {
        if (ft_result != FT_NULL) {
            printf("❌ FAILED: %s (Expected FT_NULL, got %p)\n", test_name, (void *)ft_result);
            passed = 0;
        }
    }
    // Beklenen sonuç FT_NULL değilse
    else {
        if (ft_result == FT_NULL) {
            printf("❌ FAILED: %s (Expected \"%s\", got FT_NULL)\n", test_name, expected_result_str);
            passed = 0;
        } else {
            // İçerik ve uzunluk karşılaştırması
            if (strcmp(ft_result, expected_result_str) != 0 || strlen(ft_result) != strlen(expected_result_str)) {
                printf("❌ FAILED: %s\n", test_name);
                printf("  Input: \"%s\", start: %u, len: %zu\n", s, start, len);
                printf("  ft_substr returned: \"%s\"\n", ft_result);
                printf("  Expected:           \"%s\"\n", expected_result_str);
                passed = 0;
            }
        }
    }

    // ÖNEMLİ: Tahsis edilen belleği serbest bırak!
    if (ft_result) free(ft_result);

    return passed;
}

// Kolay test çağırmak için makro
#define RUN_SUBSTR_TEST(desc, s_val, start_val, len_val, expected_val) \
    total_tests++; \
    if (_run_substr_test_case(s_val, start_val, len_val, expected_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_substr Tests ---\n\n");

    // 1. Temel Kopyalamalar
    RUN_SUBSTR_TEST("Basic substring: 'o Wo'", "Hello World", 4, 4, "o Wo");
    RUN_SUBSTR_TEST("Substring from beginning", "Hello World", 0, 5, "Hello");
    RUN_SUBSTR_TEST("Substring to end", "Hello World", 6, 10, "World"); // len 10 > kalan 5, kalanını kopyalar

    // 2. Kenar Durumlar: start out of bounds
    RUN_SUBSTR_TEST("Start out of bounds (return empty string)", "Hello", 10, 5, ""); // ft_strlen("Hello") = 5. start=10.
    RUN_SUBSTR_TEST("Start at exact length (return empty string)", "Hello", 5, 5, ""); // start=5, len=5.

    // 3. Kenar Durumlar: len (kopyalama uzunluğu)
    RUN_SUBSTR_TEST("Len is 0 (return empty string)", "Hello", 0, 0, "");
    RUN_SUBSTR_TEST("Len greater than remaining string", "Hello", 1, 10, "ello"); // Kalan 4, len 10. "ello" kopyalar.
    RUN_SUBSTR_TEST("Len exactly remaining string", "Hello", 1, 4, "ello");

    // 4. Boş Stringler
    RUN_SUBSTR_TEST("Empty input string", "", 0, 5, ""); // Boş string'den alt string

    // 5. FT_NULL Input String (PDF'e göre FT_NULL dönmeli)
    RUN_SUBSTR_TEST("FT_NULL input string (Expected FT_NULL)", FT_NULL, 0, 5, FT_NULL); // FT_NULL için FT_NULL beklenir

    // 6. Stringde Dahili FT_NULL Karakter Testi (BEKLENTİ DÜZELTİLDİ)
    // ft_strlen("abc\0def") 3 döndürdüğü için,
    // ft_substr("abc\0def", 0, 7) aslında sadece 3 karakter kopyalar ve '\0' ile sonlandırır.
    char s_internal_FT_NULL[] = "abc\0def"; // Bu bir C stringi, strlen 3 verir.
    char expected_internal_FT_NULL_substr[] = {'a', 'b', 'c', '\0'}; // Beklenen 3 bayt + FT_NULL
    char *ft_res_internal = ft_substr(s_internal_FT_NULL, 0, 7); // ft_substr 3 karakter kopyalar

    int passed_internal_FT_NULL_test = 1;
    if (ft_res_internal == FT_NULL || memcmp(ft_res_internal, expected_internal_FT_NULL_substr, 4) != 0) { // 4 byte: 3 + FT_NULL
        printf("❌ FAILED: Substring with internal FT_NULL (memcmp check)\n");
        printf("  Input: \"%s\", start: 0, len: 7\n", s_internal_FT_NULL);
        printf("  ft_substr returned: %p\n", (void*)ft_res_internal);
        if (ft_res_internal) print_memory("  Content: ", ft_res_internal, 4); // Sadece 4 baytı göster
        passed_internal_FT_NULL_test = 0;
    }
    // Bu manuel testin toplam test sayısına eklenmesi:
    total_tests++; 
    if (passed_internal_FT_NULL_test) passed_tests++; 

    if (ft_res_internal) free(ft_res_internal);


    printf("\n--- Test Summary for ft_substr ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}