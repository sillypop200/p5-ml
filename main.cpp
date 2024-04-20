#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "csvstream.hpp" 
#include <cmath>
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
        cout.precision(3);
        if (debug){
            cout << input ; 
        }
    }
    void endlprint(){
        if (debug){
        cout << endl; 
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
        cout.precision(3);
        print ("training data:"); 
        endlprint();
        map<string,string> row;  
        while (stream >> row){
            ++numPosts;
            print ("  label = " + row["tag"] + ", content = "+ row["content"]);
            endlprint();
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
                inserter.first = yummy;
                inserter.second =1; 
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
        cout << endl;
        if (debug){
            cout<<endl;
        }
        classPrint();
    }
    
    void classPrint(){
        cout.precision(3);
        print("classes: "); 
        endlprint();
        std::map<string,int>::iterator help = numPostsWithLabel.begin();
        for (;help != numPostsWithLabel.end(); ++help){
            print("  "+(*help).first+", "+to_string((*help).second) + 
            " examples, log-prior = " );
            if (debug){cout <<logPrior((*help).second);}
            endlprint();
        }
        print("classifier parameters: ");
        endlprint();
        std::map<pair<string,string>,int>::iterator yumm = numPostWithLabelThatContainsWord.begin();
        for (; yumm!=numPostWithLabelThatContainsWord.end();++yumm){
            print("  "+(*yumm).first.first+":"+(*yumm).first.second+
            ", count = "+to_string((*yumm).second)+", log-likelihood = ");
            if (debug){
               cout <<logLikelihood((*yumm).first.first,(*yumm).second,(*yumm).first.second) ;
            }
            endlprint();
        }
        if (debug){
            cout<<endl;
        }
    }
    double logPrior(int second){
        double quo = second;
        double dividend = quo/numPosts;
        return log(dividend);
    }
    double logLikelihood(string label, int bonnie, string word){
        pair<string,string> stringy; 
        stringy.first = label;
        stringy.second = word;
        std::map<pair<string,string>,int>::iterator silly;
        std::map<string,int>::iterator goose;
        silly = numPostWithLabelThatContainsWord.find(stringy);
        if(bonnie==0){
            goose = numPostsContainingWord.find(word);
            if (goose == numPostsContainingWord.end()){
                double baby = 1.0/numPosts; 
                return log(baby);
            }
            else{
                double store = (*goose).second; 
                double vaneesha = store/numPosts;
                return log(vaneesha);
            }
        }   
        cout.precision(3);
        int lover = numPostsWithLabel[label]; 
        double george = bonnie;   
        setprecision(3);
        double baby = log(george/lover);
        return baby;
    }
    pair<string,double> predict(set<string>& words){
        cout.precision(3);
        double score = -10000.0;
        std::map<string,int>::iterator yum = numPostsWithLabel.begin();
        string rishi = (*yum).first;
        for (;yum!=numPostsWithLabel.end();++yum){
            double runningTot = 0.0;
            double logpc = logPrior((*yum).second); // not the problem 
            runningTot = runningTot + logpc;
            for (string single : words){      
                pair<string,string> shawty;
                shawty.first= (*yum).first;
                shawty.second=single;
                std::map<pair<string,string>,int>::iterator mom; 
                mom = numPostWithLabelThatContainsWord.find(shawty); // cant insert 
                if (mom==numPostWithLabelThatContainsWord.end()){
                    (*mom).second =0;
                }
                runningTot += logLikelihood((*yum).first, (*mom).second, single); 
            }
            if (runningTot>score){
                rishi = (*yum).first; 
                score = runningTot; 
            }
        }
        return {rishi,score}; 
    }
    void classify(csvstream& stream){
        cout.precision(3);
        cout << "test data:"<<endl;
        int num = 0; 
        int all = 0;
        map<string,string> row;
        while (stream >> row){
            set<string> words = unique_words(row["content"]);
            pair<string,double> mommy;
            mommy = predict(words);
            cout << "  correct = " << row["tag"] << ", predicted = "<< mommy.first 
            << ", log-probability score = " << mommy.second <<endl;
            cout <<"  content = " << row["content"] << endl << endl;
            if (row["tag"] == mommy.first){ // works 
                ++num;
            }
            all++; // works 
        }
        cout << "performance: " << num << " / " << all << " posts predicted correctly" << endl;
    }

};
int main(int argc, char * argv []) {
    cout.precision(3);
    if (argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1; // 69
    }
    if (argc == 4){
        string geo = argv[3]; 
        if (geo != "--debug"){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1; // 420
        }
    }
    ifstream input(argv[1]);
    if(!input.is_open()){
        cout << "Error opening file: " <<  argv[1] << endl;
        return -1;
    }
    ifstream in(argv[2]);
    if(!in.is_open()){
        cout << "Error opening file: " <<  argv[1] << endl;
        return -1;
    }
    csvstream csvinput(input);
    csvstream meep(in);
    int katie = 0; 
    if (argc==3){
        katie =0 ; 
    }
    else{
        katie =1; 
    }
    Classifier conner (katie);
    conner.train(csvinput);
    conner.classify(meep);
}