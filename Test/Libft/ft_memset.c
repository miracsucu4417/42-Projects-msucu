#include <stdio.h>
#include <string.h>    // Orijinal memset, memcpy, memcmp, strlen için
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
        else
            printf("."); // Yazdırılamayan karakterler için nokta
    }
    printf("]\n");
}

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Dışarıdan bir buffer alarak çalışacak.
static int _run_memset_test_case(void *dest_ft, void *dest_original, const char *src_val, int c, size_t n, const char *test_name) {
    size_t original_str_len = strlen(src_val);

    // Başlangıç durumunu her iki buffer'a da kopyala
    // Bu, her testin temiz bir başlangıç noktasına sahip olmasını sağlar.
    memcpy(dest_ft, src_val, original_str_len + 1); // +1 null terminator için
    memcpy(dest_original, src_val, original_str_len + 1);

    // Kendi ft_memset fonksiyonunu çalıştır
    ft_memset(dest_ft, c, n);

    // Orijinal memset fonksiyonunu çalıştır
    memset(dest_original, c, n);

    // Karşılaştırma
    int passed = (memcmp(dest_ft, dest_original, original_str_len) == 0); // Sadece orijinal uzunluk kadar karşılaştır

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input buffer (initial from literal): ");
        print_memory(" ", src_val, original_str_len);
        printf("  Char to set: '%c' (ASCII: %d), N: %zu\n", (char)c, c, n);
        printf("  ft_memset result: ");
        print_memory(" ", dest_ft, original_str_len);
        printf("  Original memset result: ");
        print_memory(" ", dest_original, original_str_len);
    }
    return passed;
}

// Makro: Testi çağırmak için. Max 200 karakterlik bir string için kullanıyoruz.
// Test buffer'ları main içinde bir kez tanımlanacak ve makroya geçirilecek.
#define RUN_MEMSET_TEST(desc, initial_str, val, num) \
    total_tests++; \
    if (_run_memset_test_case(_ft_memset_test_buf, _original_memset_test_buf, initial_str, val, num, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    // Test Buffer'ları: Bu buffer'ları main içinde bir kez tanımlıyoruz.
    // Tüm testler bu buffer'ları kullanacak, ancak her test _run_memset_test_case
    // çağrıldığında içeriğini sıfırdan kopyalayarak temiz bir başlangıç yapacak.
    char _ft_memset_test_buf[200];
    char _original_memset_test_buf[200];


    printf("--- Running ft_memset Tests ---\n\n");

    // 1. Temel Testler
    RUN_MEMSET_TEST("Set 'A' in 'Hello World!' (first 5 chars)", "Hello World!", 'A', 5);
    RUN_MEMSET_TEST("Set 'Z' in '1234567890abcdefgh' (all chars)", "1234567890abcdefgh", 'Z', strlen("1234567890abcdefgh"));
    RUN_MEMSET_TEST("Set 0 (null char) in 'abcdef' (first 3 chars)", "abcdef", 0, 3);
    RUN_MEMSET_TEST("Set 'X' in 'abc' (all chars)", "abc", 'X', strlen("abc"));

    // 2. Kenar Durumlar
    RUN_MEMSET_TEST("n = 0 (No change)", "Hello World!", 'X', 0);
    RUN_MEMSET_TEST("Empty string, n = 0", "", 'A', 0);

    // 3. Özel Değerler (int c için)
    RUN_MEMSET_TEST("Set 255 (unsigned char max) in 'Hello'", "Hello", 255, 5);
    RUN_MEMSET_TEST("Set -1 (int) in 'Hello'", "Hello", -1, 5);
    RUN_MEMSET_TEST("Set 150 (extended ASCII) in 'Test'", "Test", 150, 4);

    // 4. NULL Pointer Testi (BU HALA SEGFAULT VERİR, YORUM SATIRI KALMALI)
    // memset/ft_memset'e NULL pointer geçmek, n=0 olsa bile C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_MEMSET_TEST("NULL pointer, n = 5", NULL, 'X', 5);
    // RUN_MEMSET_TEST("NULL pointer, n = 0", NULL, 'X', 0);


    printf("\n--- Test Summary for ft_memset ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}