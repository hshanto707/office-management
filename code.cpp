
//**********************************************************
//      INCLUDED HEADER FILES
//**********************************************************

#include <iostream>
#include <fstream>
#include <windows.h>
#include <process.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <algorithm>
using namespace std;

//**********************************************************
// TO SET CURSOR POSITION
//**********************************************************

COORD coord = {0, 0};
void gotoxy(int x, int y) {
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//**********************************************************
// THIS CLASS CONTAINS ALL THE DRAWING FUNCTIONS
//**********************************************************

class LINES {
public :
  void HORIZONTAL_LINE(int, int, int, char);
  void VERTICAL_LINE(int, int, int, char);
  void BOX(int,int,int,int,char);
};


//**********************************************************
// THIS CLASS CONTROL ALL THE FUNCTIONS IN THE MENU
//**********************************************************

class MENU {
private :
  void INTRODUCTION(void);
public :
  void MAIN_MENU(void);
};


//**********************************************************
// THIS CLASS CONTROL ALL THE FUNCTIONS RELATED TO EMPLOYEE
//**********************************************************

class EMPLOYEE {
private :
  void ADD_RECORD(int, string, string, string, int, int, int, string, int);
  void EDIT_RECORD(int, string, string, string, string, int);
  void DELETE_RECORD(int);
  int lastId(void);
  int idFound(int);
  int recordNo(int);
  int foundId(int);
  void DISPLAY_RECORD(int);
  int VALID_DATE(int, int, int);

  int id, dd, mm, yy;
  string name, address, phone, desig;
  int salary;

public :
  void NEW_EMPLOYEE(void);
  // void EDIT_EMPLOYEE(void);
  void DELETE_EMPLOYEE(void);
  void DISPLAY(void);
  void LIST(void);
  // void SALARY_SLIP(void);
};


//**********************************************************
// THIS FUNCTION CONTROL ALL THE FUNCTIONS IN THE MAIN MENU
//**********************************************************

void MENU :: MAIN_MENU(void) {
  char ch;
  LINES L;
  while (1) {
    system("cls");

    L.BOX(25, 7, 57, 9, 218);
    L.BOX(10, 5, 71, 21, 219);

    gotoxy(29, 8); cout << "Office Management System";
    gotoxy(30, 11); cout << "1. Add A New Employee";
    gotoxy(30, 12); cout << "2. Display An Employee";
    gotoxy(30, 13); cout << "3. Display All Employees";
    gotoxy(30, 14); cout << "4. Create Salary Slip";
    gotoxy(30, 15); cout << "5. Modify Employee";
    gotoxy(30, 16); cout << "6. Delete Employee";
    gotoxy(30, 17); cout << "#. Exit";
    gotoxy(30, 19); cout << "ENTER YOUR CHOICE :";

    ch = getch();

    if (ch == 27 || ch == '#') {
      system("cls");
      break;
    } else if (ch == '1') {
      EMPLOYEE E;
      E.NEW_EMPLOYEE();
    } else if (ch == '2') {
      EMPLOYEE E;
      E.DISPLAY();
    } else if (ch == '3') {
      EMPLOYEE E;
      E.LIST();
    } else if (ch == '4') {
      EMPLOYEE E;
      // E.SALARY_SLIP();
    } else if (ch == '5') {
      EMPLOYEE E;
      // E.EDIT_EMPLOYEE();
    } else if (ch == '6') {
      EMPLOYEE E;
      E.DELETE_EMPLOYEE();
    }
  }
}


//**********************************************************
// THIS FUNCTION DRAWS THE HORRIZONTAL LINE
//**********************************************************

void LINES :: HORIZONTAL_LINE(int column1, int column2, int row, char c) {
  for ( column1; column1<=column2; column1++ ) {
    gotoxy(column1,row);
    cout <<c;
  }
}


//**********************************************************
// THIS FUNCTION DRAWS THE VERTICAL LINE
//**********************************************************

void LINES :: VERTICAL_LINE(int row1, int row2, int column, char c) {
  for ( row1; row1<=row2; row1++ ) {
    gotoxy(column,row1);
    cout <<c;
  }
}


//**********************************************************
// THIS FUNCTION DRAWS THE BOX
//**********************************************************

void LINES :: BOX(int column1, int row1, int column2, int row2, char c) {
  char ch=218;
  char c1, c2, c3, c4;
  char l1=196, l2=179;
  if (c == ch) {
      c1=218;
      c2=191;
      c3=192;
      c4=217;
      l1 = 196;
      l2 = 179;
  } else {
      c1=c;
      c2=c;
      c3=c;
      c4=c;
      l1 = c;
      l2 = c;
  }
  gotoxy(column1,row1);
  cout <<c1;
  gotoxy(column2,row1);
  cout <<c2;
  gotoxy(column1,row2);
  cout <<c3;
  gotoxy(column2,row2);
  cout <<c4;
  column1++;
  column2--;
  HORIZONTAL_LINE(column1,column2,row1,l1);
  HORIZONTAL_LINE(column1,column2,row2,l1);
  column1--;
  column2++;
  row1++;
  row2--;
  VERTICAL_LINE(row1,row2,column1,l2);
  VERTICAL_LINE(row1,row2,column2,l2);
}


//**********************************************************
// ADDS DATA IN THE EMPLOYEE'S FILE
//**********************************************************

void EMPLOYEE :: ADD_RECORD(int eId, string eName, string eAddress, string ePhone, int d, int m, int y, string eDesig, int eSalary) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios::app);
  id = eId;

  name = eName;
  address = eAddress;
  phone = ePhone;
  dd = d;
  mm = m;
  yy = y;
  desig = eDesig;
  salary = eSalary;

  file.write((char *) this, sizeof(EMPLOYEE));
  file.close();
}


