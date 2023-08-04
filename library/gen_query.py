from itertools import permutations
import random
import datetime

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

def randomDate():
    day = random.randint(1, 28)
    month = random.randint(1, 12)
    year = random.randint(2019, 2021)
    return dateConvert(day) + "/" + dateConvert(month) + "/" + str(year)

def genQuery(n, datafile = None):
    # if not os.path.exists(datafile):
    # numbers = list(range(1, n+1))
    # random.shuffle(numbers)
    query = "?total_borrow_period"

    with open(datafile, 'a') as f:
        f.writelines("#\n")
    

    for i in range(n):
        startDate = randomDate()
        dayGap = random.randint(50, 365)
        endDate = futureDays(startDate, dayGap)
        this_query = query + " " + startDate + " " + endDate
        if datafile is not None:
            with open(datafile, 'a') as f:
                f.writelines(f'{this_query}\n')
    with open(datafile, 'a') as f:
        f.writelines("#")



if __name__ == "__main__":
    genQuery(100000, "./library/query_5/total_book_4.txt")