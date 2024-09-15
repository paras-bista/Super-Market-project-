#include <iostream>
#include <fstream> 
#include <sstream>
#include <windows.h> // for sleep
#include <cctype>    // make alphabet lower order

using namespace std;
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string RESET = "\033[0m";
const string BLACK = "\033[40m";
const string WHITE = "\033[47m";
const string BOLD = "\033[1m";

const string Shopkeeper_id = "1818";
const string Shopkeeper_pw = "paras123";

class Item
{
private:
    string name;
    int rate;
    int quantity;

public:
    Item()
    {
        name = "";
        rate = 0;
        quantity = 0;
    }
    Item(string n, int r, int q)
    {
        name = n;
        rate = r;
        quantity = q;
    }
    void setName(string n)
    {
        name = n; // set name of item
    }

    void setRate(int r)
    {
        rate = r; // set rate of item
    }
    void setQuantity(int q)
    {
        quantity = q; // set quantity of item
    }

    string getName() const
    {
        return name; // get name of item
    }
    int getRate() const
    {
        return rate; // get rate of item
    }
    int getQuantity() const
    {
        return quantity; // get quantity of item
    }
};

bool shopkeeperLogin() // login function for shopkeeper only
{
    string id, password;
    cout << endl;
    cout << CYAN << "\t\t\tEnter " << YELLOW << "Shopkeeper ID: " << RESET; // shopkeeper id
    cin >> id;
    cout << endl;

    cout << CYAN << "\t\t\tEnter " << YELLOW << "Shopkeeper Password: " << RESET; // shopkeeper pw
    cin >> password;

    for (char &c : id)
    {
        c = tolower(c); // make user id in lower alphabet
    }
    for (char &c : password)
    {
        c = tolower(c); // make user password in lower alphabet
    }

    return (id == Shopkeeper_id && password == Shopkeeper_pw); // check the id and pw
}

