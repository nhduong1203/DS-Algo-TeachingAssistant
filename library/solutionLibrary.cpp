#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_L 20
#define M 2000
#define N 2000

int totalOrders = 0;

typedef struct Book{
    string bid;
    string category;
    int numberBookBorrow = 0;
    struct Book* leftChild;
    struct Book* rightChild;
}Book;

typedef struct User{
    string uid;
    int numberUserBorrow = 0;
    vector<string> listBook;
    struct User* leftChild;
    struct User* rightChild;
}User;

typedef struct Category{
    string cate;
    int number = 0;
    struct Category* leftChild;
    struct Category* rightChild;
}Category;

Book* makeBook(string bid, string category){
    Book* p = new Book();
    p->bid = bid;
    p->category = category;
    p->numberBookBorrow = 1;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}

User* makeUser(string uid, vector<string>& listBook){
    User* p = new User();
    p->uid = uid;
    p->numberUserBorrow = 1;
    p->listBook = listBook;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}

Category *makeCategory(string category){
    Category* p = new Category();
    p->cate = category;
    p->number = 1;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}


Book* B[M];
User* U[N];
Category* C[M];

Book* rootB;
User* rootU;
Category* rootC;

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
    string bid = data[1];
    string category = data[2];

    //Book
    Book* thisBook = makeBook(bid, category);
    int hashValueBook = hashFunction(bid);
    if (B[hashValueBook] == NULL) B[hashValueBook] = thisBook;
    else{
        B[hashValueBook]->numberBookBorrow += 1;
    }

    // User
    int hashValueUser = hashFunction(uid);
    if (U[hashValueUser] == NULL) {
        vector<string> listBook;
        listBook.push_back(bid);
        User* thisUser = makeUser(uid, listBook);
        U[hashValueUser] = thisUser;}
    else{
        U[hashValueUser]->numberUserBorrow  += 1;
        U[hashValueUser]->listBook.push_back(bid);
    }

    //Category
    int hashValueCategory = hashFunction(category);
    Category* thisCategory = makeCategory(category);
    if (C[hashValueCategory] == NULL) C[hashValueCategory] = thisCategory;
    else{
        C[hashValueCategory]->number += 1;
    }
}

User* insertBSTUser(User* insert, User* r){
    if(r == NULL) return insert;
    //if(qty == r->qty) return r;
    if(insert->numberUserBorrow <= r->numberUserBorrow) r->leftChild = insertBSTUser(insert,r->leftChild);
    else r->rightChild = insertBSTUser(insert,r->rightChild);
    return r;
}

Category* insertBSTCategory(Category* insert, Category* r){
    if(r == NULL) return insert;
    if(insert->number <= r->number) r->leftChild = insertBSTCategory(insert, r->leftChild);
    else r->rightChild = insertBSTCategory(insert,r->rightChild);
    return r;
}

Book* insertBSTBook(Book* insert, Book* r){
    if(r == NULL) return insert;
    if(insert->numberBookBorrow <= r->numberBookBorrow) r->leftChild = insertBSTBook(insert,r->leftChild);
    else r->rightChild = insertBSTBook(insert,r->rightChild);
    return r;
}

void inOrderCategory(Category* r){
    if(r == NULL) return;
    inOrderCategory(r->leftChild);
    cout << r->cate<< " " << r->number<<endl;
    inOrderCategory(r->rightChild);
}

void inOrderUser(User* r){
    if(r == NULL) return;
    inOrderUser(r->leftChild);
    cout << r->uid << " " << r->numberUserBorrow<<endl;
    inOrderUser(r->rightChild);
}



void bestUser(User* r){
    if(r->rightChild == NULL) cout << r->uid << " " << r->numberUserBorrow<<endl;
    else bestUser(r->rightChild);
}

void bestBook(Book* r){
    if(r->rightChild == NULL) cout << r->bid << " " <<r->category << " "<< r->numberBookBorrow<<endl;
    else bestBook(r->rightChild);
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
            find_insert(strings);
            
        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }

    // Construct BST
    for(int i=0; i<N; i++){
        if(B[i] == NULL) continue;
        else rootB = insertBSTBook(B[i], rootB);
    }
    for(int i=0; i<M; i++){
        if(U[i] == NULL) continue;
        else rootU = insertBSTUser(U[i], rootU);
    }
    for(int i=0; i<M; i++){
        if(C[i] == NULL) continue;
        else rootC = insertBSTCategory(C[i], rootC);
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
            //cout<<query<<endl;
            

            if(query == "?total_book_borrow"){
                cout << totalOrders <<endl;
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?best_book"){
                bestBook(rootB);
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?best_user"){
                bestUser(rootU);
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?number_user_borrow"){
                string uid = strings[1];
                int hashValueUser = hashFunction(uid);
                cout << U[hashValueUser]->numberUserBorrow <<endl;
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?list_user_borrow"){
                string uid = strings[1];
                int hashValueUser = hashFunction(uid);
                for(int i=0; i<U[hashValueUser]->listBook.size(); i++){
                    cout << U[hashValueUser]->listBook[i] <<endl;
                }

                
                cout<< "------------------------------------------" <<endl;
            }
            else if(query == "?sort_category"){
                inOrderCategory(rootC);
            }

        }
        file.close(); // close
    }
    else {
        std::cout << "Can not open file!" << std::endl;
    }
}

int main(){
    
    string datafile = "./data/test.txt";
    int checkpoint = constructData(datafile);
    solveQuery(datafile, checkpoint);
}
