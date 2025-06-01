#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset için
#include <malloc.h>
#include "Libft/libft.h"

int main(void) {
	char str[] = "0123456789";

	// memmove(str+3, str,5);
	memcpy(str, str+3,5);
	printf("%s\n", str);
    return 0;
}
