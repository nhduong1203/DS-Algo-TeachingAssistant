**Data description**\
The data about bank transactions consists of a sequence of transactions: the information of each transaction has **the following format**:
\<OrderID>   \<CustomerID>      \<ProductID>   \<Qty>   \<Date-time>

**Details**:
- **\<OrderID>**: id number of the order placed (which is a string of length from 6 to 20 )
-	**\<CustomerID>**: id number of the customer who place the order (which is a string of length from 6 to 20)
-	**\<ProductID>**: id number of the product in the order (which is a string of length from 6 to 20)
-	**\<Qty>**: quantity of the product that the customer place (an integer)
-	**\<Date-time>**: the time point at which the order is placed, it is a string under the format DD:MM:YY  (day: month: year)\

**Example:** OID00213  CID002135 PID002145 15 02/04/2023. Means that: at 02/04/2023, the customer with id CID002135 bought product with id PID002145 in quantity 15. Id of this order is OID00213.

**Exercise:**
Write a program that process following queries: 
-	?count_total_order: compute the total number of order
-	?active_customer \<CustomerID>: Check if the customer has placed an order. Return **False** if the customer has never placed any order.
-	?number_customer_order \<CustomerID>: compute the number of orders of this customer.
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
_Input_\

 
#
_Query_\


#
_Output_\

