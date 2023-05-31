#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

char *buses[100] = {"svkdt travels", "srikrishna travels", "sri tulasi tours and travels", "Super deluxe", "Sai Baba Travels", "Shine On Travels", "Mayur Travels"};
int Amount[100] = {1190, 1300, 700, 1500, 700, 1200, 900};
char name[32][100] = {'\0'};
char number[32][2] = {'\0'};
int num1[32] = {0};
int busno;

void viewdetails();
void name_number(int booking, char numstr[100]);
void reservation();
void read_number(int busno); // Modified function declaration
void read_name(int busno);
void status();
void status1(int busno);
void cancel();

int main()
{
    int num, i;
    do
    {
        system("cls");
        printf("\n\n\n");
        printf("====================================== WELCOME TO BUS RESERVATION SYSTEM ======================================\n\n\n");
        printf("\t\t\t\t\t[1]=> View details\n");
        printf("\n");
        printf("\t\t\t\t\t[2]=> Resrvation\n");
        printf("\n");
        printf("\t\t\t\t\t[3]=> Cancel Booking\n");
        printf("\n");
        printf("\t\t\t\t\t[4]=> Bus Status Board\n");
        printf("\n");
        printf("\t\t\t\t\t[5]=> Exit\n\n");

        printf("===============================================================================================================\n\n");
        printf("\t\t\tEnter Your Choice:: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            viewdetails();
            break;
        case 2:
            reservation();
            break;
        case 3:
            cancel();
            break;
        case 4:
            status();
            break;
        }
        getch();
    } while (num != 5);
    system("CLS");
    printf("\t----------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tThank You For Using This System\t\t\t\t\t\t\n");
    getch();
    return 0;
}

void viewdetails()
{
    printf("---------------------------------------------------------------------------------------");
    printf("\nbusno\tName\t\t\t\tDestinations \t\t\t\tCharges \t\tTime\n");
    printf("---------------------------------------------------------------------------------------");
    printf("\n1\tsvkdt travels                \t\tvijayanagaram to vijayawada    \tRs.1190 \t\t22:10 ");
    printf("\n2\tsrikrishna travels           \t\tsrikakakulam to vijayawada     \tRs.1300 \t\t21:30 ");
    printf("\n3\tsri tulasi tours and travels \t\tsrikakulam to kakinada         \tRs.700  \t\t11:50 ");
    printf("\n4\tSuper deluxe                 \t\trajamahendravaram To srisailam \tRs.1500 \t\t11:00 ");
    printf("\n5\tSai Baba Travels             \t\teluru to vijayawada            \tRs.700   \t\t7:05 ");
    printf("\n6\tShine On Travels             \t\tvijayawada to tirupati         \tRs.1200  \t\t9:30 ");
    printf("\n7\tMayur Travels                \t\tvijayawada to hyderabad        \tRs.900   \t\t8:30 ");
    printf("\n---------------------------------------------------------------------------------------\n");
}

void name_number(int bookings, char numstr[100])
{
    char tempstr[100], namesfile[12] = "names", numbersfile[12] = "numbers";
    int number;
    FILE *a, *b;
    int i = 0;
    strcat(numstr, ".txt");
    strcat(namesfile, numstr);
    strcat(numbersfile, numstr);
    a = fopen(namesfile, "a");
    b = fopen(numbersfile, "a");

    for (i = 0; i < bookings; i++)
    {
        printf("============================Enter the details for ticket no %d============================\n\n\n", i + 1);
        printf("\t\t\t\tEnter the seat number:--->");
        scanf("%d", &number);
        num1[number - 1] = 1; // Mark seat as reserved
        printf("\t\t\t\tEnter the name of person:--->");
        scanf("%s", name[number - 1]);

        printf("\n======================================================================================================\n\n");
        printf("\n");
        itoa(number, tempstr, 10);
        fprintf(a, "%s ", name[number - 1]);
        fprintf(b, "%s ", tempstr);
    }

    fclose(a);
    fclose(b);
}

