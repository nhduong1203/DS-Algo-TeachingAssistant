#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//<OrderID>   <CustomerID>      <ProductID>   <Qty>   <Date-time>


int len = 9;


string convertString(int n, int len, string type){
    string s(len, '0');
    int i = len-1;
    while(n > 0){
        int r = n%10;
        s[i] = '0' + r;
        n = n/10;
        i--;
    }
    // while(i >= 3){
    //     s[i] = '0'; i--;
    // }
    s[2] = 'D';
    s[1] = 'I';

    if(type=="product") s[0] = 'P';
    else if (type=="customer") s[0] = 'C';
    else s[0] = 'O';
    
    s[len] = '\0';
    return s;
}

string dateConvert(int day){
    string s(2, '0');
    int i = 1;
    while(day>0){
        s[i] = '0'+day%10;
        day = day/10;
        i--;
    }
    s[2] = '\0';
    return s;
}


void genData(string filename, int numberOrder, int numberCus, int numberProduct){

    std::ifstream infile(filename);
    bool file_exists = infile.good();

    // creat file if not exist
    if (!file_exists) {
        std::ofstream outfile(filename);
    }

    // open file to write 
    std::ofstream outfile(filename, std::ios::out | std::ios::trunc);

    for(int i=0; i<numberOrder; i++){
        string oid = convertString(i+1, len, "order");
        int cusID = rand() % numberCus;
        int proID = rand() % numberProduct;
        string cid = convertString(cusID, len,  "customer");
        string pid = convertString(proID, len, "product");

        int day = rand() % 28 + 1;
        int month = rand() % 12 + 1;
        int year = rand() % 3 + 2020;
        string date = dateConvert(day) + "/" + dateConvert(month) + "/" + to_string(year);
        int qty = rand()%20 +1;

        // Ghi nội dung vào file
        outfile <<oid<<" "<<cid<<" "<<pid<<" "<<qty<<" "<<date<<std::endl;
    }
    // Đóng file
    outfile.close();
}

int main(){
    // string test = convertString(23,10,"product");
    // cout << test << endl;
    srand(time(NULL));
    
    // genData("data/1.txt", 100,20,28);
    // genData("data/2.txt", 1000,50,100);
    // genData("data/3.txt", 10000,150,300);
    genData("data/test.txt", 100000,700,1500);
}