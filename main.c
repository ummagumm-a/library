/* Here is a program for library admins.
 * It's capable of adding, updating, removing and showing books and customers */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lists are implemented as linked lists for both books and customers.
 * Their structs contain pointers on the next and previous items of the list. */

/* A struct for storing characteristics of a book. */
struct st_book {
    char *title;
    char *author;
    int year;
    float book_rate;
    struct st_book *next;
    struct st_book *previous;
};
typedef struct st_book book;

/* A struct for storing characteristics of a customer. */
struct st_customer {
    char *name;
    int age;
    float rate;
    struct st_customer *next;
    struct st_customer *previous;
};

/* Pointers on the first and the last items of the list of books */
book *g_first_book;
book *g_last_book;

/* Pointers on the first and the last items of the list of customers */
struct st_customer *g_first_customer;
struct st_customer *g_last_customer;

void menu();
void open_section();
void enter_to_return();
char *get_string(int size);
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

/* List of available functionalities */
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

/* Read the number of the functionality and go to corresponding function */
void open_section() {
    for (;;) {
        printf("-> ");
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
                printf("-> ");
                printf("Please, enter a valid number\n");
                continue;
        }
        enter_to_return();
    }
}

/* Function that waits for user to press Enter-key, after that returns to menu */
void enter_to_return() {
    printf("Press enter to return\n");

    while (getchar() != '\n') {

    }

    menu();
}

/* This function clears irrelevant information in input, for example \n sign
 * that interfere with other functions */
void clear_from_garbage() {
    char c;
    while ((c = (char) getc(stdin)) != EOF && c != '\n');
}

/* This function returns a string that users inputs from the terminal. */
char *get_string(int size) {
    char *string = malloc(size * sizeof(char));
    fgets(string, size, stdin);
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL) *pos = '\0';

    return string;
}

/* This function shows all books from the list in the console */
void show_books() {
    // This if-statement checks whether we have at least one book in the list
    if (g_first_book->next == NULL) {
        printf("There is nothing to show\n");
        return;
    }
    book book_from_the_list = *g_first_book->next;

    // Iterate books in the list
    for (;;) {
        display_book(book_from_the_list);
        if (book_from_the_list.next != NULL) {
            book_from_the_list = *book_from_the_list.next;
        } else {
            break;
        }
    }
}

/* Template for displaying books */
void display_book(book displayed_book) {
    printf("--------------------------------\n");
    printf("Title: %s\n", displayed_book.title);
    printf("Author: %s\n", displayed_book.author);
    printf("Year of publishing: %d\n", displayed_book.year);
    printf("Rate: %.2f\n", displayed_book.book_rate);
    printf("--------------------------------\n");
}

/* This function allocates memory for new book */
book *create_book() {
    // Allocate memory for new book
    book *temp = malloc(sizeof(book));

    // Make reference between neighbor elements
    g_last_book->next = temp;
    temp->previous = g_last_book;
    // Created book is the last in the list now
    g_last_book = temp;

    return temp;
}

/* This function asks to provide information about a book and writes it to the book's struct */
void info_about_book(book *book_to_fill_in) {
    printf("Enter a name of the book\n");
    printf("-> ");
    book_to_fill_in->title = get_string(60);

    printf("Enter a name of the author\n");
    printf("-> ");
    book_to_fill_in->author = get_string(50);

    printf("Enter a year of publishing\n");
    printf("-> ");
    scanf("%d", &book_to_fill_in->year);
    // As scanf leaves '\n' unread, we need to clear get rid of it with this function
    clear_from_garbage();

    printf("Enter a book rate\n");
    printf("-> ");
    scanf("%f", &book_to_fill_in->book_rate);
    // As scanf leaves '\n' unread, we need to clear get rid of it with this function
    clear_from_garbage();
}

/* This function adds new book to the list */
void add_book() {
    // Get memory for a book
    book *new_book = create_book();

    // Get info for the book
    info_about_book(new_book);

    // If we don't have books in the list yet, we need to put this book in the starting position
    if (g_first_book->next == NULL) {
        g_first_book = new_book;
    }

    printf("Book has been added successfully!\n");
}

/* This function updates all info about a book */
void update_book() {
    // Enter name of a book that user wants to update
    printf("Enter the name of the book that you want to update\n");
    printf("-> ");
    char *desired_title = get_string(60);

    // Get address of book with this name
    book *found_book = find_book(desired_title);

    // This if-statement checks whether book was found
    if (found_book != NULL) {
        // Provide new information about the book
        printf("Provide new information about the book\n");
        info_about_book(found_book);

        printf("Book has been updated successfully!\n");
    } else {
        printf("There is no such book in my library\n");
    }
}

// This function removes a book from the list and clears memory
void remove_book() {
    // Enter name of a book that user wants to update
    printf("Enter the name of the book that you want to remove\n");
    printf("-> ");
    char *desired_title = get_string(60);

    // Get address of book with this name
    book *found_book = find_book(desired_title);

    // This if-statement checks whether book was found
    if (found_book != NULL) {
        // Here we change references such that our book can't be found from the outside
        // Previous and next are references on previous and next books
        found_book->previous->next = found_book->next;

        // If not the last book in the list
        if (found_book->next != NULL) {
            found_book->next->previous = found_book->previous;
        }
        // If it is last book in the list, we need to make previous book as a new last
        if (found_book == g_last_book) {
            g_last_book = found_book->previous;
        }

        free(found_book);
    } else {
        printf("There is no such book in my library\n");
    }

}

