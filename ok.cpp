#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Person
{
public:
    string name;
    string phone_no;
};

class Customer: public Person
{
public:
    string password;
    int customer_id;

    Customer() {}

    Customer(int customer_id1, string name1, string password1, string phone_no1)
    {
        customer_id = customer_id1;
        name = name1;
        password = password1;
        phone_no = phone_no1;
    }
} customer;


class Employee: public Person
{
public:
    string password;
    int employee_id;
    Employee() {}

    Employee(int employee_id1, string name1, string password1, string phone_no1)
    {
        employee_id = employee_id1;
        name = name1;
        password = password1;
        phone_no = phone_no1;
    }
} employee;

class Product
{
public:
    string name;
    double value;
    Product() {};
    Product(string name1,double value1)
    {
        name=name1;
        value=value1;
    }
    Product get()
    {
        Product temp=Product(name,value);
        return temp;
    }   friend void Add_Product();
} ;// product;

void Homepage();
void Customer_Panel();
void Employee_Panel();
void Register_Customer();
void Login_Customer();
void View_Product();
void ADD_Product();


void Add_Product()
{
    int ch;
    system("cls");
    cout << "<== E-Commerce Management ==>" << endl << endl;
    cout << "Employee Panel -> Add_Product" << endl;
    string name;
    double value;

    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter value: ";
    cin >> value;

    ofstream fout;
    fout.open("product.txt", ios::app);
    if (fout.is_open()) {
        fout << name << "," << value << endl;
        fout.close();
        cout << endl << endl;
        cout << "Product Added Successfully!" << endl << "Press any key to continue...";
    }
    else {
        cout << "Unable to open the product file." << endl;
    }

    cout << endl;
    getchar(); //lock screen until enter
    View_Product();
    cout << endl;
   while(1){
     cout << "1. Add product" << endl;
    cout << "2. Homepage" << endl;
    int ak;
    cin >> ak;
    switch (ak)
    {
    case 1:
    {
        Add_Product();
        break;
    }
    case 2:
    {
        Homepage();
        break;
    }
    case 3:
        View_Product();
        break;
    default:
        cout << "Invalid option" << endl<<endl;


    }
   }
}



void View_Product()
{
    cout << "<== E-Commerce Management ==>" << endl << endl;
    cout << "Customer Panel -> View_Product" << endl;
    ifstream fin;
    fin.open("product.txt", ios::in);

    if (fin.is_open()) {
        cout << "Product_name" << "   =>  " << "Product_value" << endl << endl;
        string line;
        while (getline(fin, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string name = line.substr(0, commaPos); //to extract the product name and value from the line, based on the position of the comma.
                string valueStr = line.substr(commaPos + 1);

                try {
                    //error handeling when can not convert string to double value;
                    double value = stod(valueStr);
                    cout << name << "      =>   " << value << endl;
                } catch (const std::invalid_argument& e) {
                    cout << "Error: Invalid product value for " << name << endl;
                }
            }
        }
        fin.close();
    } else {
        cout << "Unable to open the product file." << endl;
    }
}


void Login_Employee()
{
    int ch;
    system("cls");
    cout << "<== E-Commerce Management ==>" << endl << endl;
    cout << "Employee Panel -> Login" << endl;
    string name, pass;
    cout << "Enter User Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter password: ";
    getline(cin, pass);
    ifstream fin;
    fin.open("employee.txt", ios::in);
    fin.seekg(0);

    bool isLoggedIn = false;
    while (fin.read((char*)&employee, sizeof(employee)))
    {
        if (name == employee.name && pass == employee.password)
        {
            cout << "Hello " << name << endl;
            isLoggedIn = true;
            break;
        }
    }
    fin.close();

    if (!isLoggedIn) {
        cout << "Invalid username or password. Login failed." << endl;
       while(1){
          int a;
        cout<< " 1.login_Panel"<<endl;
        cout<< " 2.Homepage"<<endl;
        cout<< " 3.Employee_Panel"<<endl<<endl;
        cout<< "Enter your choice :";

        cin>>a;
         switch(a)
         {
         case 1:
            Login_Employee();
            break;

         case 2:
            Homepage();
            break;
         case 3:
            Employee_Panel();
            break;
         default:
            cout<<"invalid, Choose right option : "<<endl;
         }

       }

        return;
    }

    cout << endl << endl;
    cout << "Press any key to continue...";
    getchar(); //lock screen until enter
    if (isLoggedIn) {
        View_Product();
        Add_Product();
    }
}



