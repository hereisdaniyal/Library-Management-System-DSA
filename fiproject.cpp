#include <iostream> // FINALIZED with comments
#include <string> // name validation testing 
#include <cstdlib>
using namespace std;

/*
LAST UPDATE ON 12:47 AM 19/02/2025
USED SINGLY LINKED LIST

LIBRARY MANAGEMENT SYSTEM
----FINAL----

DSA PROJECT

OWAIS KHAN
*/

class LibraryEntity
{
protected: // we are inherting this trait in Library and Member, Hierarchial inheritance
    int id;

public:
    LibraryEntity(int id = 0) : id(id) {} // default paratermized constructor for ID
    virtual void displayInfo() = 0;
    void setId(int val) {id = val;} // SETTER
    int getId() { return id; }
    virtual ~LibraryEntity() {} // virtual destructor so that inherited classes ka bhi destructor chale
};

class Book : public LibraryEntity
{
public: // ALL IS PUBLIC
    string title, author;
    bool isIssued;
    int issuedToId;
    Book *next; // singly linked list

    Book(int id, string title, string author) // Paratermized constructor
        : LibraryEntity(id), title(title), author(author), isIssued(false), issuedToId(0), next(nullptr)
    {
    }

    void displayInfo() override // overridable method
    {
        // yeh bass hum output kar rahe
        cout << "Book ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\n";
        // yeh ternary operator hai, agar book issued hai tou yeh output karega kay issued verna available
        cout << (isIssued ? "Issued to Member ID " + to_string(issuedToId) : "Available") << endl;
    }
};

class Member : public LibraryEntity
{
public:
    string name, password;
    Member *next; // singly linked list

    Member(int id, string name, string password) // Paratermized constructor
        : LibraryEntity(id), name(name), password(password), next(nullptr)
    {
    }

    void displayInfo() override // overridable method for displaying info
    {
        cout << "Member ID: " << id << "\nName: " << name << endl;
    }

    // yeh bass verify kar raha hai ab
    bool verifyPassword(string inputPassword) { return password == inputPassword; }
};

class LibrarySystem // MAIN CLASS YEHI HAI
{
private:
    Book *bookHead;     // 1st Node of Book
    Member *memberHead; // 1st Node of Member
    int loggedInMemberId, memberIdCounter, bookIdCounter;
    // jaise hi new member ya book aye gi, counter++, loggedinMemberId is current login

public:
    // default constructor
    LibrarySystem() : bookHead(nullptr), memberHead(nullptr), loggedInMemberId(-1), memberIdCounter(1), bookIdCounter(1) {}

    // GETTER & SETTER
    int getLoggedInMemberId() { return loggedInMemberId; }
    void setLoggedInMemberId(int memberId) { loggedInMemberId = memberId; }

    void addBook(string title, string author) // InsertAtHead()
    {
        Book * temp = bookHead; // shared memory location

        // checking agar duplicate tou nahi agayi book
        while (temp) // run till NULL
        {
            if (temp->title == title && temp->author == author) // ditto same agar hue
            {
                cout << " BOOK " << temp->title << " BY " << temp->author << " ALREADY EXISTS! \n";
                return; // function sai bahir aja
            }
            temp = temp->next; // traversing to next BOOK
        }
        // if no duplicate
        Book *newBook = new Book(bookIdCounter++, title, author); // new OBJECT
        newBook->next = bookHead;                                 // yeh simple link ho raha hai
        bookHead = newBook;                                       // trav
        cout << "Book added successfully! ID: " << newBook->getId() << endl;
    }

    void searchBook() // SEARCHING A BOOKS
    {
        if (!bookHead) // If no books exist
        {
            cout << "No books available." << endl;
            return;
        }
        // BOOKS DO EXIST IN THE LINKED LIST
    string searchTerm;
    cout << "Enter book title or author: ";
    cin.ignore(); // Yeh buffer clear karne ka scene hai, warna kabhi kabhi garbage input le leta hai
    getline(cin, searchTerm); // Pura input line lega, spaces bhi include hongi

    Book *temp = bookHead; // Yeh pointer first book ko point kar raha hai
    bool found = false; // Abhi tak koi book nahi mili

    while (temp) // Jab tak list me books hain, tab tak search karega
    {
        if (temp->title == searchTerm || temp->author == searchTerm) // Yeh exact match check karega, title ya author se
        {
            temp->displayInfo(); // Mil gayi book, ab uska info show karo
            found = true; // Ek book mil gayi bhai, ab found true kar do
        }
        temp = temp->next; // Agli book pe chalo
    }

    if (!found) // Agar koi book nahi mili toh yeh message dikhega
        { cout << "No book found matching the search criteria." << endl; }
    }