void reservation()
{
    int busno, bookings;
    char numstr[100];
    system("cls");
    viewdetails();
    printf("Enter the bus number:--->");
    scanf("%d", &busno);
    printf("\n");
    printf("Enter the number of bookings:--->");
    scanf("%d", &bookings);
    printf("\n");
    printf("Enter your mobile number:--->");
    scanf("%s", numstr);

    name_number(bookings, numstr);

    printf("Your Ticket has been booked successfully!!\n");
    printf("Bus number is %d\n", busno);
    printf("Number of seats booked is %d\n", bookings);
    printf("The amount to be paid is Rs.%d\n", bookings * Amount[busno - 1]);
    printf("Your mobile number is %s\n", numstr);
}

void read_number(int busno)
{
    char numstr[100], tempstr[100], numbersfile[12] = "numbers";
    int number;
    FILE *b;

    sprintf(numstr, "%d", busno); // Convert busno to string
    strcat(numstr, ".txt");
    strcat(numbersfile, numstr);
    b = fopen(numbersfile, "r");
    if (b == NULL)
    {
        return;
    }
    while (!feof(b))
    {
        fscanf(b, "%s", tempstr);
        number = atoi(tempstr);
        num1[number - 1] = 1; // Mark seat as reserved
    }
    fclose(b);
}

void read_name(int busno)
{
    char numstr[100], tempstr[100], namesfile[12] = "names";
    FILE *a;
    int number;
    sprintf(numstr, "%d", busno); // Convert busno to string
    strcat(numstr, ".txt");
    strcat(namesfile, numstr);
    a = fopen(namesfile, "r");
    if (a == NULL)
    {
        return;
    }
    while (!feof(a))
    {
        fscanf(a, "%s", tempstr);
        number = atoi(tempstr);
        fscanf(a, "%s", name[number - 1]);
    }
    fclose(a);
}

void status1(int busno)
{
    int i;
    printf("---------------------------------------------------------------------------------------");
    printf("\nSeat Number \t\tBooking Status\t\t\tName of the Passenger\n");
    printf("---------------------------------------------------------------------------------------");
    for (i = 0; i < 32; i++)
    {
        if (num1[i] == 1)
        {
            printf("\n%d\t\t\tReserved\t\t\t%s\n", i + 1, name[i]);
        }
        else
        {
            printf("\n%d\t\t\tVacant\n", i + 1);
        }
    }
    printf("---------------------------------------------------------------------------------------\n");
}

void status()
{
    system("cls");
    printf("Enter the bus number:--->");
    scanf("%d", &busno);
    read_number(busno);
    read_name(busno);
    status1(busno);
}

void cancel()
{
    int i, number;
    char numstr[100], tempstr[100], namesfile[12] = "names", numbersfile[12] = "numbers";
    FILE *a, *b;
    system("cls");
    printf("Enter the bus number:--->");
    scanf("%d", &busno);
    printf("\n");
    printf("Enter the seat number:--->");
    scanf("%d", &number);
    printf("\n");
    num1[number - 1] = 0; // Mark seat as vacant
    itoa(number, tempstr, 10);
    strcat(numstr, ".txt");
    strcat(namesfile, numstr);
    strcat(numbersfile, numstr);
    a = fopen(namesfile, "r");
    b = fopen(numbersfile, "r");
    FILE *c, *d;
    char newnamesfile[12] = "newnames", newnumbersfile[12] = "newnumbers";
    strcat(newnamesfile, numstr);
    strcat(newnumbersfile, numstr);
    c = fopen(newnamesfile, "w");
    d = fopen(newnumbersfile, "w");
    for (i = 0; i < 32; i++)
    {
        if (i == number - 1)
        {
            fscanf(a, "%s", tempstr);
            fscanf(b, "%s", tempstr);
            continue;
        }
        fscanf(a, "%s", tempstr);
        fscanf(b, "%s", tempstr);
        fprintf(c, "%s ", tempstr);
        fprintf(d, "%s ", tempstr);
    }
    fclose(a);
    fclose(b);
    fclose(c);
    fclose(d);
    remove(namesfile);
    remove(numbersfile);
    rename(newnamesfile, namesfile);
    rename(newnumbersfile, numbersfile);
    status();
    printf("Ticket Cancellation Successful!!\n");
}
