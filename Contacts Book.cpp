#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <istream>
#include <ios>
#include <limits>
#include "myLib.h"
using namespace std;

enum enCategory
{
    Friend = 1,
    Family = 2,
    Work = 3,
    Others = 4
};

struct stContact
{
    string name = "";
    string phone = "";
    string email = "";
    enCategory category{};
};

enum enMenuChoice
{
    AddContact = 1,
    ShowContacts = 2,
    SearchContact = 3,
    UpdateContact = 4,
    DeleteContact = 5,
    Exit = 6
};
static enMenuChoice readUserChoice()
{
    return (enMenuChoice)validation::readValidateNumber((int)enMenuChoice::AddContact, (int)enMenuChoice::Exit, "Your Choice = ");
}

enum enSearchType
{
    byName = 1,
    byPhone = 2
};

enum enUpdateType
{
    Name = 1,
    Phone = 2,
    Email = 3,
    Category = 4
};

static void printHeader(const vector<stContact>& vContacts)
{
    cout << right << setw(5) << " " << "========================================\n";
    cout << right << setw(18) << " " << "Contacts Book\n";
    cout << right << setw(5) << " " << "========================================\n";

    // to call the total contacts to be shown in here
    cout << right << setw(5) << " " << "Total Contacts: " << static_cast<int>(vContacts.size()) << endl;

    cout << endl;

    cout << right << setw(5) << " " << "[1] Add Contact.\n";
    cout << right << setw(5) << " " << "[2] Show All Contacts.\n";
    cout << right << setw(5) << " " << "[3] Search Contact.\n";
    cout << right << setw(5) << " " << "[4] Update Contact.\n";
    cout << right << setw(5) << " " << "[5] Delete Contact.\n";
    cout << right << setw(5) << " " << "[6] Exit.\n";

    cout << right << setw(5) << " " << "========================================\n";
}

static enCategory readCategory()
{
    return (enCategory)validation::readValidateNumber((int)enCategory::Friend, (int)enCategory::Others, "Please Enter Contact Category : [1] Friend [2]Family [3]Work [4]Other => ");
}

static string toLowerInPlace(string s)
{
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    
    return s;
}

static void clearScreen()
{
    system("cls");
}

static void pressKeyToContinue()
{
    cout << "\n" << right << setw(5) << " ";
    system("pause");
}

static int findContact(const vector<stContact>& vContacts,string namePhone,enSearchType searchWith = enSearchType::byName)
{
    if (vContacts.empty())
        return -1;

    for (size_t i = 0;i < vContacts.size();i++)
    {
        if (searchWith == enSearchType::byPhone)
        {
            if (vContacts[i].phone == namePhone)
                return static_cast<int>(i);
            continue;
        }

        if (toLowerInPlace(vContacts[i].name) == toLowerInPlace(namePhone))
            return static_cast<int>(i);
    }

    return -1;
}

static void validatephone(stContact& contact)
{
	bool passed = false;

    do
    {
        cout << "\n" << right << setw(5) << " " << "Please Enter your Phone Number : ";
        getline(cin, contact.phone);

        if (contact.phone.length() != 10)
        {
            cout << "\n" << right << setw(5) << " " << "Invalid Phone Number !";
            continue;
        }

        if (contact.phone.front() != '0')
        {
            cout << "\n" << right << setw(5) << " " << "Invalid Phone Number !";
            continue;
        }

        for (size_t i = 1;i < contact.phone.length();i++)
        {
            if (!isdigit(contact.phone[i]))
            {
                cout << "\n" << right << setw(5) << " " << "Invalid Phone Number !";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                break;
            }

            passed = true;
        }

        if (passed)
            break;

    } while (true);
}

static void validateEmail(stContact& contact)
{
    do {
        cout << "\n" << right << setw(5) << " " << "Please Enter a valid Email Address : ";

        getline(cin >> ws, contact.email);
    } while ((contact.email.find('@') == string::npos) || (contact.email.find('.') == string::npos));
}

