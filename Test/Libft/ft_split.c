// test_ft_split.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Libft header dosyanızın yoluna göre değiştirin:
#include "libft.h"

// ————————————————————————————————————————————————————————————————
// Yardımcı Fonksiyonlar
// ————————————————————————————————————————————————————————————————

/**
 * print_split_result:
 *    ft_split sonucu elde edilen 'char **arr' dizisini
 *    ekrana ["elem0", "elem1", ...] biçiminde yazar.
 *    Eğer arr == NULL ise “Result: NULL” çıktısı verir.
 */
static void print_split_result(char **arr) {
    if (!arr) {
        printf("    Result: NULL\n");
        return;
    }
    printf("    Result: [");
    for (int i = 0; arr[i] != NULL; i++) {
        printf("\"%s\"", arr[i]);
        if (arr[i + 1] != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * arrays_equal:
 *    İki “NULL sonlandırmalı char* dizisi”nin eleman-eleman eş olup olmadığını kontrol eder.
 *    - Eğer her ikisi de NULL pointer ise eş sayılır.
 *    - Eğer birisi NULL, diğeri NULL değil ise eş değil.
 *    - Her ikisi non-NULL pointer ise, her index'te strcmp ile eşitliği kontrol eder
 *      ve sonunda her ikisinin de NULL pointer ile bittiğinden emin olur.
 */
static int arrays_equal(char **actual, const char **expected) {
    if (!actual && !expected) {
        return 1;
    }
    if (!actual || !expected) {
        return 0;
    }
    int i = 0;
    while (actual[i] != NULL && expected[i] != NULL) {
        if (strcmp(actual[i], expected[i]) != 0) {
            return 0;
        }
        i++;
    }
    return (actual[i] == NULL && expected[i] == NULL);
}

/**
 * _run_split_test_case:
 *    Bir test senaryosu çalıştırır: ft_split(s, sep) sonucunu alır ve expected dizisiyle karşılaştırır.
 *    Eğer uyuşmazsa, testin adı, giriş ve separator, gerçek sonuç ve beklenen çıktı konsola basılır.
 *    Sonrasında ft_split'in döndürdüğü dizi ve içindeki tüm stringler free edilir.
 *
 * @param s:        Bölünecek kaynak C stringi (NULL olabilir).
 * @param sep:      Ayırıcı karakter (sep). Eğer s == NULL ise sep önemini yitirir.
 * @param expected: Beklenen sonuç, "NULL sonlandırmalı const char* dizisi".
 * @param test_name: Testi tanımlayan açıklayıcı string.
 *
 * @return 1 eğer eşitlik varsa, 0 eğer test başarısızsa.
 */
static int _run_split_test_case(const char *s, char sep, const char **expected, const char *test_name) {
    char **result = ft_split(s, sep);
    int passed = arrays_equal(result, expected);

    if (!passed) {
        printf("❌ FAILED: %s\n", test_name);
        printf("    Input: %s%s%s | Separator: '%c'\n",
               (s ? "\"" : ""), (s ? s : "NULL"), (s ? "\"" : ""), sep);
        print_split_result(result);

        printf("    Expected: [");
        if (expected) {
            for (int i = 0; expected[i] != NULL; i++) {
                printf("\"%s\"", expected[i]);
                if (expected[i + 1] != NULL) {
                    printf(", ");
                }
            }
        }
        printf("]\n\n");
    }

    // ft_split sonucu diziyi ve içindeki stringleri free et
    if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            free(result[i]);
        }
        free(result);
    }
    return passed;
}

/**
 * RUN_SPLIT_TEST:
 *    Basit bir makro ile her test için toplam testi ++, eğer geçtiyse passed_tests++ yapar.
 */
#define RUN_SPLIT_TEST(desc, str, sep, expected_arr) \
    do {                                            \
        total_tests++;                              \
        if (_run_split_test_case(str, sep, expected_arr, desc)) \
            passed_tests++;                         \
    } while (0)

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;

    printf("--- Running ft_split Tests ---\n\n");

    //
    // 1) Temel Bölme (Basic Split)
    //
    {
        const char *e1[] = {"Hello", "World", NULL};
        RUN_SPLIT_TEST("Basic split on space", "Hello World", ' ', e1);
    }
    {
        const char *e2[] = {"abc", "def", "ghi", NULL};
        RUN_SPLIT_TEST("Comma-separated", "abc,def,ghi", ',', e2);
    }
    {
        const char *e3[] = {"onetwo", NULL};
        RUN_SPLIT_TEST("No separator present", "onetwo", ' ', e3);
    }
    {
        const char *e4[] = {"a", "b", "c", NULL};
        RUN_SPLIT_TEST("Single-character separators", "a,b,c", ',', e4);
    }

    //
    // 2) Başta ve Sonda Ayraç (Leading/Trailing Separator)
    //
    {
        const char *e5[] = {"start", "end", NULL};
        RUN_SPLIT_TEST("Leading/trailing sep commas", ",start,end,", ',', e5);
    }
    {
        const char *e6[] = {"x", "y", "z", NULL};
        RUN_SPLIT_TEST("Multiple leading/trailing dashes", "---x--y--z---", '-', e6);
    }

    //
    // 3) Ardı ardına Gelen Ayraçlar (Consecutive Separators)
    //
    {
        const char *e7[] = {"One", "Two", "Four", NULL};
        RUN_SPLIT_TEST("Skip empty between dashes", "One-Two--Four", '-', e7);
    }
    {
        const char *e8[] = {"a", "b", "c", NULL};
        RUN_SPLIT_TEST("Skip empty between commas", ",a,,b,,c,", ',', e8);
    }

    //
    // 4) Boş Girdi ve Yalnızca Ayraç Karakterleri
    //
    {
        const char *e9[] = {NULL};
        RUN_SPLIT_TEST("Empty string input", "", ',', e9);
    }
    {
        const char *e10[] = {NULL};
        RUN_SPLIT_TEST("Only semicolons", ";;;;", ';', e10);
    }
    {
        const char *e11[] = {NULL};
        RUN_SPLIT_TEST("Only dashes", "xxx", 'x', e11);
    }

    //
    // 5) NULL İşaretçisi (s == NULL)
    //
    {
        const char *e12[] = {NULL};
        RUN_SPLIT_TEST("NULL input string", NULL, ',', e12);
    }

    //
    // 6) Tek Kelime (Ayraç yok) veya Boşluk Ayraç Olarak Kullanımı
    //
    {
        const char *e13[] = {"singleton", NULL};
        RUN_SPLIT_TEST("Single word, no separator", "singleton", ';', e13);
    }
    {
        const char *e14[] = {" ", NULL};
        RUN_SPLIT_TEST("Single-space-only string with comma sep", " ", ',', e14);
    }
    {
        const char *e15[] = {"no", "split", NULL};
        RUN_SPLIT_TEST("Split on space", "no split", ' ', e15);
    }

    //
    // 7) Ayraç Karakterinin Kendisi (Ayraç, boş string üretmez)
    //
    {
        const char *e16[] = {NULL};
        RUN_SPLIT_TEST("Separator equals string length '|'", "|", '|', e16);
    }
    {
        const char *e17[] = {"hello", NULL};
        RUN_SPLIT_TEST("Separator at end only comma", "hello,", ',', e17);
    }
    {
        const char *e18[] = {"hello", NULL};
        RUN_SPLIT_TEST("Separator at start only comma", ",hello", ',', e18);
    }

    //
    // 8) Farklı Karakter Kombinasyonları
    //
    {
        const char *e19[] = {"foo", "bar", "baz", NULL};
        RUN_SPLIT_TEST("Mixed chars: '#'", "#foo#bar#baz#", '#', e19);
    }
    {
        const char *e20[] = {"AB", "CD", "EF", NULL};
        RUN_SPLIT_TEST("Mixed chars: '*' on 'AB*CD*EF'", "AB*CD*EF", '*', e20);
    }
    {
        const char *e21[] = {"start", "mid", "end", NULL};
        RUN_SPLIT_TEST("Mixed whitespace sep (tab)", "start\tmid\tend", '\t', e21);
    }

    //
    // 9) Uzun Dizeler / Bellek Sınırı Durumları
    //
    {
        // 1000 karakter uzunluk, ortada bir tek virgül
        char *longstr = malloc(1001);
        if (longstr) {
            for (int i = 0; i < 500; i++) {
                longstr[i] = 'a';
            }
            longstr[500] = ',';
            for (int i = 501; i < 1000; i++) {
                longstr[i] = 'b';
            }
            longstr[1000] = '\0';

            // Beklenen: 500 adet 'a' ve 499 adet 'b'
            char *frag1 = strndup(longstr, 500);
            char *frag2 = strndup(longstr + 501, 499);
            const char *e22[] = { frag1, frag2, NULL };

            RUN_SPLIT_TEST("Very long string single comma", longstr, ',', e22);

            free(frag1);
            free(frag2);
            free(longstr);
        }
    }

    //
    // 10) Boşluk (space) Ayraç Olarak Kullanımı
    //
    {
        const char *e23[] = {"a", "b", "c", NULL};
        RUN_SPLIT_TEST("Split on space", "a b c", ' ', e23);
    }
    {
        const char *e24[] = {"leading", "trailing", NULL};
        RUN_SPLIT_TEST("Leading/trailing spaces", " leading trailing ", ' ', e24);
    }

    //
    // 11) Özel Karakterler ve Karma Durumlar
    //
    {
        const char *e25[] = {"!", "@", "#", "$", NULL};
        RUN_SPLIT_TEST("Special chars as sep '!'", "!@!#!$", '!', e25);
    }
    {
        const char *e26[] = {"mix", "of", "123", "and", "abc", NULL};
        RUN_SPLIT_TEST("Alphanumeric mix on '-'", "mix-of_123-and!abc", '-', e26);
    }

    //
    // 12) Ayraç Görünmeyen (ASCII 0) Durumu
    //
    {
        const char *e27[] = {NULL};
        RUN_SPLIT_TEST("Embedded null terminator", "hello\0world", 'o', e27);
    }

    //
    // 13) Ayrıştırılan Her Kelimenin Doğru Kopyalandığını Kontrol Et
    //
    {
        const char *e28[] = {"abc", "YZdef", NULL};
        RUN_SPLIT_TEST("Separator in middle of word 'X'", "abcXYZdef", 'X', e28);
    }

    //
    // 14) Karmaşık Ardışık Ayraç ve Boşluk Dizisi
    //
    {
        const char *e29[] = {"a", "b", "c", "d", NULL};
        RUN_SPLIT_TEST("Complex: ,a,, ,b , ,c,d,,", ",a,, ,b , ,c,d,,", ',', e29);
    }

    //
    // 15) Tek Ayraç Ama Dizinin Tamamı Ayraç
    //
    {
        const char *e30[] = {NULL};
        RUN_SPLIT_TEST("Single-character string equal to sep '|'", "|", '|', e30);
    }

    //
    // 16) Sadece Bir Karakter Uzunluğunda Tek Kelime
    //
    {
        const char *e31[] = {"x", NULL};
        RUN_SPLIT_TEST("Single char, not sep", "x", ',', e31);
    }

    //
    // 17) Çoklu Ayraç Kombinasyonları ve Boşluk
    //
    {
        const char *e32[] = {"Hello", NULL};
        RUN_SPLIT_TEST("Hello then many spaces", "Hello      ", ' ', e32);
    }
    {
        const char *e33[] = {"This", "is", "a", "test", NULL};
        RUN_SPLIT_TEST("Tabs and spaces mix", "This\t is  a\t test", ' ', e33);
    }

    //
    // 18) Ayraç Dosya Yolu Benzeri (Slash)
    //
    {
        const char *e34[] = {"usr", "local", "bin", NULL};
        RUN_SPLIT_TEST("Path-like split", "/usr/local/bin/", '/', e34);
    }

    //
    // 19) Boş dizi durumları (sadece ayraç veya NULL)
    //
    {
        const char *e35[] = {NULL};
        RUN_SPLIT_TEST("Multiple consecutive same dashes", "-----", '-', e35);
    }
    {
        const char *e36[] = {NULL};
        RUN_SPLIT_TEST("Mixed separators but all same char 'h'", "hhhhhh", 'h', e36);
    }

    //
    // 20) Özet
    //
    printf("\n--- Test Summary for ft_split ---\n");
    if (total_tests == passed_tests) {
        printf("✅ All %d tests PASSED!\n", total_tests);
    } else {
        printf("⚠️  %d/%d tests PASSED. %d tests FAILED.\n",
               passed_tests, total_tests, total_tests - passed_tests);
    }

    return 0;
}
