#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "csvstream.hpp" 
using namespace std;

int main(int argc, char * argv []) {
    if (argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1; // 69
    }
    if (argv[3] != "--debug"){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1; // 420
    }
    ifstream input(argv[1]);
    if(!input.is_open()){
        cout << "Error opening file: " <<  argv[1] << endl;
        return -1;
    }
    csvstream csvinput(input);
    
    map<string,string> row; 
    int postCount = 0; 
    int uniqueWords = 0; 
    map <string,int> numPostsContainingWord; 
    map <string,int> numPostsWithLabel;
    map <pair<string,string>, int> numPostWithLabelThatContainsWord;
    while (csvinput >> row){
      ++postCount;
        

    }
    
    int n; 
    int unique_views; 
    string tag; 
    string content = "slay"; 
    char comma;
    int total = 0;
    int posts = -1;
    int total;
    bool samePost = false;
    map<string, int> word_posts; 
    map<string, int> label_posts; 
    map<pair<string, string>,int> labelword_posts;
    map<string,int>::iterator it;

}