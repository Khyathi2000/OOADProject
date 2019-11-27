#include <iostream>
#include <iomanip>
#include <algorithm>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include <fstream>
#define ANS 20
#define ACS 6
using namespace std;

COORD coord={0,0}; // this is global variable .center of axis is set to the top left cornor of the screen

//classes declaration/
typedef struct product{
char name[ANS],code[ACS];
float rate;
int quantity;

//void display(product item , int, int, int);
}product;
product item;

class display{
	public:
		void display_mainmenu();

		void display_code();
		void display_rate();
		void display_quantity();
		void display_all();
};

class customer{
  public:
  	string userId;
  	string password;

	void login();
	void search();
	void bill();
	void exit();
};

class vendor{
  public:
	void add();
	void edit();
	void del();
};
//declaration of checking functions/
void check_code(char[]);
int check(char[]);

//declaration of display functions/
void gotoxy(int ,int);
void window(int,int,int,int);
void curser(int);
void highlight(int,int);
void dbill();
void d_mainmenu();
//void display(product *,int,int);
void dis_con();



//declaration of main menu functions/
void bill();
void edit();
void add();
void d_search(){
cout<<"search"<<endl;}
void exit();
void display(){
cout<<"display"<<endl;}

//declaration of display submenu functions/
void d_code();
void d_rate();
void d_quan();
void d_all();

void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//function to display box/
void window(int a,int b,int c,int d)
{
 int i;
 system("cls");
 gotoxy(20,10);
 for (i=1;i<=10;i++)
  cout<<"*";
 cout<<" * CC  * ";
 for (i=1;i<=10;i++)
        cout<<"*";
 cout<<endl<<endl;
 gotoxy(30,11);cout<<"Departmental Store";
 for (i=a;i<=b;i++){
        gotoxy(i,17);cout<<"\xcd";
        gotoxy(i,19);cout<<"\xcd";
        gotoxy(i,c);cout<<"\xcd";
        gotoxy(i,d);cout<<"\xcd";
        }

 gotoxy(a,17);cout<<"\xc9";
 gotoxy(a,18);cout<<"\xba";
 gotoxy(a,19);cout<<"\xc8";
 gotoxy(b,17);cout<<"\xbb";
 gotoxy(b,18);cout<<"\xba";
 gotoxy(b,19);cout<<"\xbc";

 for(i=c;i<=d;i++){
  gotoxy(a,i);cout<<"\xba";
  gotoxy(b,i);cout<<"\xba";
 }
 gotoxy(a,c);cout<<"\xc9";
 gotoxy(a,d);cout<<"\xc8";
 gotoxy(b,c);cout<<"\xbb";
 gotoxy(b,d);cout<<"\xbc";
}

void d_mainmenuForVendor()
{
 int i;
 char ch;
 const char *menu[]={"   1.Add Goods","   2.Edit Goods","   3.Display All ","   4.Search","   Exit"};
 system("cls");
 window(25,50,20,32);
 gotoxy(28,18);
 cout<<"MAIN MENU FOR VENDOR"<<endl;
 for (i=0;i<=4;i++){
  gotoxy(28,22+i+1);cout<<menu[i]<<endl;}
  //curser(7);
  int n;
  gotoxy(28,30);
  cout<<"Select your choice: ";
  cin>>n;
  switch(n){
  	case 1:
  		add();
	  break;
	case 2:
		edit();
	  break;
	case 3:
	  display();
	  break;
	case 4:
	  d_search();
	  break;
	default:
	  exit(0);
  }
 }

void d_mainmenuForCustomer()
{
 int i;
 char ch;
 const char *menu[]={"   1.Calculate Bill","   2.Display All ","   3.Search","   4.Exit"};
 system("cls");
 window(25,50,20,32);
 gotoxy(28,18);
 cout<<"MAIN MENU(CUSTOMER)"<<endl;
 for (i=0;i<=3;i++){
  gotoxy(28,22+i+1);cout<<menu[i]<<endl;}
  //curser(7);
  int n;
  gotoxy(28,27);
  cout<<"Select your choice: ";
  cin>>n;
  switch(n){
  	case 1:
  		bill();
  		break;
  	case 2:
  		display();
	  break;
	case 3:
		d_search();
	  break;
	default:
	  exit(0);
  }
 }


 selectSlot(){
 system("cls");
 cout<<"slot selected";
 }