void addItem(Item &i) // for shopkeeper add item in supermarket
{
    bool close = false;
    while (!close)
    {
        int categoryChoice;

        cout << MAGENTA << BOLD;
        cout << "\t\t_______________________________________________" << endl;
        cout << "\t\t|                                              |" << endl;
        cout << "\t\t|          Shopkeeper Menu                     |" << endl;
        cout << "\t\t|                                              |" << endl;
        cout << "\t\t|______________________________________________|" << RESET << endl;
        cout << GREEN << "\n\t\t|__________1) Fruits _________________________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________2) Vegetables _____________________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________3) Dairy __________________________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________4) Bread and Baked Goods __________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________5) Meat and Fish __________________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________6) Meat Alternatives ______________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________7) Cans and Jars __________________|";
        cout << "\n\t\t|                                             |";
        cout << "\n\t\t|__________" << RED << "8) Close" << RESET << GREEN << " __________________________|" << RESET;
        cout << endl;
        cout << YELLOW << "\n\t\t  Please Enter your choice  " << RESET;
        cin >> categoryChoice;
        if (categoryChoice >= 1 && categoryChoice <= 7)
        {
            system("cls"); // clear the screen
            string name;
            int rate, quant;
            cout << BLUE << "\tEnter Item Name: " << RESET;
            cin >> name;
            for (char &c : name)
            {
                c = tolower(c);
            }
            i.setName(name);
            cout << endl;

            cout << BLUE << "\tEnter Rate of Item per (kg/litre/Piece) -> Rs: " << RESET;
            cin >> rate;
            i.setRate(rate);
            cout << endl;

            cout << BLUE << "\tEnter Quantity of Item (kg/litre/piece): " << RESET;
            cin >> quant;
            i.setQuantity(quant);
            cout << endl;

            ofstream out("StoreItem.txt", ios::app); // open the file in apprend mode "bill.txt"
            if (!out)
            {
                cout << "\tError: file can't open!" << endl;
            }
            else
            {
                string category;
                switch (categoryChoice)
                {
                case 1:
                    category = "Fruits";
                    break;
                case 2:
                    category = "Vegetables";
                    break;
                case 3:
                    category = "Dairy";
                    break;
                case 4:
                    category = "Bread and Baked Goods";
                    break;
                case 5:
                    category = "Meat and Fish";
                    break;
                case 6:
                    category = "Meat Alternatives";
                    break;
                case 7:
                    category = "Cans and Jars";
                    break;
                }

                // write the data in a structured format
                out << i.getName() << "," << i.getRate() << "," << i.getQuantity() << "," << category << endl;
            }
            out.close(); // close the file

            cout << RED << "\tItem added successfully!" << RESET << endl;
            Sleep(3000); // hold the screen for 3 sec
        }
        else if (categoryChoice == 8)
        {
            system("cls");
            close = true;
            cout << "\033[1;34mBack to Menu\033[0m" << endl;
            Sleep(3000);
        }
        else
        {
            cout << RED << "\tInvalid choice! Please try again." << RESET << endl;
            Sleep(2000);
        }
    }
}
void listItems() // list function for list the item which is available in this supermarket
{
    ifstream inFile("StoreItem.txt"); // open file in read mode

    if (!inFile)
    {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    string line;
    cout << YELLOW << "\nAvailable items in the store:\n"
         << RESET;
    cout << BLUE << "----------------------------------------------------------------------------------\n";
    cout << "Item Name\tRate(Rs per kg/ltr/piece) Available(No. in kg/ltr/piece)\tCategory\n";
    cout << "----------------------------------------------------------------------------------" << RESET << endl;

    while (getline(inFile, line)) // read data line by line
    {
        stringstream ss(line);
        string name, category;
        int rate, quantity;

        getline(ss, name, ',');
        ss >> rate;
        ss.ignore(1); // ignore comma
        ss >> quantity;
        ss.ignore(1); // ignore comma
        getline(ss, category);

        cout << GREEN << name << "\t\t\t" << rate << "\t\t\t" << quantity << "\t\t\t" << category << RESET << endl;
    }

    inFile.close(); // close the file
}

void generateAndPrintQrCode() // Qr function for payment
{
    const int SIZE = 17;
    char qrCode[SIZE][SIZE] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', '#'},
        {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', ' ', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            if (qrCode[y][x] == '#')
                cout << BLACK << "  " << RESET;
            else
                cout << WHITE << "  " << RESET;
        }
        cout << endl;
    }
}
void Customer_menu() // customer function for buy the things in this super market
{
    system("cls");
    int count = 0;
    bool close = false;
    while (!close)
    {
        system("cls");
        int choice;
        cout << RED << "\t\t  Customer Menu \n"
             << RESET;
        cout << YELLOW << "\n\t\t|______1) Add Item to Your Cart __________________________|";
        cout << "\n\t\t|                                                         |";
        cout << "\n\t\t|______2) Bill section_____________________________________|";
        cout << "\n\t\t|                                                         |";
        cout << "\n\t\t|______3) Exit Back To Main Menu!...______________________|" << RESET;
        cout << endl;
        cout << endl;
        cout << BLUE << "\t\t Enter your Choice  : " << RESET;
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            listItems(); // list function call
            string item;
            int quant;
            cout << CYAN << "\n\t==========================================" << RESET << endl;
            cout << CYAN << "\t|| " << YELLOW << "        Add Item to Your Cart       " << CYAN << " ||" << RESET << endl;
            cout << CYAN << "\t==========================================" << RESET << endl
                 << endl;

            cout << GREEN << "\t Enter Item name to the cart: " << RESET;
            cin >> item;
            for (char &c : item)
            {
                c = tolower(c);
            }
            cout << endl;
            ifstream in("StoreItem.txt");  // open file in read mode
            ofstream out("TempStore.txt"); // temporary file open in write mode

            string line;
            bool found = false;

            while (getline(in, line))
            {
                stringstream ss(line);
                string itemName, category;
                int itemRate, itemQuant;

                // get  data from line using a comma as delimiter
                getline(ss, itemName, ',');
                ss >> itemRate;
                ss.ignore(1); // ignore the comma
                ss >> itemQuant;
                ss.ignore(1); // ignore the comma
                getline(ss, category);

                if (item == itemName)
                {
                    cout << YELLOW << "\t Enter Quantity of " << BLUE << item << YELLOW << " (in kg or ltr or piece): " << RESET;
                    cin >> quant;
                    cout << endl;

                    found = true;
                    if (quant <= itemQuant)
                    {
                        cout << MAGENTA << "\n\tItem " << BLUE << item << MAGENTA << " with quantity " << GREEN << quant << " kg/ltr/piece" << MAGENTA << " added to your cart!" << RESET << endl;
                        cout << endl;
                        int amount = itemRate * quant;
                        cout << BLUE << "\t Item | Rate | Quantity | Amount " << RESET << endl;
                        cout << RED << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;
                        int newQuant = itemQuant - quant;

                        // update the quantity and write to the temporary file
                        out << itemName << "," << itemRate << "," << newQuant << "," << category << endl;

                        count += amount; // count the total amount
                        cout << RESET;
                        cout << endl;
                        cout << YELLOW << "Item added successfully! " << RESET << endl;
                        Sleep(2000);
                    }
                    else
                    {
                        cout << YELLOW << "\t Sorry " << item << " Insufficient!" << RESET << endl;
                        out << line << endl;
                    }
                }
                else
                {
                    out << line << endl;
                }
            }

            if (!found)
            {
                cout << RED << "\t Item Not Available!" << RESET << endl;
            }

            out.close();                              // close temporary file
            in.close();                               // close bill file
            remove("StoreItem.txt");                  // remove the bill file
            rename("TempStore.txt", "StoreItem.txt"); // rename the temp file to bill.txt
        }
        else if (choice == 2) // bill section
        {
            cout << CYAN << GREEN << "  Counting Total Bill" << CYAN << RESET << endl;
            system("cls");
            cout << endl
                 << endl;
            cout << BLUE << GREEN << "      Total Bill -------------------- : " << count << BLUE << RESET << endl
                 << endl;

            bool paymentDone = false;
            while (!paymentDone)
            {
                cout << CYAN << "\n\t==============================================" << RESET << endl;
                cout << CYAN << "\t|| " << YELLOW << "          Choose Your Payment Method        " << CYAN << " ||" << RESET << endl;
                cout << CYAN << "\t==============================================" << RESET << endl;

                cout << GREEN << "\t " << YELLOW << "[1] Cash" << RESET << endl;
                cout << BLUE << "\t " << YELLOW << "[2] Online Payment" << RESET << endl;

                cout << CYAN << "\n\t----------------------------------------------" << RESET << endl;
                cout << MAGENTA << "\tPlease enter your choice: " << RESET;
                int paymentChoice;
                cin >> paymentChoice;

                if (paymentChoice == 1)
                {
                    cout << GREEN << "\n\tYou chose to pay by Cash." << RESET << endl
                         << endl;
                    ;
                    cout << BLUE << GREEN << "   Total Bill -------------------- : " << count << BLUE << RESET << endl;

                    int amount;
                    cout << CYAN << "Enter payment amount: " << RESET;
                    cin >> amount;
                    cout << endl;
                    if (amount == count)
                    {
                        cout << RED << "Payment successfull  RS " << RESET << amount << endl;
                        cout << YELLOW << "Thanks for buying! See you next time." << RESET << endl
                             << endl;
                    }
                    else
                    {
                        cout << "You enter less or more money" << endl;
                    }

                    Sleep(2000);

                    cout << BLUE << "Back To Customer Section..." << RESET << endl
                         << endl;
                    Sleep(2000);
                    paymentDone = true;
                }
                else if (paymentChoice == 2)
                {
                    system("cls");

                    cout << CYAN << "We have QR here. Please Scan for Payment." << RESET << endl;
                    cout << endl;

                    generateAndPrintQrCode(); // print QR code
                    cout << endl;
                    cout << endl;
                    cout << BLUE << GREEN << "Total Bill -------------------- : " << count << BLUE << RESET << endl;
                    int amount;
                    cout << CYAN << "Enter payment amount: " << RESET;
                    cin >> amount;
                    cout << endl;
                    if (amount >= count)
                    {
                        cout << RED << "Payment successfull  RS " << RESET << amount << endl;
                        cout << YELLOW << "Thanks for buying!" << RESET << endl
                             << endl;
                    }
                    else
                    {
                        cout << "You enter less or more money" << endl;
                    }
                    Sleep(3000);

                    cout << BLUE << "Back To Customer Section...." << RESET << endl;

                    Sleep(3000);
                    paymentDone = true;
                }
                else
                {
                    cout << RED << "\tInvalid choice. Please try again." << RESET << endl;
                }
            }
        }
        else if (choice == 3)
        {
            cout << BLUE << "Back To Main Menu!...." << RESET << endl;
            Sleep(3000);
            close = true;
        }
        Sleep(3000);
    }
}

