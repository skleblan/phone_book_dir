/*
 * smpl_phone_book.c
 *
 * This is a program that provides interaction
 * as a simple phone book
 *
 */
#include <stdio.h>

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

void main()
{
    int option;
    int i;

    printf("Welcome to the Simple Phone Book Directory\n");
    printf("\nSelect an option:\n");
    for(i = 0; i < NUM_CMND_OPTIONS; i++)
    {
        printf("%d) %s\n", i, cmnd_string[i]);
    }
}
