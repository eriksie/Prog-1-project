#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#Include <ctype.h>
int flag=1,i=0;
typedef struct
{
    unsigned day,year,month;
} Date;

typedef struct
{
    int id,salary;
    char* Fname,*Lname,*address,*email,*phone_num;
    Date* Birthday;
} Employee;

Date* constructDate (int day,int month,int year)
{
    Date*x=malloc(sizeof(Date));
    x->day=day;
    x->month=month;
    x->year=year;
    return x;
}

Employee* ConstructEmployee (int id,int salary,char* Phone_num,char*Fname,char*Lname,char* address, char* email,int day, int month, int year)
{
    Employee*x=malloc(sizeof(Employee));
    x->id=id;
    x->phone_num=(char *) malloc(strlen(Phone_num)+1);
    strcpy(x->phone_num,Phone_num);
    x->salary=salary;
    x->Fname=(char *) malloc(strlen(Fname)+1);
    strcpy(x->Fname,Fname);
    x->Lname=(char *) malloc(strlen(Lname)+1);
    strcpy(x->Lname,Lname);
    x->address=(char *) malloc(strlen(address)+1);
    strcpy(x->address,address);
    x->email=(char *) malloc(strlen(email)+1);
    strcpy(x->email,email);
    x->Birthday=constructDate(day,month,year);
    return x;
}
void DestructEmployee(Employee* x)
{
    free(x->Fname);
    free(x->Lname);
    free(x->Birthday);
    free(x->address);
    free(x->email);
    free(x);
}
int ValidName (char* Fname)
{   flag=1;
    for(i=0; i<strlen(Fname); i++)
    {
        if(Fname[i]<'A'||Fname[i]>'z')
            flag=0;
    }
    return flag;
}
int ValidPhone (char* phone_num)
{   flag=1;
    for(i=0; i<strlen(phone_num); i++)
    {
        if(phone_num[i]<'0'||phone_num[i]>'9')
            flag=0;
    }
    return flag;
}
/*int ValidNum(int x)
{
flag =1;
int j= log10(x)+1;
for (i=0;i<j;i++){
    if(!(isdigit(x))){
            flag=0;
            return flag;

            }
    x/=10;
}
return flag;
}*/
Employee* AddEmployee()
{
    int salary,id,day,month,year;
    char Lname[10],Fname[10],address[30],email[30],phone_num[15];
    printf("please enter the new Employee's first name\n");
    scanf("%s",Fname);
    while (!ValidName(Fname))
    {
        printf("please enter valid name\n");
        scanf("%s",Fname);
    }
    printf("please enter the new Employee's Last name\n");
    scanf("%s",Lname);
    while (!ValidName(Lname))
    {
        printf("please enter valid name\n");
        scanf("%s",Lname);
    }
    printf("please enter the new Employee's phone number\n");
    scanf("%s",phone_num);
    while (!ValidPhone(phone_num))
    {
        printf("please enter valid phone number\n");
        scanf("%s",phone_num);
    }
    printf("please enter the new Employee's salary\n");
    scanf("%d",&salary);
    while (!ValidNum(salary))
    {
        printf("please enter a valid salary\n");
        scanf("%d",&salary);
    }
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
