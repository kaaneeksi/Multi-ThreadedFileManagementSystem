BEGIN {
    if (choice == 1) {
        # Eğer işlem "add" ise başlıkları yazdır
        printf "%-15s %-10s %-10s\n", "Name", "Price", "Quantity";
    }
}

{
    # Geçersiz satırları atla
    if ($1 == "Name" || NF < 3) {
        next;
    }

    # "update" işlemi: Ürünü güncelle
    if (choice == 2 && $1 == prod) {
        $2 = price;
        $3 = quantity;
    }

    # "delete" işlemi: Ürünü sil
    if (choice == 3 && $1 == prod) {
        next; # Satırı atla
    }

    # Varsayılan olarak satırı yazdır
    printf "%-15s %-10d %-10d\n", $1, $2, $3;
}

END {
    if (choice == 1) {
        # Eğer işlem "add" ise, yeni ürünü ekle
        printf "%-15s %-10d %-10d\n", prod, price, quantity;
    }
}
