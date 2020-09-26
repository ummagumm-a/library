#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st_book {
    char *title;
    char *author;
    int year;
    float book_rate;
    struct st_book *next;
    struct st_book *previous;
};
typedef struct st_book book;

struct st_customer {
    char name[50];
    int age;
    float customer_rate;
    struct st_customer *next;
    struct st_customer *previous;
};

book *g_first_book;
book *g_last_book;
struct st_customer g_first_customer;
struct st_customer g_last_customer;

void menu();
int read_input();
void open_section();
void error_message();
void enter_to_return();
void clear_terminal();
char *get_string(int size);
void arrow();
void clear_from_garbage();
void display_book(book displayed_book);

void show_books();
void add_book();
void update_book();
void remove_book();
void show_customers();
void add_customer();
void update_customer();
void remove_customer();
void quit();

int main() {
    printf("Welcome to the Library!\n");
    menu();
    open_section();

    return 0;
}

void menu() {
    printf("Just put a number from 1 to 9, where:\n");
    printf("1. Show Books\n");
    printf("2. Add Book\n");
    printf("3. Update Book\n");
    printf("4. Remove Book\n");
    printf("5. Show Customers\n");
    printf("6. Add Customer\n");
    printf("7. Update Customer\n");
    printf("8. Remove Customer\n");
    printf("9. Quit\n");
}

void arrow() {
    printf("-> ");
}

void open_section() {
    for (;;) {
        arrow();
        int input;
        scanf("%d", &input);
        clear_from_garbage();

        if (input == 9) break;
//        clear_terminal();

        switch (input) {
            case 1:
                show_books();
                break;
            case 2:
                add_book();
                break;
            case 3:
                update_book();
                break;
            case 4:
                remove_book();
                break;
            case 5:
                show_customers();
                break;
            case 6:
                add_customer();
                break;
            case 7:
                update_customer();
                break;
            case 8:
                remove_customer();
                break;
            default:
                error_message();
                continue;
        }
        enter_to_return();
    }
}

void error_message() {
//    clear_terminal();
//    menu();
    arrow();
    printf("Please, enter a valid number\n");
}

void enter_to_return() {
    printf("Press enter to return\n");

    while (getchar() != '\n') {

    }
//    clear_terminal();
    menu();
}

void clear_from_garbage() {
    char c;
    while ((c = (char) getc(stdin)) != EOF && c != '\n');
}

void show_books() {
    book book_from_the_list = *g_first_book;
    do {
        display_book(book_from_the_list);
        if (book_from_the_list.next != NULL) {
            book_from_the_list = book_from_the_list.next;
        }

    } while (book_from_the_list.next != NULL);
}

void display_book(book displayed_book) {
    printf("--------------------------------\n");
    printf("Title: %s\n", displayed_book.title);
    printf("Author: %s\n", displayed_book.author);
    printf("Year of publishing: %d\n", displayed_book.year);
    printf("Rate: %.2f\n", displayed_book.book_rate);
    printf("Next: %p\n", displayed_book.next);
    printf("Previous: %p\n", displayed_book.previous);
    printf("--------------------------------\n");
}

book *create_book() {
    book *temp = malloc(sizeof(book));
    void *p = &temp;

    display_book(*g_last_book);
    g_last_book->next = p;
    temp->previous = g_last_book;

    return temp;
}

void add_book() {
    book *new_book = create_book();

    printf("Enter a name of the book\n");
    arrow();
    new_book->title = get_string(60);
//    clear_terminal();

    printf("Enter a name of the author\n");
    arrow();
    new_book->author = get_string(50);
//    clear_terminal();

    printf("Enter a year of publishing\n");
    arrow();
    scanf("%d", &new_book->year);
    clear_from_garbage();
//    clear_terminal();

    printf("Enter a book rate\n");
    arrow();
    scanf("%f", &new_book->book_rate);
    clear_from_garbage();
//    clear_terminal();
//
    g_last_book = new_book;
    if (g_first_book->next == NULL) {
        g_first_book = new_book;
    }

    printf("Book has been created successfully!\n");
}

char *get_string(int size) {
    char *string = malloc(size * sizeof(char));
    fgets(string, size, stdin);
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL) *pos = '\0';

    return string;
}

void update_book() {

}

void remove_book() {

}

void show_customers() {

}

//struct st_customer *create_customer() {
//    struct st_customer *temp = malloc(sizeof(struct st_customer));
//    temp->next = NULL;
//
//
//}

void add_customer() {
//    book *new_book = create_book();
//
//    if (g_first_book.next == NULL) {
//        g_first_book = *new_book;
//    }
//
//    printf("Enter a name of the book: ");
//    scanf("%s", &new_book->title[60]);
//    clear_terminal();
//
//    printf("Enter a name of the author: ");
//    scanf("%s", &new_book->author[50]);
//    clear_terminal();
//
//    printf("Enter a year of publishing: ");
//    scanf("%d", &new_book->year);
//    clear_terminal();
//
//    printf("Enter a book rate: ");
//    scanf("%f", &new_book->book_rate);
//    clear_terminal();
//
//    new_book->next = NULL;
//    new_book->previous = &g_last_book;
//    g_last_book.next = new_book;
//    g_last_book = *new_book;
//
//    printf("Book has been created successfully!");
//    enter_to_return();
}

void update_customer() {

}

void remove_customer() {

}

void clear_terminal() {
    system("@cls||clear");
}