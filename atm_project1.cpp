#include<stdio.h>
#include<string>
#include<cstring>
#include<stdlib.h>
#include <sstream>
#include <time.h>



void strnxcpy(char *dst,char *src,int i,int n);
void initialize();
void initialize_ul();
void initialize_us();
int is_cash_valid(char *cash);
long long int atoxi(char *cash);

main()
{
label:
    system("cls");
    initialize();
    int check;
    printf("\n\n\n");
    printf("  1.  Sign up\n");
    printf("  2.  Login\n\n");
    printf("  Please, enter your query  : ");
    scanf("%d",&check);
    if(check==1)
    {
        system("cls");
        initialize_us();
        char id[5], pin[5],name[80],m_name[80],f_name[80],phone_no[80],address[80];
        printf("\n\n\n") ;
        printf("Enter ID [4 digit] : ");
        scanf("%4s",&id);
        printf("Enter PIN [4 digit] : ");
        scanf("%4s",&pin);
        fflush(stdin);
        FILE *rawinput = fopen("./database/id_pass.txt","a");
        char dir[50] = "mkdir database\\users\\";
        strcat(dir,id);
        fprintf(rawinput,"\n%s:%s",id,pin);
        fclose(rawinput);
        printf("\n\n\n");
        printf("Your full name : ");
        scanf("%80[^\n]", name);
        fflush(stdin);
        printf("Your mother's name : ");
        scanf("%80[^\n]", m_name);
        fflush(stdin);
        printf("Your father's name : ");
        scanf("%80[^\n]", f_name);
        fflush(stdin);
        printf("Your Phone Number : ");
        scanf("%80[^\n]", phone_no);
        fflush(stdin);
        printf("Your Address : ");
        scanf("%80[^\n]", address);

        system(dir);

        char opendir[20] = "./database/users/";
        strcat(opendir,id);
        strcat(opendir,"/");
        strcat(opendir,id);
        strcat(opendir,"_user_information.txt");
        rawinput = fopen(opendir,"w");

        fprintf(rawinput,"Name: %s",name);
        fprintf(rawinput,"\nMother's Name: %s",m_name);
        fprintf(rawinput,"\nFather's Name: %s",f_name);
        fprintf(rawinput,"\nPhone Number: %s",phone_no);
        fprintf(rawinput,"\nAddress: %s",address);

        printf("\n\n");
        printf("User %s successfully signed up",id);
        fclose(rawinput);

        goto label;


    }

    if(check==2)
    {

        system("cls");
        initialize_ul();
        FILE *rawinput = fopen("./database/id_pass.txt","r");
        char id[10],pin[10], rawdata[20];
        int flag=0,attempt = 7;
        printf(" Enter your ID : ") ;
        scanf("%s",&id);
        printf(" Enter your pin : ") ;
        scanf("%s",&pin);

        while(attempt--)
        {
            int logout=0;
            fflush(rawinput);
            while(fscanf(rawinput,"%49[^\n]\n", rawdata)==1)
            {
                flag = 0;
                char get_id[6];
                char get_pin[5];
                strnxcpy(get_id,rawdata,0,4);
                strnxcpy(get_pin,rawdata,5,9);

                if(strstr(get_id,id))
                {
                    if(strstr(get_pin,pin))
                    {
                        system("cls");
                        initialize();
                        printf("\n\n");
                        printf("Logged in ID %s\n",id);
                        flag =1;
                        char str_currentBalance[50],str_balance_sheet[50],str_user_information[50];

                        char dir[20] = "./database/users/";
                        strcat(dir,id);
                        strcat(dir,"/");
                        strcat(dir,id);

                        strcpy(str_currentBalance, dir);
                        strcpy(str_balance_sheet, dir);
                        strcpy(str_user_information, dir);

                        strcat(str_currentBalance,"_currentBalance.txt");
                        strcat(str_balance_sheet,"_balance_sheet.txt");
                        strcat(str_user_information,"_user_information.txt");

                        FILE *fp = fopen(str_currentBalance,"r");
                        FILE *sheet ;

                        long long int totalBalance = 0 ;
                        long long int addcash = 0;

                        char cash[50];

                        fscanf(fp,"%llu",&totalBalance);
                        fclose(fp);

                        printf("\n1. Add cash\n2. Withdraw cash\n3. Show cash\n4. Show Balance sheet Info \n5. Show Personal Information \n6. Logout\n");
                        printf("Please Enter Your Query :  ");

                        scanf("%d",&check);
                        system("cls");
                        while(1)
                        {
                            initialize();
                            if(check==1)
                            {
                                printf("Add cash: ");
                                scanf("%s",&cash);
                                fflush(stdin);
                                if(is_cash_valid(cash))
                                {
                                    addcash = 0;
                                    time_t rawtime;
                                    struct tm * timeinfo;
                                    char buffer [80];
                                    time (&rawtime);
                                    timeinfo = localtime (&rawtime);
                                    strftime (buffer,80,"%d-%B-%Y %X",timeinfo);

                                    addcash = atoxi(cash);

                                    totalBalance += addcash;

                                    printf("\n\n") ;
                                    printf("\t\t%llu tk added successfully\n",addcash);
                                    printf("\t\tCurrent Balance: %llu tk.\n", totalBalance);
                                    printf("\n\n\n") ;

                                    fp = fopen(str_currentBalance,"w");
                                    fprintf(fp,"%llu",totalBalance);
                                    fclose(fp);

                                    sheet = fopen(str_balance_sheet,"a");
                                    if(sheet == NULL)
                                    {
                                        printf("\n\n\t\tInvalid !!\n");
                                    }
                                    fprintf(sheet,"\nAdded %llu tk on %s Current Balance %llu ",addcash,buffer,totalBalance);
                                    fclose(sheet);
                                }

                                else
                                {
                                    printf("\n\n\t\tInvalid cash !!\n\n");
                                }
                            }
                            if(check==2)
                            {
                                printf("withdraw cash: ");

                                scanf("%s",&cash);

                                if(is_cash_valid(cash))
                                {
                                    addcash = atoxi(cash);

                                    time_t rawtime;
                                    struct tm * timeinfo;
                                    char buffer [80];

                                    time (&rawtime);
                                    timeinfo = localtime (&rawtime);
                                    strftime (buffer,80,"%d-%B-%Y %X",timeinfo);

                                    if(totalBalance > 0)
                                    {
                                        if(addcash<=totalBalance)
                                        {
                                            totalBalance -= addcash;
                                            printf("\n\n\n");
                                            printf("\t\t%llu tk withdrawn successfully\n", addcash);
                                            printf("\t\tCurrent Balance: %llu tk.\n",totalBalance);
                                            printf("\n\n\n") ;

                                            fp = fopen(str_currentBalance,"w");
                                            fprintf(fp,"%llu",totalBalance);
                                            fclose(fp);

                                            sheet = fopen(str_balance_sheet,"a");
                                            if(sheet == NULL)
                                            {
                                                printf("\n\n\t\tInvalid !!\n");
                                            }
                                            fprintf(sheet,"\nWithdrawn %llu tk on %s Current Balance %llu ",addcash,buffer,totalBalance);
                                            fclose(sheet);

                                        }
                                        else
                                        {
                                            printf("\n\n\n");
                                            printf("\t\tYou don't have enough balance to withdraw  !!");
                                            printf("\n\n\n");
                                        }

                                    }
                                    else
                                    {
                                        printf("\n\n\n");
                                        printf("\t\tYou have no Balance !!");
                                        printf("\n\n\n");
                                    }
                                }

                                else
                                {
                                    printf("\n\n");
                                    printf("\t\tInvalid cash !!");
                                    printf("\n\n\n");
                                }

                            }

                            if(check==3)
                            {
                                printf("\n\n\n") ;
                                printf("\t\tTotal Cash: %llu \n ",totalBalance);
                                printf("\n\n\n") ;


                            }
                            if(check==4)
                            {
                                int c;
                                FILE *file;
                                printf("\n");
                                file = fopen(str_balance_sheet, "r");
                                printf("\n\n");
                                if (file)
                                {
                                    while ((c = getc(file)) != EOF)
                                        putchar(c);
                                    fclose(file);
                                }
                            }

                            if(check==5)
                            {
                                int c;
                                FILE *file;
                                printf("\n");
                                file = fopen(str_user_information, "r");
                                if (file)
                                {
                                    while ((c = getc(file)) != EOF)
                                        putchar(c);
                                    fclose(file);
                                }
                            }


                            if(check==6)
                            {
                                logout=1;
                                printf("\n\n\n") ;
                                printf("\t\tYou have Logged Out your account.\n\n");
                                break;
                                break;
                                break;
                            }

                            printf("\n\n1. Add cash\n2. Withdraw cash\n3. Show cash\n4. Show Balance sheet Info \n5. Show Personal Information \n6. Logout\n");
                            printf("Please Enter Your Query :  ");
                            fflush(stdin);
                            scanf("%d",&check);
                            system("cls");

                        }
                    }
                }

            }



            if(flag==0 && logout == 0)
            {
                printf("\n");
                printf("Login Failed !!!\n");
                printf("You have %d attempts Left\n",attempt);
                printf("\n");
                printf( " Enter your ID : " );
                scanf("%s",&id);
                printf (" Enter your pin : ") ;
                scanf("%s",&pin);
                fclose(rawinput);
                rawinput = fopen("./database/id_pass.txt","r");

            }

            if(logout==1)
            {

                attempt=7;
                system("cls");
                goto label;

            }
        }


        fclose(rawinput);

    }

}






