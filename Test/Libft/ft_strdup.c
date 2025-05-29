#include <stdio.h>
#include <string.h>    // Orijinal strdup, strcmp, strlen için
#include <stdlib.h>    // malloc, free için

// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
static int _run_strdup_test_case(const char *s, const char *test_name) {
    char *ft_result = NULL;
    char *original_result = NULL;
    int passed = 1; // Varsayılan olarak geçer

    ft_result = ft_strdup(s);
    original_result = strdup(s);

    // 1. NULL dönüşlerini kontrol et
    if (ft_result == NULL && original_result == NULL) {
        // İkisi de NULL döndürdüyse (bellek yetersizliği veya bazı sistemlerde 0 boyutu için)
        // Bu durum başarılı kabul edilir.
        passed = 1;
    } else if (ft_result != NULL && original_result != NULL) {
        // İkisi de başarılı tahsis ettiyse, içerik ve uzunlukları karşılaştır.
        // strdup null terminator'ı da kopyalar, bu yüzden strlen ve strcmp yeterli.
        if (strcmp(ft_result, original_result) != 0 || strlen(ft_result) != strlen(original_result)) {
            passed = 0; // İçerik veya uzunluk uyuşmazlığı
        }
    } else {
        // Birisi NULL döndürdü, diğeri döndürmedi (tutarsızlık)
        passed = 0;
    }

    // Sadece FAILED olduğunda detayları yazdır
    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input: \"%s\"\n", s ? s : "NULL (Input was NULL)");
        printf("  ft_strdup returned:      %p -> \"%s\"\n", (void *)ft_result, ft_result ? ft_result : "(null)");
        printf("  Original strdup returned: %p -> \"%s\"\n", (void *)original_result, original_result ? original_result : "(null)");
    }

    // ÖNEMLİ: Tahsis edilen belleği serbest bırak!
    if (ft_result) free(ft_result);
    if (original_result) free(original_result);

    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRDUP_TEST(desc, str_val) \
    total_tests++; \
    if (_run_strdup_test_case(str_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_strdup Tests ---\n\n");

    // 1. Temel Kopyalamalar
    RUN_STRDUP_TEST("Basic string", "Hello World!");
    RUN_STRDUP_TEST("Single character string", "A");
    RUN_STRDUP_TEST("String with numbers and symbols", "123!@#$abc");
    RUN_STRDUP_TEST("String with spaces", "   This has spaces   ");

    // 2. Kenar Durumlar
    RUN_STRDUP_TEST("Empty string", ""); // ft_strdup(0) ve malloc(1) olmalı
    RUN_STRDUP_TEST("String with internal null", "Part1\0Part2"); // Sadece ilk null'a kadar kopyalamalı
    RUN_STRDUP_TEST("Very long string (1000 chars)", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

    // 3. NULL Pointer Testi (UNSAFE - YORUM SATIRI KALMALI)
    // strdup'a NULL pointer geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRDUP_TEST("NULL input", NULL);


    printf("\n--- Test Summary for ft_strdup ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}