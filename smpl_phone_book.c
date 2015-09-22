/*
 * smpl_phone_book.c
 *
 * This is a program that provides interaction
 * as a simple phone book
 *
 */
#include <stdio.h>
#include <string.h> //for memset()
#include <stdlib.h> //for exit()

#define PHONE_BOOK_SIZE    100

enum
{
    LIST_ALL,
    VIEW_ENTRY,
    ADD,
    REMOVE,
    COUNT,
    SAVE,
    REMOVE_ALL,
    QUIT,

    NUM_CMND_OPTIONS
};

struct phn_dir_entry
{
    int id; //or should i do some sort of hash?
    char name[32];
    char phone_num[10];
};
typedef struct phn_dir_entry phn_dir_entry_t;

phn_dir_entry_t   my_phone_book[PHONE_BOOK_SIZE];
unsigned int      num_entries;

char * cmnd_string[] =
{
    "List All Entries",
    "View an Entry",
    "Add a new Entry",
    "Remove an Entry",
    "Count the number of Entries",
    "Save to a file",
    "Remove all Entries",
    "Quit"
};

void print_menu( void );
void handle_cmnd_list_all(void);

void main()
{
    int option;

    option = -1;

    printf("Welcome to the Simple Phone Book Directory\n");
    //move the line down
    //
    //it appears that after i make modifications to the file by moving some
    //tagged stuff down a line number or a million, the tag will follow it

    while( option != QUIT )
    {
        print_menu();
        scanf("%d", &option);

        if(option == QUIT)
        {
            printf("Goodbye\n");
            exit(0);
        }

        if( option == -1 || option >= NUM_CMND_OPTIONS )
        {
            printf("Invalid option\nGoodbye\n");
            exit(-1);
        }

        switch(option)
        {
            case LIST_ALL:
                handle_cmnd_list_all();
                break;
        }
    }
}

void init_all_vars(void)
{
    unsigned int i;

    num_entries = 0;
    memset(my_phone_book, 0, sizeof(phn_dir_entry_t)*PHONE_BOOK_SIZE);
    for(i = 0; i < PHONE_BOOK_SIZE; i++)
    {
        my_phone_book[i].id = -1;
    }
}

void print_menu( void )
{
    unsigned int i;

    printf("\nSelect an option:\n");
    for(i = 0; i < NUM_CMND_OPTIONS; i++)
    {
        printf("%d) %s\n", i, cmnd_string[i]);
    }
}

void handle_cmnd_list_all(void)
{
    unsigned int i;

    if( num_entries == 0)
    {
        printf("Your phone book is empty\n");
        return;
    }

    for(i = 0; i < PHONE_BOOK_SIZE; i++)
    {
        if(my_phone_book[i].id != -1)
        {
            printf("%d - %s\n\t(%s)\n",
                my_phone_book[i].id,
                my_phone_book[i].name,
                my_phone_book[i].phone_num);
        }
    }
}
