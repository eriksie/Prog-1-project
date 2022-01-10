#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int flag=0,i=0,sz=0;
char filename[30];
typedef struct
{
    unsigned day,year,month;
} Date;
// Employee struct
typedef struct
{
    int id;
    float salary;
    char* Fname,*Lname,*address,*email,*phone_num;
    Date* Birthday;
} Employee;
Employee *Emp[100];

Date* constructDate (int day,int month,int year)
{
    Date*z=malloc(sizeof(Date));
    z->day=day;
    z->month=month;
    z->year=year;
    return z;
}

Employee* ConstructEmployee (int id,float salary,char* Phone_num,char*Fname,char*Lname,char* address, char* email,int day, int month, int year)
{
    Employee*y=(Employee*)malloc(sizeof(Employee));
    y->id=id;
    y->phone_num=(char *)malloc(strlen(Phone_num)+1);
    strcpy(y->phone_num,Phone_num);
    y->salary=salary;
    y->Fname=(char *) malloc(strlen(Fname)+1);
    strcpy(y->Fname,Fname);
    y->Lname=(char *) malloc(strlen(Lname)+1);
    strcpy(y->Lname,Lname);
    y->address=(char *) malloc(strlen(address)+1);
    strcpy(y->address,address);
    y->email=(char *) malloc(strlen(email)+1);
    strcpy(y->email,email);
    y->Birthday=constructDate(day,month,year);
    return y;
}

Employee * deSerialize(char *str,char d) // deserialize the entries in the file
{ char del[2]={d,0};
    char *tok=strtok(str,del);   //getting first tok
    int i=0,id=0,day=0,month=0,year=0;
    float salary;
char Lname[20],Fname[20],address[20],email[20],phone_num[100];
    while (tok != NULL)
    {
        switch (i)
        {
        case 0:
            id=atoi(tok);
            break;
        case 1:
            salary=atof(tok);
            break;
        case 2:
            strcpy(phone_num,tok);
            break;
        case 3:
            strcpy(Fname,tok);
            break;
        case 4:
            strcpy(Lname,tok);
            break;
        case 5:
            strcpy(address,tok);
            break;
        case 6:
            strcpy(email,tok);
            break;
        case 7:
            day=atoi(tok);
            break;
        case 8:
            month=atoi(tok);
            break;
        case 9:
            year=atoi(tok);
            break;
        }
        i++;
        tok=strtok(NULL,del);
    }
   return   ConstructEmployee(id,salary,phone_num,Fname,Lname,address,email,day,month,year);

}

void Load(char *filename,char del) // loads the file into an array
{   sz=0;
    FILE *fp;
    fp=fopen(filename,"r");
    if(!fp)
    {
        fprintf(stdout,"ERROR Reading FILE %s\n",filename);
        exit(1);
    }
    char str[200];
    while(!feof(fp))
    {
        char *s=fgets(str, 199, fp);
        if (!s)
            break;
      Emp[(sz)++]=deSerialize(str,del);
    }
    fclose(fp);

}
  void AddEmployee() // adds new employee entered by user
{
    int id,day,month,year;
    float salary;
    char Lname[10],Fname[10],address[30],email[30],phone_num[15],SALARY[10],ID[10];
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
    scanf("%s",SALARY);
    while (!ValidSalary(SALARY))
    {
            printf("please enter a valid salary\n");
            scanf("%s",SALARY);
    }
    salary = atof(SALARY);


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


    printf("please enter Employee ID\n");
scanf("%s",ID);
     while (!ValidID(ID))
    {
            printf("please enter valid ID\n");
            scanf("%s",ID);
    }
    id = atoi(ID);

    Emp[sz++] = ConstructEmployee(id,salary,phone_num,Fname,Lname,address,email,day,month,year);
}

