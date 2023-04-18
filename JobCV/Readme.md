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
-  ?total_book_borrow: Return the total number of times to borrow books from the library.
-  ?best_book: Return the book that has been borrow most.
-  ?best_user: Return the user that borrowed the most book.
-  ?number_user_borrow \<UserID>: Return the number of book that the user borrowed.
-  ?list_user_borrow \<UserID>: Return list book that the user borrowed.
-  ?sort_category: Return the list of book's category that has been sort in ascending order of times it has been borrowed.

  
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

END.
