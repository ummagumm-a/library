


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
    char *name;
    int age;
    float rate;
    struct st_customer *next;
    struct st_customer *previous;
};

book *g_first_book;
book *g_last_book;
struct st_customer *g_first_customer;
struct st_customer *g_last_customer;

void menu();
void open_section();
void enter_to_return();
char *get_string(int size);
void arrow();
void clear_from_garbage();
void display_book(book displayed_book);
void display_customer(struct st_customer displayed_customer);
void info_about_book(book *book_to_fill_in);
void info_about_customer(struct st_customer *customer_to_fill_in);
book *create_book();
struct st_customer *create_customer();
book *find_book();
struct st_customer *find_customer(char *desired_name);

void show_books();
void add_book();
void update_book();
void remove_book();
void show_customers();
void add_customer();
void update_customer();
void remove_customer();

int main() {
    g_first_book = malloc(sizeof(book));
    g_last_book = g_first_book;
    g_first_customer = malloc(sizeof(struct st_customer));
    g_last_customer = g_first_customer;
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
        auto int input;
        scanf("%d", &input);
        clear_from_garbage();

        if (input == 9) break;

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
                arrow();
                printf("Please, enter a valid number\n");
                continue;
        }
        enter_to_return();
    }
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

char *get_string(int size) {
    char *string = malloc(size * sizeof(char));
    fgets(string, size, stdin);
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL) *pos = '\0';

    return string;
}

void show_books() {
    if (g_first_book->next == NULL) {
        printf("There is nothing to show\n");
        return;
    }
    book book_from_the_list = *g_first_book->next;

    for (;;) {
        display_book(book_from_the_list);
        if (book_from_the_list.next != NULL) {
            book_from_the_list = *book_from_the_list.next;
        } else {
            break;
        }
    }
}

void display_book(book displayed_book) {
    printf("--------------------------------\n");
    printf("Title: %s\n", displayed_book.title);
    printf("Author: %s\n", displayed_book.author);
    printf("Year of publishing: %d\n", displayed_book.year);
    printf("Rate: %.2f\n", displayed_book.book_rate);
//    printf("Next: %p\n", displayed_book.next);
//    printf("Previous: %p\n", displayed_book.previous);

    printf("--------------------------------\n");
}

book *create_book() {
    book *temp = malloc(sizeof(book));

    g_last_book->next = temp;
    temp->previous = g_last_book;
    g_last_book = temp;

    return temp;
}

void info_about_book(book *book_to_fill_in) {
    printf("Enter a name of the book\n");
    arrow();
    book_to_fill_in->title = get_string(60);
//    clear_terminal();

    printf("Enter a name of the author\n");
    arrow();
    book_to_fill_in->author = get_string(50);
//    clear_terminal();

    printf("Enter a year of publishing\n");
    arrow();
    scanf("%d", &book_to_fill_in->year);
    clear_from_garbage();
//    clear_terminal();

    printf("Enter a book rate\n");
    arrow();
    scanf("%f", &book_to_fill_in->book_rate);
    clear_from_garbage();
//    clear_terminal();
}

void add_book() {
    book *new_book = create_book();

    info_about_book(new_book);

    g_last_book = new_book;
    if (g_first_book->next == NULL) {
        g_first_book = new_book;
    }

    printf("Book has been added successfully!\n");
}

void update_book() {
    printf("Enter the name of the book that you want to update\n");
    arrow();
    char *desired_title = get_string(60);
    printf("Provide new information about the book\n");
    book *found_book = find_book(desired_title);

    info_about_book(found_book);

    printf("Book has been updated successfully!\n");
}

void remove_book() {
    printf("Enter the name of the book that you want to remove\n");
    arrow();
    char *desired_title = get_string(60);
    book *found_book = find_book(desired_title);

    if (found_book != NULL) {
        found_book->previous->next = found_book->next;

        if (found_book->next != NULL) {
            found_book->next->previous = found_book->previous;
            found_book->next = NULL;
        }
        if (found_book == g_last_book) {
            g_last_book = found_book->previous;
        }
        found_book->previous = NULL;
        free(found_book);
    } else {
        printf("There is no such book in my library\n");
    }

}

book *find_book(char *desired_title) {
    book *book_from_the_list = g_first_book->next;

    while (book_from_the_list != NULL) {
        if (*book_from_the_list->title == *desired_title) {
            return book_from_the_list;
        } else {
            book_from_the_list = book_from_the_list->next;
        }
    }

    return NULL;
}

void show_customers() {
    if (g_first_customer->next == NULL) {
        printf("There is nothing to show\n");
        return;
    }
    struct st_customer customer_from_the_list = *g_first_customer->next;

    for (;;) {
        display_customer(customer_from_the_list);
        if (customer_from_the_list.next != NULL) {
            customer_from_the_list = *customer_from_the_list.next;
        } else {
            break;
        }
    }
}

void display_customer(struct st_customer displayed_customer) {
    printf("--------------------------------\n");
    printf("Title: %s\n", displayed_customer.name);
    printf("Age: %d\n", displayed_customer.age);
    printf("Rate: %f\n", displayed_customer.rate);

    printf("--------------------------------\n");
}

struct st_customer *create_customer() {
    struct st_customer *temp = malloc(sizeof(struct st_customer));

    g_last_customer->next = temp;
    temp->previous = g_last_customer;
    g_last_customer = temp;

    return temp;
}

void info_about_customer(struct st_customer *customer_to_fill_in) {
    printf("Enter a name of the customer\n");
    arrow();
    customer_to_fill_in->name = get_string(50);

    printf("Enter an age of the customer\n");
    arrow();
    scanf("%d", &customer_to_fill_in->age);
    clear_from_garbage();

    printf("Enter a rate of the customer\n");
    arrow();
    scanf("%f", &customer_to_fill_in->rate);
    clear_from_garbage();
}

void add_customer() {
    struct st_customer *new_customer = create_customer();

    info_about_customer(new_customer);

    g_last_customer = new_customer;
    if (g_first_customer->next == NULL) {
        g_first_customer = new_customer;
    }

    printf("Customer has been added successfully!\n");
}

void update_customer() {
    printf("Enter the name of the customer that you want to update\n");
    arrow();
    char *desired_name = get_string(50);
    struct st_customer *found_customer = find_customer(desired_name);

    printf("Provide new information about the customer\n");
    info_about_customer(found_customer);

    printf("Customer has been updated successfully!\n");
}

void remove_customer() {
    printf("Enter the name of the customer that you want to remove\n");
    arrow();
    char *desired_name = get_string(50);
    struct st_customer *found_customer = find_customer(desired_name);

    if (found_customer != NULL) {
        found_customer->previous->next = found_customer->next;

        if (found_customer->next != NULL) {
            found_customer->next->previous = found_customer->previous;
            found_customer->next = NULL;
        }
        if (found_customer == g_last_customer) {
            g_last_customer = found_customer->previous;
        }
        found_customer->previous = NULL;
        free(found_customer);
    } else {
        printf("There is no such customer in my database\n");
    }
}

struct st_customer *find_customer(char *desired_name) {
    struct st_customer *customer_from_the_list = g_first_customer->next;

    while (customer_from_the_list != NULL) {
        if (*customer_from_the_list->name == *desired_name) {
            return customer_from_the_list;
        } else {
            customer_from_the_list = customer_from_the_list->next;
        }
    }

    return NULL;
}