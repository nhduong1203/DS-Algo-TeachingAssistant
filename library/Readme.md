**Data description**\
The data includes information about borrow and return books in a library. The information of each book borrow has **the following format**:
\<UserID>   \<BookID>  \<BookCategory>   \<BorrowDate>   \<ReturnDate>

**Details**:
- **\<UserID>**: id number of the user who borrow the book (which is a string of length from 6 to 20 )
-	**\<BookID>**: id number of the book (which is a string of length from 6 to 20)
-	**\<BookCategory>**: category of the book (which is a string of length from 6 to 20)
-	**\<BorrowDate>**: the day that the user start borrow the book, it is a string under the format DD:MM:YY  (day: month: year)
-	**\<ReturnDate>**: the day the user return the book, it is a string under the format DD:MM:YY  (day: month: year)

**Example:** UID000015 BID000042 economics 17/01/2021 14/02/2021. Means that: the user **UID000015** started borrowing the **economics** book **BID000042** at 17/01/2021. After that, the user returned the book at 14/02/2021.

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
_Input_\
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
_Query_\
?count_total_order\
?active_customer CID00000\
?number_customer's_order CID00003\
?best_customer\
?best_product


#
_Output_\
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
------------------------------------------\
\
END.
