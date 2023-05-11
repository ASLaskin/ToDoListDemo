//
// Created by Andrew Laskin on 5/10/23.
//

#include "txtEditor.h"
#include <vector>
#include <fstream>
#include <iostream>


void txtEditor::addTex(string thing) {
    ofstream file("resources/todo.txt", ios::app);
    file << thing << endl;
    file.close();
}
void txtEditor::removeTex(int lineNum) {
    //Basically just rewriting the file and excluding the line
    //we want to remove effectively deleting
    fstream file("resources/todo.txt",ios::in | ios::out);

    vector<string> lines;
    string temp;
    while (getline(file, temp)) {
        lines.push_back(temp);
    }
    file.close();

    file.open("resources/todo.txt", ios::out);

    int lineCount = 1;
    for (const auto& currentLine : lines) {
        if (lineCount != lineNum) {
            file << currentLine << endl;
        }
        lineCount++;
    }
    file.close();
}
vector<string > txtEditor::getVector() {
    fstream file("resources/todo.txt",ios::in | ios::out);

    vector<string> lines;
    string temp;
    while (getline(file, temp)) {
        lines.push_back(temp);
    }
    file.close();

    int i = 1;
    vector<string> toDoStrings;
    for (string line : lines){
        string toOut = to_string(i);
        toOut += ". ";
        toOut += line;

        toDoStrings.push_back(toOut);
        i++;
    }
    return toDoStrings;
}
txtEditor::txtEditor() {

}