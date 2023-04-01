#include <bits/stdc++.h>
using namespace std;
string firstname[15] = {"an","anh","bang","binh","bao","cuong","dung","duong","ha","hai",
"hung","huong","hieu","khoa","khoi"};
string lastname[11] = {"nguyen","pham","tran","le","doan","dang","bui","do","trieu","ngo",
"ta"};
string bank[7] = {"bidv","vcb","tcb","tpb","shb","vib","hdb"};
string atm[6] = {"atm1","atm2","atm3","atm4","atm5","atm6"};
void stdString(char* s, int n, int len){
    int i = len-1;
    while(n > 0){
        int r = n%10;
        s[i] = '0' + r;
        n = n/10;
        i--;
    }
    while(i >= 0){
        s[i] = '0'; i--;
    }
    //s[0] = 'T';
    s[len] = '\0';
}
void stdAccString(char* s, int n, int len){
    int i = len-1;
    while(n > 0){
        int r = n%10;
        s[i] = '0' + r;
        n = n/10;
        i--;
    }
    while(i >= 1){
        s[i] = '0'; i--;
    }
    s[0] = 'T';
    s[len] = '\0';
}

void gen(char* filename, int nbTrans, int nbAcc, int nbQuery, int minQ, int maxQ){
    FILE* f = fopen(filename,"w");
    srand(time(NULL));
    char acc[20];
    /*
    for(int it = 1; it <= nbAcc; it++){
        stdString(acc,it,10);
        int i = rand()%15;
        int j = rand()%11;
        int k = rand()%7;
        fprintf(f,"%s %s_%s %s\n",acc,firstname[i].c_str(),lastname[j].c_str(),bank[k].c_str());
    }
    */

    char s_year[5];
    char s_month[3];
    char s_date[3];
    char s_hour[3];
    char s_minute[3];
    char s_second[3];
    char s_fromAcc[20];
    char s_toAcc[20];
    for(int it = 1; it <= nbTrans; it++){
        int fromAcc = rand()%nbAcc + 1;
        int toAcc = rand()%nbAcc + 1;
        int money = rand()%100000 + 1;
        int year = rand()%2 + 2020;
        int month = rand()%12 + 1;
        int date = rand()%30 + 1;
        int hour = rand()%24;
        int minute = rand()%60;
        int second = rand()%60;
        int i_atm = rand()%6;
        stdString(s_year,year,4);
        stdString(s_month,month,2);
        stdString(s_date,date,2);
        stdString(s_hour,hour,2);
        stdString(s_minute,minute,2);
        stdString(s_second,second,2);
        stdAccString(s_fromAcc,fromAcc,10);
        stdAccString(s_toAcc,toAcc,10);
        //fprintf(f,"%s %s %d %s-%s-%s %s:%s:%s %s\n",s_fromAcc,s_toAcc,money,s_year,
        //        s_month,s_date,s_hour,s_minute,s_second,atm[i_atm].c_str());
        fprintf(f,"%s %s %d %s:%s:%s %s\n",s_fromAcc,s_toAcc,money,s_hour,s_minute,s_second,atm[i_atm].c_str());

        if(it % 10000 == 0)
            cout << "finished " << it << "/" << nbTrans << endl;

    }
    fprintf(f,"#\n");

    // gen query ?max_money_period
    char s_hour1[3];
    char s_minute1[3];
    char s_second1[3];
    for(int i = 1; i <= nbQuery; i++){
        int hour = rand()%24;
        int minute = rand()%60;
        int second = rand()%60;
        stdString(s_hour,hour,2);
        stdString(s_minute,minute,2);
        stdString(s_second,second,2);
        int hour1 = rand()%24;
        int minute1 = rand()%60;
        int second1 = rand()%60;
        stdString(s_hour1,hour1,2);
        stdString(s_minute1,minute1,2);
        stdString(s_second1,second1,2);
        int opt = rand()%4;
        if(opt == 0){
            fprintf(f,"?max_money_period 00:00:00 %s:%s:%s\n",s_hour, s_minute, s_second);
        }else if(opt == 1){
            fprintf(f,"?max_money_period %s:%s:%s 23:59:59\n",s_hour, s_minute, s_second);
        }else if(opt == 2){
                fprintf(f,"?max_money_period 00:00:00 23:59:59\n",s_hour, s_minute, s_second);
        }else{
            if(hour*3600+minute*60+second > hour1*3600+minute1*60+second1){
                fprintf(f,"?max_money_period %s:%s:%s %s:%s:%s\n",s_hour1, s_minute1, s_second1,s_hour, s_minute, s_second);
            }else{
                fprintf(f,"?max_money_period %s:%s:%s %s:%s:%s\n",s_hour, s_minute, s_second,s_hour1, s_minute1, s_second1);
            }
        }
    }

    // gen query ?total_money_transaction_from
    /*
    for(int i = 1; i <= nbQuery; i++){
        int fromAcc = rand()%nbAcc + 1;
        stdAccString(s_fromAcc,fromAcc,10);
        fprintf(f,"?total_money_transaction_from %s\n",s_fromAcc);
    }
    */

    // gen query ?inspect_cycle
    /*
    for(int i = 1; i <= nbQuery; i++){
        int fromAcc = rand()%nbAcc + 1;
        stdAccString(s_fromAcc,fromAcc,10);
        int q = rand()%(maxQ - minQ+1) + minQ;
        fprintf(f,"?inspect_cycle %s %d\n",s_fromAcc,q);
    }
    */

    // gen query ?list_sorted_accounts
    //fprintf(f,"?list_sorted_accounts\n");

    // gen query ?total_money_transaction
    //fprintf(f,"?total_money_transaction\n");

    // gen query ?number_transactions
   // fprintf(f,"?number_transactions\n");

    fprintf(f,"#");
    fclose(f);
}
int main(){
    //char s[100];
    //stdString(s,3,5);
    //printf("%s\n",s);

    //gen("public-test-case/problem4/1-input.txt",10,5,10,2,6);
    //gen("public-test-case/problem4/2-input.txt",100,50,50,2,6);
    //gen("public-test-case/problem4/3-input.txt",100000,5000,5000,2,6);


    //gen("public-test-case/problem5/1-input.txt",10,10,7,2,4);
    //gen("public-test-case/problem5/2-input.txt",20,10,10,2,5);
    //gen("public-test-case/problem5/3-input.txt",40,15,15,2,6);

    //gen("public-test-case/problem3/1-input.txt",10,10,1,2,6);
    //gen("public-test-case/problem3/2-input.txt",100,100,1,2,6);
    //gen("public-test-case/problem3/3-input.txt",100000,100000,1,2,6);


    //gen("public-test-case/problem2/1-input.txt",10,10,1,2,6);
    //gen("public-test-case/problem2/2-input.txt",100,100,1,2,6);
    //gen("public-test-case/problem2/3-input.txt",100000,100000,1,2,6);

    //gen("public-test-case/problem1/1-input.txt",10,10,1,2,6);
    //gen("public-test-case/problem1/2-input.txt",100,100,1,2,6);
    //gen("public-test-case/problem1/3-input.txt",100000,100000,1,2,6);

    //gen("test/1-max_money_period.txt",10,5,10,2,6);
    //gen("test/2-max_money_period.txt",100,50,100,2,6);
    //gen("test/3-max_money_period.txt",10000,5000,100000,2,6);
    //gen("test/4-max_money_period.txt",10000,5000,100000,2,6);
    //gen("test/5-max_money_period.txt",10000,5,100000,2,6);
    gen("public-test-case/problem6/1-input.txt",10,5,10,2,6);
    gen("public-test-case/problem6/2-input.txt",100,50,100,2,6);
    gen("public-test-case/problem6/3-input.txt",10000,5000,100000,2,6);



    //gen("test/1-total_money_transaction_from.txt",10,5,10,2,6);
    //gen("test/2-total_money_transaction_from.txt",100,50,50,2,6);
    //gen("test/3-total_money_transaction_from.txt",1000,500,500,2,6);
    //gen("test/4-total_money_transaction_from.txt",10000,5000,5000,2,6);
    //gen("test/5-total_money_transaction_from.txt",100000,100000,100000,2,6);

    //gen("test/1-inspect_cycle.txt",10,10,7,2,4);
    //gen("test/2-inspect_cycle.txt",20,10,20,2,5);
    //gen("test/3-inspect_cycle.txt",30,12,20,2,5);
    //gen("test/4-inspect_cycle.txt",30,13,10,2,5);
    //gen("test/5-inspect_cycle.txt",40,15,15,2,6);

    //gen("test/1-list_sorted_accounts.txt",10,10,1,2,6);
    //gen("test/2-list_sorted_accounts.txt",100,100,1,2,6);
    //gen("test/3-list_sorted_accounts.txt",1000,1000,1,2,6);
    //gen("test/4-list_sorted_accounts.txt",10000,10000,1,2,6);
    //gen("test/5-list_sorted_accounts.txt",100000,100000,1,2,6);

    //gen("test/1-total_money_transaction.txt",10,10,1,2,6);
    //gen("test/2-total_money_transaction.txt",100,100,1,2,6);
    //gen("test/3-total_money_transaction.txt",1000,1000,1,2,6);
    //gen("test/4-total_money_transaction.txt",10000,10000,1,2,6);
    //gen("test/5-total_money_transaction.txt",100000,100000,1,2,6);

    //gen("test/1-number_transactions.txt",10,10,1,2,6);
    //gen("test/2-number_transactions.txt",100,100,1,2,6);
    //gen("test/3-number_transactions.txt",1000,1000,1,2,6);
    //gen("test/4-number_transactions.txt",10000,10000,1,2,6);
    //gen("test/5-number_transactions.txt",100000,100000,1,2,6);
    return 0;
}
