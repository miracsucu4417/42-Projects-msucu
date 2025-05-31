#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset için

void *ft_calloc(size_t count, size_t size); // ft_calloc fonksiyonun varsa burada prototipi olmalı

void print_result(const char *label, void *ptr, size_t total_size) {
    if (ptr == NULL) {
        printf("%s: NULL (allocation failed or size is 0)\n", label);
        return;
    }

    // İlk birkaç baytı yazdır
    printf("%s: not NULL, first bytes:", label);
    size_t limit = total_size < 8 ? total_size : 8;
    for (size_t i = 0; i < limit; ++i)
        printf(" %02x", ((unsigned char *)ptr)[i]);
    printf("\n");
}

int main(void) {
    void *std_ptr1 = calloc(0, 10);
    void *ft_ptr1  = ft_calloc(0, 10);

    void *std_ptr2 = calloc(10, 0);
    void *ft_ptr2  = ft_calloc(10, 0);

    printf("=== Testing calloc(0, 10) vs ft_calloc(0, 10) ===\n");
    print_result("calloc", std_ptr1, 0);
    print_result("ft_calloc", ft_ptr1, 0);

    printf("\n=== Testing calloc(10, 0) vs ft_calloc(10, 0) ===\n");
    print_result("calloc", std_ptr2, 0);
    print_result("ft_calloc", ft_ptr2, 0);

    // Serbest bırak
    free(std_ptr1);
    free(ft_ptr1);
    free(std_ptr2);
    free(ft_ptr2);

    return 0;
}
