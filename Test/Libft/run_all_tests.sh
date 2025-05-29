#!/bin/bash

# Include ve Libft yolu
INCLUDE_DIR="../../Libft"
LIB_DIR="../../Libft"
LIB_NAME="ft"

# Dizindeki tüm ft_*.c dosyalarını bul
for test_file in ft_*.c; do
    # Çalıştırılabilir isim (örneğin ft_putnbr_fd.c -> ft_putnbr_fd)
    # exe_name="${test_file%.c}"
    exe_name="prg"

    echo "-----------------------------------------"
    echo "Compiling and running test: $test_file"
    echo "-----------------------------------------"

    gcc "$test_file" -o prg -I "$INCLUDE_DIR" -L "$LIB_DIR" -l"$LIB_NAME"
    if [ $? -ne 0 ]; then
        echo "❌ Compilation failed for $test_file"
        echo
        continue
    fi

    ./"$exe_name"
	rm -f "$exe_name"
    echo
done
