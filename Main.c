#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int flag=1,i=0,n;
char del=','; // global variable flag used in validations and i used in iterations instead of declaring again in every function
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
Employee *x[100];  //global array
char filename[]="employees.txt";
// we pass the date and it creates the struct
void printE(int i);
Date* constructDate (int day,int month,int year)
{
    Date*x=malloc(sizeof(Date));
    x->day=day;
    x->month=month;
    x->year=year;
    return x;
}
Employee* ConstructEmployee (int id,float salary,char* Phone_num,char*Fname,char*Lname,char* address, char* email,int day, int month, int year)
{
    Employee*x=(Employee*)malloc(sizeof(Employee));
    x->id=id;
    x->phone_num=(char *)malloc(strlen(Phone_num)+1);
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
int  Numrec(char *filename)   //gets the total number of records
{   int n=0;
    FILE *fp=fopen(filename,"r");;
    if (!fp) return -1;
    fseek(fp, 0, SEEK_END);
    n=ftell(fp)/sizeof(Employee);
    fclose(fp);
    return n;
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
{   int sizee=0;
    FILE *fp;
    fp=fopen("employees.txt","r");
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
      x[(sizee)++]=deSerialize(str,del);
    }
    fclose(fp);

}
void sortbyLname(Employee* x[],int n) //sorts by last name
{
    int j,temp;
    for (i=0; i<n; i++)
    {
        for (j=i+i; j<n; j++)
        {
            if((strcasecmp((x[i]->Lname),(x[j]->Lname))>0))
            {
                temp=x[j];
                x[j]=x[i];
                x[i]=temp;
            }
        }
    }
}
void sortbyDOB(Employee* x[],int n) // sorts by Date of Birth
{
    int j,temp;
    for (i=0; i<n; i++)
    {
        for (j=i+i; j<n; j++)
        {
            if ((x[i]->Birthday->year)>(x[j]->Birthday->year))
            {  temp=x[j];
                x[j]=x[i];
                x[i]=temp;

            }
            if ((x[i]->Birthday->month)>(x[j]->Birthday->month))
            {
                temp=x[j];
                x[j]=x[i];
                x[i]=temp;
            }
            if ((x[i]->Birthday->day)>(x[j]->Birthday->day))
            {
                temp=x[j];
                x[j]=x[i];
                x[i]=temp;
            }
        }
    }
}
void sortbySalary(Employee* x[],int n) // sorts employees by salary
{
    int j,temp;
    for (i=0; i<n; i++)
    {
        for (j=i+i; j<n; j++)
        {
            if((x[i]->salary)>(x[j]->salary))
            {
                temp=x[j];
                x[j]=x[i];
                x[i]=temp;
            }
        }
    }
}
void Printsort(char *x )   //printing after sorting
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
        sortbyLname(x,Numrec(filename));
        break;
    case 2:
        sortbyDOB(x,Numrec(filename));
        break;
    case 3:
        sortbySalary(x,Numrec(filename));
        break;
    }
    for (i=0;i<Numrec(filename);i++)
    printf("Id = %d, First name=%s, Last name=%s, Email=%s, Address=%s, Salary=%f, Phone number=%s , Birthday = %d/%d/%d \n",x[i]->id,x[i]->Fname,x[i]->Lname,x[i]->email,x[i]->address,x[i]->salary,x[i]->phone_num,x[i]->Birthday->day,x[i]->Birthday->month, x[i]->Birthday->year);
}
//  we pass it the data and it creates the employee from scratch
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
Employee* AddEmployee() // adds new employee entered by user
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


    printf("please enter Employee ID");
    scanf("%s",ID);
     while (!ValidID(ID))
    {
            printf("please enter valid ID\n");
            scanf("%s",ID);
    }
    id = atoi(ID);

    return  ConstructEmployee(id,salary,phone_num,Fname,Lname,address,email,day,month,year);
}
void printE(int i)
{
    printf("First name:  %s\nLast name:  %s\nID of employee:  %d\nDate of birth of employee:  %d/%d/%d\nSalary of employee:  %.2f\nEmail of employee:  %s\nAddress of employee:  %s\nPhone number of employee:  %s\n",x[i]->Fname,x[i]->Lname,x[i]->id,x[i]->Birthday->day,x[i]->Birthday->month,x[i]->Birthday->year,x[i]->salary,x[i]->email,x[i]->address,x[i]->phone_num);
}

