#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "csvstream.hpp" 
using namespace std;

class Classifier {
private: 
    bool debug; // 1 is debug 0 is don't debug 
    int numPosts;
    int uniqueWords; 
    map <string,int> numPostsContainingWord; 
    map <string,int> numPostsWithLabel;
    map <pair<string,string>, int> numPostWithLabelThatContainsWord;
public: 
    Classifier (bool debug) 
    : debug (debug), numPosts (0),uniqueWords(0){

    } 
    void print (string input ){
        if (debug){
            cout << input << endl; 
        }
    }

    set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
    }

    void train (csvstream& stream){
        print ("training data:"); 
        map<string,string> row;  
        while (stream >> row){
            ++numPosts;
            print ("  label = " + row["tag"] + ", content = "+ row["content"]);
            set<string> words = unique_words(row["content"]);

             // adding the num of posts to label 
            string label = row["tag"];
            pair<std::map<string,int>::iterator, bool> pairchild;
            pair<string, int> pary;
            pary.first = label;
            pary.second = 1;
            pairchild = numPostsWithLabel.insert(pary);
            if(!pairchild.second){
                ++(*pairchild.first).second;
            }
            // num unique words totall 
            for(string single : words){
                pair<string, int> parry;
                parry.first = single;
                parry.second = 1;
                pair<std::map<string,int>::iterator, bool> pared;
                pared = numPostsContainingWord.insert(parry);
                if(!pared.second){
                    ++(*pared.first).second;
                }
                
                pair<string,string> yummy; 
                yummy.first = label; 
                yummy.second = single; 
                pair<pair<string,string>,int> inserter; 
                pair<std::map<pair<string,string>,int>::iterator, bool> banana;
                banana = numPostWithLabelThatContainsWord.insert(inserter);
                if(!banana.second){
                    ++(*banana.first).second;
                }
        }
    }
      uniqueWords = numPostsContainingWord.size();
    cout << "trained on " << to_string(numPosts) << " examples" << endl;
        print ("vocabulary size = " + to_string(uniqueWords));
        classPrint();
    }
    void classPrint(){
        print("classes: ");
        std::map<string,int>::iterator help = numPostsWithLabel.begin();
        for (;help != numPostsWithLabel.end(); ++help){
            print((*help).first+", "+to_string((*help).second) + 
            " examples, log-prior = "+logPrior((*help).second));
        }
        print("classifier parameters: ");
        std::map<pair<string,string>,int>::iterator yumm = numPostWithLabelThatContainsWord.begin();
        for (; yumm!=numPostWithLabelThatContainsWord.end();++yumm){
            print((*yumm).first.first+":"+(*yumm).first.second+
            ", count = "+to_string((*yumm).second)+", log-likelihood = "+
            logLikelihood((*yumm).first.first,(*yumm).second));
        }
    }
    string logPrior(int second){
        return to_string(log(second/numPosts));
    }
    string logLikelihood(string help, int second){
        int lover = numPostsWithLabel[help];
        int baby = log(second/lover);
        return to_string(baby);
    }
    void classify(istream& inserting){

    }
    // For each word in set
    // string word;
    // pair<std::map<string,int>::iterator, bool> findingWord;
    // findingWord = numPostsContainingWord.find(word);
    // if()
    

    
};
int main(int argc, char * argv []) {
    cout.precision(3); 
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
    
   

}