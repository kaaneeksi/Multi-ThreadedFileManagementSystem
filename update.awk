BEGIN {
    # Eğer "choice" 1 (add) ise, başlıkları yazdır
    if (choice == 1) {
        printf "%-15s %-10s %-10s\n", "Name", "Price", "Quantity";
    }
}

{
    # Geçersiz satırları atla
    if ($1 == "Name" || NF < 3) {
        next;
    }

    # "choice" 2 (update): Ürün güncelle
    if (choice == 2 && $1 == prod) {
        $2 = price;
        $3 = quantity;
    }

    # "choice" 3 (delete): Ürün sil
    if (choice == 3 && $1 == prod) {
        next; # Satırı atla
    }

    # Varsayılan olarak mevcut satırı yazdır
    printf "%-15s %-10d %-10d\n", $1, $2, $3;
}

END {
    # Eğer "choice" 1 (add) ise, yeni ürünü ekle
    if (choice == 1) {
        printf "%-15s %-10d %-10d\n", prod, price, quantity;
    }
}
