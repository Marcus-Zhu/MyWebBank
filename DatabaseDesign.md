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
+ balance
+ status(normal or frozen)
+ createdTime

# transactionRecord TABLE:
+ key
+ accountKey1
+ accountKey2
+ sum
+ time
+ balance(of accountKey1)

# payment TABLE:
+ key
+ accountKey
+ sum
+ time
+ balance
+ type(Water, Electricity or Gas)

# message TABLE:
+ key
+ userKey
+ time
+ content

# log TABLE:
+ key
+ userKey
+ time
+ type(login or logout)

> fundMarket TABLE:
key, code, name, NAV(dan wei jing zhi), date, NCV(lei ji jing zhi), monthGR, yearGR

>fundRecord TABLE:
key, accountKey, code, name, NAV, date, share, refMV, refProfit