#include <stdio.h>
#include <stdlib.h>
 
void insert();
void search();
void displayall();
void deleterec();
 
struct book
{
    int book_no;
    char title[50];
    char auth_name[50];
};
 
struct book s;
 
void main()
{
    int userch;
    while (userch != 5)
    {
        printf("\n\n");
        printf("\tWELCOME TO THE LIBRARY\n\n\n");
 
        printf("\tChoose from one of the options below :\n\n");
        printf("\t\t1. Insert a Book Record\n");
        printf("\t\t2: Search for a Book Record\n");
        printf("\t\t3: Display all Book Records\n");
        printf("\t\t4: Delete a Book Record\n");
        printf("\t\t5: Exit\n\n");
        printf("\tEnter Your Choice : ");
        scanf("%d", &userch);
        switch (userch)
        {
        case 1:
            system("clear");
            insert(); 
            break;
          
        case 2:
            system("clear");
            search();
            break;
          
        case 3:
            system("clear");
            displayall();
            break;
          
        case 4:
            system("clear");
            deleterec();
            break;        
          
        case 5:
            exit(1);
            break; 
          
        default:
            printf("\n\tPlease enter your choice according to the options!\n\n");
        } 
    }
}
 
void insert()
{ 
 
    FILE *lib_file;
    lib_file = fopen("books.txt", "a+");
    printf("\n\n\tENTER BOOK DATA\n\n");
    printf("\t\tEnter Book Code : ");
    scanf("%d", &s.book_no);
    fflush(stdin);
    printf("\n\t\tEnter Book's Title : ");
    scanf("%s", s.title);
    printf("\n\t\tEnter Auth_name's Title : ");
    scanf("%s", s.auth_name);
    fwrite(&s, sizeof(s), 1, lib_file);
    {
        printf("\n\n\tRecorded Successfully!\n\n");
    }
    fclose(lib_file);
    printf("\tFile Saved and Record Updated!\n\n");
}
 
void search()
{
    int code, flag = 0;
    FILE *lib_file;
    lib_file = fopen("books.txt", "r");
    if (lib_file == NULL)
    {
        printf("\n\t\tThis file does not exist.");
        return;
    }
    printf("\n\n\tEnter the code of the book you want to search for : ");
    scanf("%d", &code);
    while (fread(&s, sizeof(s), 1, lib_file) > 0 && flag == 0)
    {
        if (s.book_no == code)
        {
            flag = 1;
            printf("\n\n\tHere are the book details :\n");
            printf("\n\t\tBook Code: %d", s.book_no);
            printf("\n\t\tTitle of the Book: %s",s.title);
            printf("\n\t\tName of the Author: %s\n\n",s.auth_name);
        }
    }
    if (flag == 0)
    {
        printf("\n\n\t\tRecord Doesn't Exist!\n\n");
    }
    fclose(lib_file);
}

void displayall()
{
    int code, size = 0;
  
    FILE *lib_file;
    lib_file = fopen("books.txt", "r");
    if (lib_file == NULL)
    {
        printf("\n\t\tThis file does not exist.");
        return;
    }
  
    if (lib_file != NULL)
    {   
        fseek (lib_file, 0, SEEK_END);
        size = ftell (lib_file);
        rewind(lib_file);
    }

    if(size==0)
    {
      printf("\tThe File is empty! Please enter some records first.\n");
    }

    else{
        printf("\n\n\tHere are the book details :\n");
        while (fread(&s, sizeof(s), 1, lib_file) > 0)
        {  
            printf("\n\t\tBook Code: %d", s.book_no);
            printf("\n\t\tTitle of the Book: %s",s.title);
            printf("\n\t\tName of the Author: %s\n\n",s.auth_name);
        }
      
        fclose(lib_file);
    }
}

void deleterec()
{
    int code, flag = 0;
    FILE *lib_file;
    FILE *temp = fopen("temp.txt","a");
    lib_file = fopen("books.txt", "r");
    if (lib_file == NULL)
    {
        printf("\n\t\tThis file does not exist.");
        return;
    }
    printf("\n\n\tEnter the code of the book you want to delete : ");
    scanf("%d", &code);
  
    while (fread(&s, sizeof(s), 1, lib_file) > 0 && flag == 0)
    {
        if (s.book_no == code)
        {
          
        }

        else
        {
          fwrite(&s,sizeof(s),1,temp);
          flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\n\n\t\tRecord Doesn't Exist!\n\n");
    }
  
    fclose(lib_file);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
    printf("\tRecord Deleted and File Saved!\n\n");
  
}
