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


void insertMember() {

    SetConsoleTitle("Library System > Member Menu > Inserting New Member");

    // no need for array
    // writing into files will be instantly
    memberDataType member;

    // for verifications
    bool valid;

    // iterator
    int i=1;

    do {
        system("cls");

        // series of terniry operators for ordinal indicators
        // i.e. 1(st), 2(nd), etc.
        printf("Please, Enter %d%s Member's Details.\n\n", i++, (i==1)?"st":(i==2)?"nd":(i==3)?"rd":"th" );


        // first name entry
        do {
            printf("\nFirst Name : ");
            strcap(gets(member.name.first));

            if( strcmp(member.name.first , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member.name.first , "") == 0 );


        // last name entry
        do {
            printf("\nLast Name : ");
            strcap(gets(member.name.last));

            if( strcmp(member.name.last , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member.name.last , "") == 0 );



        // city entry
        do {
            printf("\nCity : ");
            strcap(gets(member.address.city));

            if( strcmp(member.address.city , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member.address.city , "") == 0 );



        // building entry
        do {
            printf("\nBulding : ");
            scanf("%d",&member.address.building);

            if( member.address.building<0 )
                errMsg("Error !\nusage: only positive integers are allowed");

        } while ( member.address.building<0 );



        // street entry
        do {
            printf("\nStreet : ");
            scanf("%d",&member.address.street);

            // avoiding logical errors causes by contiguous scanf and gets
            getc(stdin);

            if( member.address.street<0 )
                errMsg("Error !\nusage: only positive integers are allowed");

        } while ( member.address.street<0 );



        // ID entry
        do {
            printf("\nID : ");
            gets(member.ID);

            valid = duplicateID(member.ID);

            if(!valid)
                errMsg("Error !\nThis ID was previously taken");

            if( strcmp(member.ID , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member.ID , "") == 0 || !valid );

        acpMsg("Valid ID");



        // age entry
        do{
            printf("\nAge : ");
            scanf("%d", &member.age);

            // avoiding logical errors causes by contiguous scanf and gets
            getc(stdin);

            // check age validity
            if( member.age<=0 )
                errMsg("Error !\nusage: age must be positive number");

        } while ( member.age<=0 );


        // phone number entry
        do{
            printf("\nPhone Number (11 digits) : ");
            gets(member.phoneNum);

            // check phone number validity
            if( strlen(member.phoneNum)!=11 )
                errMsg("Error !\nusage: phone numbers must consist of 11 digit");

            else
                acpMsg("Valid phone number");

        } while ( strlen(member.phoneNum)!=11 );


        // check email validity
        do{
            printf("\nE-Mail : ");
            gets(member.email);

            valid = isEmail(member.email);

            if(valid)
                acpMsg("Valid e-mail address");
            else
                errMsg("Error\ninvalid e-mail address");

        } while(!valid);


        // initializing logic values to each structure without user's interfere
        member.borrowedBooks = 0;


        // write i(th) member data into file
        FILE * members = fopen("members.bin", "a");

        // failure check
        if(members==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        fwrite(&member, sizeof(memberDataType), 1, members);

        fclose(members);

    } while( yesNoRequest("add another member")==true );

    fflush(stdin);
    memberMenu();
}
