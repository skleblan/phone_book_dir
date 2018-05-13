/*
 * smpl_phone_book.c
 *
 * This is a program that provides interaction
 * as a simple phone book
 *
 */
#include <stdio.h>  //for printf(), scanf()
#include <string.h> //for memset(), strlen(), strncpy()
#include <stdlib.h> //for exit()

#include "ct_assert.h"
#include "util.h"

#define PHONE_BOOK_SIZE    100

enum
{
    LIST_ALL,
    VIEW_ENTRY,
    ADD,
    REMOVE,
    COUNT,
    SAVE,
    LOAD,
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
//int               next_id_val;
//unsigned int      next_open_idx;

char * cmnd_string[] =
{
    /*"Reprint this option list",*/
    "List All Entries",
    "View an Entry",
    "Add a new Entry",
    "Remove an Entry",
    "View Number of Entries",
    "Save to a file",
    "Load from a file",
    "Remove all Entries",
    "Quit"
};

//compile-time assert
//ct_assert( sizeof(cmnd_string)/sizeof(char) == NUM_CMND_OPTIONS );

void init_all_vars( void );
void print_menu( unsigned char b_full_menu );
void handle_cmnd_list_all( void );
void handle_cmnd_add( void );
void handle_cmnd_rem_all( void );
void handle_cmnd_count( void );
void handle_cmnd_view_entry( void );
int find_id_from_name(char* name);
int find_next_open_array_idx(void);
void print_entry(int id);
void flush_stdin_buffer();
void handle_save_cmnd(void);

void main()
{
    int option;
    char input_string[100];
    int input_len;

    init_all_vars();

    option = -1;

    printf("Welcome to the Simple Phone Book Directory\n");
    //move the line down
    //
    //it appears that after i make modifications to the file by moving some
    //tagged stuff down a line number or a million, the tag will follow it

    print_menu( TRUE ); //print full menu

    while( option != QUIT )
    {
        memset(input_string, 0, 100);

        fgets(input_string, 100, stdin);
        input_len = strlen(input_string);
        if(input_len == 0 || input_string[0] == '\n')
        {
            print_menu(TRUE);
            continue;
        }
        else
        {
            sscanf(input_string, "%d", &option);
        }

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

            case ADD:
                handle_cmnd_add();
                break;

            case REMOVE_ALL:
                handle_cmnd_rem_all();
                break;

            case COUNT:
                handle_cmnd_count();
                break;

            case VIEW_ENTRY:
                handle_cmnd_view_entry();
                break;

            case SAVE:
                handle_save_cmnd();
                break;

        }
        print_menu( FALSE );
        flush_stdin_buffer();
    }
}