//**********************************************************
// MODIFY DATA IN THE EMPLOYEE'S FILE
//**********************************************************

void EMPLOYEE :: EDIT_RECORD(int eId, string eName, string eAddress, string ePhone, string eDesig, int eSalary) {
  int recNo;
  recNo = recordNo(eId);
  fstream file;
  file.open("EMPLOYEE.DAT", ios::out | ios::ate);

  name = eName;
  address = eAddress;
  phone = ePhone;
  desig = eDesig;
  salary = eSalary;

  int location;
  location = (recNo - 1) * sizeof(EMPLOYEE);

  file.seekp(location);
  file.write((char *) this, sizeof(EMPLOYEE));
  file.close();
}


//**********************************************************
// DELETE EMPLOYEE BY ID
//**********************************************************

void EMPLOYEE :: DELETE_RECORD(int eId) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios::in);

  fstream temp;
  temp.open("temp.dat", ios::out);
  file.seekg(0, ios::beg);

  while (!file.eof()) {
    file.read((char *) this, sizeof(EMPLOYEE));

    if (file.eof()) break;
    if (id != eId) temp.write((char *) this, sizeof(EMPLOYEE));
  }

  file.close();
  temp.close();
  file.open("EMPLOYEE.DAT", ios::out);
  temp.open("temp.dat", ios::in);
  temp.seekg(0, ios::beg);

  while (!temp.eof()) {
    temp.read((char *) this, sizeof(EMPLOYEE));
    if (temp.eof()) break;
    file.write((char *) this, sizeof(EMPLOYEE));
  }

  file.close();
  temp.close();
}


// ! **********************************************************
// !  GET THE LAST EMPLOYEE'S ID
// ! **********************************************************

int EMPLOYEE :: lastId(void) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios::in);
  file.seekg(0, ios::beg);
  int count = 0;

  while (file.read((char *) this, sizeof(EMPLOYEE))) count = id;

  file.close();
  return count;
}


// ! **********************************************************
// !  CHECK IF THE GIVEN ID IS FOUND OR NOT
// ! **********************************************************

int EMPLOYEE :: foundId(int eId) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios::in);
  file.seekg(0, ios::beg);
  int found=0;

  while (file.read((char *) this, sizeof(EMPLOYEE))) {
    if (id == eId) {
      found = 1;
      break;
    }
  }

  file.close();
  return found;
}


// ! **********************************************************
// !  GET RECORD NO. OF THE GIVEN ID
// ! **********************************************************

int EMPLOYEE :: recordNo(int eId) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios::in);
  file.seekg(0, ios::beg);
  int recNo=0;

  while (file.read((char *) this, sizeof(EMPLOYEE))) {
    recNo++;
    if (id == eId) break;
  }

  file.close();
  return recNo;
}


//**********************************************************
// THIS FUNCTION DISPLAYS THE LIST OF THE EMPLOYEES
//**********************************************************