void Register_Employee()
{
    int ch;
    system("cls");
    cout << "<== E-Commerce Management ==>" << endl << endl;
    cout << "Employee Panel -> Register" << endl;
    int id;
    string name, pass, phone;
    id = static_cast<int>(time(0)); // used for individi id generate
    id *= 999;
    id %= 1000;
    id += 10000;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter password: ";
    getline(cin, pass);
    cout << "Enter phone no: ";
    getline(cin, phone);
    employee = Employee(id, name, pass, phone);
    ofstream fout;
    fout.open("employee.txt", ios::app);
    fout.write((char*)&employee, sizeof(employee));
    fout.close();
    cout << endl << endl;
    cout << "Registration Successful!" << endl << "Press any key to continue...";
    getchar(); //lock screen until enter
    Employee_Panel();
}

void Employee_Panel()
{
    int ch;
    while (1)
    {
        system("cls");
        cout << "<== E-Commerce Management ==>" << endl << endl;
        cout << "Employee Panel" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout<<  "3. Homepage "<<endl;
        cout << endl;
        cout << "Enter Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            Login_Employee();
            break;
        case 2:
            Register_Employee();
            break;
        case 3:
            Homepage();
            break;
        default:
            cout << "Invalid Option" << endl;
            Homepage();

        }
        cout << endl << endl;
        cout << "Press any key to continue...";
        getchar(); //lock screen until enter
    }
}



void Login_Customer()
{
    int ch;
    system("cls");
    cout << "<== E-Commerce Management ==>" << endl << endl;
    cout << "Customer Panel -> Login" << endl;
    string name, pass;
    cout << "Enter User Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter password: ";
    getline(cin, pass);
    ifstream fin;
    fin.open("customer.txt", ios::in);
    fin.seekg(0);//fin stands for read input and seekg(0) for starting line;

    bool isLoggedIn = false;
    while (fin.read((char*)&customer, sizeof(customer)))
    {
        if (name == customer.name && pass == customer.password)
        {
            cout << "Hello " << name << endl;
            isLoggedIn = true;
            break;
        }
    }
    fin.close();

    if (!isLoggedIn) {
        cout << "Invalid username or password. -> Login failed." << endl;
       while(1){
          int a;
        cout<< " 1. login_Panel"<<endl;
        cout<< " 2. Homepage"<<endl;
        cout<< " 3. Customer_Panel"<<endl<<endl;
        cout<< "    Enter your choice :";

        cin>>a;
         switch(a)
         {
         case 1:
            Login_Customer();
            break;

         case 2:
            Homepage();
            break;
         case 3:
            Customer_Panel();
            break;
         default:
            cout<<" Invalid , Choose Right Option : "<<endl;
         }

       }
        return;
    }

    cout << endl << endl;
    cout << "Press any key to continue...";
    getchar(); //lock screen until enter
    if (isLoggedIn) {
        View_Product();
    }
}



void Register_Customer()
{
    int ch;
    system("cls");
    cout << "<== E-Commerce Management ==>" << endl << endl;
    cout << "Customer Panel -> Register" << endl;
    int id;
    string name, pass, phone;
    id = static_cast<int>(time(0));
    id *= 999;
    id %= 1000;
    id += 10000;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter password: ";
    getline(cin, pass);
    cout << "Enter phone no: ";
    getline(cin, phone);
    customer = Customer(id, name, pass, phone);
    ofstream fout;
    fout.open("customer.txt", ios::app);
    fout.write((char*)&customer, sizeof(customer));
    fout.close();
    cout << endl << endl;
    cout << "Registration Successful!" << endl << "Press any key to continue...";
    getchar(); //lock screen until enter
    Customer_Panel();
}

void Customer_Panel()
{
    int ch;
    while (1)
    {
        system("cls");
        cout << "<== E-Commerce Management ==>" << endl << endl;
        cout << "Customer Panel" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout<<  "3. Hompage "<<endl;
        cout << endl;
        cout << "Enter Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            Login_Customer();
            break;
        case 2:
            Register_Customer();
            break;
        case 3:
            Homepage();
            break;
        default:
            cout << "Invalid Option" << endl;
            Customer_Panel();
        }
        cout << endl << endl;
        cout << "Press any key to continue...";
        getchar(); //lock screen until enter
    }
}

void Homepage()
{
    int ch;
    while (1)
    {
        system("cls");//used for clear scren
        cout << "<== E-Commerce Management ==>" << endl << endl;
        cout << "1. As a Customer" << endl;
        cout << "2. As a Employee" << endl;
        cout << "3. As a Admin" << endl;
        cout << "4. Exit "<<endl;
        cout << endl;
        cout << "Enter Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            Customer_Panel();
            break;
        case 2:
            Employee_Panel();
            break;
        case 3:
           // Admin_Panel();
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid Option" << endl;
             cout << endl << endl;

          getchar(); //lock screen until enter
          cout << "Press any key to continue...";
          Homepage();
        }

        getchar(); //lock screen until enter
    }
}

int main()
{
    Homepage();
    return 0;

}