void bill()
{
  string x="0000";
  int j=29,q=0,size=0,i=1;
  float total=0,gtotal=0;
  FILE *file;
  file=fopen("record2.txt","r+b");
  rewind(file);
  system("cls");
  int k;
 gotoxy(20,10);
 for (k=1;k<=10;k++)
  cout<<"*";
 cout<<" * CC * ";
 for (k=1;k<=10;k++)
        cout<<"*";
 cout<<endl<<endl;
 gotoxy(30,11);cout<<"Departmental Store";
 gotoxy(32,25);cout<<"CUSTOMER'S BILL";
 gotoxy(13,27);cout<<"SN.   Item Name     Quantity     Rate          Total";
  gotoxy(26,15);
  cout<<"enter  \"end\" to finish input";
  while(1){
  gotoxy(25,18);
  cout<<"                    ";
  gotoxy(25,19);
  cout<<"                    ";
  gotoxy(25,18);
  cout<<"enter item code:";
  cin>>x;
  if(x=="end")
   break;
  gotoxy(25,19);
  cout<<"enter quantity:";
  cin>>q;
  rewind(file);
  while(fread(&item,sizeof(item),1,file)){
   if(item.code==x){
    total=item.rate*q;
    gotoxy(11,j);
    printf("%4d    ",i);
    printf("%9s    ",item.name);
    printf("%13d   ",q);
    printf("%15.2f ",item.rate);
    printf("%13.2f ",total);

    gtotal=gtotal+total;
    size=sizeof(item);
    item.quantity=item.quantity-q;
    j=j+2;
    i++;
    fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
    break;
   }
    }
 }
 if(gtotal!=0){
  gotoxy(30,j+5);
  printf("TOTAL AMOUNT = NRs. ");
  printf("%6.2f",gtotal);
}
gotoxy(30,j+7);

cout<<"Select your payment mode";
gotoxy(30,j+8);
cout<<"1.Pay on Delivery";
gotoxy(30,j+9);
cout<<"2.Pay by Card.";
int z;
gotoxy(30,j+10);
cin>>z;
if(z==1)
    selectSlot();
else if(z==2){
    selectSlot();
}
 fclose(file);
 getch();
 d_mainmenuForCustomer();
}

//function to check availability of code/
void check_code(char y[])
{
 int flag;
 FILE *file;
 file=fopen("record2.txt","rb");
 while(1){
  system("cls");
  window(20,58,23,36);
  gotoxy(32,18);cout<<" ADD ARTICLES ";
  flag=1;
  rewind(file);
  gotoxy(22,25);cout<<"Enter new code of the article:";
  scanf(" %[^\n]",y);
  while(fread(&item,sizeof(item),1,file)==1){
   if (strcmp(y,item.code)==0){
    flag=0;
    gotoxy(26,30);cout<<"code already exists";
    gotoxy(29,32);cout<<"enter again";
    getch();
    break;
   }
  }
  if (flag==1)
  break;
 }
}

