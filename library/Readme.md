**Data description**\
The data includes information about borrow and return books in a library. The information of each book borrow has **the following format**:
\<UserID>   \<BookID>  \<BookCategory>   \<BorrowDate>   \<ReturnDate>

**Details**:
- **\<UserID>**: id number of the user who borrow the book (which is a string of length from 6 to 20 )
-	**\<BookID>**: id number of the book (which is a string of length from 6 to 20)
-	**\<BookCategory>**: category of the book (which is a string of length from 6 to 20). Which is one of three category ["history", "science", "economics"].
-	**\<BorrowDate>**: the day that the user start borrow the book, it is a string under the format DD/MM/YY  (day/ month/ year)

**Example:** UID000015 BID000042 economics 17/01/2021 14/02/2021. Means that: the user **UID000015** started borrowing the **economics** book **BID000042** at 17/01/2021. After that, the user returned the book at 14/02/2021.

**Exercise:**
Write a program that process following queries: 
-  ?total_book_borrow: Return the total number of times to borrow books from the library.
-  ?best_book: Returns the number of borrowings of the most borrowed book.
-  ?number_user_borrow \<UserID>: Return the number of book that the user borrowed.
-  ?user_favourite_category \<UserID>: Return the book's category that user borrow most.
-  ?total_borrow_period <start-date> <end-date>: Return number of books that have been borrowed between start-date and end-date.

  
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
UID000002 BID000002 history 19/05/2021
UID000002 BID000008 economics 05/04/2021
UID000002 BID000007 history 03/11/2019
UID000003 BID000005 history 28/10/2020
UID000003 BID000003 economics 22/01/2019
UID000003 BID000004 history 09/10/2020
UID000002 BID000001 economics 16/10/2019
UID000001 BID000006 science 12/03/2021
UID000005 BID000007 history 26/11/2019
UID000005 BID000002 history 17/06/2021
 
#
_Query_\
?total_book_borrow
?best_book
?number_user_borrow UID000002
?user_favourite_category UID000002
?total_borrow_period 1/1/2019 1/1/2020


#
_Output_\
10
2
4
history
4

END.
