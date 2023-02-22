#include <iostream>
#include <cstring>
#include "rapidxml_utils.hpp"  // I used rapidxml library
     

using namespace std;
rapidxml::xml_node<>* nodeFrame;
rapidxml::xml_node<>* test = NULL;
char numbers[1000][1000];           //Every number will be collected in this array
int numberAmount = 0;


//This function will look for a specific node
//It is a recursive function and it will look for every node in the XML file until it finds the node that is called "aixm:voice"
//because that is the node where I can find the phone number

void find_phone_number(rapidxml::xml_node<> *node,char *str) {
    if (node != NULL && strcmp(node->name(),str) == 0){
        test = node;
        int help = 0;
        for (int j = 0;j<=numberAmount ;j++){
            if (strcmp(numbers[j],node->first_node()->value()) == 0)
                help = 1;
        }
        if (help == 0){
            strcpy(numbers[numberAmount],node->first_node()->value());
            numberAmount++;
        }
    }
    if ( node->name() != NULL && node->next_sibling() != NULL ) {
        node = node->next_sibling();
        find_phone_number(node,str);
    }
    if ( node->name() != NULL && node->first_node() != NULL ){
        node = node->first_node();
        find_phone_number(node,str);
    }
    return;
}

int main()
{
    char file[1000];

    char str[] = "aixm:voice";                        //the node that I'm looking for

    cout << "Type in the location of the XML file, for example: C:/Users/vbarc/OneDrive/Dokumenty/AirportHeliport.xml"<< endl;

    cin >> file;                                      //the user have to type in the XML file location

    rapidxml::file<> xmlFile(file);

    rapidxml::xml_document<> doc;

    doc.parse<rapidxml::parse_full>(xmlFile.data());

    nodeFrame = doc.first_node()->next_sibling();

    find_phone_number(nodeFrame,str);

    if (test != NULL) {
        for(int j = 0;j<numberAmount;j++){
            cout << numbers[j]<<endl;
        }
        return 0;
    }
    else{
        cout << "ERROR !!! There is no phone number in this XML file !!!" << endl;
        return 1;
    }
}



