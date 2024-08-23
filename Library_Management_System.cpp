#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<conio.h>
using namespace std;

class Book {
    public:
        char bookname[100],auname[50],sc[20];
        int q,B,p;
       Book()
       {
           strcpy(bookname,"NO Book Name");
           strcpy(auname,"No Author Name");
           strcpy(sc,"No Book ID");       
           q=0;
           B=0;
           p=0;
       }
       
    void getbook();
    void show(int);   

};

class Lib : public  Book
{
   public:       
          void get();                    
          void librarian();  
          void booklist(int);         
          void modify();         
          int branch(int);
          void issue();
          void der(char[],int,int);          
          void see(int);
          void Mem();          
          
};
class Member: public Lib
{
    public:
        char memberName[100], memberID[20];        
        void mbr();
        void showMember();
        void addMember();
        void removeMember();
        void updateMember();
        void memberList();
};

void Book::show(int i)
{
    cout<<"\n\t\tBook Name : "<<bookname<<endl;
    cout<<"\n\t\tBook's Author Name : "<<auname<<endl;
    cout<<"\n\t\tBook's ID : "<<sc<<endl;
    
    if(i==2)
    {
        cout<<"\n\t\tBook's Price : "<<p<<endl;
        cout<<"\n\t\tBook's Quantity : "<<q<<endl;
    }
}
  void Lib::booklist(int i)
  {
                int b,r=0;
                system("cls");
                b=branch(i);
                system("cls");
                ifstream intf("Booksdata.txt",ios::binary);
                if(!intf)
                    cout<<"\n\t\tFile Not Found.";
                else
                {
                    cout<<"\n\t    ************ Book List ************ \n\n";
                    intf.read((char*)this,sizeof(*this));
                while(!intf.eof())
                {
                    if(b==B)
                    {
                        if(q!=0)                       
                            {
                                r++;
                                cout<<"\n\t\t********** "<<r<<". ********** \n";
                                show(i);
                            }
                            else{
                                cout<<"Book not available";
                            }
                    }
                    intf.read((char*)this,sizeof(*this));
                }
                }
                cout<<"\n\t\tPress any key to continue.....";
                getch();
                system("cls");
                if(i==1)
                    Mem();
                else
                    librarian();
    }
  void Lib::modify()
  {
    char st1[100];
    int i=0,b,cont=0;
    system("cls");
    cout<<"\n\t\t>>Please Choose one option :-\n";
    cout<<"\n\t\t1.Modification In Current Books\n\n\t\t2.Add New Book\n\n\t\t3.Delete A Book\n\n\t\t4.Go back\n";
    cout<<"\n\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1)
    {
                    system("cls");
                    b=branch(2);
                    ifstream intf1("Booksdata.txt",ios::binary);
                    if(!intf1)
                    {
                        cout<<"\n\t\tFile Not Found\n";
                        cout<<"\n\t\tPress any key to continue.....";
                        getch();
                        system("cls");
                        librarian();
                    }                    
                        intf1.close();
                        system("cls");
                        fflush(stdin);
                        cout<<"\n\t\tEnter Book's ID : ";
                        cin.getline(st1,100);
                        system("cls");
                                fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);
                                intf.seekg(0);
                                intf.read((char*)this,sizeof(*this));
                                while(!intf.eof())
                                    {
                                        for(i=0;b==B&&sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);
                                        if(sc[i]=='\0'&&st1[i]=='\0')
                                            {
                                                cont++;
                                                getbook();
                                                intf.seekp(intf.tellp()-sizeof(*this));
                                                intf.write((char*)this,sizeof(*this));
                                                break;
                                            }
                                        intf.read((char*)this,sizeof(*this));
                                    }

                                intf.close();                      
                   
                        if(cont==0)
                        {
                            cout<<"\n\t\tBook Not Found.\n";
                            cout<<"\n\t\tPress any key to continue.....";
                            getch();
                            system("cls");
                            modify();
                        }
                        else
                            cout<<"\n\t\tUpdate Successful.\n";

    }
    else if(i==2)
    {
                    system("cls");
                    B=branch(2);
                    system("cls");
                    getbook();
                    ofstream outf("Booksdata.txt",ios::app|ios::binary);
                    outf.write((char*)this,sizeof(*this));
                    outf.close();
                    cout<<"\n\t\tBook added Successfully.\n";
    }
    else if(i==3)
    {                    
                     b=branch(2);
                    ifstream intf1("Booksdata.txt",ios::binary);
                    if(!intf1)
                    {
                        cout<<"\n\t\tFile Not Found\n";
                        cout<<"\n\t\tPress any key to continue.....";
                        getch();
                        intf1.close();
                        system("cls");
                        librarian();
                    }
                        intf1.close();                    

      system("cls");      
      cout<<"\n\t\tSearch By Book's ID\n";  
      fflush(stdin);  
      fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);
    intf.seekg(0);
    intf.read((char*)this,sizeof(*this));
             
          cout<<"\n\t\tEnter Book's ID : ";
          cin.getline(st1,100);
          system("cls");
          while(!intf.eof())
          {
              for(i=0;b==B&&q!=0&&sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);
              if(sc[i]=='\0'&&st1[i]=='\0')
                {                            
                            cont++;
                            q=0;                            
                            intf.seekp(intf.tellp()-sizeof(*this));
                            intf.write((char*)this,sizeof(*this));
                            break;
                }
               intf.read((char*)this,sizeof(*this));
          }          
          intf.close();                                            
                        if(cont==0)
                        {
                            cout<<"\n\t\tBook Not Found.\n";
                            cout<<"\n\t\tPress any key to continue.....";
                            getch();
                            system("cls");
                            modify();
                        }
                        else
                            cout<<"\n\t\tDeletion Successful.\n";

    }
    else if(i==4)
    {
    system("cls");
    librarian();
    }
    else
    {
    cout<<"\n\t\tWrong Input.\n";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    modify();
    }
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    librarian();

  }
  int Lib::branch(int x)
  {
      int i;
      cout<<"\n\t\t>>Please Choose one Branch :-\n";
      cout<<"\n\t\t1.Maths\n\n\t\t2.English\n\n\t\t3.Science\n\n\t\t4.CIVIL\n\n\t\t5.MECHANICAL\n\n\t\t6.CSE\n\n\t\t7.Go to menu\n";
      cout<<"\n\t\tEnter youur choice : ";
      cin>>i;
      switch(i)
      {
          case 1: return 1;
                  break;
          case 2: return 2;
                  break;
          case 3: return 3;
                  break;
          case 4: return 4;
                  break;
          case 5: return 5;
                  break;
          case 6: return 6;
                  break;
          case 7: system("cls");
                  if(x==1)
                  Mem();
                  else
                    librarian();
          default : cout<<"\n\t\tPlease enter correct option :(";
                    getch();
                    system("cls");
                    branch(x);
        }
        return 0;
  }
  void Lib::see(int x)
  {
      int i,b,cont=0;
      char ch[100];
      system("cls");
      b=branch(x);
      ifstream intf("Booksdata.txt",ios::binary);
        if(!intf)
        {
            cout<<"\n\t\tFile Not Found.\n";
            cout<<"\n\t\t->Press any key to continue.....";
            getch();
            system("cls");
            if(x==1)
            Mem();
            else
            librarian();
        }
      system("cls");      
      cout<<"\n\t\tSearch By Book's ID\n";  
      fflush(stdin);  
      intf.read((char*)this,sizeof(*this));       
          cout<<"\n\t\tEnter Book's ID : ";
          cin.getline(ch,100);
          system("cls");
          while(!intf.eof())
          {
              for(i=0;b==B&&q!=0&&sc[i]!='\0'&&ch[i]!='\0'&&ch[i]==sc[i];i++);
              if(sc[i]=='\0'&&ch[i]=='\0')
                {
                            cout<<"\n\t\tBook Found :-\n";
                            show(x);
                            cont++;
                            break;
                }
               intf.read((char*)this,sizeof(*this));
          }         
       
          intf.close();
          if(cont==0)
              cout<<"\n\t\tThis Book is not available :( \n";

    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    if(x==1)
    Mem();
    else
    librarian();

  }
