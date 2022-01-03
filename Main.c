#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int flag=1;
typedef struct
{
    unsigned day,year,month;
} Date;

typedef struct
{
    int id,salary,phone_num;
    char* Fname,*Lname,*address,*email;
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

Employee* ConstructEmployee (int id,int salary,int Phone_num,char*Fname,char*Lname,char* address, char* email,int day, int month, int year)
{
    Employee*x=malloc(sizeof(Employee));
    x->id=id;
    x->phone_num=Phone_num;
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
{
    int i;
    for(i=0; i<strlen(Fname); i++)
    {
        if(Fname[i]<'A'||Fname[i]>'z')
            flag=0;
    }
    return flag;
}
Employee* AddEmployee()
{
    int i,j,salary,id,phone_num,day,month,year;
    char* Lname,*Fname,*address,*email;
    printf("please enter the new Employee's first name\n");
    scanf("%s",Fname);
    while (!ValidName(Fname))
    {
        printf("please enter valid name\n");
        scanf("%s",Fname);
        flag=1;
    }
    printf("please enter the new Employee's Last name\n");
    scanf("%s",Lname);
    while (!ValidName(Lname))
    {
        printf("please enter valid name\n");
        scanf("%s",Lname);
        flag=1;
    }

}
int main()
{
    printf("Hello world!\n");
    return 0;
}
