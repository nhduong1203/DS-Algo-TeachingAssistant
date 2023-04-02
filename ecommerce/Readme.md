**Data description**\
The data about bank transactions consists of a sequence of transactions: the information of each transaction has **the following format**:
<OrderID>   <CustomerID>      <ProductID>   <Qty>   <Date-time>

**Details**:
- **<OrderID>**: id number of the order placed (which is a string of length from 6 to 20 )
-	**<CustomerID>**: id number of the customer who place the order (which is a string of length from 6 to 20)
-	**<ProductID>**: id number of the product in the order (which is a string of length from 6 to 20)
-	**<Qty>**: quantity of the product that the customer place (an integer)
-	**<Date-time>**: the time point at which the order is placed, it is a string under the format DD:MM:YY  (day: month: year)\

**Example:** OID00213  CID002135 PID002145 15 02/04/2023. Means that: at 02/04/2023, the customer with id CID002135 bought product with id PID002145 in quantity 15. Id of this order is OID00213.

**Exercise:**
Write a program that process following queries: 
-	?count_total_transactions: compute the total number of transactions of the data
-	?count_total_money: compute the total amount of money of transactions  
-	?list_sorted_account: compute the sequence of bank accounts (including sending and receiving accounts) appearing in the transaction (sorted in an increasing (alphabetical) order)  
-	?amount_money_trans_from <account>: compute the total amount of money transferred from the account <account>  
  
**Input (stdin)**
The input consists of 2 blocks of information: the data block and the query block
-	The data block consists lines
    -	Each line contains the information about a transaction described above
    -	The data is terminated by a line containing #
-	The query block consists of lines:
    -	Each line is a query described above
    -	The query block is terminated by a line containing #

**Output (stdout)**
-	Print to stdout (in each line) the result of each query described above

**Example:**
 #
_Input_\
T000010010 T000010020 1000 10:20:30 ATM1\
T000010010 T000010030 2000 10:02:30 ATM2\
T000010010 T000010040 1500 09:23:30 ATM1 \
T000010020 T000010030 3000 08:20:31 ATM1 \
T000010030 T000010010 4000 12:40:00 ATM2 \
T000010040 T000010010 2000 10:30:00 ATM1\
T000010020 T000010040 3000 08:20:31 ATM1 \
T000010040 T000010030 2000 11:30:00 ATM1\
T000010040 T000010030 1000 18:30:00 ATM1
 
  #
_Query_\
?number_transactions\
?total_money_transaction \
?list_sorted_accounts\
?total_money_transaction_from T000010010
#

_Output_\
9\
19500\
T000010010 T000010020 T000010030 T000010040\
4500