    void deleteBook() // DELETING A BOOK
    {
    if (!bookHead) // If no books exist
    {
        cout << "No books available." << endl;
        return;
    }

    int id; // Prompt user
    cout << " ENTER ID OF BOOK TO DELETE: ";
    cin >> id;

    // Special case: If head needs to be deleted
    if (bookHead->getId() == id)
    {
        Book *temp = bookHead;
        bookHead = bookHead->next;
        delete temp;
        --bookIdCounter;
        cout << " SUCCESSFULLY DELETED Book Id. " << id << endl;
    }
    else
    {
        // General case: Search for the book in the list
        Book *temp = bookHead;
        while (temp->next != nullptr)
        {
            if (temp->next->getId() == id)
            {
                Book *deleteBook = temp->next;
                temp->next = temp->next->next;
                delete deleteBook;
                --bookIdCounter;
                cout << " SUCCESSFULLY DELETED Book Id. " << id << endl;

                // **Reassign IDs after deletion**
                Book *current = bookHead;
                int newId = bookHead->getId(); // Restarting ID from 1
                while (current)
                {
                current->setId(--newId); // Assigning new ID
                current = current->next;
                }
                break;
            }
            temp = temp->next;
        }

    }
    }


    void addMember(string name, string password) // InsertAtHead()
    {
        Member *newMember = new Member(memberIdCounter++, name, password);
        newMember->next = memberHead; // same as above
        memberHead = newMember;
        cout << "Member added successfully! ID: " << newMember->getId() << endl;
    }

    void displayBooks()
    {
        if (!bookHead) // agar book hi null hai tou empty
        {
            cout << "No books available." << endl;
            return; // function band
        }
        for (Book *b = bookHead; b; b = b->next) // yeh for kay through traversal ka tariqa hai
        {                                        // b meaning is b != nullptr tak chale
            b->displayInfo();                    // yeh object by object display karwata rahe ga details
            cout << endl;
        }
    }

    void displayMembers() // SAME LOGIC AS IN DISPLAYBOOKS()
    {
        if (!memberHead)
        {
            cout << "No members available." << endl;
            return;
        }
        for (Member *m = memberHead; m; m = m->next)
        {
            m->displayInfo();
            cout << endl;
        }
    }

    void adminlogin() // FOR ADMIN LOGIN
    {
        string password; // PROMPT
        cout << "Enter Admin Password: ";
        cin.ignore();
        getline(cin, password);

        if (password == "1234") // 1234 is password for admin
        {
            cout << " ADMIN LOGGED IN SUCCESFULLY! \n";
            setLoggedInMemberId(1234); // SETTING LOGGED IN MEMBER ID
        }
        else // password is WRONG
        {
            cout << " INCORRECT PASSWORD FOR ADMIN! \n";
        }
    }

    bool userlogin() // improved
    {
        if (memberHead == nullptr) // agar member hi nahi exist karta
        {
            cout << "No members available." << endl; // Member avaliable nahi hai
            return false;                            // false meaning member nahi exist karta
        }
        int memberId; // PROMPT
        string password;
        cout << "\nEnter Member ID: ";
        cin >> memberId;
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, password);
        // displayMembers();
        for (Member *m = memberHead; m; m = m->next) // TRAVERSING
        {
            if (m->getId() == memberId && m->verifyPassword(password)) // AGAR DONE TRUE HAI?
            {
                setLoggedInMemberId(memberId);                           // SETTING LOGGED IN MEMBER ID
                cout << "Logged in successfully as " << m->name << endl; // SUCCESSFUL LOGIN
                return true;
            }
        }
        // agar kuch match nahi hua phir yeh output chale gi
        cout << "Invalid Member ID or Password!" << endl;
        return false;
    }

    void issueBook() // self explanatory
    {
        if (bookHead == nullptr) // agar Book hi nahi exist karti tou issue ka kya faida?
        {
            cout << "No Books available." << endl; // Member avaliable nahi hai
            return;                                // function sai nikal jaye
        }

        // PROMPT
        displayBooks(); // display all books for it to issue
        int bookId;
        cout << "\nEnter Book ID to issue: ";
        cin >> bookId;

        for (Book *b = bookHead; b; b = b->next) // traversing
        {
            if (b->getId() == bookId) // IF BOTH ARE EQUAL
            {
                if (b->isIssued) // kya book already issued hai?
                    cout << "Already issued!" << endl;
                else // NAHI, IT'S AVAILABLE
                {
                    b->isIssued = true;               // ab issue hogayi hai
                    b->issuedToId = loggedInMemberId; // jo member logged in hai usko issue hogayi hai
                    cout << "Issued successfully!" << endl;
                }
                return;
            }
        }
        // AGAR SPECIFIC BOOK NAHI MILI TOU IDHAR AJAYE GA
        cout << "Book not found!" << endl;
    }

    void logout() // SIMPLE LOGOUT
    {
        setLoggedInMemberId(-1); // v.v.important
        cout << "Logged out successfully!" << endl;
    }

    // DESTRUCTOR FOR REMOVING MEMORY LEAKAGE (SPECIALLY FOR OWAIS KHAN)
    ~LibrarySystem()
    {
        // Delete all books
        while (bookHead)
        {
            Book *temp = bookHead;
            bookHead = bookHead->next;
            delete temp;
        }

        // Delete all members
        while (memberHead)
        {
            Member *temp = memberHead;
            memberHead = memberHead->next;
            delete temp;
        }
    }
};

