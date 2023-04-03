#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_L 20
#define M 2000
#define N 2000
//<OrderID>   <CustomerID>      <ProductID>   <Qty>   <Date-time>

typedef struct Node{
    string pid;
    string cid;
    int qty;
    int index;
    struct Node* leftChild;
    struct Node* rightChild;
}Node;

Node* makeNode(string cid, string pid, int qty){
    Node* p = new Node();
    p->pid = pid;
    p->cid = cid;
    p->qty = qty;

    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}

std::vector<std::string> get_strings(string line) {
    std::vector<std::string> strings;
    string data[5];
    string temp = "";
    int n = line.length();
    int count = 0;
    for(int i=0; i<n; i++){
        if(line[i] == ' '){
            data[count] = temp;
            temp = "";
            count++;
        }
        else{
            temp += line[i];
        }
    }
    strings.push_back(data[1]);
    strings.push_back(data[2]);
    strings.push_back(data[3]);
    return strings;
}

Node* C[N];
Node* P[M];
Node* rootC;
Node* rootP;

int hashFunction(string id){
    int c = 0;
    int n = id.length();
    for(int i = 3; i < n; i++){
        c = (c*256 + id[i]) % M;
    }
    return c;
}

void find_insert(string cid, string pid, int qty){
    Node* thisNode = makeNode(cid, pid, qty);

    int hashValueC = hashFunction(cid);
    if (C[hashValueC] == NULL) C[hashValueC] = thisNode;
    else{
        C[hashValueC]->qty += qty;
    }

    int hashValueP = hashFunction(pid);
    if (P[hashValueP] == NULL) P[hashValueP] = thisNode;
    else{
        P[hashValueP]->qty += qty;
    }
}

Node* insertBST(string cid, string pid, int qty, Node* r){
    if(r == NULL) return makeNode(cid, pid, qty);
    //if(qty == r->qty) return r;
    if(qty <= r->qty) r->leftChild = insertBST(cid, pid, qty,r->leftChild);
    else r->rightChild = insertBST(cid, pid, qty,r->rightChild);
    return r;
}

void run(string datafile){
    std::ifstream file(datafile); // Open file
    std::string line;

    std::vector<std::string> strings; // store data extract from each line

    if (file.is_open()) { // Check if file open succesfull
        while (std::getline(file, line)) { // readline
            if(line[0] == '#') break;
            strings = get_strings(line);
            string cid = strings[0];
            string pid = strings[1];
            int qty = std::stoi(strings[2]);
            find_insert(cid, pid, qty);
            // rootC = insertBST(cid, pid, qty, rootC);
            // rootP = insertBST(cid, pid, qty, rootP);
        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }

    for(int i=0; i<N; i++){
        if(C[i] == NULL) continue;
        else rootC = insertBST(C[i]->cid, C[i]->pid, C[i]->qty, rootC);
    }

    for(int i=0; i<M; i++){
        if(P[i] == NULL) continue;
        else rootP = insertBST(P[i]->cid, P[i]->pid, P[i]->qty, rootP);
    }
}

void inOrder(Node* r){
    if(r == NULL) {
        return;
    }
    inOrder(r->leftChild);
    cout << r->cid << " " << r->pid << " " << r->qty<<endl;
    inOrder(r->rightChild);
}

int main(){
    run("data/0.txt");

    // for(int i=0; i<N; i++){
    //     if(C[i] == NULL) continue;
    //     else rootC = insertBST(C[i]->cid, C[i]->pid, C[i]->qty, rootC);
    // }

    inOrder(rootC);
    cout <<endl;
    inOrder(rootP);
}

