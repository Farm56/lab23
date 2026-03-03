#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string textline;
    while(getline(file, textline)){
        size_t idx = textline.find(':');
        if (idx != string::npos) {
            string name = textline.substr(0, idx);
            names.push_back(name);
            
            int s1, s2, s3;
            sscanf(textline.c_str() + idx + 1, "%d %d %d", &s1, &s2, &s3);
            int sum = s1 + s2 + s3;
            scores.push_back(sum);
            grades.push_back(score2grade(sum));
        }
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin, line);
    
    size_t spacePos = line.find_first_of(" ");
    if (spacePos != string::npos) {
        command = line.substr(0, spacePos);
        key = line.substr(spacePos + 1);
    } else {
        command = line;
        key = "";
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        string g(1, grades[i]);
        if(g == key){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            // Print the top separator line
            cout << "---------------------------------\n";
            // Print invalid command message
            cout << "Invalid command.\n";
            // Print the bottom separator line
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}