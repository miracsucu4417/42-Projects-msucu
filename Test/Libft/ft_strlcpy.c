#include <stdio.h>
#include <string.h>    // Orijinal strlcpy (veya strcpy/strncpy) ve memcmp için
#include <stdlib.h>    // malloc ve free için

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
            printf("."); // Diğer yazdırılamayan karakterler için nokta
    }
    printf("]\n");
}

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// `ft_dest_buf`, `original_dest_buf` main'den gelen buffer'lardır.
static int _run_strlcpy_test_case(char *ft_dest_buf, char *original_dest_buf, 
                                  const char *src, size_t dest_size, const char *test_name) {
    
    // Her iki hedef buffer'ı da başlangıçta 'A' ile dolduralım
    // Kopyalanmayan kısımların değiştirilmediğini test etmek için.
    memset(ft_dest_buf, 'A', 200); // 200, main'deki buffer boyutuna göre
    memset(original_dest_buf, 'A', 200); // 200, main'deki buffer boyutuna göre

    // ft_strlcpy'yi çağır
    size_t ft_ret = ft_strlcpy(ft_dest_buf, src, dest_size);

    // Orijinal strlcpy'yi çağır
    size_t original_ret = strlcpy(original_dest_buf, src, dest_size);

    // Karşılaştırma: Tüm hedef buffer'ı (200 bayt) karşılaştır.
    // Bu, null terminasyonun ve buffer sınırının doğru çalışmasını kontrol eder.
    int passed = (memcmp(ft_dest_buf, original_dest_buf, 200) == 0 && ft_ret == original_ret);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Source String: \"%s\" (len: %zu)\n", src, strlen(src));
        printf("  Destination Buffer Size: %zu\n", dest_size);
        printf("  ft_strlcpy Dest:      "); print_memory(" ", ft_dest_buf, dest_size + 2); // Kopyalanan kısım ve sonrası
        printf("  Original strlcpy Dest: "); print_memory(" ", original_dest_buf, dest_size + 2);
        printf("  ft_strlcpy Return:    %zu\n", ft_ret);
        printf("  Original strlcpy Return: %zu\n", original_ret);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRLCPY_TEST(desc, src_str, dest_buff_size) \
    total_tests++; \
    if (_run_strlcpy_test_case(_ft_strlcpy_test_buf, _original_strlcpy_test_buf, src_str, dest_buff_size, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    // Test Buffer'ları: main içinde bir kez tanımlanıyor.
    char _ft_strlcpy_test_buf[200];
    char _original_strlcpy_test_buf[200];

    printf("--- Running ft_strlcpy Tests ---\n\n");

    // 1. Temel Kopyalamalar
    RUN_STRLCPY_TEST("Full copy", "Hello World!", 20); // String sığar, null terminator dahil
    RUN_STRLCPY_TEST("Exact fit", "ExactFit", 9);      // Tam sığar, null terminator dahil
    RUN_STRLCPY_TEST("Partial copy (dest_size < src_len)", "Too Long String", 5); // "Too " kopyalanır, null ile biter
    RUN_STRLCPY_TEST("Empty source string", "", 10);   // Boş string, sadece null kopyalanır
    RUN_STRLCPY_TEST("Single char source", "A", 2);    // "A\0" kopyalanır

    // 2. Kenar Durumlar
    RUN_STRLCPY_TEST("dest_size = 0 (No copy, no null)", "Hello", 0); // Hiçbir şey kopyalanmaz, null da. Return len("Hello").
    RUN_STRLCPY_TEST("dest_size = 1 (Only null)", "Hello", 1);       // Sadece null kopyalanır. Return len("Hello").
    RUN_STRLCPY_TEST("Source has internal null", "A\0B\0C", 10);    // İlk null'a kadar kopyalanır ("A\0" şeklinde)
    RUN_STRLCPY_TEST("Source len is 0, dest_size is 0", "", 0); // Return 0, dest değişmez


    // 3. NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // strlcpy'ye NULL dest veya NULL src geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRLCPY_TEST("NULL dest, valid src, size > 0", "source", 5); // dest pointer'ı
    // RUN_STRLCPY_TEST("Valid dest, NULL src, size > 0", NULL, 10); // src pointer'ı
    // RUN_STRLCPY_TEST("NULL dest, NULL src, size > 0", NULL, 5); // dest pointer'ı
    // RUN_STRLCPY_TEST("Valid dest, valid src, size=0", "source", 0);


    printf("\n--- Test Summary for ft_strlcpy ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}