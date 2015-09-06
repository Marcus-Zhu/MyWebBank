# user TABLE:
+ key
+ name
+ password
+ id
+ createdDate
+ tel
+ email
+ address
+ zipCode
+ type(normal or VIP)

# account TABLE:
+ key
+ userKey
+ type
+ number
+ fixedDeposit
+ currentDeposit
+ status(normal or frozen)
+ createdTime

# transactionRecord TABLE:
+ key
+ accountKey1
+ accountKey2
+ sum
+ time
+ fixedDeposit
+ currentDeposit

# payment TABLE:
+ key
+ accountKey
+ sum
+ time
+ currentDeposit
+ type(Water, Electricity or Gas)

# autopay TABLE:
+ key
+ accountKey
+ item
+ lastPayDate

# message TABLE:
+ key
+ userKey
+ time
+ content
+ status

# log TABLE:
+ key
+ userKey
+ time
+ type(login or logout)

> fundMarket TABLE:
key, code, name, NAV(dan wei jing zhi), date, NCV(lei ji jing zhi), monthGR, yearGR

>fundRecord TABLE:
key, accountKey, code, name, NAV, date, share, refMV, refProfit