int main()
{
    LibrarySystem library; // MAIN CLASS KA OBJECT BANA LIYA HAI
    int choice;
    while (true) // YEH TAB TAK CHALE GA JAB TAK break; keyword na ajaye
    {
        system("cls"); // for clearing the screen
        cout << "\nLibrary Management System Menu:" << endl;

        // WHICH PROMPT TO SHOW BASED ON MEMBER ID?
        if (library.getLoggedInMemberId() == -1)
        {
            cout << "1. User Log In\n2. Admin Login \n3. Create Account\n4. Exit" << endl;
        }
        else if (library.getLoggedInMemberId() == 1234) // ADMIN ID EQUAL HAI?
        {
            cout << "1. Add Book\n2. Delete Book\n3. Display Books\n4. Display Members\n5. Search Book\n6. Log Out " << endl;
        }
        else // library.getLoggedInMemberId() != -1
        {
            cout << "1. Issue Book \n2. Display Books\n3. Search Book\n4. Log Out" << endl;
        }

        // PROMPT
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (library.getLoggedInMemberId() == -1) // agar kohi logged in hi nahi?
        {
            if (choice == 1) // USER LOGIN
            {
                library.userlogin(); // login function call
            }
            else if (choice == 2) // ADMIN LOGIN
            {
                library.adminlogin();
            }
            else if (choice == 3) // CREATE ACCOUNT
            {
                string name, password;
                bool digitn = false;
                cout << "\nEnter Member Name: ";
                cin.ignore();
                getline(cin, name);
                for (char i : name) // for each loop
                {
                    if (isdigit(i)) // checking agar character digit tou nahi
                    {
                        digitn = true; // check on hogaya
                        break; // out of for loop
                    }
                }
                if (digitn) // checking purposes
                {
                    cout << " NAME CANNOT CONTAIN NUMBER! \n";
                }
                else
                {
                    cout << "Enter Password: ";
                getline(cin, password);
                library.addMember(name, password);
                }
            }
            else if (choice == 4) // EXIT PERMANETLY
            {
                cout << "Exiting program..." << endl;
                break;
            }
        }
        else if (library.getLoggedInMemberId() == 1234) // ADMIN LOGGED IN
        {
            if (choice == 1) // + BOOK
            {
                string title, author;
                bool digit = false; // for checking if author mai num tou nahi
                cout << "\nEnter Book Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                for (char i : author)
                {
                    if (isdigit(i))
                    {
                        digit = true; // digit hai idhar
                        break; // from for loop
                    }
                }
                if (digit)
                {
                    cout << " AUTHOR NAME CAN'T CONTAIN NUMBER! \n";
                }
                else
                {
                library.addBook(title, author);
                }
            }
            else if (choice == 2) // DELETE BOOK
            {
                library.deleteBook();
            }
            else if (choice == 3) // DISPLAYING BOOKS ONLY
            {
                library.displayBooks();
            }
            else if (choice == 4) // DISPLAYING MEMBERS
            {
                library.displayMembers(); // displaying all members affliated with the library
            }
            else if (choice == 5)
                library.searchBook();
            else if (choice == 6) // LOGOUT
                library.logout();
        }
        else // user IS LOGGED INS
        {
            if (choice == 1) // ISSUING A BOOK WITH VALIDATION
            {
                library.issueBook();
            }
            else if (choice == 2) // DISPLAYING BOOKS ONLY
            {
                library.displayBooks();
            }
            else if (choice == 3) // LOGOUT
                library.searchBook();

            else if (choice == 4) // LOGOUT
                library.logout();
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(); // TAAKAY PROGRAM ROOKE FOR USER INPUT
        cin.get();    // ENTER KEY JAB PRESS HOGA PHIR AGAI JAYE GA AS PER USER
    }
    return 0;
}