static stContact readContact()
{
    stContact contact{};

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n" << right << setw(5) << " " << "Please Enter your Fullname : ";
    getline(cin, contact.name);

	validatephone(contact);
    validateEmail(contact);

    return contact;
}

static void addContact(vector<stContact>& vContacts)
{
    stContact contact = readContact();
    
    int idx = findContact(vContacts, contact.name);
    bool isIdentical = false;

    if(idx != -1)
        isIdentical = (toLowerInPlace(contact.name) == toLowerInPlace(vContacts[idx].name)) && (toLowerInPlace(contact.email) == toLowerInPlace(vContacts[idx].email)) && (contact.phone == vContacts[idx].phone);

    if (!isIdentical)
    {
        contact.category = readCategory();

        vContacts.push_back(contact);
        cout << "\n" << right << setw(5) << " " << "Contact Added Successfully!" << endl;
    }
    else
        cout << "\n" << right << setw(5) << " " << "Contact Details Exists!" << endl;

    pressKeyToContinue();
    clearScreen();
}

static void printContactsHeader()
{
    cout << right << setw(5) << " " << "###############################################################################\n";
    cout << right << setw(5) << " " << "|" << right << setw(6) << " " << "Contact Name" << right << setw(6) << " " << "|";
    cout << right << setw(4) << " " << "Phone" << right << setw(4) << " " << "|";
    cout << right << setw(6) << " " << "Email Address" << right << setw(6) << " " << "|";
    cout << right << setw(2) << " " << "Category" << right << setw(2) << " " << "|\n";
    cout << right << setw(5) << " " << "###############################################################################\n";
}

static string categoryString(enCategory c)
{
    switch (c)
    {
    case enCategory::Family: return "Family";
    case enCategory::Friend: return "Friend";
    case enCategory::Work:   return "Work";
    case enCategory::Others: return "Others";
    default:                 return "Unknown";
    }
}
static void showContactsList(const vector<stContact>& vContacts)
{
    printContactsHeader();

    if (vContacts.empty())
        cout << right << setw(26) << " " << "No Contacts Available At The Moment." << endl; // 36

    for (const stContact& c : vContacts)
    {
        string cat = categoryString(c.category);

        cout << right << setw(5) << " " << "| " << c.name << right << setw(max(1, 22 - (int)c.name.length())) << " ";
        cout << right << setw(1) << " " << "| " << c.phone << right << setw(10 - c.phone.length()) << " ";
        cout << right << setw(1) << " " << "| " << c.email << right << setw(23 - c.email.length()) << " ";
        cout << right << setw(1) << " " << "| " << cat << right << setw(11 - cat.length()) << " " << "|\n";
    }

    cout << right << setw(5) << " " << "###############################################################################\n"; // 78
    
    pressKeyToContinue();
    clearScreen();
}

static enSearchType readSearchType()
{
    return (enSearchType)validation::readValidateNumber((int)enSearchType::byName, enSearchType::byPhone, "Search by [1] Name  [2] Phone : ");
}

static string readSearchQuery(enSearchType type)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string query = "";

    switch (type)
    {
    case enSearchType::byName:
    {
        cout << right << setw(5) << " " << "Enter Name : ";
        getline(cin, query);
    }
    break;
    case enSearchType::byPhone:
    {
        cout << right << setw(5) << " " << "Enter Phone : ";
        getline(cin, query);
    }
    break;
    default:
        return "";
    }

    return query;
}

static int searchContact(const vector<stContact>& vContacts)
{
    enSearchType searchType = readSearchType();
    string query = readSearchQuery(searchType);

    return findContact(vContacts, query, searchType);
}

static void printFoundContact(const vector<stContact>& vContacts)
{
    int contactIdx = searchContact(vContacts);

    if (contactIdx != -1)
    {
        stContact contact = vContacts[contactIdx];
        cout << endl << right << setw(7) << " " << "Found !" << endl << endl;

        cout << right << setw(5) << " " << "# Name  : " << contact.name << endl;
        cout << right << setw(5) << " " << "# Phone : " << contact.phone << endl;
        cout << right << setw(5) << " " << "# Email : " << contact.email << endl;
        cout << right << setw(5) << " " << "# Categ : " << categoryString(contact.category) << endl;

        pressKeyToContinue();
        clearScreen();
        return;
    }
    else
        cout << right << setw(5) << " " << "No Matched Criteria !" << endl;

    pressKeyToContinue();
    clearScreen();
}

