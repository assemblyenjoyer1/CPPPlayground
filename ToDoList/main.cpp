#include <iostream>
#include <list>
#include <utility>

class ToDoList{
private:
    std::string name;
    std::list<std::string> myList;
public:
    ToDoList() : name("TODO LIST") {}
    explicit ToDoList(std::string name) : name(std::move(name)) {}
    void insertTask();
    void removeTask();
    void showList();
    void showMenu();
    void setName();
    void evaluateChoice(int choice);
    void loop();
};

void ToDoList::showMenu() {
    int choice = -1;
    bool fail;
    int nameLength = static_cast<int>(this->name.length());

    do {
        int headerLength = nameLength + 10;

        std::cout << std::string(headerLength, '-') << std::endl;
        std::cout << std::string(headerLength/4, '-') << this->name << std::string(headerLength/4, '-') << std::endl;
        std::cout << std::string(headerLength, '-') << std::endl;

        std::cout << "(1) Aufgabe hinzufügen" << std::endl;
        std::cout << "(2) Aufgabe entfernen" << std::endl;
        std::cout << "(3) Aufgabe(n) anzeigen" << std::endl;
        std::cout << "(4) Name ändern" << std::endl;
        std::cout << "(0) Abbrechen" << std::endl;
        std::cout << std::string(headerLength, '-') << std::endl;

        std::cout << "Deine Auswahl: ";
        std::cin >> choice;
        fail = std::cin.fail();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (fail || choice < 0 || choice > 4);

    evaluateChoice(choice);
}

void ToDoList::evaluateChoice(int choice) {
    switch (choice) {
        case 1:
            insertTask();
            break;
        case 2:
            removeTask();
            break;
        case 3:
            showList();
            break;
        case 4:
            setName();
            break;
        case 0:
            exit(1);
        default:
            break;
    }
}

void ToDoList::setName() {
    std::string userInput;
    std::cout << "Enter name > ";

    getline(std::cin, userInput);

    name = userInput;
    std::cout << "Name was changed successfully" << std::endl;
    loop();
}

void ToDoList::insertTask() {
    std::string userInput;
    std::cout << "Aufgabe hinzufügen:\n(q, um die Eingabe abzubrechen" << std::endl;
    do {
        std::cout << "> ";
        getline(std::cin, userInput);
        if (userInput == "q") {
            break;
        }
        if (userInput.empty()){
            std::cout << "Invalid Input" << std::endl;
        }else{
            myList.push_back(userInput);
        }
    }while (true);
    if(!myList.empty()){
        std::cout << "Einträge erfolgreich hinzugefügt" << std::endl;
    }else{
        std::cout << "Keine Einträge hinzugefügt" << std::endl;
    }
    loop();
}

void ToDoList::showList() {
    if(myList.empty()){
        std::cout << "Empty List - nothing to be shown" << std::endl;
    }

    std::list<std::string>::iterator it;
    it = myList.begin();

    std::cout << this->name << std::endl;
    std::cout << "---------------------" << std::endl;
    for (size_t i = 0; i < myList.size(); i++){
        std::cout << i+1 << ". " << *it++ << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    loop();
}

void ToDoList::loop() {
    std::cout << "Enter, um zurück ins Menü zu gelangen." << std::endl;
    std::cin.get();
    showMenu();
}

void ToDoList::removeTask() {
    std::string userInput = "";
    int choice = -1;
    bool inputOK = false;
    std::list<std::string>::iterator it;
    it = myList.begin();

    for(size_t i = 0; i < myList.size(); i++){
        std::cout << i+1 << ". " << *it++ << std::endl;
    }

    if(myList.empty()){
        std::cout << "Die Liste ist leer." << std::endl;
    }else{
        do{
            inputOK = false;
            std::cout << "Welchen Einträg möchtest du entfernen?" << std::endl;
            getline(std::cin, userInput);
            try {
                choice = std::stoi(userInput);
                inputOK = true;
            }catch(...){
                std::cerr << "Eingabe war inkorrekt" << std::endl;
            }
        } while (!inputOK || choice < 0 || choice > myList.size());
    }

    it = myList.begin();

    for (size_t i = 0; i < (choice-1); i++){
        it++;
    }
    myList.erase(it);
    std::cout << "Der Eintrag wurde erfolgreich entfernt" << std::endl;
    loop();
}

std::ostream & operator << (std::ostream & cout , ToDoList & l){
    l.showMenu();
    return cout;
}
int main() {

    ToDoList myList("Banana King");
    std::cout << myList;
    std::cout << "\n";
    return 0;
}
