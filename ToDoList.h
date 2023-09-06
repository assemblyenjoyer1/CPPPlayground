//
// Created by Reiss, Timo on 05.09.23.
//

#ifndef PROJECTS_TODOLIST_H
#define PROJECTS_TODOLIST_H


#include <string>
#include <list>

class ToDoList {
private:
    std::string name;
    std::list<std::string> myList;
public:
    ToDoList(){
        this->name = "TODO LIST";
    }
    explicit ToDoList(std::string name){
        this->name = name;
    }
    void insertTask();
    void removeTask();
    void showList();
    void showMenu();
};


#endif //PROJECTS_TODOLIST_H
