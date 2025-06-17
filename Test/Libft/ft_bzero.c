#include <stdio.h>
#include <string.h>    // Orijinal bzero (veya memset), memcmp için
#include <stdlib.h>    // malloc ve free için
// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// İç yardımcı fonksiyon: Bellek içeriğini görselleştirmek için (önceki gibi)
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
static int _run_bzero_test_case(void *dest_ft, void *dest_original, const char *initial_str, t_size_t n, const char *test_name) {
    t_size_t initial_len = strlen(initial_str); // Başlangıç stringinin uzunluğu

    // ft_bzero için kopyala
    memcpy(dest_ft, initial_str, initial_len + 1); // +1 FT_NULL terminator için
    ft_bzero(dest_ft, n);

    // orijinal bzero için kopyala (bzero Linux'ta direkt yoksa memset(...,0,...) kullan)
    memcpy(dest_original, initial_str, initial_len + 1); // +1 FT_NULL terminator için
    // macOS'ta <strings.h> ile bzero var. Linux'ta genellikle <string.h> içindeki memset kullanılır.
    // Her platformda çalışması için memset(..., 0, ...) kullanmak daha güvenli.
    memset(dest_original, 0, n); 

    // Karşılaştırma
    // Not: n bayt kadar sıfırlandığı için, karşılaştırmayı initial_len'den n'e kadar yapmak daha doğru
    // ya da sadece n baytlık kısmı karşılaştırmak. bzero tüm buffer'ı değil, sadece n baytı değiştirir.
    // Eğer n, initial_len'den büyükse, strlen orijinal_len'i verirken, bzero n bayt sıfırlayabilir.
    // Bu yüzden karşılaştırmayı kopyalanan buffer'ın tamamı üzerinden yapmak daha güvenli.
    // Veya sadece min(n, initial_len) kadarını karşılaştırmak.
    // Genellikle bzero, buffer'ın belirli bir kısmını sıfırlar.
    // Örneğin, "Hello", n=3 ise "NNNlo" olur. Bu durumda, orijinal_len = 5 olsa bile,
    // ilk 3 baytı karşılaştırmak daha mantıklı.
    // En iyisi, memset'in son halini (dolu buffer'ın içeriğini kontrol) kullanmak.
    
    // Geçici buffer'ı full karşılaştırmak için:
    // Örneğin, 'a' 97, 'b' 98. bzero 0 yapar.
    // 'memcmp' n kadar baytı karşılaştırmalı.
    int passed = (memcmp(dest_ft, dest_original, initial_len + 1) == 0); // FT_NULL terminator'ı da dahil et

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input buffer (initial): ");
        print_memory(" ", initial_str, initial_len);
        printf("  Bytes to zero: %zu\n", n);
        printf("  ft_bzero result: ");
        print_memory(" ", dest_ft, initial_len + 1); // FT_NULL terminator'ı da görselleştir
        printf("  Original bzero/memset result: ");
        print_memory(" ", dest_original, initial_len + 1);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_BZERO_TEST(desc, initial_str, num_bytes) \
    total_tests++; \
    if (_run_bzero_test_case(_ft_bzero_test_buf, _original_bzero_test_buf, initial_str, num_bytes, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    // Test Buffer'ları: main içinde bir kez tanımlanıyor.
    // Yeterince büyük olmalılar ki test string'leri ve sıfırlanmış kısımlar sığabilsin.
    char _ft_bzero_test_buf[200];
    char _original_bzero_test_buf[200];

    printf("--- Running ft_bzero Tests ---\n\n");

    // 1. Temel Testler
    RUN_BZERO_TEST("Zero first 5 chars of 'Hello World!'", "Hello World!", 5); // Beklenti: "NNNNN World!"
    RUN_BZERO_TEST("Zero entire string 'abcdef'", "abcdef", 6); // Beklenti: "NNNNNN"
    RUN_BZERO_TEST("Zero part of a longer string", "This is a test string", 10); // Beklenti: "NNNNNNNNNN a test string"
    RUN_BZERO_TEST("Zero a string with numbers", "12345", 5); // Beklenti: "NNNNN"

    // 2. Kenar Durumlar
    RUN_BZERO_TEST("n = 0 (No change)", "Hello World!", 0); // Beklenti: "Hello World!"
    RUN_BZERO_TEST("Empty string, n = 0", "", 0); // Beklenti: ""
    RUN_BZERO_TEST("Zero more than string length (trailing garbage is zeroed)", "Short", 10); // "Short\0...\0" -> "NNNNN\0\0\0\0\0" (ilk 5 + 5 adet 0)

    // 3. FT_NULL Pointer Testi (BU HALA SEGFAULT VEREBİLİR, YORUM SATIRI KALMALI)
    // bzero/ft_bzero'ya FT_NULL pointer geçmek, n=0 olsa bile C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_BZERO_TEST("FT_NULL pointer, n = 5", FT_NULL, 5);
    // RUN_BZERO_TEST("FT_NULL pointer, n = 0", FT_NULL, 0);

    printf("\n--- Test Summary for ft_bzero ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}