#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "Contact.h"
// Contact class

ContactBook book;
static void EnterContact() {
    std::cout << "Enter contact's name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Enter contact's phone number: ";
    std::string phone;
    std::cin >> phone;
    std::cout << "Enter contact's email: ";
    std::string email;
    std::cin >> email;
    book.AddContact(name, phone, email);
}

static void RemoveContact() {
    std::string name;
    std::cout << "Enter contact's name: ";
    std::cin >> name;
    book.removeContact(name);
}

int main() {
    char value;
    bool flag = true;

    book.LoadContactsFromFile();
    while (flag == true) {
        std::cout << "Select an option:" << std::endl << "(a to add a contact, r to remove a contact, l to list a contact," <<
            " q to exit)" << std::endl;
        std::cin >> value;
        switch (value) {
            case 'a': {
                EnterContact();
                break;
            }
            case 'r': {
                RemoveContact();
                break;
            }
            case 'l': {
                book.listContacts();
                break;
            }
            case 'q': {
                flag = false;
                book.SaveAllToFile();
                break;
            }
            default: {
                std::cout << "Invalid option." << std::endl;
                break;
            }
        }
    }
    return 0;
}