void flush_stdin_buffer()
{
    char c;
    c = getchar();
    //discard all characters up to and including newline
    while(c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void init_all_vars(void)
{
    unsigned int i;

    num_entries = 0;
    //next_id_val = 0;
    //next_open_idx = 0;
    memset(my_phone_book, 0, sizeof(phn_dir_entry_t)*PHONE_BOOK_SIZE);
    for(i = 0; i < PHONE_BOOK_SIZE; i++)
    {
        my_phone_book[i].id = -1;
    }
}

int find_next_open_array_idx(void)
{
    int i;

    for(i = 0; i < PHONE_BOOK_SIZE; i++)
    {
        if(my_phone_book[i].id == -1)
        {
            return i;
        }
    }
    return -1;
}

void print_menu( unsigned char b_print_full )
{
    unsigned int i;

    if( b_print_full != 0)
    {
        for(i = 0; i < NUM_CMND_OPTIONS; i++)
        {
            printf("%d) %s\n", i, cmnd_string[i]);
        }
    }

    printf("\nSelect an option: ");
}

void handle_cmnd_count(void)
{
    printf("Phone book contains %d entries\n", num_entries);
}

void handle_cmnd_rem_all(void)
{
    char temp[20];

    printf("Are you sure you want to remove all entries?\n");
    scanf("%s", temp);

    if(temp[0] == 'y' || temp[0] == 'Y')
    {
        init_all_vars();
        printf("Phone book has been cleared\n");
    }
    else
    {
        printf("Removal cancalled\n");
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

void handle_cmnd_view_entry(void)
{
    char input_str[100];
    int id;

    memset(input_str, 0, sizeof(input_str));

    printf("Enter a name or an id number: ");
    scanf("%s", input_str);

    sscanf(input_str, "%d", &id);

    //check for a valid id. otherwise it's a string
    if(id >= 0 && id < PHONE_BOOK_SIZE && my_phone_book[id].id != -1)
    {
        print_entry(id);
    }
    else
    {
        //invalid id. treat it as a name and search for the entry
        id = find_id_from_name(input_str);
        if(id != -1)
        {
            print_entry(id);
        }
        else
        {
            printf("Could not find %s in the phone book.\n", input_str);
        }
    }
}

void print_entry(int id)
{
    printf("ID: %d\n", my_phone_book[id].id);
    printf("Name: %s\n", my_phone_book[id].name);
    printf("Phone Number: %s\n", my_phone_book[id].phone_num);
}

int find_id_from_name(char* name)
{
    unsigned int i;

    for(i = 0; i < PHONE_BOOK_SIZE; i++)
    {
        if(my_phone_book[i].id != -1)
        {
            int result;

            //make the name-under-test the same length
            //as the string provided
            char name_truncated[32];
            int new_size = 0;
            memset(name_truncated, 0, 32);

            new_size = strlen(name);
            strncpy(name_truncated, my_phone_book[i].name, new_size);

            result = strncasecmp(name_truncated, name, 32);
            //strncasecmp ignores case
            if(result == 0)
            {
                return i;
            }
        }
    }
    return -1;
}

void handle_cmnd_add(void)
{
    char temp[40];
    int new_id;
    int temp_str_len;

    new_id = -1;
    temp_str_len = 0;
    memset(temp, 0, 40);

    if( num_entries < PHONE_BOOK_SIZE )
    {
        new_id = find_next_open_array_idx();
    }

    if( new_id == -1 )
    {
        printf("Phone Book is full. Can't add a new entry.\n");
        return;
    }

    printf("User selected: Add Entry\n");

    printf("Enter Name: ");
    scanf("%s", temp);
    temp_str_len = strlen(temp);
    strncpy(my_phone_book[new_id].name, temp, MIN(temp_str_len, 32));
    //max size of name is 32, max size of temp is 40
    memset(temp, 0, 40);

    printf("Enter Number: ");
    scanf("%s", temp);
    temp_str_len = strlen(temp);
    strncpy(my_phone_book[new_id].phone_num, temp, MIN(temp_str_len, 10));
    //max size of phone_num is 10, max size of temp is 40

    my_phone_book[new_id].id = new_id;

    num_entries++;

    //next_id_val++;

    printf("Entry has been added. ID: %d", new_id);
}

void handle_save_cmnd(void)
{
    char data_file_name[] = "save.dat";

    int i;

    FILE* f_out;

    f_out = fopen(data_file_name, "w");

    for(i = 0; i < PHONE_BOOK_SIZE; i++)
    {
        if(my_phone_book[i].id == -1)
        {
            continue;
        }

        fprintf(f_out, "entry\n");
        fprintf(f_out, "id:%d\n", my_phone_book[i].id);
        fprintf(f_out, "name:%s\n", my_phone_book[i].name);
        fprintf(f_out, "phone:%s\n", my_phone_book[i].phone_num);
    }

    fclose(f_out);

    printf("Phone book has been saved to disk\n");
}

void handle_cmnd_load_entry()
{
    char data_file_name[] = "save.dat";

    FILE* f;

    f = fopen(data_file_name, "r");

}