//function for editing/
void edit()
{
 int flag=0,choice;
 char x[ACS],y[ACS];
 FILE *file;
 int size;
 system("cls");
 window(20,63,20,46);
 gotoxy(35,18);
 cout<<"EDIT RECORDS";
 gotoxy(25,23);
 cout<<"enter item code: ";
 scanf("%s",x);
 //cin.getline(x,ACS);
 flag=check(x);
 if(flag==0){
  file=fopen("record2.txt","r+b");
  rewind(file);
  while (fread(&item,sizeof (item),1,file)){
   if(strcmp(item.code,x)==0){
    gotoxy(25,27);
    cout<<"name       = "<<item.name;
    gotoxy(25,28);
    cout<<"code       = "<<item.code;
    gotoxy(25,29);
    cout<<"rate       = "<<item.rate;
    gotoxy(25,30);
    cout<<"quantity   = "<<item.quantity;
    gotoxy(25,32);;
     cout<<"do you want to edit this record(y/n):";
    fflush(file);
    if(toupper(getch())=='Y'){
     gotoxy(25,34);
     cout<<"1- edit name ";
     gotoxy(25,35);
    cout<<"2- edit code ";
     gotoxy(25,36);
     cout<<"3- edit rate ";
     gotoxy(25,37);
     cout<<"4- edit quantity ";
     gotoxy(25,39);  ;
     cout<<" Enter your choice(1, 2, 3, 4) ";
     cin>>choice;
     switch(choice){
      case 1:
       system("cls");
      window(23,48,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       cout<<" enter new name: ";
       cin>>item.name;
       size=sizeof(item);
       fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
       break;
      case 2:
       system("cls");
       window(23,65,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       check_code(y);
       strcpy(item.code,y);
       size=sizeof(item);
       fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
       break;
      case 3:
       system("cls");
       window(23,65,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       cout<<" enter new rate: ";
       cin>>item.rate;
       size=sizeof(item);
       fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
       break;
      case 4:
       system("cls");
       window(23,65,20,40);
       gotoxy(35,18);
      cout<<"EDIT RECORDS";
       gotoxy(25,24);
       cout<<" enter new quantity: ";
       cin>>item.quantity;
       size=sizeof(item);
       fseek(file,-size,1);
       fwrite(&item,sizeof(item),1,file);
       break;
     }
     gotoxy(27,30);
     cout<<"--- item edited---";
     break;
    }
   }
  }
 }
 if (flag==1){
  gotoxy(32,30);
  cout<<"item does not exist";
gotoxy(36,32);
  cout<<"TRY AGAIN";
 }
 getch();
 fclose(file);
 d_mainmenuForVendor();
}

//function to display in screen/
void display(product &item,int i,int j)
{
 gotoxy(16,i);
 printf("%4d",j);
 printf("%9s",item.name);
 printf("%12s",item.code);
 printf("%14.2f",item.rate);
 printf("%11d",item.quantity);
}

//function to display window for item display/
void dis_con()
{
 int i;
 system("cls");
 gotoxy(20,10);
 ;
 for (i=1;i<=10;i++)
  cout<<"*";
 cout<<" * CC * ";
 for (i=1;i<=10;i++)
        cout<<"*";
 cout<<endl<<endl;
 gotoxy(30,11);
 cout<<"Departmental Store";

 gotoxy(32,17);
 cout<<"RECORDS";
 gotoxy(18,23);
 cout<<"SN   Item Name   Item Code      Rate     Quantity";
}

//function to display by code/
void d_code()
{
  int i,j=1;
  char x[4]={0};
  FILE *file;
  dis_con();
  file=fopen("record2.txt","rb");
  rewind(file);
  i=26;
  gotoxy(16,20);
  cout<<"enter item code: ";
  scanf("%s",x);
  //cin.getline(x, 4);
  fflush(file);
  while(fread(&item,sizeof(item),1,file)){
  if((strcmp(item.code,x)==0)){
   //display(&item,i,j);
   i++;
   j++;
   break;
  }
  }
  if (i==26){
  gotoxy(28,30);
   cout<<"no item found";
  }
  getch();
  fclose(file);
  d_search();
}

//function to check validity of code while editing and deleting/
int check(char x[ANS])
{
 FILE *file;
 int flag=1;
 file=fopen("record2.txt","rb");
 rewind(file);
 while (fread(&item,sizeof (item),1,file)){
  if(strcmp(item.code,x)==0){
   flag=0;
   break;
  }
 }
 fclose(file);
 return flag;
 }

//function to add records/
void add ()
{
 FILE *file;
 char y[ACS],x[12];
 system("cls");
 gotoxy(25,25);cout<<"Enter new record(Y/N)?";
 while(toupper(getche())=='Y'){
  system("cls");
  file=fopen("record2.txt","ab");
  check_code(y);
  strcpy(item.code,y);
  gotoxy(22,28);cout<<"Enter rate of the item:";
  cin>>item.rate;
  gotoxy(22,30);cout<<"Enter quantity of the item:";
  cin>>item.quantity;
  gotoxy(22,32);cout<<"Enter name of the item:";
  cin>>item.name;
  fseek(file,0,SEEK_END);
  fwrite(&item,sizeof(item),1,file);
  fclose(file);
  gotoxy(22,34);cout<<"Enter new record(Y/N)?";
}
   d_mainmenuForVendor();
}

//start of main/
int main()
{
	window(25,50,20,32);
	gotoxy(28,23);
	cout<<"Enter 1 for Customer.";
	gotoxy(28,24);
	cout<<"Enter 2 for Vendor.";
	gotoxy(28,25);
	cout<<"Select your choice: ";
	int n;
	cin>>n;
	if(n==2){
		d_mainmenuForVendor();
	}

	else{
		d_mainmenuForCustomer();
	}

 return 0;
}

