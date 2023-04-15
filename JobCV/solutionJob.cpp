#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_L 20
#define M 2000
#define N 2000

int totalUser = 0;


typedef struct School{
    string name;
    int count;
    struct School* leftChild;
    struct School* rightChild;
}School;
School* Sc[N];
School* rootSc;
School* makeSchool(string name, int count){
    School* p = new School();
    p->name = name;
    p->count = count;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}

typedef struct Skill{
    string name;
    int count;
    struct Skill* leftChild;
    struct Skill* rightChild;
}Skill;
Skill* makeSkill(string name, int count){
    Skill* p = new Skill();
    p->name = name;
    p->count = count;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}
Skill* Sk[N];
Skill* rootSk;

typedef struct Job{
    string name;
    int count;
    struct Job* leftChild;
    struct Job* rightChild;
};
Job* makeJob(string name, int count){
    Job* p = new Job();
    p->name = name;
    p->count = count;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}
Job* J[N];
Job* rootJ;



int hashFunction(string id){
    int c = 0;
    int n = id.length();
    for(int i = 3; i < n; i++){
        c = (c*256 + id[i]) % M;
    }
    return c;
}

std::vector<std::string> extractData(string line) {
    std::vector<std::string> strings;
    string temp = "";
    line += ' ';
    int n = line.length();
    for(int i=0; i<n; i++){
        if(line[i] == ' '){
            strings.push_back(temp);
            temp = "";
        }
        else{
            temp += line[i];
        }
    }
    return strings;
}

void find_insert(vector<string>& data){
    string uid = data[0];
    string school = data[1];
    string skill = data[2];
    string job = data[3];

    // User
    int hashValueSchool = hashFunction(school);
    if (Sc[hashValueSchool] == NULL) {  

        School* thisSchool = makeSchool(school, 1);
        Sc[hashValueSchool] = thisSchool;
    }
    else{
        Sc[hashValueSchool]->count++;
    }

    int hashValueSkill= hashFunction(skill);
    if (Sk[hashValueSkill] == NULL) {  

        Skill* thisSkill = makeSkill(school, 1);
        Sk[hashValueSchool] = thisSkill;
    }
    else{
        Sk[hashValueSkill]->count++;
    }

    int hashValuejob= hashFunction(job);
    if (J[hashValuejob] == NULL) {  

        Job* thisJob = makeJob(job, 1);
        J[hashValuejob] = thisJob;
    }
    else{
        J[hashValuejob]->count++;
    }



}

School* insertBSTSchool(School* insert, School* r){
    if(r == NULL) return insert;
    if(insert->count <= r->count) r->leftChild = insertBSTSchool(insert,r->leftChild);
    else r->rightChild = insertBSTSchool(insert,r->rightChild);
    return r;
}

Skill* insertBSTSkill(Skill* insert, Skill* r){
    if(r == NULL) return insert;
    if(insert->count <= r->count) r->leftChild = insertBSTSkill(insert,r->leftChild);
    else r->rightChild = insertBSTSkill(insert,r->rightChild);
    return r;
}

Job* insertBSTJob(Job* insert, Job* r){
    if(r == NULL) return insert;
    if(insert->count <= r->count) r->leftChild = insertBSTJob(insert,r->leftChild);
    else r->rightChild = insertBSTJob(insert,r->rightChild);
    return r;
}



int constructData(string datafile){
    int nextLine = 0;
    std::ifstream file(datafile); // Open file
    std::string line;
    std::vector<std::string> strings; // store data extract from each line

    // Read data
    if (file.is_open()) { // Check if file open succesfull
        while (std::getline(file, line)) { // readline
            nextLine += 1;
            if(line[0] == '#') break;
            strings = extractData(line);
            find_insert(strings);
            totalUser++;
            
        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }

    // Construct BST
    for(int i=0; i<N; i++){
        if(Sc[i] == NULL) continue;
        else rootSc = insertBSTSchool(Sc[i], rootSc);
    }
    for(int i=0; i<M; i++){
        if(Sk[i] == NULL) continue;
        else rootSk = insertBSTSkill(Sk[i], rootSk);
    }
    for(int i=0; i<M; i++){
        if(J[i] == NULL) continue;
        else rootJ = insertBSTJob(J[i], rootJ);
    }
    return nextLine;
}

void inOrderSchool(School* r){
    if(r == NULL) return;
    inOrderSchool(r->leftChild);
    cout << r->name << " " << r->count<<endl;
    inOrderSchool(r->rightChild);
}

void reverseInOrderSkill(Skill *r, int &a){
    if(r==NULL) return;
    reverseInOrderSkill(r->rightChild, a);
    if(a >= 5) return;
    cout << r->name << " " << r->count << endl;
    a += 1;
    reverseInOrderSkill(r->leftChild, a);
}

void reverseInOrderJob(Job *r, int &a){
    if(r==NULL) return;
    reverseInOrderJob(r->rightChild, a);
    if(a >= 5) return;
    cout << r->name << " " << r->count << endl;
    a += 1;
    reverseInOrderJob(r->leftChild, a);
}

void solveQuery(string datafile, int checkpoint){
    std::ifstream file(datafile); // Open file
    std::string line;
    int lineIndex = -1;
    std::vector<std::string> strings;
    string query;

    if (file.is_open()) { // Check if file open succesfull
        while (std::getline(file, line)) { // readline
            lineIndex += 1;
            if(lineIndex < checkpoint) continue;
            if(line[0] == '#') break;
            // TODO
            strings = extractData(line);
            query = strings[0];
            //cout<<query<<endl;
            

            if(query == "?number_user"){
                cout << totalUser <<endl;
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?list_school"){
                inOrderSchool(rootSc);
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?top_job"){
                int count = 0;
                reverseInOrderJob(rootJ, count);
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?top_skill"){
                int count = 0;
                reverseInOrderSkill(rootSk, count);
                cout<< "------------------------------------------" <<endl;
            }
            

        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }
}

int main(){
    // string line = "UID000003 BID000002 sports 03/06/2020 28/06/2020";
    // vector<std::string> data = extractData(line);
    // for(int i=0; i<data.size(); i++){
    //     cout << data[i] <<endl;
    // }
    string datafile = "./data/test.txt";
    int checkpoint = constructData(datafile);
    // cout <<checkpoint;
    solveQuery(datafile, checkpoint);

}
