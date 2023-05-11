//
// Created by Andrew Laskin on 5/10/23.
//

#ifndef TODOLISTDEMO_TXTEDITOR_H
#define TODOLISTDEMO_TXTEDITOR_H
#include <string>

using namespace std;
class txtEditor {
public:
    txtEditor();
    void addTex(string thing);
    void removeTex(int lineNum);
    vector<string> getVector();

};


#endif //TODOLISTDEMO_TXTEDITOR_H
