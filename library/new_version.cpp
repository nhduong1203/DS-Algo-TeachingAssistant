#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>



using namespace std;

#define MAX_LINES 1000
#define size 10e6



int total_sub = 0;
int users[3][10000000] = {0};
int books[10000000] = {0};
int days[3000] = {0};
const char* bookCategory[] = {"economics", "history", "science"};


int findMaxValue(const int books[]) {
    int max = books[0];
    for (int i = 1; i < size; i++) {
        if (books[i] > max) {
            max = books[i];
        }
    }
    return max;
}

int timeStringToDays(char* timeStr) {
    int day, month, year;
    sscanf(timeStr, "%d/%d/%d", &day, &month, &year);
    return (day - 1) + 31 * (month - 1) + 372 * (year - 2019);
}

void parse_input(string datafile, string outputfile) {
    std::ifstream file(datafile); // Open file
    std::string line;
    std::ofstream outputFile(outputfile);

    while (std::getline(file, line)) {
        char uid[100], bid[100], book_category[100], start_date[100];
        std::istringstream iss(line);
        iss >> uid >> bid >> book_category >> start_date;
        if (strcmp(uid, "#") == 0) {
            break;
        }
        total_sub += 1;
        int int_uid = atoi(&uid[3]);
        int int_bid = atoi(&bid[3]);
        
        if (strcmp("economics", book_category) == 0){
            users[0][int_uid]++;
        }
        else if (strcmp("history", book_category) == 0){
            users[1][int_uid]++;
        }
        else users[2][int_uid]++;
        int this_day = timeStringToDays(start_date);
        days[this_day] += 1;
        
        books[int_bid]++;
    }
    for(int i=1; i<3000; i++){
        days[i] += days[i-1];
    }

    while(std::getline(file, line)){
        char query[100];
        std::istringstream iss(line);
        iss >> query; 
        if (strcmp(query, "#") == 0) {
            break;
        }
        if (strcmp("?total_book_borrow", query)==0){
            outputFile << total_sub << "\n";
        }
        else if(strcmp(query, "?best_book") == 0){
            int r = findMaxValue(books);
            outputFile << r << "\n";
        }
        else if(strcmp(query, "?number_user_borrow") == 0){
            char this_uid[100];
            iss >> this_uid;
            int this_int_uid = atoi(&this_uid[3]);
            int r = 0;
            for (int i=0; i<3; i++){
                r += users[i][this_int_uid];
            }
            outputFile << r << "\n";
        }
        else if(strcmp(query, "?user_favourite_category") == 0){
            char this_uid[100];
            iss >> this_uid;
            int this_int_uid = atoi(&this_uid[3]);
            int max = -1;
            for(int i=0; i<3; i++){
                if(users[i][this_int_uid] > max){
                    max = users[i][this_int_uid];
                }
            }
            if (max == 0){
                outputFile << "0\n";
                continue;
            } 
            for(int i=0; i<3; i++){
                if(users[i][this_int_uid] == max){
                    outputFile <<  bookCategory[i] << " ";
                }
            }
            outputFile << "\n";

        }
        else if(strcmp(query, "?total_borrow_period") == 0){
            char start_date[100], end_date[100];
            iss >> start_date >> end_date;
            int int_start_day = timeStringToDays(start_date);
            int int_end_day = timeStringToDays(end_date);
            
            if(int_end_day < int_start_day) outputFile << "0\n";
            else{
                int r;
                if(int_start_day == 0) r = days[int_end_day];
                else r = days[int_end_day] - days[int_start_day - 1];
                outputFile << r << "\n";
            }
        }


    }

}



int main() {
    string infile = "./total_data/query_4/total_book_0.txt";
    string outfile = "./result/query_4/total_book_0.txt";
    parse_input(infile, outfile);
    return 0;
}
