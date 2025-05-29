#include <stdio.h>
#include <string.h>    // Orijinal strlcat, memcmp, strlen, memset için
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
static int _run_strlcat_test_case(char *ft_dest_buf, char *original_dest_buf, 
                                  const char *initial_dest_content, const char *src, 
                                  size_t dest_total_size, const char *test_name) {
    
    // Her iki hedef buffer'ı da başlangıçta 'A' ile dolduralım
    // Kopyalanmayan kısımların değiştirilmediğini test etmek için.
    // Max buffer size for tests should be consistent with main.
    memset(ft_dest_buf, 'A', 200); 
    memset(original_dest_buf, 'A', 200); 

    // Copy initial content into the buffers (ensuring it's null-terminated)
    size_t initial_dest_len = strlen(initial_dest_content);
    
    // strncpy kullanırken dikkat: dest_total_size'ı değil, initial_dest_len'i kopyalıyoruz
    // ve üzerine null terminasyonu manuel ekliyoruz.
    // Eğer initial_dest_len >= 200 ise buffer taşması olabilir, bu nedenle test buffer'ları yeterince büyük olmalı.
    memcpy(ft_dest_buf, initial_dest_content, initial_dest_len);
    ft_dest_buf[initial_dest_len] = '\0'; // Ensure null termination of initial content

    memcpy(original_dest_buf, initial_dest_content, initial_dest_len);
    original_dest_buf[initial_dest_len] = '\0'; // Ensure null termination of initial content

    // Call ft_strlcat and strlcat
    size_t ft_ret = ft_strlcat(ft_dest_buf, src, dest_total_size);
    size_t original_ret = strlcat(original_dest_buf, src, dest_total_size);

    // Compare results: check both content and return value
    // We compare up to 200 bytes of the buffer to ensure no unintended writes.
    int passed = (memcmp(ft_dest_buf, original_dest_buf, 200) == 0 && ft_ret == original_ret);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Initial Dest: \"%s\" (len: %zu)\n", initial_dest_content, initial_dest_len);
        printf("  Source:       \"%s\" (len: %zu)\n", src, strlen(src));
        printf("  Dest Size:    %zu\n", dest_total_size);
        printf("  ft_strlcat Dest:      "); print_memory(" ", ft_dest_buf, dest_total_size + 2); // Show relevant portion
        printf("  Original strlcat Dest: "); print_memory(" ", original_dest_buf, dest_total_size + 2);
        printf("  ft_strlcat Return:    %zu\n", ft_ret);
        printf("  Original strlcat Return: %zu\n", original_ret);
    }
    return passed;
}

// Kolay test çağırmak için makro
#define RUN_STRLCAT_TEST(desc, initial_dest_str, src_str, size_val) \
    total_tests++; \
    if (_run_strlcat_test_case(_ft_strlcat_test_buf, _original_strlcat_test_buf, initial_dest_str, src_str, size_val, desc)) { \
        passed_tests++; \
    }

int main(void)
{
    int total_tests = 0;
    int passed_tests = 0;

    // Test Buffer'ları: main içinde bir kez tanımlanıyor.
    char _ft_strlcat_test_buf[200];
    char _original_strlcat_test_buf[200];

    printf("--- Running ft_strlcat Tests ---\n\n");

    // 1. Temel Birleştirmeler (Yeterli Alan Var)
    RUN_STRLCAT_TEST("Full append: dest + src fits", "Hello", " World!", 20); // Result: "Hello World!"
    RUN_STRLCAT_TEST("Full append: shorter strings", "A", "B", 5);          // Result: "AB"
    RUN_STRLCAT_TEST("Full append: numbers", "123", "456", 10);              // Result: "123456"

    // 2. Tam Sığan Durumlar
    RUN_STRLCAT_TEST("Exact fit: dest + src + null = size", "Exact", "Fit", 9); // strlen("Exact")=5, strlen("Fit")=3. 5+3+1=9. Result: "ExactFit"
    RUN_STRLCAT_TEST("Exact fit: empty dest", "", "Test", 5); // strlen("")=0, strlen("Test")=4. 0+4+1=5. Result: "Test"

    // 3. Kısmi Birleştirmeler (Alan Yetersiz)
    RUN_STRLCAT_TEST("Partial append: dest_len + src_len + 1 > size", "Hello", " Too Long", 10); // 5 + 8 + 1 = 14. size=10. Result: "Hello Too" (9 chars + null)
    RUN_STRLCAT_TEST("Partial append: very short dest_size", "Long_String", "End", 5); // dest_len=11. size=5. Result: "Long_" (4 chars + null)
    RUN_STRLCAT_TEST("Partial append: only dest_len fits", "Hello", "World", 6); // 5 + 5 + 1 = 11. size=6. Result: "Hello" (5 chars + null)

    // 4. Kenar Durumlar
    RUN_STRLCAT_TEST("size = 0 (No copy, no null)", "Hello", "World", 0); // dest değişmez, ret = 5+5=10
    RUN_STRLCAT_TEST("size <= dest_len (No append)", "Hello", "World", 5); // dest değişmez, ret = 5+5=10
    RUN_STRLCAT_TEST("Empty source string", "Hello", "", 10); // dest değişmez, ret = 5+0=5
    RUN_STRLCAT_TEST("Empty dest string", "", "World", 10); // behaves like strlcpy, result "World"
    RUN_STRLCAT_TEST("Empty dest and source, size > 0", "", "", 10); // Result: ""
    RUN_STRLCAT_TEST("Empty dest and source, size = 0", "", "", 0); // Result: ""

    // 5. Kaynak Stringde Dahili Null Karakter
    RUN_STRLCAT_TEST("Source with internal null", "Prefix", "Mid\0Suffix", 15); // "Mid" kısmı eklenmeli. Result: "PrefixMid"
    RUN_STRLCAT_TEST("Source starts with null", "Hello", "\0World", 10); // Hiçbir şey eklenmez. Result: "Hello"

    // 6. NULL Pointer Testleri (UNSAFE - YORUM SATIRI KALMALI)
    // strlcat'e NULL dest veya NULL src geçmek C standartlarında tanımsız davranıştır.
    // Bu yüzden bu testleri çalıştırmak programın çökmesine neden olabilir.
    // RUN_STRLCAT_TEST("NULL dest, valid src, size > 0", NULL, "source", 10);
    // RUN_STRLCAT_TEST("Valid dest, NULL src, size > 0", "dest", NULL, 10);
    // RUN_STRLCAT_TEST("NULL dest, NULL src, size > 0", NULL, NULL, 10);

    printf("\n--- Test Summary for ft_strlcat ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n", passed_tests, total_tests, total_tests - passed_tests);
    }

    return (0);
}