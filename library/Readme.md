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
-  ?best_book: Return the book that has been borrow most.
-  ?best_user: Return the user that borrowed the most book.
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
UID000001 BID000007 economics 26/10/2019 06/11/2019 \
UID000005 BID000004 science 15/09/2019 28/09/2019 \
UID000001 BID000007 economics 07/11/2019 22/11/2019\
UID000001 BID000001 sports 26/04/2019 15/05/2019 \
UID000004 BID000008 science 09/10/2022 29/10/2022 \
UID000005 BID000002 sports 19/04/2020 20/04/2020 \
UID000005 BID000010 sports 05/09/2019 18/09/2019\
UID000004 BID000005 history 15/07/2020 13/08/2020\
UID000003 BID000007 economics 28/11/2019 11/12/2019\
UID000001 BID000002 sports 21/04/2020 19/05/2020\
UID000003 BID000005 history 24/08/2020 02/10/2020\
UID000004 BID000007 economics 24/12/2019 17/01/2020\
UID000003 BID000008 science 02/11/2022 08/11/2022\
UID000004 BID000008 science 23/11/2022 21/12/2022\
UID000003 BID000002 sports 03/06/2020 28/06/2020 



 
#
_Query_\
?total_book_borrow\
?best_book\
?best_user\
?number_user_borrow UID000003\
?list_user_borrow UID000003\
?sort_category


#
_Output_\
15\
------------------------------------------\
BID000007 economics 4\
------------------------------------------\
UID000001 4\
------------------------------------------\
4\
------------------------------------------\
BID000007\
BID000005\
BID000008\
BID000002\
------------------------------------------\
history 2\
science 4\
economics 4\
sports 5\
------------------------------------------\
\
END.
