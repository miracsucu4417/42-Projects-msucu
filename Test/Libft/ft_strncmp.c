#include <stdio.h>
#include <string.h>    // Orijinal strncmp için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_strncmp_test_case(const char *s1, const char *s2, t_size_t n, const char *test_name) {
    int ft_result = ft_strncmp(s1, s2, n);
    int original_result = strncmp(s1, s2, n);
    
    // Geçme koşulu: Sonuçların işareti aynı mı?
    // ft_result = 0 && original_result = 0  -> Eşitlik
    // ft_result > 0 && original_result > 0  -> s1 > s2
    // ft_result < 0 && original_result < 0  -> s1 < s2
    int passed = ((ft_result == 0 && original_result == 0) ||
                  (ft_result > 0 && original_result > 0) ||
                  (ft_result < 0 && original_result < 0));

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  String 1: \"%s\"\n", s1);
        printf("  String 2: \"%s\"\n", s2);
        printf("  N: %zu\n", n);
        printf("  ft_strncmp returned: %d\n", ft_result);
        printf("  Original strncmp returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRNCMP_TEST(desc, s1_val, s2_val, n_val) \
    total_tests++; \
    if (_run_strncmp_test_case(s1_val, s2_val, n_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strncmp Tests ---\n\n");

    // 1. Temel Eşitlik Testleri
    RUN_STRNCMP_TEST("Equal strings (full)", "Hello", "Hello", 5);
    RUN_STRNCMP_TEST("Equal strings (partial)", "Hello World", "Hello There", 5);
    RUN_STRNCMP_TEST("Empty strings", "", "", 5);
    RUN_STRNCMP_TEST("One char string", "a", "a", 1);

    // 2. Eşitsizlik Testleri (ft_result < 0)
    RUN_STRNCMP_TEST("s1 < s2 (first char)", "apple", "banana", 5);
    RUN_STRNCMP_TEST("s1 < s2 (later char)", "apple", "apricot", 5);
    RUN_STRNCMP_TEST("s1 < s2 (different length)", "hello", "hello world", 10); // ' ' (32) vs '\0' (0)

    // 3. Eşitsizlik Testleri (ft_result > 0)
    RUN_STRNCMP_TEST("s1 > s2 (first char)", "banana", "apple", 5);
    RUN_STRNCMP_TEST("s1 > s2 (later char)", "apricot", "apple", 5);
    RUN_STRNCMP_TEST("s1 > s2 (different length)", "hello world", "hello", 10); // ' ' (32) vs '\0' (0)

    // 4. N Parametresi Testleri
    RUN_STRNCMP_TEST("N = 0 (always equal)", "Hello", "World", 0);
    RUN_STRNCMP_TEST("N less than common prefix", "apple", "apricot", 2); // "ap" equal
    RUN_STRNCMP_TEST("N larger than string length", "hi", "hi", 10); // Should stop at FT_NULL
    RUN_STRNCMP_TEST("N larger than one string, but stops at diff", "abc", "abd", 10); // "ab" equal, c vs d

    // 5. FT_NULL Karakter Testleri
    RUN_STRNCMP_TEST("s1 has FT_NULL in middle", "ab\0cd", "ab\0ef", 5); // Should compare a,b,FT_NULL,c,d
    RUN_STRNCMP_TEST("s2 has FT_NULL in middle", "ab\0ef", "ab\0cd", 5); // Should compare a,b,FT_NULL,e,f
    RUN_STRNCMP_TEST("s1 shorter (ends with FT_NULL)", "abc", "abcd", 4); // 'c' vs 'd' on 4th char
    RUN_STRNCMP_TEST("s2 shorter (ends with FT_NULL)", "abcd", "abc", 4); // 'd' vs '\0' on 4th char
    RUN_STRNCMP_TEST("One empty, one not (N > 0)", "", "abc", 1);
    RUN_STRNCMP_TEST("One empty, one not (N > 0, reversed)", "abc", "", 1);

    // 6. Özel Karakterler (unsigned char davranışı için)
    // C'de char signed veya unsigned olabilir, bu yüzden >127 değerler farklı yorumlanabilir.
    // strncmp'nin unsigned char olarak karşılaştırdığını garanti etmeliyiz.
    // Örneğin, Türkçe karakterler veya ikili veriler.
    char s_ext1[] = {'A', 'B', (char)200, 'D', '\0'};
    char s_ext2[] = {'A', 'B', (char)100, 'D', '\0'}; // 100 < 200
    char s_ext3[] = {'A', 'B', (char)200, 'D', '\0'}; // Same as s_ext1
    RUN_STRNCMP_TEST("Extended ASCII: s1 > s2", s_ext1, s_ext2, 4); // Should be s1 > s2
    RUN_STRNCMP_TEST("Extended ASCII: s1 == s2", s_ext1, s_ext3, 4); // Should be s1 == s2

    // 7. FT_NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // strncmp'e FT_NULL pointer geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRNCMP_TEST("FT_NULL s1", FT_NULL, "test", 5);
    // RUN_STRNCMP_TEST("FT_NULL s2", "test", FT_NULL, 5);
    // RUN_STRNCMP_TEST("FT_NULL s1, FT_NULL s2", FT_NULL, FT_NULL, 5);


    printf("\n--- Test Summary for ft_strncmp ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}