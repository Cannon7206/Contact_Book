//
// Created by christian on 6/27/25.
//
class Contact{
    private:
    std::string name;
    std::string phone;
    std::string email;
    public:
    Contact(std::string name, std::string phone, std::string email)
        : name(std::move(name)), phone(std::move(phone)), email(std::move(email)) {}
    void display() const {
        std::cout << name << " " << phone << " " << email << std::endl;
    }
    [[nodiscard]] std::string getName() const {
        return name;
    }
    [[nodiscard]] std::string getPhone() const {
        return phone;
    }
    [[nodiscard]] std::string getEmail() const {
        return email;
    }
};
//Contact book class
class ContactBook {
private:
    std::vector<Contact*> contacts; //create a vector for a dynamic memory allocation

public:
    typedef std::string string; // i got tired of typing std::string

    [[nodiscard]] bool contactExists(const std::string& name, const string& phone, const string& email) const {
        for (const auto* contact : contacts) {
            if (contact->getName() == name && contact->getPhone() == phone && contact->getEmail() == email) {
                return true;
            }
        }
        return false;
    }

    void AddContact(const string& name, const string& phone, const string& email) {
        if (!contactExists(name, phone, email)) {
            contacts.push_back(new Contact(name, phone, email)); //add new contact to dynamic array
        }
        else {
            std::cout << "Contact already exists" << std::endl;
        }
    }

    void removeContact(const string& name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if ((*it)->getName() == name) {
                std::cout << "Contact removed: " << (*it)->getName() << std::endl;
                delete *it;
                contacts.erase(it);
                return;
            }

        }
    }

    void listContacts() const {
        int number = 1;
        for (const auto contact : contacts) {
            std::cout << number << ". " << contact->getName() << " "
            << contact->getPhone() << " " << contact->getEmail() << std::endl;
            number++;
        }
    }

    void SaveAllToFile() const {
        std::ofstream outFile("/home/christian/Documents/contacts.txt");
        for (const auto contact : contacts) {
            outFile << contact->getName() << "," <<  contact->getPhone() << "," << contact->getEmail() << std::endl;
        }
    }

    void LoadContactsFromFile() {
        std::ifstream inFile("/home/christian/Documents/contacts.txt");
        if (!inFile) {
            std::cerr << "Unable to open file" << std::endl;
            return;
        }
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string name, phone, email;

            std::getline(ss, name, ',');
            std::getline(ss, phone, ',');
            std::getline(ss, email, ',');
            if (!name.empty() && !phone.empty() && !email.empty()) {
                AddContact(name, phone, email);
            }
        }

        inFile.close();
    }
    ~ContactBook() {
        for (const Contact* c : contacts) {
            delete c;
        }

    };


};
#ifndef CONTACT_H
#define CONTACT_H

#endif //CONTACT_H
