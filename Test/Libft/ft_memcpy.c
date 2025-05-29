#include <stdio.h>
#include <string.h>    // Orijinal memcpy, memcmp, strlen için
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
// Bu fonksiyon, her test için geçici buffer'ları hazırlar.
static int _run_memcpy_test_case(const char *initial_src_val, size_t initial_src_len, size_t n_bytes, const char *test_name) {
    // Statik olarak büyük bir buffer tanımlayalım, her testte kopyalayacağız
    // Minimum 200 veya daha büyük bir boyut seçilebilir.
    char ft_dest_buf[200];
    char original_dest_buf[200];
    
    // Her iki hedef buffer'ı da başlangıçta temizleyelim veya dolduralım (isteğe bağlı)
    // Örnek: 'X' ile dolduralım ki kopyalanmayan kısımları görelim.
    memset(ft_dest_buf, 'X', sizeof(ft_dest_buf));
    memset(original_dest_buf, 'X', sizeof(original_dest_buf));

    // ft_memcpy'yi çağır
    // Kopyalama kaynağı initial_src_val
    // Kopyalama hedefi ft_dest_buf
    // Kopyalanacak bayt sayısı n_bytes
    ft_memcpy(ft_dest_buf, initial_src_val, n_bytes);

    // Orijinal memcpy'yi çağır
    // Kopyalama kaynağı initial_src_val
    // Kopyalama hedefi original_dest_buf
    // Kopyalanacak bayt sayısı n_bytes
    memcpy(original_dest_buf, initial_src_val, n_bytes);

    // Karşılaştırma: Kopyalanan n_bytes kadar ve sonrası da (eğer kopyalanmayan kısım varsa) aynı mı?
    // En güvenlisi, kopyalama sonrası tüm buffer'ı karşılaştırmak.
    int passed = (memcmp(ft_dest_buf, original_dest_buf, sizeof(ft_dest_buf)) == 0);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Initial Source: \"%s\" (len: %zu)\n", initial_src_val, initial_src_len);
        printf("  Bytes to copy (N): %zu\n", n_bytes);
        printf("  ft_memcpy Dest:     ");
        print_memory(" ", ft_dest_buf, initial_src_len + 5); // Biraz daha fazla gösterim
        printf("  Original memcpy Dest: ");
        print_memory(" ", original_dest_buf, initial_src_len + 5);
    }
    return passed;
}

// Kolay test çağırmak için makro
// Makroya geçici bufferlar veya boyutlar yerine sadece kaynak string literal'ı ve N'i veriyoruz.
#define RUN_MEMCPY_TEST(desc, src_str, num_bytes) \
    total_tests++; \
    if (_run_memcpy_test_case(src_str, strlen(src_str), num_bytes, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_memcpy Tests ---\n\n");

    // 1. Temel Kopyalamalar
    RUN_MEMCPY_TEST("Basic string copy (full)", "Hello World!", strlen("Hello World!") + 1); // +1 null terminator için
    RUN_MEMCPY_TEST("Partial string copy", "Long string", 5); // "Long "
    RUN_MEMCPY_TEST("Empty string as source", "", 1); // Sadece null terminator kopyala
    RUN_MEMCPY_TEST("String with internal null", "A\0B\0C", 5); // Kopyalanacak bayt sayısı null'u içeriyor

    // 2. Kenar Durumlar
    RUN_MEMCPY_TEST("N = 0 (No copy)", "Any string", 0); // Hedef değişmemeli
    RUN_MEMCPY_TEST("Destination has existing data", "New Data", strlen("New Data") + 1); // Hedefe "New Data" yazılmalı

    // 3. Farklı Karakter Değerleri
    char raw_bytes_src[] = {0x01, 0xFF, 0x7F, 0x80, 0x00, 0xAA, 0x55, 0x20, 0x7E, 0x01};
    RUN_MEMCPY_TEST("Copying raw bytes (including 0x00, 0xFF etc.)", raw_bytes_src, sizeof(raw_bytes_src));

    // 4. Büyük Kopyalama
    char long_src[100];
    for (int i = 0; i < 99; i++) long_src[i] = 'a' + (i % 26);
    long_src[99] = '\0';
    RUN_MEMCPY_TEST("Long string copy", long_src, strlen(long_src) + 1);
    
    // 5. Array Kopyalama (int dizisi)
    int int_src[] = {1, 2, 3, 4, 5};
    // NOT: Bu test string_len yerine sizeof(int_src) kullanmalı
    // _run_memcpy_test_case, strlen kullandığı için bu tür testler için uygun değil.
    // Başka bir yardımcı fonksiyon yazmak veya strlen'i çağırmamak gerekir.
    // Şimdilik string literal'larına odaklanalım, onlar en yaygın kullanım.
    
    // 6. NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // memcpy'ye NULL pointer geçmek, n=0 olsa bile C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_MEMCPY_TEST("NULL dest, n=5", NULL, 5);
    // RUN_MEMCPY_TEST("NULL src, n=5", "test", 5);
    // RUN_MEMCPY_TEST("NULL dest, n=0", NULL, 0);
    // RUN_MEMCPY_TEST("NULL src, n=0", "test", 0);

    printf("\n--- Test Summary for ft_memcpy ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}