void Lib::issue()
{
    char st1[20],sc1[10];
    int b,i,j,d,m,y,cont=0;
    system("cls");
    cout<<"\n\t\t->Please Choose one option :-\n";
    cout<<"\n\t\t1.Issue Book\n\n\t\t2.View Issued Book\n\n\t\t3.Return Book\n\n\t\t4.Go back to menu\n\n\t\tEnter Your Choice : ";
    cin>>i;
    fflush(stdin);
    if(i==1)
    {
    system("cls");
    b=branch(2);
    system("cls");
    fflush(stdin);
    cout<<"\n\t\t->Please Enter Details :-\n";
    cout<<"\n\t\tEnter Book's ID : ";
    cin.getline(sc,20);
    //strcpy(st,sc);
    der(sc,b,1);
    cout<<"\n\t\tEnter Member Name : ";
    cin.getline(auname,100);
    cout<<"\n\t\tEnter date : ";
    cin>>q>>B>>p;
    ofstream outf("Mem.txt",ios::binary|ios::app);
    outf.write((char*)this,sizeof(*this));
    outf.close();
    cout<<"\n\n\t\tIssue Successfully.\n";
    }
    else if(i==2)
    {
    ifstream intf("Mem.txt",ios::binary);
    system("cls");
    cout<<"\n\t\t->The Details are :-\n";
    intf.read((char*)this,sizeof(*this));
    i=0;
    while(!intf.eof())
    {
    i++;
    cout<<"\n\t\t********** "<<i<<". ********** \n";
    cout<<"\n\t\tMember Name : "<<auname<<"\n\t\t"<<"Book Name : "<<bookname<<"\n\t\t"<<"Book's ID : "<<sc<<"\n\t\t"<<"Date : "<<q<<"/"<<B<<"/"<<p<<"\n";
    intf.read((char*)this,sizeof(*this));
    }
    intf.close();
    }
    
    else if(i==3)
    {
    system("cls");
    b=branch(2);
    system("cls");
    fflush(stdin);
    cout<<"\n\t\t->Please Enter Details :-\n";
    cout<<"\n\t\tEnter Book's ID : ";
    cin.getline(st1,20);
    der(st1,b,2);
    cout<<"\n\t\tEnter Present date : ";
    cin>>d>>m>>y;
    ofstream outf("temp.txt",ios::app|ios::binary);
    ifstream intf("Mem.txt",ios::binary);
    intf.read((char*)this,sizeof(*this));
    while(!intf.eof())
        {
            for(i=0;sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);
            for(j=0;sc1[j]!='\0';j++);
            if(sc[i]=='\0'&&sc1[j]=='\0'&&st1[i]=='\0'&&cont==0)
                {
                    cont++;
                    intf.read((char*)this,sizeof(*this));                 
                    cout<<"\n\t\tReturned successfully.";
                    
                }
            else
                {
                    cout<<"Book not found";
                    outf.write((char*)this,sizeof(*this));
                    intf.read((char*)this,sizeof(*this));
                }
        }

    intf.close();
    outf.close();
    getch();
    remove("Mem.txt");
    rename("temp.txt","Mem.txt");
    }
    else if(i==4)
    {
    system("cls");
    librarian();
    }
    else
        cout<<"\n\t\tWrong Input.\n";

    cout<<"\n\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    librarian();
}
void Lib::der(char st[],int b,int x)
{
    int i,cont=0;
    fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);
    intf.seekg(0);
    intf.read((char*)this,sizeof(*this));
    while(!intf.eof())
    {
        for(i=0;b==B&&sc[i]!='\0'&&st[i]!='\0'&&st[i]==sc[i];i++);
        if(sc[i]=='\0'&&st[i]=='\0')
        {     
            if(x==1 && q>0)
            {      
                cont++;        
                q--;
            }
            else{
                if(x==2)
                {
                    q++;
                    cont++;
                }                
            }            
            intf.seekp(intf.tellp()-sizeof(*this));
            intf.write((char*)this,sizeof(*this));
            break;
        }
        intf.read((char*)this,sizeof(*this));
    }    
    if(cont==0)
    {
        cout<<"\n\t\tBook not found.\n";
        cout<<"\n\n\t\tPress any key to continue.....";
        getch();
        system("cls");
        issue();
    }
    intf.close();
}
void Lib::get()
{
   int i;
   string password;
        cout<<"\n\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n"<<"\n\t\t\t    L M S C++\n";
        cout<<"\n\t\t>>Please Choose Any Option To login \n";
        cout<<"\n\t\t1.Member\n\n\t\t2.Librarian\n\n\t\t3.Close Application\n";
        cout<<"\n\t\tEnter your choice : ";
        cin>>i;
        if(i==1)
        {
            system("cls");
            Mem();
        }
        else if(i==2)
        {
        cout << "Enter password: ";
        cin >> password;

        if (password == "pass") 
            { // Use a simple password for demonstration purposes.
                 system("cls");
                 librarian();
            } else {
            cout << "Incorrect password.\n";\
             getch();
             system("CLS");
             get();
                    }
        }      
}
void Member::mbr()
{
    cout<<"\n\t************ WELCOME Member ************\n";
    cout<<"\n\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    Mem();
}
// Function to display member details
void Member::showMember()
{
    cout << "\n\t\tMember Name : " << memberName << endl;
    cout << "\n\t\tMember ID : " << memberID << endl;
}