void Search(char *Lname)
{
    n = Numrec(filename);
    int c=0,j;
    for (i=0;i<n;i++)
    {
        j = strcasecmp(Lname,x[i]->Lname);
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

Employee * ModifyEmployee(int ID, Employee* x)  // function that deletes the employee to be modified and creates a new one
{ int day,month,year;
 float salary;
  char Lname[10],Fname[10],address[30],email[30],phone_num[15], SALARY[10];
    printf("please enter the modified Employee's first name\n");
    scanf("%s",Fname);
    while (!ValidName(Fname))
    {
        printf("please enter valid name\n");
        scanf("%s",Fname);
    }


    printf("please enter the modified Employee's Last name\n");
    scanf("%s",Lname);
    while (!ValidName(Lname))
    {
        printf("please enter valid name\n");
        scanf("%s",Lname);
    }


    printf("please enter the modified Employee's phone number\n");
    scanf("%s",phone_num);
    while (!ValidPhone(phone_num))
    {
        printf("please enter valid phone number\n");
        scanf("%s",phone_num);
    }


    printf("please enter the modified Employee's salary\n");
    scanf("%s",SALARY);
    while (!ValidSalary(SALARY))
    {
        printf("please enter a valid salary\n");
        scanf("%s",SALARY);
    }
    salary = atof(SALARY);

    printf("please enter the modified Employee's Address\n");
    scanf("%s",address);

    printf("please enter the modified Employee's email\n");
    scanf("%s",email);
    while (!Validemail(email))
    {
        printf("please enter valid email\n");
        scanf("%s",email);
    }

    printf("please enter the modified Date of birth DD/MM/YYYY\n");
    scanf("%d %d %d",&day,&month,&year);
    while (!validDate(day,month,year))
           {
               printf("please enter correct Date of birth DD/MM/YYYY\n");
               scanf("%d %d %d",&day,&month,&year);
           }
          Employee* y= ConstructEmployee(ID,salary,phone_num,Fname,Lname,address,email,day,month,year);
              printf("%.2f is the new employee salary\n",y->salary);

  return y;
}
char * serializeStudent(Employee *s, char d) //d=delimeeter
{
    char ste[100];
    ste[0]=0;
    sprintf(ste,"%d%c%f%c%s%c%s%c%s%c%s%c%s%c%d%c%d%c%d\n",s->id,d,s->salary,d,s->phone_num,d,s->Fname,d,s->Lname,d,s->address,d,s->email,d,s->Birthday->day,d,s->Birthday->month,d,s->Birthday->year);
    char* ret=malloc(strlen(ste)+1);
    strcpy(ret,ste);
    return ret;
}
void saveFile(char *filename,Employee *emp[],char del)
{
    FILE * fp=fopen(filename,"w");
    if(!fp)
    {
        fprintf(stdout,"ERROR CREATING FILE\n");
        exit(0);
    }
    for (i=0; i<Numrec(filename); i++)
    {
        char *str=serializeStudent(emp[i],del);
        fprintf(fp,str);
        free(str);
    }
    fclose(fp);
    printf("File %s saved\n",filename);
}
int main()
{
    Load(filename,',');
    Search("Khaled");
    saveFile(filename,x,del);
     /*  int Mod;
    printf("please enter an Employee's data\n");
    x[0] = ConstructEmployee(124,7000,"0123456","youssef","Elkady","asd","mos@hotmail.com",13,10,2001);
    x[1] = ConstructEmployee(124,7000,"0123456","youssef","Elkady","asd","mos@hotmail.com",13,10,2001);
 printf("please enter the employee ID to be modified\n");
    scanf("%d",&Mod);
    for (i=0;i<10;i++)
    {
         if (x[i]->id==Mod){
            x[i] = ModifyEmployee(Mod,x);
            break;
    }
    /*printf("please enter the employee ID to be deleted\n");
    for (i=0;i<10;i++)
    {
         if (x[i]->id==deletee){
            DestructEmployee(x[i]);
            break;
    }*/

    return 0;
}
