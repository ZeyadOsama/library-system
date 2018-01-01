#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "book.h"
#include "member.h"
#include "admin.h"
#include "menu.h"
#include "dataTypes.h"
#include "utilities.h"


void insertBook() {

    SetConsoleTitle("Library System > Book Menu > Inserting New Book");

    // no need for array
    // writing into files will be instantly
    bookDataType book;

    // for verifications
    bool valid;

    // iterator
    int i=1;

    do {
        system("cls");

        // series of terniry operators for ordinal indicators
        // i.e. 1(st), 2(nd), etc.
        printf("Please, Enter %d%s Book Details.\n\n", i++, (i==1)?"st":(i==2)?"nd":(i==3)?"rd":"th" );


        // title entry
        do {
            printf("\nTitle : ");
            strcap(gets(book.title));

            if( strcmp(book.title , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book.title , "") == 0 );



        // author entry
        do {
            printf("\nAuthor : ");
            strcap(gets(book.author));

            if( strcmp(book.author , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book.author , "") == 0 );



        // publisher entry
        do {
            printf("\nPublisher : ");
            strcap(gets(book.publisher));

            if( strcmp(book.publisher , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book.publisher , "") == 0 );



        // ISBN entry
        do {
            printf("\nISBN : ");
            gets(book.ISBN);

            valid = duplicateISBN(book.ISBN);

            if(!valid)
                errMsg("Error !\nThis ISBN was previously taken");

            if( strcmp(book.ISBN , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book.ISBN , "") == 0 || (!valid) );

        acpMsg("Valid ISBN");



        // publish date entry
        printf("\nDate of Publish.");
        do {
            // assure being initialized if user skipped
            book.publishDate.day   = 1;
            book.publishDate.month = 1;
            book.publishDate.year  = 1;

            printf("\nDay\t: ");
            scanf("%d",&book.publishDate.day);

            printf("Month\t: ");
            scanf("%d",&book.publishDate.month);

            printf("Year\t: ");
            scanf("%d",&book.publishDate.year);

            valid = isDate(book.publishDate.day, book.publishDate.month, book.publishDate.year);

            if(!valid)
                errMsg("Error !\nusage: not a valid date");

        } while (!valid);



        // number of copies entry
        do {
            printf("\nNo of Copies : ");
            scanf("%d", &book.copiesNum);

            // avoiding logical errors causes by contiguous scanf and gets
            getc(stdin);

            // check copies number validity
            if( book.copiesNum < 0 )
                errMsg("Error !\nusage: copies number >= 0");

        } while ( book.copiesNum < 0 );



        // category entry
        do {
            printf("\nCategory: ");
            strcap(gets(book.category));

            if( strcmp(book.category , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book.category , "") == 0 );


        // initializing logic values to each structure without user's interfere
        book.borrowed=0;
        book.avalCopiesNum = book.copiesNum;

        // write i(th) book data into file
        FILE * books = fopen("books.bin", "a");

        // failure check
        if(books==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        fwrite(&book, sizeof(bookDataType), 1, books);

        fclose(books);

    } while( yesNoRequest("insert another book")==true );

    fflush(stdin);
    bookMenu();
}
