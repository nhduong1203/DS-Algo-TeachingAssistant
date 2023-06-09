#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define size 10e6

int total_sub = 0;
int users[3][10000000] = {0};
int books[10000000] = {0};
int days[3000] = {0};
const char* bookCategory[] = {"history", "science", "economics"};


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

void parse_input() {
    int count = 0;
    int flag = 0;
    char line[256];

    while (1) {
        
        char uid[100], bid[100], book_category[100], start_date[100], end_date[100];
        scanf("%s", uid);
        if (strcmp(uid, "#") == 0) {
            break;
        }
        total_sub += 1;
        scanf("%s %s %s %s", bid, book_category, start_date, end_date);
        int int_uid = atoi(&uid[3]);
        int int_bid = atoi(&bid[3]);
        
        printf("%d %d\n", int_uid, int_bid);
        if (strcmp("history", book_category) == 0){
            users[0][int_uid]++;
        }
        else if (strcmp("science", book_category) == 0){
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

    while(1){
        char query[100];
        scanf("%s", query);
        if (strcmp(query, "#") == 0) {
            break;
        }
        if (strcmp("?total_book_borrow", query)==0){
            printf("%d\n", total_sub);
        }
        else if(strcmp(query, "?best_book") == 0){
            int r = findMaxValue(books);
            printf("%d\n", r);
        }
        else if(strcmp(query, "?number_user_borrow") == 0){
            char this_uid[100];
            scanf("%s", this_uid);
            int this_int_uid = atoi(&this_uid[3]);
            int r = 0;
            for (int i=0; i<3; i++){
                r += users[i][this_int_uid];
            }
            printf("%d\n", r);
        }
        else if(strcmp(query, "?user_favourite_category") == 0){
            char this_uid[100];
            char result[100];
            scanf("%s", this_uid);
            int this_int_uid = atoi(&this_uid[3]);
            int max_id = 0;
            int max = -1;
            for(int i=0; i<3; i++){
                if(users[i][this_int_uid] > max){
                    max = users[i][this_int_uid];
                    max_id = i;
                }
            }
            if(max_id == 0) strcpy(result, "history");
            else if(max_id == 1) strcpy(result, "science");
            else strcpy(result, "economics");

            printf("%s\n", result);
        }
        else if(strcmp(query, "?total_borrow_period") == 0){
            char start_date[100], end_date[100];
            scanf("%s %s", start_date, end_date);
            int int_start_day = timeStringToDays(start_date);
            int int_end_day = timeStringToDays(end_date);
            
            if(int_end_day < int_start_day) printf("0\n");
            else{
                int r;
                if(int_start_day == 0) r = days[int_end_day];
                else r = days[int_end_day] - days[int_start_day - 1];
                printf("%d\n", r);
            }
        }


    }

}



int main() {


    parse_input();
    return 0;
}