void ModifyEmployee(int ID,int i)  // function that deletes the employee to be modified and creates a new one
{ int day,month,year;
 float salary;
  char Lname[10],Fname[10],address[30],email[30],phone_num[15], SALARY[10];
    printf("please enter the modified Employee's first name\n");
    scanf("%s",Fname);
    strcpy(Emp[i]->Fname,Fname);
    while (!ValidName(Fname))
    {
        printf("please enter valid name\n");
        scanf("%s",Fname);
        strcpy(Emp[i]->Fname,Fname);

    }


    printf("please enter the modified Employee's Last name\n");
    scanf("%s",Lname);
    strcpy(Emp[i]->Lname,Lname);

    while (!ValidName(Lname))
    {
        printf("please enter valid name\n");
        scanf("%s",Lname);
        strcpy(Emp[i]->Lname,Lname);

    }


    printf("please enter the modified Employee's phone number\n");
    scanf("%s",phone_num);
    strcpy(Emp[i]->phone_num,phone_num);

    while (!ValidPhone(phone_num))
    {
        printf("please enter valid phone number\n");
        scanf("%s",phone_num);
        strcpy(Emp[i]->phone_num,phone_num);

    }


    printf("please enter the modified Employee's salary\n");
    scanf("%s",SALARY);
    while (!ValidSalary(SALARY))
    {
        printf("please enter a valid salary\n");
        scanf("%s",SALARY);
    }
    salary = atof(SALARY);
    Emp[i]->salary = salary;
    printf("please enter the modified Employee's Address\n");
    scanf("%s",address);
    strcpy(Emp[i]->address,address);


    printf("please enter the modified Employee's email\n");
    scanf("%s",email);
    strcpy(Emp[i]->email,email);

    while (!Validemail(email))
    {
        printf("please enter valid email\n");
        scanf("%s",email);
        strcpy(Emp[i]->email,email);

    }

    printf("please enter the modified Date of birth DD/MM/YYYY\n");
    scanf("%d %d %d",&day,&month,&year);
    while (!validDate(day,month,year))
           {
               printf("please enter correct Date of birth DD/MM/YYYY\n");
               scanf("%d %d %d",&day,&month,&year);
           }
           Emp[i]->Birthday->day = day;
           Emp[i]->Birthday->month = month;
           Emp[i]->Birthday->year = year;
             // printf("%.2f is the new employee salary\n",y->salary);
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
    if(strlen(phone_num) != 11)
        return 0;
    for(i=0; i<strlen(phone_num); i++)
    {
        if(phone_num[0]!= '0')
        {
            flag = 0;
        }
        if(phone_num[i]<'0'||phone_num[i]>'9')
            flag=0;
    }
    return flag;
}
int ValidID(char *x)  // validates the ID entered
{
    flag=1;
    if(strlen(x) != 3)
    return 0;
    for(i=0; i<strlen(x); i++)
    {
        if(x[i]<'0'||x[i]>'9')
            flag=0;
    }
    return flag;
}

int ValidSalary(char *x)  // validates the salary entered
{
    flag=1;
    for(i=0; i<strlen(x); i++)
    {
        if(x[i]<'0'||x[i]>'9')
        {
           if(x[i]!='.')
            flag=0;
        }
    }
    return flag;
}
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

char * serializeStudent(Employee *s, char d) //d=delimeeter
{
    char ste[100];
    ste[0]=0;
    sprintf(ste,"%d%c%.2f%c%s%c%s%c%s%c%s%c%s%c%d%c%d%c%d\n",s->id,d,s->salary,d,s->phone_num,d,s->Fname,d,s->Lname,d,s->address,d,s->email,d,s->Birthday->day,d,s->Birthday->month,d,s->Birthday->year);
    char* ret=malloc(strlen(ste)+1);
    strcpy(ret,ste);
    return ret;
}
void saveFile(char *filename,Employee *emp[],char del)
{   printf("size of record in save file is %d\n",sz);
    FILE *fj=fopen(filename,"w");
    if(!fj)
    {
        fprintf(stdout,"ERROR OPENING FILE\n");
        exit(0);
    }
    for (i=0; i<sz; i++)
    {
        char *str=serializeStudent(emp[i],del);
        fprintf(fj,str);
        free(str);
    }
    fclose(fj);
    printf("File %s saved\n",filename);
}

void printE(int i)
{
    printf("First name:  %s\nLast name:  %s\nID of employee:  %d\nDate of birth of employee:  %d/%d/%d\nSalary of employee:  %.2f\nEmail of employee:  %s\nAddress of employee:  %s\nPhone number of employee:  %s\n",Emp[i]->Fname,Emp[i]->Lname,Emp[i]->id,Emp[i]->Birthday->day,Emp[i]->Birthday->month,Emp[i]->Birthday->year,Emp[i]->salary,Emp[i]->email,Emp[i]->address,Emp[i]->phone_num);
}

void Search(char *Lname)
{
    int c=0,j;
    for (i=0;i<sz;i++)
    {
        j = strcasecmp(Lname,Emp[i]->Lname);
        if(j == 0)
        {
            printE(i);
            printf("\n");
            c++;
        }
    }
    if (!c)
        printf("There are no employees with this last name.\n");
}

