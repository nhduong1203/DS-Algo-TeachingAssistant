import datetime
import random
import os

# today = datetime.date(2023, 4, 10)
# future_date = today + datetime.timedelta(days=10)

# print(future_date.strftime('%d/%m/%Y'))

M = 2000

def futureDays(str, d):
    splitStr = str.split('/')
    today = datetime.date(int(splitStr[2]), int(splitStr[1]), int(splitStr[0]))
    future_date = today + datetime.timedelta(days=d)
    return future_date.strftime('%d/%m/%Y')

def dateConvert(day):
    s = "00"
    i = 1
    while day > 0:
        s = s[:i] + str(day % 10) + s[i+1:]
        day = day // 10
        i -= 1
    return s



def convertString(n, length, type):
    s = '0' * length
    i = length - 1
    while n > 0:
        r = n % 10
        s = s[:i] + str(r) + s[i+1:]
        n = n // 10
        i -= 1

    s = '0ID' + s[3:]
    if type == "book":
        s = 'B' + s[1:]
    else:
        s = 'U' + s[1:]

    return s

def randomDate():
    day = random.randint(1, 28)
    month = random.randint(1, 12)
    year = random.randint(2019, 2022)
    return dateConvert(day) + "/" + dateConvert(month) + "/" + str(year)

def hashFunction(s):
    hash_value = 0
    for i in range(len(s)):
        hash_value += ord(s[i]) * (i+1)
        hash_value = hash_value % M
    return hash_value

# define parameters
bookCategory = ["history", "science", "economics"] 
lenCategory = len(bookCategory)

# ensure each bookID identify the same book (that has the same catagory and can't be borrow by 2 people at the same time)
bookDate = [None] * M
saveBookCate = [None] * M

def genData(datafile, lenData,nbUsers, nbBooks):
    # if not os.path.exists(datafile):
        
    for i in range(lenData):
        thisUser = random.randint(1, nbUsers)
        thisBook = random.randint(1, nbBooks)
        
        thisUser = convertString(thisUser, 9, "user")
        thisBook = convertString(thisBook, 9, "book")
        

        hashValue = hashFunction(thisBook)
        if(bookDate[hashValue] == None):
            thisCate = random.randint(1, lenCategory) - 1
            thisCate = bookCategory[thisCate]
            saveBookCate[hashValue] = thisCate

            thisStartDate = randomDate()
            dayGap = random.randint(1, 30)
            thisEndDate = futureDays(thisStartDate, dayGap)
            bookDate[hashValue] = thisEndDate

            

        else:
            thisStartDate = bookDate[hashValue]
            gapToStart = random.randint(1, 15)
            gapToEnd = random.randint(1, 30)

            thisStartDate = futureDays(thisStartDate, gapToStart)
            thisEndDate = futureDays(thisStartDate, gapToStart + gapToEnd)
            # if(thisBook == "BID000043"):
            #     print(thisStartDate, thisEndDate)
            bookDate[hashValue] = thisEndDate
            thisCate = saveBookCate[hashValue]

        with open(datafile, 'a') as f:
            f.writelines(f'{thisUser} {thisBook} {thisCate} {thisStartDate} \n')




if __name__ == '__main__':
    #print(os.listdir())
    # genData("./library/data/0.txt", 1000, 20, 100)
    # genData("./library/data/1.txt", 10000, 200, 500)
    # genData("./library/data/2.txt", 100000, 500, 1000)
    genData("./library/data/3.txt", 1000000, 1000, 2000)
    #genData("./library/data/test.txt", 15, 5, 10)