// This function return pointer on the book with entered name
book *find_book(char *desired_title) {
    // We start from the first book in the list
    book *book_from_the_list = g_first_book->next;

    // Iterate through each book in the list till the book is found
    while (book_from_the_list != NULL) {
        if (strcmp(book_from_the_list->title, desired_title) == 0) {
            return book_from_the_list;
        } else {
            book_from_the_list = book_from_the_list->next;
        }
    }

    // If nothing was found, return NULL
    return NULL;
}

/* This function shows all customers from the list in the console */
void show_customers() {
    // This if-statement checks whether we have at least one customer in the list
    if (g_first_customer->next == NULL) {
        printf("There is nothing to show\n");
        return;
    }
    struct st_customer customer_from_the_list = *g_first_customer->next;

    // Iterate customers in the list
    for (;;) {
        display_customer(customer_from_the_list);
        if (customer_from_the_list.next != NULL) {
            customer_from_the_list = *customer_from_the_list.next;
        } else {
            break;
        }
    }
}

/* Template for displaying customers */
void display_customer(struct st_customer displayed_customer) {
    printf("--------------------------------\n");
    printf("Name: %s\n", displayed_customer.name);
    printf("Age: %d\n", displayed_customer.age);
    printf("Rate: %.2f\n", displayed_customer.rate);

    printf("--------------------------------\n");
}

/* This function allocates memory for new customers */
struct st_customer *create_customer() {
    // Allocate memory for new customers
    struct st_customer *temp = malloc(sizeof(struct st_customer));

    // Make reference between neighbor elements
    g_last_customer->next = temp;
    temp->previous = g_last_customer;
    // Created customer is the last in the list now
    g_last_customer = temp;

    return temp;
}

/* This function asks to provide information about a customer and writes it to the customer's struct */
void info_about_customer(struct st_customer *customer_to_fill_in) {
    printf("Enter a name of the customer\n");
    printf("-> ");
    customer_to_fill_in->name = get_string(50);

    printf("Enter an age of the customer\n");
    printf("-> ");
    scanf("%d", &customer_to_fill_in->age);
    // As scanf leaves '\n' unread, we need to clear get rid of it with this function
    clear_from_garbage();

    printf("Enter a rate of the customer\n");
    printf("-> ");
    scanf("%f", &customer_to_fill_in->rate);
    // As scanf leaves '\n' unread, we need to clear get rid of it with this function
    clear_from_garbage();
}

/* This function adds new customer to the list */
void add_customer() {
    // Get memory for a customer
    struct st_customer *new_customer = create_customer();

    // Get info for the customer
    info_about_customer(new_customer);

    // If we don't have customers in the list yet, we need to put this customer in the starting position
    if (g_first_customer->next == NULL) {
        g_first_customer = new_customer;
    }

    printf("Customer has been added successfully!\n");
}

/* This function updates all info about a customer */
void update_customer() {
    // Enter name of a customer that user wants to update
    printf("Enter the name of the customer that you want to update\n");
    printf("-> ");
    char *desired_name = get_string(50);

    // Get address of customer with this name
    struct st_customer *found_customer = find_customer(desired_name);

    // This if-statement checks whether customer was found
    if (found_customer != NULL) {
        // Provide new information about the customer
        printf("Provide new information about the customer\n");
        info_about_customer(found_customer);

        printf("Customer has been updated successfully!\n");
    } else {
        printf("There is no such customer in my library\n");
    }
}

// This function removes a customer from the list and clears memory
void remove_customer() {
    // Enter name of a customer that user wants to update
    printf("Enter the name of the customer that you want to remove\n");
    printf("-> ");
    char *desired_name = get_string(50);
    // Get address of customer with this name
    struct st_customer *found_customer = find_customer(desired_name);

    // This if-statement checks whether customer was found
    if (found_customer != NULL) {
        // Here we change references such that our customer can't be found from the outside
        // Previous and next are references on previous and next customers
        found_customer->previous->next = found_customer->next;

    // If not the last customer in the list
        if (found_customer->next != NULL) {
            found_customer->next->previous = found_customer->previous;
        }
        // If it is last customer in the list, we need to make previous customer as a new last
        if (found_customer == g_last_customer) {
            g_last_customer = found_customer->previous;
        }

        free(found_customer);
    } else {
        printf("There is no such customer in my database\n");
    }
}

// This function return pointer on the customer with entered name
struct st_customer *find_customer(char *desired_name) {
    // We start from the first customer in the list
    struct st_customer *customer_from_the_list = g_first_customer->next;

    // Iterate through each customer in the list till the customer is found
    while (customer_from_the_list != NULL) {
        if (strcmp(customer_from_the_list->name, desired_name) == 0) {
            return customer_from_the_list;
        } else {
            customer_from_the_list = customer_from_the_list->next;
        }
    }

    // If nothing was found, return NULL
    return NULL;
}