int main()
{
    Item i;
    while (true)
    {
        system("cls");

        cout << RED << "\t\t ____________________________________________________________________________ \n";
        cout << "\t\t|                                                                            |\n";
        cout << "\t\t|                          " << YELLOW << "Welcome to the Supermarket System" << RED << "                 |\n";
        cout << "\t\t|____________________________________________________________________________|\n";

        cout << RED << "\t\t|                                                                            |\n";
        cout << "\t\t|                        " << RESET << GREEN << "    Supermarket Main Menu" << RESET << RED << "                           |\n";
        cout << "\t\t|                                                                            |\n";
        cout << "\t\t|____________________________________________________________________________|\n";

        cout << BLUE << "\t\t|                                                                            |\n";
        cout << "\t\t|                        " << RESET << "(1) " << CYAN << "Shopkeeper Login" << RESET << BLUE << "                                |\n";
        cout << "\t\t|                                                                            |\n";
        cout << "\t\t|                        " << RESET << "(2) " << CYAN << "Customer Menu" << RESET << BLUE << "                                   |\n";
        cout << "\t\t|                                                                            |\n";
        cout << "\t\t|                        " << RESET << "(3) " << CYAN << "Exit" << RESET << BLUE << "                                            |\n";
        cout << "\t\t|                                                                            |\n";
        cout << "\t\t|____________________________________________________________________________|\n";
        cout << RESET;

        cout << GREEN << "\t\tEnter your choice: " << RESET;
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (shopkeeperLogin())
            {
                system("cls");
                cout << BLUE << "Login successful!" << RESET << endl;
                addItem(i);
            }
            else
            {
                cout << RED << "Invalid ID or Password!" << RESET << endl;
                Sleep(3000);
            }
        }
        else if (choice == 2)
        {
            Customer_menu();
        }
        else if (choice == 3)
        {
            cout << endl;
            cout << YELLOW << "Thank you for using the Supermarket System. Goodbye!" << RESET << endl;
            cout << endl;
            cout << endl;
            Sleep(2000);
            break;
        }
        else
        {
            cout << RED << "Invalid choice! Please try again." << RESET << endl;
            Sleep(2000);
        }
    }

    return 0;
}
