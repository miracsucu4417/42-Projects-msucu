#include <stdio.h>
#include <string.h>    // strlen için
#include <stdlib.h>    // Orijinal atoi için

// Hangi include doğruysa onu kullan, setup'ına göre:
// #include "Libft/libft.h" // Eğer libft.h Libft klasöründeyse
#include "libft.h"     // Eğer libft.h main.c ile aynı dizindeyse

// Test yardımcı fonksiyonu: Tek bir test senaryosunu çalıştırır ve sonucu döndürür.
static int _run_atoi_test_case(const char *str, const char *test_name) {
    int ft_result = ft_atoi(str);
    int original_result = atoi(str); // Orijinal atoi

    // atoi'nin overflow durumunda UB olduğunu unutma.
    // Bu yüzden bu testlerde sadece normal ve kenar durumları test edeceğiz,
    // overflow durumları (INT_MAX + 1 vb.) için tam eşleşme garanti edilmez.
    // Ancak 42 projesinde genellikle "atoi'nin davrandığı gibi davran" denir,
    // yani overflow da dahil aynı değeri döndürmesi beklenir.
    // Kendi atoi'nizi yazarken long long kullanarak taşmayı kontrol etmek ve
    // INT_MAX/INT_MIN'den büyük/küçükse ilgili sınırı döndürmek daha sağlam bir yaklaşımdır.
    // Ancak orijinal atoi bu kontrolü yapmaz.
    // Biz burada sadece dönüş değerinin aynı olup olmadığını kontrol edeceğiz.
    int passed = (ft_result == original_result);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input String: \"%s\"\n", str);
        printf("  ft_atoi returned: %d\n", ft_result);
        printf("  Original atoi returned: %d\n", original_result);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_ATOI_TEST(desc, str_val) \
    total_tests++; \
    if (_run_atoi_test_case(str_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_atoi Tests ---\n\n");

    // 1. Temel Sayılar
    RUN_ATOI_TEST("Positive number", "123");
    RUN_ATOI_TEST("Negative number", "-456");
    RUN_ATOI_TEST("Zero", "0");
    RUN_ATOI_TEST("Large positive number", "2147483647"); // INT_MAX
    RUN_ATOI_TEST("Large negative number", "-2147483648"); // INT_MIN

    // 2. İşaret Testleri
    RUN_ATOI_TEST("Positive with plus sign", "+789");
    RUN_ATOI_TEST("Multiple plus signs (UB)", "++123"); // Orijinal atoi 0 döndürür
    RUN_ATOI_TEST("Multiple minus signs (UB)", "--456"); // Orijinal atoi 0 döndürür
    RUN_ATOI_TEST("Sign in middle (UB)", "12-34"); // Orijinal atoi 12 döndürür
    RUN_ATOI_TEST("Sign at end (UB)", "123-"); // Orijinal atoi 123 döndürür

    // 3. Boşluk Karakterleri (Whitespace)
    RUN_ATOI_TEST("Whitespace only", "   "); // Orijinal atoi 0 döndürür
    RUN_ATOI_TEST("Whitespace before number", "   123");
    RUN_ATOI_TEST("Whitespace after number", "123   "); // Sadece 123 döndürür
    RUN_ATOI_TEST("Whitespace around sign", "  - 123"); // Orijinal atoi 0 döndürür
    RUN_ATOI_TEST("Newline before number", "\n\t\v\f\r 123"); // Tüm boşlukları atlamalı
    RUN_ATOI_TEST("Whitespace in middle (stops reading)", "1 2 3"); // Orijinal atoi 1 döndürür

    // 4. Rakam Olmayan Karakterler
    RUN_ATOI_TEST("Alpha in middle (stops reading)", "123abc"); // Orijinal atoi 123 döndürür
    RUN_ATOI_TEST("Symbol in middle (stops reading)", "123!@#"); // Orijinal atoi 123 döndürür
    RUN_ATOI_TEST("Non-digit at start", "abc123"); // Orijinal atoi 0 döndürür
    RUN_ATOI_TEST("Empty string", ""); // Orijinal atoi 0 döndürür

    // 5. Overflow / Underflow Testleri (Davranış tanımsızdır, ancak 42 projelerinde genellikle
    // aynı değeri döndürmesi beklenir. Yani derleyicinin/sistemin atoi'sinin döndürdüğü değeri.)
    RUN_ATOI_TEST("Overflow INT_MAX + 1 (string)", "2147483648"); // Genellikle -2147483648 döndürür (taşma)
    RUN_ATOI_TEST("Underflow INT_MIN - 1 (string)", "-2147483649"); // Genellikle 2147483647 döndürür (taşma)
    RUN_ATOI_TEST("Very large number", "99999999999999999999"); // Genellikle bir taşma sonucu döndürür

    // 6. NULL Pointer Testi (UNSAFE - YORUM SATIRI KALMALI)
    // atoi'ye NULL str geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_ATOI_TEST("NULL string", NULL);

    printf("\n--- Test Summary for ft_atoi ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}