static enUpdateType readUpdateCategory()
{
    return (enUpdateType)validation::readValidateNumber((int)enUpdateType::Name, (int)enUpdateType::Category, "Update: [1]Name [2]Phone [3]Email [4]Category : ");
}

static string contactToLineString(const stContact& c)
{
    return c.name + " | " + c.phone + " | " + categoryString(c.category);
}

static void update(enUpdateType type,int idx,vector<stContact>& vContacts)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (type)
    {
    case enUpdateType::Name:
    {
        string newName = "";

        cout << right << setw(5) << " " << "New Name : ";
        getline(cin, newName);

        vContacts[idx].name = newName;
    }
    break;
    case enUpdateType::Phone:
        validatephone(vContacts[idx]);
    break;
    case enUpdateType::Email:
        validateEmail(vContacts[idx]);
    break;
    case enUpdateType::Category:
    {
        enCategory newCategory = readCategory();
        vContacts[idx].category = newCategory;
    }
    break;
    default:
        return;
    }
}

static void updateContact(vector<stContact>& vContacts)
{
    string nameToUpdate = "";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << right << setw(5) << " " << "Enter name to update : ";
    getline(cin, nameToUpdate);

    int idx = findContact(vContacts,nameToUpdate);

    if (idx != -1)
    {
        cout << right << setw(5) << " " << "Current Data : " << contactToLineString(vContacts[idx]) << endl;
        update(readUpdateCategory(),idx,vContacts);

        cout << right << setw(5) << " " << "Contact Updated !";

        pressKeyToContinue();
        clearScreen();
    }
    else
    {
        cout << right << setw(5) << " " << "No Matched Criteria!" << endl;
        pressKeyToContinue();
        clearScreen();
    }
}

static void deleteContact(vector<stContact>& vContacts)
{
    string contactToDelete = "";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << right << setw(5) << " " << "Enter name to delete : ";
    getline(cin, contactToDelete);

    int idx = findContact(vContacts,contactToDelete);

    if (idx != -1)
    {
        cout << endl << right << setw(5) << " " << "Found ! : ";
        cout << contactToLineString(vContacts[idx]);

        char confirm = 'n';

        cout << endl << right << setw(5) << " " << "Are you sure [Y/y] : ";
        cin >> confirm;

        if (tolower(confirm) == 'y') 
        {
            vContacts.erase(vContacts.begin() + idx);
            cout << endl << right << setw(5) << " " << "Contact Deleted." << endl;
        }
        else
            cout << endl << right << setw(5) << " " << "Operation Canceled." << endl;

        
        pressKeyToContinue();
        clearScreen();
    }
    else
    {
        cout << right << setw(5) << " " << "No Matched Criteria!" << endl;
        pressKeyToContinue();
        clearScreen();
    }
}

static void redirectToScreens(enMenuChoice choice, vector<stContact>& vContacts)
{
    switch (choice)
    {
    case enMenuChoice::AddContact:
        addContact(vContacts);
        break;
    case enMenuChoice::DeleteContact:
        deleteContact(vContacts);
        break;
    case enMenuChoice::SearchContact:
        printFoundContact(vContacts);
        break;
    case enMenuChoice::ShowContacts:
        showContactsList(vContacts);
        break;
    case enMenuChoice::UpdateContact:
        updateContact(vContacts);
        break;
    case enMenuChoice::Exit:
        break;
    default:
        return;
    }
}

static void startContactBook(vector<stContact>& vContacts)
{
    enMenuChoice choice{};

    do
    {
        printHeader(vContacts);

        choice = readUserChoice();
        redirectToScreens(choice,vContacts);
    
    } while (choice != enMenuChoice::Exit);
}

int main()
{
    vector<stContact> vContacts{};

    startContactBook(vContacts);
}