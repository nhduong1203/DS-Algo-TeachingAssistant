#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_L 20
#define M 2000
#define N 2000
//<OrderID>   <CustomerID>      <ProductID>   <Qty>   <Date-time>

int totalOrders = 0;

typedef struct Node{
    string pid;
    string cid;
    int qty;
    int numberOrder = 0;
    int index;
    struct Node* leftChild;
    struct Node* rightChild;
}Node;

Node* makeNode(string cid, string pid, int qty){
    Node* p = new Node();
    p->pid = pid;
    p->cid = cid;
    p->qty = qty;
    p->numberOrder = 1;

    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}

std::vector<std::string> extractData(string line) {
    std::vector<std::string> strings;
    string data[5];
    string temp = "";
    int n = line.length();
    int count = 0;
    for(int i=0; i<n; i++){
        if(line[i] == ' '){
            strings.push_back(temp);
            data[count] = temp;
            temp = "";
            count++;
        }
        else{
            temp += line[i];
        }
    }
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
    Node* thisNodeC = makeNode(cid, pid, qty);
    int hashValueC = hashFunction(cid);
    if (C[hashValueC] == NULL) C[hashValueC] = thisNodeC;
    else{
        C[hashValueC]->qty += qty;
        C[hashValueC]->numberOrder += 1;
    }

    Node* thisNodeP = makeNode(cid, pid, qty);
    int hashValueP = hashFunction(pid);
    if (P[hashValueP] == NULL) P[hashValueP] = thisNodeP;
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

void reverseInOrder(Node *r, int &a, string type){
    if(r==NULL) return;
    reverseInOrder(r->rightChild, a, type);
    if(a >= 5) return;
    if (type == "customer") cout << r->cid << " " << r->qty << endl;
    else if (type == "product")cout << r->pid << " " << r->qty << endl;
    a += 1;
    reverseInOrder(r->leftChild, a, type);
}

void inOrder(Node* r){
    if(r == NULL) return;
    inOrder(r->leftChild);
    cout << r->cid << " " << r->pid << " " << r->qty<<endl;
    inOrder(r->rightChild);
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
            totalOrders += 1;
            strings = extractData(line);
            string cid = strings[1];
            string pid = strings[2];
            int qty = std::stoi(strings[3]);
            find_insert(cid, pid, qty);
            
        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }

    // Construct BST
    for(int i=0; i<N; i++){
        if(C[i] == NULL) continue;
        else rootC = insertBST(C[i]->cid, C[i]->pid, C[i]->qty, rootC);
    }
    for(int i=0; i<M; i++){
        if(P[i] == NULL) continue;
        else rootP = insertBST(P[i]->cid, P[i]->pid, P[i]->qty, rootP);
    }
    return nextLine;
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

            if(query == "?count_total_order"){
                cout << totalOrders <<endl;
            }

            else if(query == "?active_customer"){
                string cid = strings[1];
                int hashValue = hashFunction(cid);
                if (C[hashValue] == NULL) cout << "False"<<endl;
                else cout << "True"<<endl;
            }

            else if(query == "?number_customer's_order"){
                string cid = strings[1];
                int hashValue = hashFunction(cid);
                if (C[hashValue] == NULL) cout << "0"<<endl;
                else cout << C[hashValue]->numberOrder << endl;
            }
            
            else if(query == "?best_customer"){
                int count = 0;
                reverseInOrder(rootC, count, "customer");
            }

            else if(query == "?best_product"){
                int count = 0;
                reverseInOrder(rootP, count, "product");
            }

        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }
}


int main(){
    constructData("data/1.txt");
    int count = 0;
    reverseInOrder(rootC, count, "customer");
}

