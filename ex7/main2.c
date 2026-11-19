#include <stdio.h>
#include <stdlib.h>

#define BOOK_COUNT 6
#define TITLE_LEN 100

typedef struct Books {
    int id;
    int price;
    char title[TITLE_LEN];
} book_t;

void total_price(const book_t books[], int count) {
    long long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += books[i].price;
    }
    printf("Total price: %lld\n", sum);
}

void list_books(const book_t books[], int count) {
    printf("%-4s %-8s %s\n", "Id", "Price", "Title");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-8d %s\n", books[i].id, books[i].price, books[i].title);
    }
}

int main(void) {
    book_t books[BOOK_COUNT] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300,  "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550,  "Killers of the Flower Moon"},
        {5, 870,  "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    list_books(books, BOOK_COUNT);
    total_price(books, BOOK_COUNT);

    FILE *fp = fopen("Book.bin", "wb");
    if (!fp) {
        perror("無法開啟 Book.bin");
        return 1;
    }

    size_t written = fwrite(books, sizeof(book_t), BOOK_COUNT, fp);
    fclose(fp);

    if (written != BOOK_COUNT) {
        fprintf(stderr, "寫入 Book.bin 不完整\n");
        return 1;
    }

    return 0;
}
