**Data description**\
The data about bank transactions consists of a sequence of transactions: the information of each transaction has **the following format**:
\<OrderID>   \<CustomerID>      \<ProductID>   \<Qty>   \<Date-time>

**Details**:
- **\<OrderID>**: id number of the order placed (which is a string of length from 6 to 20 )
-	**\<CustomerID>**: id number of the customer who place the order (which is a string of length from 6 to 20)
-	**\<ProductID>**: id number of the product in the order (which is a string of length from 6 to 20)
-	**\<Qty>**: quantity of the product that the customer place (an integer)
-	**\<Date-time>**: the time point at which the order is placed, it is a string under the format DD:MM:YY  (day: month: year)

**Example:** OID00213  CID002135 PID002145 15 02/04/2023. Means that: at 02/04/2023, the customer with id CID002135 bought product with id PID002145 in quantity 15. Id of this order is OID00213.

**Exercise:**
Write a program that process following queries: 
-	?count_total_order: compute the total number of order
-	?active_customer \<CustomerID>: Check if the customer has placed an order. Return **False** if the customer has never placed any order.
-	?number_customer's_order \<CustomerID>: compute the number of orders of this customer.
- ?best_customer: compute the top 5 customers who have the biggest orders.
- ?best_product: calculate the top 5 most purchased products
  
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
_Input_
OID00001 CID00000 PID00002 8 19/11/2021\
OID00002 CID00003 PID00001 17 20/04/2022\
OID00003 CID00004 PID00002 11 10/03/2020\
OID00004 CID00000 PID00000 14 17/08/2020\
OID00005 CID00003 PID00002 18 18/08/2020\
OID00006 CID00002 PID00000 2 28/09/2022\
OID00007 CID00004 PID00004 19 23/12/2022\
OID00008 CID00002 PID00002 5 07/05/2021\
OID00009 CID00001 PID00002 15 14/08/2022\
OID00010 CID00002 PID00005 13 25/08/2022



 
#
_Query_
?count_total_order\
?active_customer CID00000\
?number_customer's_order CID00003\
?best_customer\
?best_product


#
_Output_
10\
------------------------------------------\
True\
------------------------------------------\
2\
------------------------------------------\
CID00003 35\
CID00004 30\
CID00000 22\
CID00002 20\
CID00001 15\
------------------------------------------\
PID00002 57\
PID00004 19\
PID00001 17\
PID00000 16\
PID00005 13\
------------------------------------------

