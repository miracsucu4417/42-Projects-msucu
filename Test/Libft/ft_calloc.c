#include <stdio.h>
#include <string.h>    // memset, memcmp için
#include <stdlib.h>    // Orijinal calloc, free için
#include <limits.h>    // INT_MAX/MIN gibi bazı sınırlar için
#include <stdint.h>    // SIZE_MAX için

// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
// Sadece FAILED olduğunda detayları yazdırır.
static int _run_calloc_test_case(t_size_t nmemb, t_size_t size, const char *test_name) {
    void *ft_ptr = FT_NULL;
    void *original_ptr = FT_NULL;
    int passed = 1; // Varsayılan olarak geçer

    // ft_calloc çağrısı
    ft_ptr = ft_calloc(nmemb, size);

    // Orijinal calloc çağrısı
    original_ptr = calloc(nmemb, size);

    // Kural: nmemb * size = 0 olduğunda benzersiz, free edilebilir pointer dönmesi
    if (nmemb == 0 || size == 0) {
        if (ft_ptr == FT_NULL) { // ft_calloc FT_NULL döndürdüyse, FAILED (kurala göre non-FT_NULL freeable ptr beklenir)
            passed = 0;
        }
    } else { // nmemb * size > 0 ise
        // Çarpma taşması veya bellek yetersizliği durumu.
        // ft_calloc'un bu durumda FT_NULL dönmesi beklenir.
        // Orijinal calloc da genellikle bu durumda FT_NULL döner.
        // total_size_check, olası taşmayı kontrol etmek için
        t_size_t total_size_check;
        // Eğer nmemb veya size 0 değilse ve çarpım SIZE_MAX'i aşıyorsa
        // (SIZE_MAX / nmemb < size ile kontrol edilir), o zaman overflow vardır.
        // Bu durumda FT_NULL beklenir.
        int is_overflow_expected = (nmemb > 0 && size > SIZE_MAX / nmemb);

        if (ft_ptr == FT_NULL && original_ptr == FT_NULL) {
            // Her ikisi de FT_NULL döndürdüyse, başarılıdır (özellikle overflow durumlarında)
            passed = 1; 
        } else if (ft_ptr != FT_NULL && original_ptr != FT_NULL) {
            // Her ikisi de non-FT_NULL döndürdüyse, içeriklerini karşılaştır.
            // Bu sadece is_overflow_expected false iken başarılı olmalı.
            // total_size'ı hesaplarken taşma olmaması için dikkatli ol.
            total_size_check = nmemb * size; // Bu hesaplama taşma olmayacaksa yapılır.
            char *expected_zeros = (char *)malloc(total_size_check);
            if (expected_zeros == FT_NULL) { // Test için bile bellek tahsis edilemezse
                passed = 0; // Test altyapısı hatası
            } else {
                memset(expected_zeros, 0, total_size_check);
                if (memcmp(ft_ptr, expected_zeros, total_size_check) != 0) {
                    passed = 0; // İçerik sıfır değilse hata
                }
                free(expected_zeros);
            }
            if (is_overflow_expected && passed) { // Hem overflow bekleniyor hem de non-FT_NULL döndü, bu bir hata
                passed = 0;
            }
        } else { // Biri FT_NULL döndü, diğeri dönmedi (tutarsızlık)
            passed = 0;
        }
    }

    // Sadece FAILED olduğunda detayları yazdır
    if (!passed) {
        printf("❌ FAILED: %s (nmemb: %zu, size: %zu)\n", test_name, nmemb, size);
        printf("  ft_calloc returned: %p\n", ft_ptr);
        printf("  Original calloc returned: %p\n", original_ptr);
    }
    
    // Tahsis edilen belleği serbest bırak
    if (ft_ptr != FT_NULL) free(ft_ptr);
    if (original_ptr != FT_NULL) free(original_ptr);

    return passed;
}


// Kolay test çağırmak için makro
#define RUN_CALLOC_TEST(desc, nmemb_val, size_val) \
    total_tests++; \
    if (_run_calloc_test_case(nmemb_val, size_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_calloc Tests ---\n\n");

    // 1. Temel Tahsis Testleri
    RUN_CALLOC_TEST("Allocate 5 ints", 5, sizeof(int));
    RUN_CALLOC_TEST("Allocate 10 chars", 10, sizeof(char));
    RUN_CALLOC_TEST("Allocate 3 long longs", 3, sizeof(long long));
    RUN_CALLOC_TEST("Allocate large char array", 1000, sizeof(char));

    // 2. Kenar Durumlar (0 nmemb veya 0 size) - PROJE KURALI BURADA ÖNEMLİ!
    RUN_CALLOC_TEST("nmemb = 0, size = 1", 0, 1);
    RUN_CALLOC_TEST("nmemb = 1, size = 0", 1, 0);
    RUN_CALLOC_TEST("nmemb = 0, size = 0", 0, 0);

    // 3. Çarpma Taşması (Overflow) Durumları
    // nmemb * size sonucu SIZE_MAX'i aşarsa FT_NULL dönmeli
    RUN_CALLOC_TEST("Multiplication overflow: nmemb * size > SIZE_MAX (Expected FT_NULL)", SIZE_MAX / 2 + 1, 2);
    RUN_CALLOC_TEST("Multiplication overflow: nmemb = SIZE_MAX, size = 2 (Expected FT_NULL)", SIZE_MAX, 2);
    RUN_CALLOC_TEST("Multiplication within limit: nmemb = 1, size = SIZE_MAX (Expected non-FT_NULL)", 1, SIZE_MAX);
    RUN_CALLOC_TEST("Multiplication within limit: nmemb = SIZE_MAX / 2, size = 1 (Expected non-FT_NULL)", SIZE_MAX / 2, 1);

    // 4. Çok Büyük Tahsis (Potansiyel Başarısız Tahsis)
    RUN_CALLOC_TEST("Very large allocation (potentially fails)", (t_size_t)1024 * 1024 * 1024, 1);

    printf("\n--- Test Summary for ft_calloc ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}