void EMPLOYEE :: LIST(void) {
  system("cls");

  int row = 7, found = 0, flag = 0;
  char ch;

  gotoxy(36, 2); cout << "LIST OF EMPLOYEES";
  gotoxy(35, 3); cout << "~~~~~~~~~~~~~~~~~~~";
  gotoxy(1, 5); cout << "id   NAME                     PHONE            DOJ            DESIGNATION       SALARY";
  gotoxy(1, 6); cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

  fstream file;
  file.open("EMPLOYEE.DAT", ios::in);
  file.seekg(0,ios::beg);

  while (file.read((char *) this, sizeof(EMPLOYEE))) {
    flag = 0;
    Sleep(20);
    found = 1;
    gotoxy(2,row); cout <<id;
    gotoxy(6,row); cout <<name;
    gotoxy(31,row); cout <<phone;
    gotoxy(48,row); cout <<dd <<"/" <<mm <<"/" <<yy;
    gotoxy(63,row); cout <<desig;
    gotoxy(81,row); cout <<salary;

    if ( row == 23 ) {
      flag = 1;
      row = 6;
      gotoxy(1, 25); cout << "Press any key to continue or Press <ESC> to exit";
      ch = getch();
      if (ch == 27) break;
      system("cls");
      gotoxy(36, 2); cout << "LIST OF EMPLOYEES";
      gotoxy(35, 3); cout << "~~~~~~~~~~~~~~~~~~~";
      gotoxy(1, 5); cout << "id   NAME                     PHONE            DOJ            DESIGNATION       SALARY";
      gotoxy(1, 6); cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    } else row++;
  }

  if (!found) {
    gotoxy(5,10); cout <<"\7Records not found";
  }

  if (!flag) {
    gotoxy(1,25); cout <<"Press any key to continue...";
    getche();
  }
  file.close ();
}


// ! **********************************************************
// !  DISPLAY A RECORD
// ! **********************************************************

void EMPLOYEE :: DISPLAY_RECORD(int eId) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios::in);
  file.seekg(0,ios::beg);

  while (file.read((char *) this, sizeof(EMPLOYEE))) {
    if (id == eId) {
      gotoxy(5,5); cout <<"Employee id # " <<id;
      gotoxy(5,6); cout <<"~~~~~~~~~~~~~";
      gotoxy(5,7); cout <<"Name         : " <<name;
      gotoxy(5,8); cout <<"Address      : " <<address;
      gotoxy(5,9); cout <<"Phone no.    : " <<phone;
      
      gotoxy(5,11); cout <<"JOINING DATE";
      gotoxy(5,12); cout <<"~~~~~~~~~~~~";
      gotoxy(5,13); cout <<"Day   : " <<dd;
      gotoxy(5,14); cout <<"Month : " <<mm;
      gotoxy(5,15); cout <<"Year  : " <<yy;
      gotoxy(5, 17); cout << "Designation  : " << desig;
      gotoxy(5, 18); cout << "Salary        : " << salary;
    }
  }
  file.close();
}


//**********************************************************
// ADD A NEW EMPLOYEE
//**********************************************************

