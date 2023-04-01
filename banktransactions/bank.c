#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 20
#define M 100000
#define N 20
typedef struct Node{
    char id[MAX_L];
    int index;// mapped index
    int amount;
    struct Node* leftChild;
    struct Node* rightChild;
}Node;

//int** A; // A[i][j] = 1: account i transfers to account j
int A[N][N]; // A[i][j] = 1: account i transfers to account j
int n;// number of accounts;
int x[N];
int found;
int visited[N];

Node* T[M]; // T[i] is the pointer to the root of th ith BST
Node* accountStore; // pointer to the root of BST

Node* makeNode(char*id, int amount){
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->id,id);
    p->amount = amount;
    p->leftChild = NULL; p->rightChild = NULL;
    return p;
}
int h(char* id){
    int c = 0;
    int n = strlen(id);
    for(int i = 0; i < n; i++){
        c = (c*256 + id[i]) % M;
    }
    return c;
}
Node* findBST(char* id, Node* r){
    if(r == NULL) return NULL;
    int c = strcmp(id,r->id);
    if(c == 0) return r;
    if(c < 0) return findBST(id,r->leftChild);
    return findBST(id,r->rightChild);
}
Node* find(char*id){
    int i = h(id);
    return findBST(id,T[i]);
}
Node* insertBST(char* id, int amount, Node* r){
    if(r == NULL) return makeNode(id, amount);
    int c = strcmp(id,r->id);
    if(c == 0) return r;
    if(c < 0) r->leftChild = insertBST(id,amount,r->leftChild);
    else r->rightChild = insertBST(id,amount,r->rightChild);
    return r;
}
void insert(char*id, int amount){
    int i = h(id);
    T[i] = insertBST(id,amount,T[i]);
}

int convertHHMMSS2Second(char* t){
    int h = (t[0] - '0')*10 + (t[1] - '0');
    int m = (t[3] - '0')*10 + (t[4] - '0');
    int s = (t[6] - '0')*10 + (t[7] - '0');
    return h*3600 + m*60 + s;
}
void inOrder(Node* r){
    if(r == NULL) return;
    inOrder(r->leftChild);
    printf("%s ",r->id);
    inOrder(r->rightChild);
}
void initSolveCycle(){
    for(int i = 1; i <= n; i++){
        visited[i] = 0;
    }
}
void solution(int Q){
    if(A[x[Q]][x[1]] == 1){
        found = 1;
    }
}

void Try(int k, int Q){
    if(found) return;
    for(int v = 1; v <= n; v++)if(A[x[k-1]][v] == 1){
        if(visited[v] == 0){
            x[k] = v; visited[v] = 1;
            if(k == Q) solution(Q);
            else Try(k+1,Q);
            visited[v] = 0;
        }
    }
}
void solveFindCycle(int s, int Q){
    if(s == 0) {
        printf("0\n"); return;
    }
    initSolveCycle();
    x[1] = s; visited[s] = 1; found = 0;
    Try(2,Q);
    printf("%d\n",found);
}
void run(){
    char fromAcc[MAX_L], toAcc[MAX_L];
    int money;
    char time_trans[MAX_L], atm[MAX_L];
    int nbTrans = 0;
    int totalMoneyTrans = 0;
    n = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            A[i][j] = 0;
    }

    while(1){
        scanf("%s",fromAcc);
        if(strcmp(fromAcc,"#")==0) break;
        scanf("%s %d %s %s",toAcc,&money,time_trans,atm);
        nbTrans += 1;
        totalMoneyTrans += money;
        //printf("%d: READ %s %s %d %s %s\n",nbTrans,fromAcc, toAcc, money,time_trans,atm);
        Node* node = find(fromAcc);
        if(node == NULL){
            insert(fromAcc,money);
        }else{
            node->amount += money;
        }
        Node* p = findBST(fromAcc, accountStore);
        if(p == NULL){
                accountStore = insertBST(fromAcc, 0, accountStore);
                p = findBST(fromAcc, accountStore);
                n += 1;
                p->index = n;
        }
        Node* q = findBST(toAcc,accountStore);
        if(q == NULL){
                accountStore = insertBST(toAcc, 0, accountStore);
                n += 1;
                q = findBST(toAcc, accountStore);
                q->index = n;
        }
        A[p->index][q->index] = 1;
    }

    char cmd[MAX_L];
    char acc[MAX_L];
    char fromTime[MAX_L], toTime[MAX_L];
    int Q, D;
    while(1){
        scanf("%s",cmd);
        //printf("READ cmd %s\n",cmd);
        if(strcmp(cmd,"#")==0) break;
        else if(strcmp(cmd,"?number_transactions")==0){
            printf("%d\n",nbTrans);
        }else if(strcmp(cmd,"?total_money_transaction")==0){
            printf("%d\n",totalMoneyTrans);
        }else if(strcmp(cmd,"?list_sorted_accounts")==0){
            inOrder(accountStore);
            printf("\n");
        }else if(strcmp(cmd,"?total_money_transaction_from")==0){
            scanf("%s",acc);
            Node* node = find(acc);
            if(node == NULL) printf("0\n");
            else printf("%d\n",node->amount);
        }else if(strcmp(cmd,"?count_suspected_acc")==0){
            scanf("%d %d",&Q,&D);
            // TODO
        }else if(strcmp(cmd,"?max_money_period")==0){
            scanf("%s %d",fromTime, toTime);
            // TODO
        }else if(strcmp(cmd,"?inspect_cycle")==0){
            scanf("%s %d",acc, &Q);
            //printf("inspect_cycle, acc = %s, Q= %d\n",acc,Q);
            Node* p = findBST(acc,accountStore);
            int s = 0;
            if(p != NULL) s = p->index;
            solveFindCycle(s,Q);
        }
    }
}
int main(){
    freopen("test/demo-example.txt","r",stdin);
    //freopen("test/1-total_money_transaction_from.txt","r",stdin);
    //freopen("test/2-total_money_transaction_from.txt","r",stdin);
    //freopen("test/3-total_money_transaction_from.txt","r",stdin);
    //freopen("test/4-total_money_transaction_from.txt","r",stdin);
    //freopen("test/5-total_money_transaction_from.txt","r",stdin);

    //freopen("test/1-inspect_cycle.txt","r",stdin);
    //freopen("test/2-inspect_cycle.txt","r",stdin);
    //freopen("test/3-inspect_cycle.txt","r",stdin);
    //freopen("test/4-inspect_cycle.txt","r",stdin);
    //freopen("test/5-inspect_cycle.txt","r",stdin);

    //freopen("test/1-list_sorted_accounts.txt","r",stdin);
    //freopen("test/2-list_sorted_accounts.txt","r",stdin);

    //freopen("test/5-total_money_transaction.txt","r",stdin);

    //freopen("test/5-number_transactions.txt","r",stdin);
    //freopen("test/3-number_transactions.txt","r",stdin);

    run();
    return 0;
}
