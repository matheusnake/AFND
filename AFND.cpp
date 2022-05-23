#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

vector<string> split (const string &s) {
        vector<string> result;
        stringstream ss (s);
        string item;

        while (getline (ss, item, ' ')) {
            result.push_back (item);
        }

        return result;
}

class AFND {

    public:
        AFND(string line){
            vector<string> w = split(line);
            state = w.at(0);
            word = w.at(1);
            nextState = w.at(2);
        };
        ~AFND(){};

        string word,state,nextState;
        
        
};

 bool sim(list<AFND> afndL, string w, string init,vector<string> final){

    std::list<string> final_states,helper;
    final_states.insert(final_states.begin(),init);

    for(int k=0; k<(int)w.size(); k++) {

        helper.clear();

        for (auto x : final_states){
                
                for (const AFND & afnd : afndL) {
                    
                    if(x == afnd.state){

                        if(afnd.word.at(0) == w[k]){                 
                            helper.insert(helper.end(),afnd.nextState);
                        }
                        
                    }
                }


        }

        final_states = helper;

    }

    bool warning = false;
    
        for (auto u : final_states){
            for(auto x : final){
                if(x == u){
                    return true;
                }
            }
        }
    
    return warning;
}

int main () {

    string line,stateInit = "0",stateA;
    int transitions = 0;
    
    getline(cin, line);
    vector<string> states = split(line);
    getline(cin, line);
    vector<string> alphabet = split(line);
    cin >> transitions;

    std::list<AFND> list;

    for(int i = 0; i<transitions; i++){
        getline(cin>>ws,line);
        vector<string> test = split(line);
        int cout = 0;

        for(auto testA : alphabet){
            if(testA == test.at(1)){
                list.insert(list.end(),AFND(line));
                break;
            } else{
                cout++;
            }
        }

        if(cout == (int)alphabet.size()){
            i--;
        }

    }

    getline(cin, stateInit);
    getline(cin, line);
    vector<string> stateFinal = split(line);

    getline(cin>>ws, line);
    vector<string> words = split(line);

    for (int i = 0; i<(int)words.size(); i++) {

        string wPointer = words.at(i);
        stateA = stateInit;

        if(sim(list,wPointer,stateInit,stateFinal)) cout << "S" << endl;
        else cout << "N" << endl;

    }

    return 1;
    
}