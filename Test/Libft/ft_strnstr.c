#include <stdio.h>
#include <string.h>    // Orijinal strstr, memcmp, strlen için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Bellek içeriğini görselleştirmek için
void print_memory(const char *label, const char *mem, size_t n) {
    printf("%s [", label);
    for (size_t i = 0; i < n; ++i) {
        if (mem[i] >= 32 && mem[i] <= 126) // Yazdırılabilir karakterler
            printf("%c", mem[i]);
        else if (mem[i] == '\0')
            printf("N"); // Null bayt için 'N' (Null)
        else
            printf("%02X", (unsigned char)mem[i]); // Hex değerini göster
    }
    printf("]\n");
}

// Orijinal strnstr'ın davranışını taklit eden yardımcı fonksiyon (BSD bağımlılığını kaldırmak için)
// Bu fonksiyonu test main.c dosyanızın içinde bulundurun.
static char *my_original_strnstr(const char *big, const char *little, size_t len)
{
    size_t  little_len;

    if (!little) // Güvenlik için, NULL needle kabul etmez. Orijinal strnstr'ın davranışı NULL'da UB'dir.
        return (NULL);
    little_len = strlen(little);
    if (little_len == 0)
        return ((char *)big); // Eğer little boşsa, big'i döndür

    // Arama yapılacak alanın boyutunu big ve len'in minimumu olarak al
    size_t big_len_actual = strlen(big);
    if (len == 0) return NULL; // Eğer arama uzunluğu 0 ise ve needle boş değilse, bulunamaz.

    // big_len, arama yapılacak max big_len.
    // big_len = (big_len_actual < len) ? big_len_actual : len;

    // big'i baştan sona tara
    for (size_t i = 0; i < len && big[i]; i++) // len'e kadar veya big'in sonuna kadar git
    {
        // Eğer kalan big uzunluğu little'dan kısaysa, artık bulamayız
        if (len - i < little_len)
            return (NULL);

        // Eğer mevcut karakter eşleşirse ve kalan kısım yeterliyse
        if (big[i] == little[0] && memcmp(&big[i], little, little_len) == 0)
        {
            return ((char *)&big[i]); // Bulunan yeri döndür
        }
    }
    return (NULL); // Bulunamadı
}


// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
static int _run_strnstr_test_case(const char *haystack, const char *needle, size_t len, const char *test_name) {
    char *ft_result = ft_strnstr(haystack, needle, len);
    char *original_result = my_original_strnstr(haystack, needle, len); // Kendi yazdığımız orijinal taklit fonksiyonu
    
    // Geçme koşulu: Her iki pointer da aynı mı?
    int passed = (ft_result == original_result);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Haystack: \"%s\"\n", haystack);
        printf("  Needle:   \"%s\"\n", needle);
        printf("  Len:      %zu\n", len);
        printf("  ft_strnstr returned:      %p (-> \"%s\")\n", (void *)ft_result, ft_result ? ft_result : "NULL");
        printf("  Original strnstr returned: %p (-> \"%s\")\n", (void *)original_result, original_result ? original_result : "NULL");
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRNSTR_TEST(desc, haystack_val, needle_val, len_val) \
    total_tests++; \
    if (_run_strnstr_test_case(haystack_val, needle_val, len_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strnstr Tests ---\n\n");

    // 1. Temel Bulma Testleri
    RUN_STRNSTR_TEST("Needle at beginning", "Hello World", "Hello", 11);
    RUN_STRNSTR_TEST("Needle in middle", "Hello World", "World", 11);
    RUN_STRNSTR_TEST("Needle at end", "Hello World", "rld", 11);
    RUN_STRNSTR_TEST("Needle is single char", "Hello World", "o", 11);

    // 2. Boş Needle Testleri
    RUN_STRNSTR_TEST("Empty needle, valid haystack", "Hello World", "", 11); // Should return haystack start
    RUN_STRNSTR_TEST("Empty needle, empty haystack", "", "", 0);             // Should return haystack start

    // 3. Bulunamama Testleri
    RUN_STRNSTR_TEST("Needle not found", "Hello World", "xyz", 11);
    RUN_STRNSTR_TEST("Needle not found (case sensitive)", "Hello World", "hello", 11);

    // 4. Len Parametresi Testleri (Sınırlandırma)
    RUN_STRNSTR_TEST("Needle fits, len covers it", "Foo Bar Baz", "Bar", 11);
    RUN_STRNSTR_TEST("Needle fits, len exactly covers it", "Foo Bar Baz", "Bar", 7); 
    RUN_STRNSTR_TEST("Needle partial (len cuts it short)", "Foo Bar Baz", "Bar", 6); 
    RUN_STRNSTR_TEST("Needle after len limit", "Hello World", "World", 5); 
    RUN_STRNSTR_TEST("Len is 0", "Hello World", "Hello", 0); 
    RUN_STRNSTR_TEST("Len is 0, empty needle", "Hello World", "", 0); 

    // 5. Haystack / Needle İçinde Null Karakter
    RUN_STRNSTR_TEST("Needle with internal null", "abc\0def", "bc\0d", 7); 
    RUN_STRNSTR_TEST("Haystack with internal null, needle before null", "abc\0def", "bc", 3); 
    RUN_STRNSTR_TEST("Haystack with internal null, needle after null", "abc\0def", "def", 7); 

    // 6. Çok Uzun Stringler
    char long_haystack[200];
    char long_needle[] = "long";
    memset(long_haystack, 'x', 199);
    long_haystack[100] = 'l'; long_haystack[101] = 'o'; long_haystack[102] = 'n'; long_haystack[103] = 'g';
    long_haystack[199] = '\0';
    RUN_STRNSTR_TEST("Long haystack, needle in middle", long_haystack, long_needle, 200);
    RUN_STRNSTR_TEST("Long haystack, needle not found", long_haystack, "nope", 200);
    RUN_STRNSTR_TEST("Long haystack, needle beyond len", long_haystack, long_needle, 50); 

    // 7. NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // strnstr'a NULL pointer geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRNSTR_TEST("NULL haystack", NULL, "test", 5);
    // RUN_STRNSTR_TEST("NULL needle", "test", NULL, 5);


    printf("\n--- Test Summary for ft_strnstr ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}