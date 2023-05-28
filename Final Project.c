#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
char null;
struct user_info
{
    int passport_no;
    char name[50];
    int flight_no;
    int seat_no;
} u[50], temp1;

struct flight_info
{
    int flight_no;
    char departure[50];
    char destination[50];
    int ticket_price;
} f[50],temp2;

int scan_user(int n)
{
    int i = n;
    char choice[4];
    do
    {
        printf("Enter the traveller's passport's number: ");
        scanf("%d",&u[i].passport_no);
        printf("Enter the traveller's name:");
        scanf("%c",&null);
        gets(u[i].name);
        printf("Enter the traveller's flight number:");
        scanf("%d",&u[i].flight_no);
        printf("Enter the traveller's seat number:");
        scanf("%d",&u[i].seat_no);
        printf("Do you want to add another traveller?");
        scanf("%s",choice);
        i++;
    }
    while(choice[0] == 'y' || choice[0] == 'Y' || choice == "yes" || choice == "Yes");
    return i;
}
void store_user(int start, int n)
{
    FILE *f1;
    if (start == 0)
      f1 = fopen("user_info.txt","w");
    else f1 = fopen("user_info.txt","a");
    if(f1 == NULL)
    {
        printf("can't open or create user file");
    }
    else
    {
        int i;
        for(i = start ; i < n ; i++)
        {
        	if(i == 0)
            	fprintf(f1,"%d\n%s\n%d\n%d",u[i].passport_no, u[i].name, u[i].flight_no, u[i].seat_no);
            else fprintf(f1,"\n%d\n%s\n%d\n%d",u[i].passport_no, u[i].name, u[i].flight_no, u[i].seat_no);
        }
    }
    fclose(f1);
}
int read_user()
{
    FILE *f1;
    f1 = fopen("user_info.txt","r");
    if(f1 == NULL)
    {
        printf("can't open or create user file");
    }
    else
    {
        int i = 0;
        while(!feof(f1))
        {
            fscanf(f1,"%d %[^\n] %d %d", &u[i].passport_no, u[i].name, &u[i].flight_no, &u[i].seat_no);
            i++;
        }
        fclose(f1);
        return i;
    }
}
void print_user(int n)
{
    int i;
    for(i = 0 ; i < n ; i++)
    {
        printf("\n\ntraveller %d:\n\t",i+1);
        printf("passport number: %d\n\t",u[i].passport_no);
        printf("name: ");
        puts(u[i].name);
        printf("\tflight number: %d\n\t",u[i].flight_no);
        printf("seat number: %d\n",u[i].seat_no);
    }
    printf("\n\n");
}
void sort_by_name(int n)
{
    int i, j;
    for(i = 0 ; i < n-1 ; i++)
    {
        for(j = i+1 ; j < n ; j++)
        {
            if(strcmp(u[i].name,u[j].name) > 0)
            {
                temp1 = u[i];
                u[i] = u[j];
                u[j] = temp1;
            }
        }

    }
}
int read_flight()
{
    FILE *f1;
    int k = 0;
    f1 = fopen("flight_info.txt","r");
    if(f1 == NULL)
    {
        printf("can't open or create user file");
    }
    else
    {
        while(!feof(f1))
        {
            fscanf(f1,"%d %[^\n] %[^\n] %d", &f[k].flight_no, f[k].departure, f[k].destination, &f[k].ticket_price);
            k++;
        }
        fclose(f1);
        return k;
    }
}
void print_flight(int n)
{
    int i;
    for(i = 0 ; i < n ; i++)
    {
        printf("flight %d:\n\t",i+1);
        printf("flight number: %d\n\t",f[i].flight_no);
        printf("departure: ");
        puts(f[i].departure);
        printf("\tdestination: ");
        puts(f[i].destination);
        printf("\tticket price: %d\n\n\n",f[i].ticket_price);
    }
}
int scan_flight(int k)
{
    char choice[4];
    do
    {
        printf("new flight's information:\nEnter the flight's number:");
        scanf("%d",&f[k].flight_no);
        printf("Enter the flight's departure:");
        scanf("%c",&null);
        gets(f[k].departure);
        printf("Enter the flight's destination:");
        gets(f[k].destination);
        printf("Enter the flight's ticket price:");
        scanf("%d",&f[k].ticket_price);
        printf("Do you want to enter another flight information? ");
        k++;
        scanf("%s",choice);
    }
    while(choice == "yes" || choice[0] == 'y' || choice == "Yes" || choice[0] == 'Y');
    return(k);
}
void store_flight(int n, int k)
{
    FILE *f1;
    if(n == 0)
        f1 = fopen("flight_info.txt","w");
    else f1 = fopen("flight_info.txt","a");
    if(f1 == NULL)
    {
        printf("can't open or create user file");
    }
    else
    {
        int i;
        for(i = n; i < k ; i++)
        if(i == 0)
            fprintf(f1,"%d\n%s\n%s\n%d",f[i].flight_no,f[i].departure,f[i].destination,f[i].ticket_price);
            else fprintf(f1,"\n%d\n%s\n%s\n%d",f[i].flight_no,f[i].departure,f[i].destination,f[i].ticket_price);
    }
    fclose(f1);
}
void sort_by_flight_no(int n)
{
    int i, j;
    for(i = 0 ; i < n-1 ; i++)
    {
        for(j = 0 ; j < n-1-i ; j++)
        {
            if(f[j+1].flight_no < f[j].flight_no)
            {
                temp2 = f[j];
                f[j] = f[j+1];
                f[j+1] = temp2;
            }
        }
    }
}
void search_by_flight_number(int n)
{
    int i,j,s,found;
    printf("\nEnter number to search: ");
    scanf("%d",&s);
    int flag=0;
    for(i=0; i<n; i++)
    {
        if(s==f[i].flight_no)
        {
            flag=1;
            found=i;
            break;
        }
    }
    if(flag == 1)
    {
        printf("Flight number is found\n\n");
        printf("flight %d:\n\t",found+1);
        printf("flight number: %d\n\t",f[found].flight_no);
        printf("departure: ");
        puts(f[found].departure);
        printf("\tdestination: ");
        puts(f[found].destination);
        printf("\tticket price: %d\n\n\n",f[found].ticket_price);
    }
    else
    {
        printf("Not found\n\n");
    }
}
void sum_and_average_of_tickets(int n)
{
    int i, sum = 0;
    float avg = 0;
    for(i = 0 ; i < n ; i++)
    {
        sum += f[i].ticket_price;
    }
    avg = (sum*1.0)/n;
    printf("Sum = %d\nAverage = %f\n\n", sum, avg);
}
int main()
{
    int i, n, action;
    int users;
    int flights;
    int new_user;
    int new_flights;
    printf("\t\t\t\t~~~~~~~~~~~Welcome to Airlines Reservation~~~~~~~~~~~\n\n\n");
    do
    {
        users = read_user();
        flights = read_flight();
        new_user = users;
        new_flights = flights;
        printf("Enter the action number:\n\t1) Add user.\n\t2) Print users.\n\t3) Sort users.\n\t4) Add flight.\n\t5) Print flights.\n\t6) Sort flights.\n\t7) Search for a flight.\n\t8) Sum and average of of tickets.\n\t9) Exit.\n");
        printf("Your action: ");
        scanf("%d",&action);
        switch(action)
        {
        case 1:
            new_user = scan_user(users);
            store_user(users, new_user);
            break;
        case 2:
            print_user(new_user);
            break;
        case 3:
            sort_by_name(new_user);
            store_user(0,new_user);
            printf("\nSorted users: \n");
            print_user(new_user);
            break;
        case 4:
            new_flights = scan_flight(flights);
            store_flight(flights, new_flights);
            break;
        case 5:
            print_flight(new_flights);
            break;
        case 6:
            sort_by_flight_no(new_flights);
            store_flight(0, new_flights);
            printf("\nSorted flights: \n");
            print_flight(new_flights);
            break;
        case 7:
            search_by_flight_number(new_flights);
            break;
        case 8:
            sum_and_average_of_tickets(new_flights);
            break;
        case 9:
            printf("------------------------------------------------------------------------------------------------------------------------");
            printf("\t\t\t\t\tThank you for using our services.\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            exit(0);
            break;
        default :
            printf("Invalid input");
            scanf("%d",& action);
            switch(action);
        }
    }
    while(action != 9);
}

