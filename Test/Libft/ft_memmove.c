#include <stdio.h>
#include <string.h>    // Orijinal memmove, memcmp, strlen, memset için
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
// `dest_ft`, `dest_original` bu test için oluşturulan mutable buffer'lardır.
static int _run_memmove_test_case(char *dest_ft, char *dest_original,
                                  const char *initial_buffer_str, size_t initial_len, size_t n_bytes,
                                  char *dest_offset_ptr_from_initial, char *src_offset_ptr_from_initial,
                                  const char *test_name) {
    
    // Her iki test buffer'ını da başlangıçtaki değere kopyala
    // ve kopyalanmayan kısımları ayırt etmek için 'X' ile doldur
    
    // İlk olarak dest_ft ve dest_original'ı sıfırla/doldur (güvenlik için)
    // sizeof(dest_ft) burada pointer boyutu vereceği için, ana buffer'ın gerçek boyutunu bilmeliyiz.
    // main'deki buffer'lar 200 boyutunda olduğu için 200 kullanalım.
    memset(dest_ft, 'X', 200); // 200, main'deki buffer boyutuna göre
    memset(dest_original, 'X', 200);

    // Başlangıç değerini kopyala
    memcpy(dest_ft, initial_buffer_str, initial_len);
    dest_ft[initial_len] = '\0'; // <-- DÜZELTME: Bu satırda `ft_test_buf` yerine `dest_ft` kullanılmalıydı
    memcpy(dest_original, initial_buffer_str, initial_len);
    dest_original[initial_len] = '\0'; // <-- DÜZELTME: Bu satırda `original_test_buf` yerine `dest_original` kullanılmalıydı

    // Gerçek dest ve src pointer'larını ana buffer'lar üzerinde ayarla
    char *ft_d = dest_ft + (dest_offset_ptr_from_initial - initial_buffer_str);
    char *ft_s = dest_ft + (src_offset_ptr_from_initial - initial_buffer_str);

    char *orig_d = dest_original + (dest_offset_ptr_from_initial - initial_buffer_str);
    char *orig_s = dest_original + (src_offset_ptr_from_initial - initial_buffer_str);

    // ft_memmove'yi çağır
    void *ft_ret = ft_memmove(ft_d, ft_s, n_bytes);

    // Orijinal memmove'yi çağır
    void *original_ret = memmove(orig_d, orig_s, n_bytes);

    // Karşılaştırma: Tüm buffer'ı (initial_len + 10) karşılaştır
    // 200 baytlık buffer'ın tamamını karşılaştırmak daha güvenli.
    int passed = (memcmp(dest_ft, dest_original, 200) == 0);
    // Dönüş değeri kontrolü (memmove dest pointer'ını döndürmeli)
    if (ft_ret != ft_d || original_ret != orig_d) {
        passed = 0; // Eğer dönüş değeri yanlışsa başarısız say
        printf("  Return value mismatch! ft_ret: %p, Expected: %p\n", ft_ret, ft_d);
    }

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Initial Buffer:       "); print_memory(" ", initial_buffer_str, initial_len);
        printf("  Src Offset: %ld, Dest Offset: %ld, N: %zu\n",
               (long)(src_offset_ptr_from_initial - initial_buffer_str), (long)(dest_offset_ptr_from_initial - initial_buffer_str), n_bytes);
        printf("  ft_memmove Result:    "); print_memory(" ", dest_ft, initial_len + 5);
        printf("  Original memmove Result: "); print_memory(" ", dest_original, initial_len + 5);
    }
    return passed;
}

// Kolay test çağırmak için makro
// Makroya test buffer'ları ve offset'ler doğrudan main'deki tanımlardan geçiriliyor.
#define RUN_MEMMOVE_TEST(desc, buffer_arr, dest_off, src_off, num_bytes) \
    total_tests++; \
    if (_run_memmove_test_case(_ft_memmove_test_buf, _original_memmove_test_buf, buffer_arr, strlen(buffer_arr), num_bytes, buffer_arr + dest_off, buffer_arr + src_off, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    // Test Buffer'ları: main içinde bir kez tanımlanıyor ve sabit boyutlu array'ler.
    // Bu array'leri RUN_MEMMOVE_TEST makrosuna ve oradan _run_memmove_test_case'e geçiriyoruz.
    // En büyük olası test string'lerinden daha büyük olmalılar (200 bayt olarak ayarlandı).
    char _ft_memmove_test_buf[200];
    char _original_memmove_test_buf[200];


    printf("--- Running ft_memmove Tests ---\n\n");

    // Test buffer'ları string literal olarak verilecek ve _run_memmove_test_case
    // içinde _ft_memmove_test_buf ve _original_memmove_test_buf'a kopyalanacak.
    
    // _temp_buf yerine bu sabit string literal'lar kullanılacak.
    char base_str_1[] = "ABCDEFGHIJ"; // Genel testler için (mutable olmalı)
    char base_str_2[] = "0123456789"; // Genel testler için (mutable olmalı)
    // char base_str_short[] = "abc"; // Şu an kullanılmıyor ama örnek olarak kalsın

    // 1. Temel Testler (Çakışma Yok)
    RUN_MEMMOVE_TEST("No overlap: dest after src", base_str_1, 5, 0, 5); // From ABCDE to FGHIJ, Result: FGHIJFGHIJ
    RUN_MEMMOVE_TEST("No overlap: dest before src", base_str_1, 0, 5, 5); // From FGHIJ to ABCDE, Result: FGHIJFGHIJ
    RUN_MEMMOVE_TEST("No overlap: full string", "Test String", 0, 0, strlen("Test String") + 1); // Self-copy
    RUN_MEMMOVE_TEST("No overlap: Different data", "xxxxxxxxxx", 0, 0, 10); // Should copy "xxxxxxxxxx" onto itself, N=10

    // 2. Kenar Durumlar
    RUN_MEMMOVE_TEST("N = 0 (No copy)", "Hello World!", 0, 0, 0); // Should return dest, no change
    RUN_MEMMOVE_TEST("Empty source string, n=0", "", 0, 0, 0); // No change
    
    // 3. KRİTİK ÇAKIŞMA Durumları (dest < src: sondan başa kopyalama gerektirir)
    RUN_MEMMOVE_TEST("Overlap: dest < src (copy forward)", base_str_1, 2, 0, 5);
    RUN_MEMMOVE_TEST("Overlap: dest < src (larger N)", base_str_2, 1, 0, 8);

    // 4. KRİTİK ÇAKIŞMA Durumları (dest > src: baştan sona kopyalama gerektirir)
    RUN_MEMMOVE_TEST("Overlap: dest > src (copy backward)", base_str_1, 0, 2, 5);
    RUN_MEMMOVE_TEST("Overlap: dest > src (larger N)", base_str_2, 0, 1, 8);

    // 5. NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // memmove'a NULL pointer geçmek, n=0 olsa bile C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_MEMMOVE_TEST("NULL dest, n=5", NULL, 0, 0, 5); // Cannot use NULL as initial_buffer_str
    // RUN_MEMMOVE_TEST("NULL src, n=5", "test", 0, 0, 5); // Cannot use NULL as offset from "test"
    // RUN_MEMMOVE_TEST("NULL dest, n=0", NULL, 0, 0, 0);
    // RUN_MEMMOVE_TEST("NULL src, n=0", "test", 0, 0, 0);

    printf("\n--- Test Summary for ft_memmove ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}