// Function to add a new member
void Member::addMember()
{
    fflush(stdin);
    cout << "\n\t\tEnter the details :-\n";
    cout << "\n\t\tEnter Member's Name : ";
    cin.getline(memberName, 100);
    cout << "\n\t\tEnter Member's ID : ";
    cin.getline(memberID, 20);
    
    ofstream outf("memberdata.txt", ios::app | ios::binary);
    outf.write((char*)this, sizeof(*this));
    outf.close();
    
    cout << "\n\t\tMember added successfully.\n";
}

// Function to remove a member
void Member::removeMember()
{
    char id[20];
    int found = 0;
    system("cls");
    cout << "\n\t\tEnter Member's ID to remove: ";
    cin.getline(id, 20);
    
    ifstream intf("memberdata.txt", ios::binary);
    ofstream outf("temp.txt", ios::binary);
    
    intf.read((char*)this, sizeof(*this));
    while (!intf.eof()) 
    {
        if (strcmp(memberID, id) != 0) 
        {
            outf.write((char*)this, sizeof(*this));
        } 
        else 
        {
            found = 1;
        }
        intf.read((char*)this, sizeof(*this));
    }
    
    intf.close();
    outf.close();
    
    remove("memberdata.txt");
    rename("temp.txt", "memberdata.txt");
    
    if (found)
        cout << "\n\t\tMember removed successfully.\n";
    else
        cout << "\n\t\tMember not found.\n";
}

