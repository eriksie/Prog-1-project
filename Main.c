#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
int flag=1,i=0; // global variable flag used in validations and i used in iterations instead of declaring again in every function
typedef struct
{
    unsigned day,year,month;
} Date;
// Employee struct
typedef struct
{
    int id,salary;
    char* Fname,*Lname,*address,*email,*phone_num;
    Date* Birthday;
} Employee;
// we pass the date and it creates the struct
Date* constructDate (int day,int month,int year)
{
    Date*x=malloc(sizeof(Date));
    x->day=day;
    x->month=month;
    x->year=year;
    return x;
}
//  we pass it the data and it creates the employee from scratch
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
void DestructEmployee(Employee* x) // frees the memory of the employee data after we are done using it
{
    free(x->Fname);
    free(x->Lname);
    free(x->Birthday);
    free(x->address);
    free(x->email);
    free(x);
}
int Validemail (char* email) // validates email entered
{ if (strstr(email,"@")&& strstr(email,".com"))
    return 1;

return 0;
}
int ValidName (char* Fname) //validates name entered
{   flag=1;
    for(i=0; i<strlen(Fname); i++)
    {
        if(Fname[i]<'A'||Fname[i]>'z')
            flag=0;
    }
    return flag;
}
int ValidPhone (char* phone_num) // validates the phone number entered
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

int validDate(int day,int month, int year)// validates the date entered
{
if(year>=1900 && year<=9999)
    {
        if(month>=1 && month<=12)
        {
            if((day>=1 && day<=31) && (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12))
                return 1;
            else if((day>=1 && day<=30) && (month==4 || month==6 || month==9 || month==11))
                return 1;
            else if((day>=1 && day<=28) && (month==2))
                return 1;
            else if(day==29 && month==2 && (year%400==0 ||(year%4==0 && year%100!=0)))
                return 1;
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
Employee* AddEmployee() // adds new employee entered by user.... still need to validate ID and Salary in it.
{
    int salary,id,day,month,year;
    char Lname[10],Fname[10],address[30],email[30],phone_num[15],buffer[20];
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
    scanf("%s",buffer);
    while (!ValidNum(salary))
    {
        printf("please enter a valid salary\n");
        scanf("%d",&salary);
        scanf("%s",buffer);
    }
    printf("please enter the new Employee's Address\n");
    scanf("%s",address);

    printf("please enter the new Employee's email\n");
    scanf("%s",email);
    while (!Validemail(email))
    {
        printf("please enter valid email\n");
        scanf("%s",email);
    }
    printf("please enter Date of birth DD/MM/YYYY\n");
    scanf("%d %d %d",&day,&month,&year);
    while (!validDate(day,month,year))
           {
               printf("please enter correct Date of birth DD/MM/YYYY\n");
               scanf("%d %d %d",&day,&month,&year);
           }
    printf("please enter Employee ID");
    scanf("%d",&id);
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
