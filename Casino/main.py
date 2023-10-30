import loginFront

username,password,credits,userPos = loginFront.login()
print("Back to Main!")
print("Username:",username)
print("Password:",password)
print("credits:",credits)
print("Position of Username:",userPos)

import casinoBack
casinoBack.casinoFloor(username,password,credits,userPos)
