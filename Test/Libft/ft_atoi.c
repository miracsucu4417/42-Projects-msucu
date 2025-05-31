#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"  // ft_atoi'nin prototipi burada olmalı

// Test sonucu karşılaştırma fonksiyonu
static int test_atoi_case(const char *str, int expected, const char *test_name)
{
    int result = ft_atoi(str);
    if (result != expected)
    {
        printf("❌ FAILED: %s\n", test_name);
        printf("  Input: \"%s\"\n", str ? str : "NULL");
        printf("  Expected: %d\n", expected);
        printf("  Got: %d\n\n", result);
        return 0;
    }
    return 1;
}

int main(void)
{
    int total = 0;
    int passed = 0;

    printf("--- Running ft_atoi Tests ---\n\n");

    total++; if (test_atoi_case("42", 42, "Simple positive number")) passed++;
    total++; if (test_atoi_case("-42", -42, "Simple negative number")) passed++;
    total++; if (test_atoi_case("   123", 123, "Leading spaces")) passed++;
    total++; if (test_atoi_case(" \t\n\r\v\f 456", 456, "Various whitespace chars")) passed++;
    total++; if (test_atoi_case("+789", 789, "Explicit plus sign")) passed++;
    total++; if (test_atoi_case("0", 0, "Zero")) passed++;
    total++; if (test_atoi_case("-0", 0, "Negative zero")) passed++;
    total++; if (test_atoi_case("2147483647", INT_MAX, "INT_MAX")) passed++;
    total++; if (test_atoi_case("-2147483648", INT_MIN, "INT_MIN")) passed++;
    total++; if (test_atoi_case("2147483648", INT_MAX + 1, "Overflow positive")) passed++;  // Note: behavior undefined in standard atoi
    total++; if (test_atoi_case("-2147483649", INT_MIN - 1, "Overflow negative")) passed++;  // Ditto
    total++; if (test_atoi_case("123abc456", 123, "Stop at first non-digit")) passed++;
    total++; if (test_atoi_case("abc123", 0, "No leading number")) passed++;
    total++; if (test_atoi_case("", 0, "Empty string")) passed++;
    total++; if (test_atoi_case(NULL, 0, "NULL string")) passed++;

    printf("\n--- Test Summary ---\n");
    if (total == passed)
        printf("✅ All %d tests passed!\n", total);
    else
        printf("⚠️ %d/%d tests passed, %d failed.\n", passed, total, total - passed);

    return 0;
}
