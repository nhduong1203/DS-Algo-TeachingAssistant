#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//<OrderID>   <CustomerID>      <ProductID>   <Qty>   <Date-time>


int len = 9;
string school_list[100] = {"HUST", "UET", "FPT", "PTIT", "NEU", "NUCE", "VInUni", "GTVT", "ThuyLoi", "MTA"};
string skill_list[100] = {"C++", "Python", "Java", "HTML/CSS", "Go", "Ruby", "PHP", "JavaScripts", "NodeJs", "Pascal"};
string job_list[100] = {"Frontend", "Backend", "FullStack", "AIEngineer", "DataEngineer", "DevOps", "DataScientist", "Embedding", "DataAnalyst", "GameDeveloper"};
int N = 10;


string convertString(int n, int len){
    string s(len, '0');
    int i = len-1;
    while(n > 0){
        int r = n%10;
        s[i] = '0' + r;
        n = n/10;
        i--;
    }
    s[2] = 'D';
    s[1] = 'I';
    s[0] = 'U';
    
    s[len] = '\0';
    return s;
}

void genData(string filename, int numberUser){

    std::ifstream infile(filename);
    bool file_exists = infile.good();

    // creat file if not exist
    if (!file_exists) {
        std::ofstream outfile(filename);
    }

    // open file to write 
    std::ofstream outfile(filename, std::ios::out | std::ios::trunc);

    for(int i=0; i<numberUser; i++){
        string uid = convertString(i+1, len);
        int jobID = rand() % N;
        int skillID = rand() % N;
        int schoolID = rand() % N;
        string job = job_list[jobID];
        string skill = skill_list[skillID];
        string school = school_list[schoolID]; 

        // Ghi nội dung vào file
        outfile <<uid<<" "<<school << " "<<job<<" "<<skill<<std::endl;
    }
    // Đóng file
    outfile.close();
}

int main(){

    srand(time(NULL));
    
    // genData("data/1.txt", 100,20,28);
    // genData("data/2.txt", 1000,50,100);
    // genData("data/3.txt", 10000,150,300);
    // genData("data/test.txt", 100000,700,1500);
    //genData("data/1.txt", 1000);
    // genData("data/2.txt", 10000);
    // genData("data/3.txt", 100000);
    genData("data/4.txt", 1000000);
}