// Function to update member details
void Member::updateMember()
{
    char id[20];
    int found = 0;
    system("cls");
    cout << "\n\t\tEnter Member's ID to update: ";
    cin.getline(id, 20);
    
    fstream intf("memberdata.txt", ios::in | ios::out | ios::binary);
    
    intf.read((char*)this, sizeof(*this));
    while (!intf.eof()) 
    {
        if (strcmp(memberID, id) == 0) 
        {
            cout << "\n\t\tEnter new details :-\n";
            addMember();
            intf.seekp(intf.tellp() - sizeof(*this));
            intf.write((char*)this, sizeof(*this));
            found = 1;
            break;
        }
        intf.read((char*)this, sizeof(*this));
    }
    
    intf.close();
    
    if (found)
        cout << "\n\t\tMember updated successfully.\n";
    else
        cout << "\n\t\tMember not found.\n";
}

// Function to display the list of members
void Member::memberList()
{
    ifstream intf("memberdata.txt", ios::binary);
    if (!intf) 
    {
        cout << "\n\t\tNo members found.\n";
        return;
    }
    
    intf.read((char*)this, sizeof(*this));
    while (!intf.eof()) 
    {
        showMember();
        intf.read((char*)this, sizeof(*this));
    }
    
    intf.close();
    cout << "\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    Mem();
}
void Lib::Mem()
{
    int i;        
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Manage Members\n\n\t\t4.Go to main menu\n\n\t\t5.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    system("cls");
    switch(i)
    {
        case 1:
            booklist(1);
            break;
        case 2:
            see(1);
            break;
        case 3:
            {
                Member m;
                int choice;
                cout << "\n\t\t1. View Members List\n\n\t\t2. Add Member\n\n\t\t3. Remove Member\n\n\t\t4. Update Member\n";
                cout << "\n\t\tEnter your choice: ";
                cin >> choice;
                fflush(stdin);
                switch(choice)
                {
                    case 1: 
                        m.memberList();
                        break;
                    case 2: 
                        m.addMember();
                        break;
                    case 3: 
                        m.removeMember();
                        break;
                    case 4: 
                        m.updateMember();
                        break;
                    default: 
                        cout << "\n\t\tInvalid option.\n";
                        getch();
                        system("cls");
                        Mem();
                }
                break;
            }
        case 4:
            get();
            break;
        case 5:
            exit(0);
        default:
            cout << "\n\t\tPlease enter correct option :(";
            getch();
            system("cls");
            Mem();
    }
}
void Lib::librarian()
{
    int i;
        cout<<"\n\t************ WELCOME LIBRARIAN ************\n";
        cout<<"\n\t\t>>Please Choose One Option:\n";
        cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Modify/Add Book\n\n\t\t4.Issue Book\n\n\t\t5.Go to main menu\n\n\t\t6.Close Application\n";
        cout<<"\n\t\tEnter your choice : ";
        cin>>i;
        switch(i)
        {
            case 1:booklist(2);
                     break;
            case 2:see(2);
                     break;
            case 3:modify();
                     break;
            case 4:issue();
                     break;
            case 5:system("cls");
                     get();
                     break;
            case 6:exit(0);
            default:cout<<"\n\t\tPlease enter correct option :(";
            getch();
            system("cls");
            librarian();
        }
}

void Book::getbook()
{
                    int i;
                    fflush(stdin);
                    cout<<"\n\t\tEnter the details :-\n";
                    cout<<"\n\t\tEnter Book's Name : ";
                    cin.getline(bookname,100);
                    for(i=0;bookname[i]!='\0';i++)
                    {
                    if(bookname[i]>='a'&&bookname[i]<='z')
                       bookname[i]-=32;
                    }
                    cout<<"\n\t\tEnter Author's Name : ";
                    cin.getline(auname,50);
                    
                    cout<<"\n\t\tEnter Book's ID : ";
                    cin.getline(sc,20);
                    cout<<"\n\t\tEnter Book's Price : ";
                    cin>>p;
                    cout<<"\n\t\tEnter Book's Quantity : ";
                    cin>>q;
}

int main()
{
    Lib obj;
    obj.get();
    getch();
    return 0;
}