void EMPLOYEE :: NEW_EMPLOYEE(void) {
  system("cls");
    
  char ch;
  string eName, eAddress, ePhone, eDesig, t1;
  int eSalary = 0, d = 0, m = 0, y = 0, eId, valid;

  gotoxy(72,2); cout <<"<0>=EXIT";
  gotoxy(28,3); cout <<"ADDITION OF NEW EMPLOYEE";
  gotoxy(5,5); cout <<"Employee id # ";
  gotoxy(5,6); cout <<"~~~~~~~~~~~~~";
  gotoxy(5,7); cout <<"Name         : ";
  gotoxy(5,8); cout <<"Address      : ";
  gotoxy(5,9); cout <<"Phone no.    : ";

  gotoxy(5,11); cout <<"JOINING DATE";
  gotoxy(5,12); cout <<"~~~~~~~~~~~~";
  gotoxy(5,13); cout <<"Day   : ";
  gotoxy(5,14); cout <<"Month : ";
  gotoxy(5,15); cout <<"Year  : ";

  gotoxy(5, 17); cout << "OTHER INFO";
  gotoxy(5, 18); cout << "~~~~~~~~~~~~";
  gotoxy(5,19); cout <<"Designation  : ";
  gotoxy(5, 20); cout << "Salary       : ";

  eId = lastId() + 1;

  if (eId == 1) {
    ADD_RECORD(eId, "null", "null", "null", 0, 0, 0, "null", 0);
    DELETE_RECORD(eId);
  }

  gotoxy(21,5); cout <<eId;

  // ! TAKING EMPLOYEE NAME
    
  do {
    valid = 1;
    gotoxy(5,25); "\033[K";
    cout <<"Enter the name of the Employee";
    gotoxy(20,7); "\033[K";
    
    getline(cin, eName);
    transform(eName.begin(), eName.end(), eName.begin(), ::toupper);
    
    if (eName[0] == '0') return;
    if (eName.size() < 5) {
      valid = 0;
      gotoxy(5,25); "\033[K";
      cout << "\7Name can not be less than 5 characters";
      getch();
    }
  } while (!valid);

  // ! TAKING EMPLOYEE ADDRESS

  do {
    valid = 1;
    gotoxy(5,25);
    "\033[K";
    cout <<"Enter Address of the Employee";
    gotoxy(20,8);
    "\033[K";

    getline(cin, eAddress);
    transform(eAddress.begin(), eAddress.end(), eAddress.begin(), ::toupper);

    if (eAddress[0] == '0') return;
    if (eAddress.size() < 5) {
      valid = 0;
      gotoxy(5,25); "\033[K";
      cout << "\7Address can not be less than 5 characters";
      getch();
    }
  } while (!valid);

  // ! TAKING EMPLOYEE PHONE NUMBER

  do {
    valid = 1;
    gotoxy(5,25); "\033[K";
    cout <<"Enter Phone no. of the Employee";
    gotoxy(20,9); "\033[K";

    getline(cin, ePhone);

    if (ePhone[0] == '0') return;
    if (ePhone.size() < 3) {
      valid = 0;
      gotoxy(5,25); "\033[K";
      cout <<"\7Enter a valid number";
      getch();
    }
  } while (!valid);

  //! TAKING EMPLOYEE JOINING DATE

  string tday, tmonth, tyear;

  do {
    valid = 1;
    do {
      gotoxy(5,25); "\033[K";
      cout <<"ENTER DAY OF JOINING";
      gotoxy(13,13); "\033[K";
      
      cin >> tday;
      d = stoi(tday);
      
      if (tday[0] == '0') return;
    } while (d == 0);

    do {
      gotoxy(5,25); "\033[K";
      cout <<"ENTER MONTH OF JOINING";
      gotoxy(13,14); "\033[K";
      cin >> tmonth;
      m = stoi(tmonth);
      if (tmonth[0] == '0') return;
    } while (m == 0);

    do {
      gotoxy(5,25); "\033[K";
      cout <<"ENTER YEAR OF JOINING";
      gotoxy(13,15); "\033[K";
      cin >> tyear;
      y = stoi(tyear);
      if (tyear[0] == '0') return;
    } while (y == 0);

    if (d>31 || d<1) valid = 0;
    else if (((y%4)!=0 && m==2 && d>28) || ((y%4)==0 && m==2 && d>29)) valid = 0;
    else if ((m==4 || m==6 || m==9 || m==11) && d>30) valid = 0;
    else if (y<1990 || y>2023) valid = 0;

    if (!valid) {
      valid = 0;
      gotoxy(5,25); "\033[K";
      cout <<"\7Enter correctly";
      getch();
    }
  } while (!valid);

  do {
    valid = 1;
    gotoxy(5,25); "\033[K";
    cout <<"Enter Designation of the Employee";
    gotoxy(20,19); "\033[K";

    getline(cin, eDesig);
    transform(eDesig.begin(), eDesig.end(), eDesig.begin(), ::toupper);

    if (eDesig[0] == '0') return;
    if (eDesig.size() < 1 || eDesig.size() > 15) {
      valid = 0;
      gotoxy(5,25); "\033[K";
      cout <<"\7Designation must be under 15 characters";
      getch();
    }
  } while (!valid);

  // ! TAKING EMPLOYEE SALARY
  
  do {
    valid = 1;
    gotoxy(5, 25); "\033[K";
    cout << "Enter Salary of the Employee";
    gotoxy(20, 20); "\033[K";

    cin >> eSalary;

    if (eSalary == 0) return;
    if (eSalary > 50000) {
      valid = 0;
      gotoxy(5, 25); "\033[K";
      cout << "\7SALARY SHOULD NOT GREATER THAN 50000                         ";
      getch();
    }
  } while (!valid);

  gotoxy(5, 25); "\033[K";

  do {
    gotoxy(5,25); "\033[K";
    cout <<"Do you want to save (y/n) ";
    ch = getche();
    ch = toupper(ch);
    if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return;
  
  ADD_RECORD(eId, eName, eAddress, ePhone, d, m, y, eDesig, eSalary);
}


//**********************************************************
// THIS FUNCTION GIVE id FOR THE DISPLAY OF THE RECORD
//**********************************************************

void EMPLOYEE :: DISPLAY(void)
{
    system("cls");
    char t1[10];
    int t2, eId;
    gotoxy(72,2);
    cout <<"<0>=EXIT";
    gotoxy(5,5);
    cout <<"Enter id of the Employee  ";
    gets(t1);
    t2 = atoi(t1);
    eId = t2;
    if (eId == 0)
        return;
    system("cls");
    if (!foundId(eId))
    {
        gotoxy(5,5);
        cout <<"\7Record not found";
        getch();
        return;
    }
    DISPLAY_RECORD(eId);
    gotoxy(5,25);
    cout <<"Press any key to continue...";
    getch();
}


//**********************************************************
// THIS FUNCTION GIVE DATA FOR THE EDIT_EMPLOYEE OF THE
// EMPLOYEE RECORD
//**********************************************************

// void EMPLOYEE :: EDIT_EMPLOYEE(void) {
//   system("cls");
//   char ch;
//   string eName, eAddress, ePhone, eDesig;
//   int eSalary = 0;
//   int eId, valid;

//   gotoxy(72,2); cout <<"<0>=EXIT";
//   gotoxy(5,5); cout <<"Enter id of the Employee  ";

//   cin >> eId;
//   if (eId == 0) return;
//   system("cls");

//   if (!foundId(eId)) {
//     gotoxy(5,5); cout <<"\7Record not found";
//     getch();
//     return;
//   }

//   gotoxy(72,2); cout <<"<0>=EXIT";
//   gotoxy(22,3); cout <<"EDIT_EMPLOYEE OF THE EMPLOYEE RECORD";
//   DISPLAY_RECORD(eId);

//   do {
//     gotoxy(5,24); "\033[K";
//     cout <<"Do you want to modify this record (y/n) ";
//     ch = getche();
//     ch = toupper(ch);
//     if (ch == '0') return;
//   } while (ch != 'Y' && ch != 'N');
  
//   if (ch == 'N') return;
//   system("cls");

//   fstream file;
//   file.open("EMPLOYEE.DAT", ios::in);
//   file.seekg(0,ios::beg);
  
//   while (file.read((char *) this, sizeof(EMPLOYEE))) {
//     if (id == eId) break;
//   }

//   file.close();

//   gotoxy(5,5); cout <<"Employee id # " <<eId;
//   gotoxy(5,6); cout <<"~~~~~~~~~~~~~";
//   gotoxy(40,5); cout <<"JOINING DATE : ";
//   gotoxy(40,6); cout <<"~~~~~~~~~~~~~~";
//   gotoxy(55,5); cout <<dd <<"/" <<mm <<"/" <<yy;
//   gotoxy(5,7); cout <<"Name         : ";
//   gotoxy(5,8); cout <<"Address      : ";
//   gotoxy(5,9); cout <<"Phone no.    : ";
//   gotoxy(5,10); cout <<"Designation  : ";
//   gotoxy(5,11);
//   cout <<"Grade        : ";
//   gotoxy(5,14);
//   cout <<"Loan           : ";

//   // ! MODIFYING EMPLOYEE NAME

//   do {
//     valid = 1;

//     gotoxy(5,25); "\033[K";
//     cout <<"Enter the name of the Employee or <ENTER> FOR NO CHANGE";
//     gotoxy(20,7); "\033[K";

//     getline(cin, eName);
//     transform(eName.begin(), eName.end(), eName.begin(), ::toupper);
    
//     if (eName[0] == '0') return;

//     if (eName.size() < 5) {
//       valid = 0;
//       gotoxy(5,25); "\033[K";
//       cout <<"\7Name can not be less than 5 characters";
//       getch();
//     }
//   } while (!valid);

//   if (eName.size() == 0) {
//     eName = name;
//     gotoxy(20, 7); cout << eName;
//   }

//     do
//     {
//         valid = 1;
//         gotoxy(5,25);
//         "\033[K";
//         cout <<"Enter Address of the Employee or <ENTER> FOR NO CHANGE";
//         gotoxy(20,8);
//         "\033[K";
//         gets(eAddress);
//         strupr(eAddress);
//         if (eAddress[0] == '0')
//             return;
//         if (strlen(eAddress) > 30)
//         {
//             valid = 0;
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"\7Enter correctly (Range: 1..30)";
//             getch();
//         }
//     }
//     while (!valid);
//     if (strlen(eAddress) == 0)
//     {
//         strcpy(eAddress,address);
//         gotoxy(20,8);
//         cout <<eAddress;
//     }
//     do
//     {
//         valid = 1;
//         gotoxy(5,25);
//         "\033[K";
//         cout <<"Enter Phone no. of the Employee or or <ENTER> FOR NO CHANGE";
//         gotoxy(20,9);
//         "\033[K";
//         gets(ePhone);
//         if (ePhone[0] == '0')
//             return;
//         if ((strlen(ePhone) < 7 && strlen(ePhone) > 0) || (strlen(ePhone) > 9))
//         {
//             valid = 0;
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"\7Enter correctly";
//             getch();
//         }
//     }
//     while (!valid);
//     if (strlen(ePhone) == 0)
//     {
//         strcpy(ePhone,phone);
//         gotoxy(20,9);
//         cout <<ePhone;
//     }
//     do
//     {
//         valid = 1;
//         gotoxy(5,25);
//         "\033[K";
//         cout <<"Enter Designation of the Employee or <ENTER> FOR NO CHANGE";
//         gotoxy(20,10);
//         "\033[K";
//         gets(eDesig);
//         strupr(eDesig);
//         if (eDesig[0] == '0')
//             return;
//         if (strlen(eDesig) > 15)
//         {
//             valid = 0;
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"\7Enter correctly (Range: 1..15)";
//             getch();
//         }
//     }
//     while (!valid);
//     if (strlen(eDesig) == 0)
//     {
//         strcpy(eDesig,desig);
//         gotoxy(20,10);
//         cout <<eDesig;
//     }
//     do
//     {
//         gotoxy(5,25);
//         "\033[K";
//         cout <<"Enter Grade of the Employee (A,B,C,D,E) or <ENTER> FOR NO CHANGE";
//         gotoxy(20,11);
//         "\033[K";
//         egrade = getche();
//         egrade = toupper(egrade);
//         if (egrade == '0')
//             return;
//         if (egrade == 13)
//         {
//             egrade = grade;
//             gotoxy(20,11);
//             cout <<grade;
//         }
//     }
//     while (egrade < 'A' || egrade > 'E');
//     if (egrade != 'E')
//     {
//         gotoxy(5,12);
//         cout <<"House (y/n)    : ";
//         gotoxy(5,13);
//         cout <<"Convense (y/n) : ";
//         gotoxy(5,15);
//         cout <<"Basic Salary   : ";
//         do
//         {
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"ALLOTED HOUSE ALLOWANCE ? or <ENTER> FOR NO CHANGE";
//             gotoxy(22,12);
//             "\033[K";
//             ehouse = getche();
//             ehouse = toupper(ehouse);
//             if (ehouse == '0')
//                 return;
//             if (ehouse == 13)
//             {
//                 ehouse = house;
//                 gotoxy(22,12);
//                 cout <<ehouse;
//             }
//         }
//         while (ehouse != 'Y' && ehouse != 'N');
//         do
//         {
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"ALLOTED CONVENCE ALLOWANCE or <ENTER> FOR NO CHANGE";
//             gotoxy(22,13);
//             "\033[K";
//             econv = getche();
//             econv = toupper(econv);
//             if (econv == '0')
//                 return;
//             if (econv == 13)
//             {
//                 econv = convense;
//                 gotoxy(22,13);
//                 cout <<econv;
//             }
//         }
//         while (econv != 'Y' && econv != 'N');
//     }
//     do
//     {
//         valid = 1;
//         gotoxy(5,25);
//         "\033[K";
//         cout <<"ENTER LOAN AMOUNT or <ENTER> FOR NO CHANGE";
//         gotoxy(22,14);
//         "\033[K";
//         gets(t1);
//         t2 = atof(t1);
//         eloan = t2;
//         if (eloan > 50000)
//         {
//             valid = 0;
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"\7SHOULD NOT GREATER THAN 50000";
//             getch();
//         }
//     }
//     while (!valid);
//     if (strlen(t1) == 0)
//     {
//         eloan = loan;
//         gotoxy(22,14);
//         cout <<eloan;
//     }
//     if (egrade != 'E')
//     {
//         do
//         {
//             valid = 1;
//             gotoxy(5,25);
//             "\033[K";
//             cout <<"ENTER BASIC SALARY or <ENTER> FOR NO CHANGE";
//             gotoxy(22,15);
//             "\033[K";
//             gets(t1);
//             t2 = atof(t1);
//             ebasic = t2;
//             if (t1[0] == '0')
//                 return;
//             if (ebasic > 50000)
//             {
//                 valid = 0;
//                 gotoxy(5,25);
//                 "\033[K";
//                 cout <<"\7SHOULD NOT GREATER THAN 50000";
//                 getch();
//             }
//         }
//         while (!valid);
//         if (strlen(t1) == 0)
//         {
//             ebasic = basic;
//             gotoxy(22,15);
//             cout <<ebasic;
//         }
//     }
//     gotoxy(5,25);
//     "\033[K";
//     do
//     {
//         gotoxy(5,18);
//         "\033[K";
//         cout <<"Do you want to save (y/n) ";
//         ch = getche();
//         ch = toupper(ch);
//         if (ch == '0')
//             return;
//     }
//     while (ch != 'Y' && ch != 'N');
//     if (ch == 'N')
//         return;
//     EDIT_RECORD(eId,eName,eAddress,ePhone,eDesig,egrade,ehouse,econv,eloan,ebasic);
//     gotoxy(5,23);
//     cout <<"\7Record Modified";
//     gotoxy(5,25);
//     cout <<"Press any key to continue...";
//     getch();
// }


//**********************************************************
// THIS FUNCTION GIVE id NO. FOR THE DELETE_EMPLOYEE OF THE
// EMPLOYEE RECORD
//**********************************************************

void EMPLOYEE :: DELETE_EMPLOYEE(void)
{
    system("cls");
    char t1[10], ch;
    int t2, eId;
    gotoxy(72,2);
    cout <<"<0>=EXIT";
    gotoxy(5,5);
    cout <<"Enter id of the Employee  ";
    gets(t1);
    t2 = atoi(t1);
    eId = t2;
    if (eId == 0)
        return;
    system("cls");
    if (!foundId(eId))
    {
        gotoxy(5,5);
        cout <<"\7Record not found";
        getch();
        return;
    }
    gotoxy(72,2);
    cout <<"<0>=EXIT";
    gotoxy(24,3);
    cout <<"DELETE_EMPLOYEE OF THE EMPLOYEE RECORD";
    DISPLAY_RECORD(eId);
    do
    {
        gotoxy(5,24);
        "\033[K";
        cout <<"Do you want to delete this record (y/n) ";
        ch = getche();
        ch = toupper(ch);
        if (ch == '0')
            return;
    }
    while (ch != 'Y' && ch != 'N');
    if (ch == 'N')
        return;
    DELETE_RECORD(eId);
    LINES L;
    gotoxy(5,23);
    cout <<"\7Record Deleted";
    gotoxy(5,25);
    cout <<"Press any key to continue...";
    getch();
}


//**********************************************************
// THIS FUNCTION RETURN 0 IF THE GIVEN DATE IS INVALID
//**********************************************************

int EMPLOYEE :: VALID_DATE(int d1, int m1, int y1) {
  int valid=1;
  if (d1>31 || d1<1) valid = 0;
  else if (((y1%4)!=0 && m1==2 && d1>28) || ((y1%4)==0 && m1==2 && d1>29)) valid = 0;
  else if (m1 > 12 || m1 < 1) valid = 0;
  else if ((m1==4 || m1==6 || m1==9 || m1==11) && d1>30) valid = 0;
  return valid;
}


//**********************************************************
// THIS FUNCTION PRINTS THE SALARY SLIP FOR THE EMPLOYEE
//**********************************************************

// void EMPLOYEE :: SALARY_SLIP(void) {
//   system("cls");
//   char t1[10];
//   int t2, eId, valid;
//   gotoxy(72,2);
//   cout <<"<0>=EXIT";
//   gotoxy(5,5);
//   cout <<"Enter ID of the Employee  ";
//   gets(t1);
//   t2 = atoi(t1);
//   eId = t2;
//   if (eId == 0)
//       return;
//   system("cls");
//   if (!foundId(eId))
//   {
//       gotoxy(5,5);
//       cout <<"\7Record not found";
//       getch();
//       return;
//   }
//   fstream file;
//   file.open("EMPLOYEE.DAT", ios::in);
//   file.seekg(0,ios::beg);
//   while (file.read((char *) this, sizeof(EMPLOYEE))) {
//     if (id == eId) break;
//   }
//   file.close();
//   int d1 = 1, m1 = 1, y1 = 1;
//   // struct date d;
//   // getdate(&d);
//   // d1 = d.da_day;
//   // m1 = d.da_mon;
//   // y1 = d.da_year;
//   char *mon[12]= {"January","February","March","April","May","June","July","August","September","November","December"};
//   LINES L;
//   L.BOX(2,1,79,25,219);
//   gotoxy(31,2);
//   cout <<"NADEEM AKHTAR, PGDBA - 200754667";
//   L.HORIZONTAL_LINE(3,78,3,196);
//   gotoxy(34,4);
//   cout <<"SALARY SLIP";
//   gotoxy(60,4);
//   cout <<"Date: " <<d1 <<"/" <<m1 <<"/" <<y1;
//   gotoxy(34,5);
//   cout <<mon[m1-1] <<", " <<y1;
//   L.HORIZONTAL_LINE(3,78,6,196);
//   gotoxy(6,7);
//   cout <<"Employee Name : " <<name;
//   gotoxy(6,8);
//   cout <<"Designation   : " <<desig;
//   gotoxy(67,8);
//   cout <<"Grade : " <<grade;
//   L.BOX(6,9,75,22,218);
//   L.HORIZONTAL_LINE(10,71,20,196);
//   int days, hours;
//   if (grade == 'E') {
//     do {
//       valid = 1;
//       gotoxy(10,21);
//       cout <<"ENTER NO. OF DAYS WORKED IN THE MONTH ";
//       gotoxy(10,11);
//       cout <<"No. of Days   : ";
//       gets(t1);
//       t2 = atof(t1);
//       days = t2;
//       if (!VALID_DATE(days,m1,y1)) {
//         valid = 0;
//         gotoxy(10,21);
//         cout <<"\7ENTER CORRECTLY                       ";
//         getch();
//         gotoxy(10,11);
//         cout <<"                    ";
//       }
//     } while (!valid);
//     do {
//       valid = 1;
//       gotoxy(10,21);
//       cout <<"ENTER NO. OF HOURS WORKED OVER TIME   ";
//       gotoxy(10,13);
//       cout <<"No. of hours  : ";
//       gets(t1);
//       t2 = atof(t1);
//       hours = t2;
//       if (hours > 8 || hours < 0) {
//         valid = 0;
//         gotoxy(10,21);
//         cout <<"\7ENTER CORRECTLY                     ";
//         getch();
//         gotoxy(10,13);
//         cout <<"                    ";
//       }
//     } while (!valid);
//     gotoxy(10,21);
//     cout <<"                                               ";
//     gotoxy(10,11);
//     cout <<"                        ";
//     gotoxy(10,13);
//     cout <<"                        ";
//   }
//   gotoxy(10,10);
//   cout <<"Basic Salary         : Rs.";
//   gotoxy(10,12);
//   cout <<"ALLOWANCE";
//   if (grade != 'E') {
//     gotoxy(12,13);
//     cout <<"HRA  : Rs.";
//     gotoxy(12,14);
//     cout <<"CA   : Rs.";
//     gotoxy(12,15);
//     cout <<"DA   : Rs.";
//   } else {
//     gotoxy(12,13);
//     cout <<"OT   : Rs.";
//   }
//   gotoxy(10,17);
//   cout <<"DEDUCTIONS";
//   gotoxy(12,18);
//   cout <<"LD   : Rs.";
//   if (grade != 'E') {
//     gotoxy(12,19);
//     cout <<"PF   : Rs.";
//   }
//   gotoxy(10,21);
//   cout <<"NET SALARY           : Rs.";
//   gotoxy(6,24);
//   cout <<"CASHIER";
//   gotoxy(68,24);
//   cout <<"EMPLOYEE";
//   float HRA=0.0, CA=0.0, DA=0.0, PF=0.0, LD=0.0, OT=0.0, allowance, deduction, netsalary;
//   if (grade != 'E') {
//     if (house == 'Y')
//       HRA = (5*basic)/100;
//     if (convense == 'Y')
//       CA  = (2*basic)/100;
//     DA  = (5*basic)/100;
//     PF  = (2*basic)/100;
//     LD  = (15*loan)/100;
//     allowance = HRA+CA+DA;
//     deduction = PF+LD;
//   } else {
//     basic = days * 30;
//     LD  = (15*loan)/100;
//     OT  = hours * 10;
//     allowance = OT;
//     deduction = LD;
//   }
//   netsalary = (basic+allowance)-deduction;
//   gotoxy(36,10);
//   cout <<basic;
//   if (grade != 'E') {
//     gotoxy(22,13);
//     cout <<HRA;
//     gotoxy(22,14);
//     cout <<CA;
//     gotoxy(22,15);
//     cout <<DA;
//     gotoxy(22,19);
//     cout <<PF;
//   }
//   else {
//     gotoxy(22,13);
//     cout <<OT;
//   }
//   gotoxy(22,18);
//   cout <<LD;
//   gotoxy(33,15);
//   cout <<"Rs." <<allowance;
//   gotoxy(33,19);
//   cout <<"Rs." <<deduction;
//   gotoxy(36,21);
//   cout <<netsalary;
//   gotoxy(2,1);
//   getch();
// }


//**********************************************************
// MAIN FUNCTION CALLING MAIN MENU
//**********************************************************

int main(void) {
  MENU menu;
  menu.MAIN_MENU();

  return 0;
}