void strnxcpy(char *dst,char *src,int i,int n)
{
    int j = -1,k;
    for(k =i ; k <n ; k++)
    {
        dst[++j] = src[k];
    }

    dst[++j] = '\0';

}

void initialize()
{
    printf("        ||=====================================================||\n");
    printf("        ||                                                     ||\n");
    printf("        ||            AUTOMATED TELLER MACHINE(ATM)            ||\n");
    printf("        ||                                                     ||\n");
    printf("        ||=====================================================||\n");


}

void initialize_ul()
{
    printf("        ||=====================================================||\n");
    printf("        ||                                                     ||\n");
    printf("        ||            AUTOMATED TELLER MACHINE(ATM)            ||\n");
    printf("        ||                   USER LOG IN                       ||\n");
    printf("        ||                                                     ||\n");
    printf("        ||=====================================================||\n");


}


void initialize_us()
{
    printf("        ||=====================================================||\n");
    printf("        ||                                                     ||\n");
    printf("        ||            AUTOMATED TELLER MACHINE(ATM)            ||\n");
    printf("        ||                   USER SIGN UP                      ||\n");
    printf("        ||                                                     ||\n");
    printf("        ||=====================================================||\n");


}

int is_cash_valid(char *cash)
{

    int state = 0;

    for(int i = 0 ; i < strlen(cash) ; i++)
    {
        if(cash[i]>= '0' && cash[i]<= '9')
        {
            continue;
        }
        else
        {
            state = 1;
            return 0 ;
            break;
        }
    }


    if(state==0)
    {
        return 1;

    }
}

long long int atoxi(char *cash)
{
    long long int num = 0;
    for(int i = 0 ; i<strlen(cash); i++)
    {
        num = num * 10 + (cash[i] - '0');
    }

    return num;

}