void sortbySalary(Employee* x[],int n) // sorts employees by salary
{
    int j;
    Employee *temp;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n-1; j++)
        {
            if((Emp[j+1]->salary)>(Emp[j]->salary))
            {
                temp=Emp[j];
                Emp[j]=Emp[j+1];
                Emp[j+1]=temp;
            }
        }
    }
}

void sortbyDOB(Employee* x[],int n) // sorts by Date of Birth
{
    int j;
    Employee* temp;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n-1; j++)
        {
            if ((Emp[j+1]->Birthday->year)>(Emp[j]->Birthday->year))
            {  temp=Emp[j];
                Emp[j]=Emp[j+1];
                Emp[j+1]=temp;

            }
           else if ((Emp[j+1]->Birthday->year)==(Emp[j]->Birthday->year)&&(Emp[j+1]->Birthday->month)>(Emp[j]->Birthday->month))
            {
                temp=Emp[j];
                Emp[j]=Emp[j+1];
                Emp[j+1]=temp;
            }
           else  if ((Emp[j+1]->Birthday->year)==(Emp[j]->Birthday->year)&&(Emp[j+1]->Birthday->month)==(Emp[j]->Birthday->month)&&(Emp[j+1]->Birthday->day)>(Emp[j]->Birthday->day))
            {
                temp=Emp[j];
                Emp[j]=Emp[j+1];
                Emp[j+1]=temp;
            }
        }
    }
}

void sortbyLname(Employee* x[],int n) //sorts by last name
{
    int j;
    Employee* temp;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n-1; j++)
        {
            if((strcasecmp((Emp[j+1]->Lname),(Emp[j]->Lname))>0))
            {
                temp=Emp[j];
                Emp[j]=Emp[j+1];
                Emp[j+1]=temp;
            }
        }
    }
}
void Printsort()   //printing after sorting
{
    int s;
    printf("Please choose type of sorting from this menu:\n");
    printf("1. Sort by Last name\t2.Sort by date of birth.\t3.Sort by salary.\n");
    scanf("%d",&s);
    while (!(s==1||s==2||s==3))
    {
        printf("Please choose a number from the list\n");
        scanf("%d",&s);
    }
    switch(s)
    {
    case 1:
       sortbyLname(Emp,sz);
        break;
    case 2:
       sortbyDOB(Emp,sz);
        break;
    case 3:
        sortbySalary(Emp,sz);
        break;
    }
    for (i=0;i<sz;i++){
    printf("\n\n");
    printE(i);
    }
}

void DeleteFunction(char first[20],char last[20])
{
    int i,j;
    for(i=0; i<sz; i++)
    {
        if(strcasecmp(Emp[i]->Lname,last)==0 && strcasecmp(Emp[i]->Fname,first)==0)
        {
            for(j=i; j<sz-1; j++)
                Emp[j]=Emp[j+1];
            sz-=1;
            i--;
            DeleteFunction(first,last);
        }
    }
}

int main()
{   int mod,j,o,c=1;
    char sure;
    char Lname[20],Fname[20];
    printf("this is the main menu\n");

    printf("please enter file name to load from. it must be in the format of .txt\n");
    scanf("%s",filename);

    Load(filename,',');// mehtag a3ml validation ll filename lesa
    while (c){
    printf("please choose one of the following options to do\n");
    printf("search for an Employee by last name: 1\n");
    printf("Add a new Employee: 2\n");
    printf("Delete an already existing Employee: 3\n");
    printf("Modify an already existing Employee: 4\n");
    printf("Print Employee records: 5\n");
    printf("Save file: 6\n");
    printf("Quit: 7\n");
    scanf("%d",&o);
    switch (o)
    {
     case 1: printf("enter last name to search for\n");
             scanf("%s",Lname);
             Search(Lname);
             break;
     case 2:
        AddEmployee();
        break;
     case 3:
        printf("please enter Employee first name to be deleted\n");
        scanf("%s",Fname);
        printf("please enter Employee last name to be deleted\n");
        scanf("%s",Lname);
        DeleteFunction(Fname,Lname);
        break;
     case 4:
          printf("please enter employee ID to be modified\n");
          scanf("%d",&mod);

          for (j=0;j<sz;j++){
             if (Emp[j]->id==mod){
               ModifyEmployee(mod,j);
               break;
               }
             if (j==sz-1)
           printf("no employee is found with this ID\n");
           }
           break;
     case 5:
        Printsort();
        break;
     case 6:
        saveFile(filename,Emp,',');
        break;
     case 7:
        printf("are you sure you want to quit?\n type Y if sure and anything else if you want to return to the menu\n");
        sure = getchar();
        if (sure == 'Y' || 'y')
            c=0;
        else break;
    }
    }
       return 0;
}
