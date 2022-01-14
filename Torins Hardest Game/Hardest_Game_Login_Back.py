import pygame
import Hardest_Game_Login_Front
import Hardest_Game_File_Handler


#Main function of the login screens. This function calls on loginhandling to handle logins, and calls on new account handling to handle new accounts. They both report back to here(main)
#INPUT: This function takes in no input
#OUTPUT: Returns the listOfUsernames,listOfPasswords,listOfAttempts,listOfTimes, usersposition, userattempts
def main():

    try:
        userLogins = open(Hardest_Game_File_Handler.currentTextFile, "r")
        userInfo = []
        splitInfo = []

            #Need to reset each time or else we append with new instances of same user
        Hardest_Game_Login_Front.listOfUsernames = []
        Hardest_Game_Login_Front.listOfPasswords = []
        Hardest_Game_Login_Front.listOfAttempts = []
        Hardest_Game_Login_Front.listOfTimes = []
            #Need to reset each time or else we append with new instances of same user

        for x in userLogins:
            splitInfo = x.split("z")

        try:
            splitInfo.pop(0)
        except:
            print("There is nothing in the list")
            pass

        for x in range(len(splitInfo)):
            userInfo.append(splitInfo[x])

        #there are four categories to a given account so dividing the length of the user info by 4 gives us how many users there are
        Hardest_Game_Login_Front.numOfAccounts = int(len(userInfo) / 4)

        for x in range(Hardest_Game_Login_Front.numOfAccounts):
            username,password,attempts,time = Hardest_Game_File_Handler.decryptData(userInfo[(x*4) + 0],userInfo[(x*4) + 1],userInfo[(x*4) + 2],userInfo[(x*4) + 3])
            Hardest_Game_Login_Front.listOfUsernames.append(username)
            Hardest_Game_Login_Front.listOfPasswords.append(password)
            Hardest_Game_Login_Front.listOfAttempts.append(attempts)
            Hardest_Game_Login_Front.listOfTimes.append(time)
        userLogins.close()
        #At this point we have confirmed that there is a text doc with the potential users in it, and we have populated our local variables with those potential individuals

        

        while True:
            
            Hardest_Game_Login_Front.defaultScreen()
            Hardest_Game_Login_Front.possibleError = 0
            for event in pygame.event.get():

                #QUIT FROM THE ESCAPE KEY
                if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                    pygame.quit()
                    exit()


                clicked1,clicked2,clicked3 = pygame.mouse.get_pressed(num_buttons=3)
                if clicked1 == True:
                    x,y = pygame.mouse.get_pos()

                    #Add User Button
                    if ((x >= 1170) and (x <= 1270)) and ((y >= 610)and(y <= 710)):
                        x = newAccountHandling()
                        if x == 0:
                            #print("No user was added")
                            pass
                        pass

                    #Checking for clicks on accounts - Goes to login Screen if the account is there | if login is successful goes back to main
                        #First user Account - 1
                    if ((x >= 100) and (x <= 400)) and ((y >= 50)and(y <= 200)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 1:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[0])
                            if x == 1:
                                #pygame.display.quit()
                                print (type(Hardest_Game_Login_Front.listOfUsernames), type(Hardest_Game_Login_Front.listOfPasswords), type(Hardest_Game_Login_Front.listOfAttempts), type(Hardest_Game_Login_Front.listOfTimes), type(0), type(Hardest_Game_Login_Front.listOfAttempts[0]))
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 0, Hardest_Game_Login_Front.listOfAttempts[0]
                            pass
                        pass
                        #Second user Account - 2
                    if ((x >= 500) and (x <= 800)) and ((y >= 50)and(y <= 200)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 2:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[1])
                            if x == 1:
                                #pygame.display.quit()
                                print (Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 1, Hardest_Game_Login_Front.listOfAttempts[1])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 1, Hardest_Game_Login_Front.listOfAttempts[1]
                            pass
                        pass
                        #Third user Account - 3
                    if ((x >= 900) and (x <= 1200)) and ((y >= 50)and(y <= 200)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 3:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[2])
                            if x == 1:
                                #pygame.display.quit()
                                print (Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 2, Hardest_Game_Login_Front.listOfAttempts[2])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 2, Hardest_Game_Login_Front.listOfAttempts[2]
                            pass
                        pass
                        #Fourth user Account - 4
                    if ((x >= 100) and (x <= 400)) and ((y >= 250)and(y <= 400)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 4:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[3])
                            if x == 1:
                                #pygame.display.quit()
                                print(Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 3, Hardest_Game_Login_Front.listOfAttempts[3])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 3, Hardest_Game_Login_Front.listOfAttempts[3]
                            pass
                        pass
                        #Fifth user Account - 5
                    if ((x >= 500) and (x <= 800)) and ((y >= 250)and(y <= 400)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 5:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[4])
                            if x == 1:
                                #pygame.display.quit()
                                print(Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 4, Hardest_Game_Login_Front.listOfAttempts[4])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 4, Hardest_Game_Login_Front.listOfAttempts[4]
                            pass
                        pass
                        #Sixth user Account - 6
                    if ((x >= 900) and (x <= 1200)) and ((y >= 250)and(y <= 400)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 6:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[5])
                            if x == 1:
                                #pygame.display.quit()
                                print(Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 5, Hardest_Game_Login_Front.listOfAttempts[5])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 5, Hardest_Game_Login_Front.listOfAttempts[5]
                            pass
                        pass
                        #Seventh user Account - 7
                    if ((x >= 100) and (x <= 400)) and ((y >= 450)and(y <= 600)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 7:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[6])
                            if x == 1:
                                #pygame.display.quit()
                                print(Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 6, Hardest_Game_Login_Front.listOfAttempts[6])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 6, Hardest_Game_Login_Front.listOfAttempts[6]
                            pass
                        pass
                        #Eigth user Account - 8
                    if ((x >= 500) and (x <= 800)) and ((y >= 450)and(y <= 600)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 8:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[7])
                            if x == 1:
                                #pygame.display.quit()
                                print(Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 7, Hardest_Game_Login_Front.listOfAttempts[7])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 7, Hardest_Game_Login_Front.listOfAttempts[7]
                            pass
                        pass
                        #Ninth user Account - 9
                    if ((x >= 900) and (x <= 1200)) and ((y >= 450)and(y <= 600)):
                        if Hardest_Game_Login_Front.numOfAccounts >= 9:
                            x  = loginHandling(Hardest_Game_Login_Front.listOfUsernames[8])
                            if x == 1:
                                #pygame.display.quit()
                                print(Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 8, Hardest_Game_Login_Front.listOfAttempts[8])
                                return Hardest_Game_Login_Front.listOfUsernames, Hardest_Game_Login_Front.listOfPasswords, Hardest_Game_Login_Front.listOfAttempts, Hardest_Game_Login_Front.listOfTimes, 8, Hardest_Game_Login_Front.listOfAttempts[8]
                            pass
                        pass
                    #Checking for clicks on accounts - Goes to login Screen if the account is there | if login is successful goes back to main


                    #Nothing "clickable" was clicked
                    else:
                        #print("button wasn't clicked")
                        pass
            pass #on the while loop

    #Just to make sure there is a file at start
    #No need to write any more code in the except
    except:
        userLogins = open(Hardest_Game_File_Handler.currentTextFile, "x")
        userLogins.close()
        main()
        pass
    pass

#This function handles logging in. The user inputs as well as displaying the login function
#INPUT: This function takes in the username of the selected profile
#OUTPUT: return 1 means that there was a successful login. Anything else is a failed login and returns to the default screen
def loginHandling(u):
    password = ""
    while True:
        Hardest_Game_Login_Front.loginScreen(u, password)

        for event in pygame.event.get():

        #QUIT FROM THE ESCAPE KEY
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_a):
                password += "a"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_b):
                password += "b"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_c):
                password += "c"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_d):
                password += "d"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_e):
                password += "e"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_f):
                password += "f"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_g):
                password += "g"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_h):
                password += "h"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_i):
                password += "i"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_j):
                password += "j"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_k):
                password += "k"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_l):
                password += "l"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_m):
                password += "m"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_n):
                password += "n"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_o):
                password += "o"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_p):
                password += "p"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_q):
                password += "q"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_r):
                password += "r"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_s):
                password += "s"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_t):
                password += "t"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_u):
                password += "u"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_v):
                password += "v"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_w):
                password += "w"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_x):
                password += "x"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_y):
                password += "y"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_z):
                password += "z"
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_SPACE):
                password += " "
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_BACKSPACE):
                password = password[:-1]
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_RETURN):
                a = loginCheck(u,password)
                if a == 1:
                    return a
                else:
                    Hardest_Game_Login_Front.possibleError = 1
                    continue

            clicked1,clicked2,clicked3 = pygame.mouse.get_pressed(num_buttons=3)
            if clicked1 == True:
                x,y = pygame.mouse.get_pos()

                #CONFIRM LOGIN BUTTON
                if ((x >= 1170) and (x <= 1270)) and ((y >= 610)and(y <= 710)):
                    a = loginCheck(u,password)

                    if a == 1:
                        return a
                    else:
                        Hardest_Game_Login_Front.possibleError = 1
                        continue

                        #GO BACK BUTTON
                if ((x >= 10) and (x <= 110)) and ((y >= 610)and(y <= 710)):
                    return 0
                    pass

            #Nothing was clicked
            else:
                #print("button wasn't clicked")
                pass

    pass

#This function handles the new account screen. 
#INPUT: Takes no input
#OUTPUT: return 1 means that there was a successful account added. Anything else is a failed account added and returns to the default screen
def newAccountHandling():
    firstletter = ""
    secondletter = ""
    thirdletter = ""
    fourthletter = ""
    username = ""
    password = ""
    charactersUsed = 0
    Hardest_Game_Login_Front.addUserScreen(firstletter, secondletter, thirdletter, fourthletter, password)
    \
    while True:
        for event in pygame.event.get():

            #Checking for key inputs and assigning letters to the username and password
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_a):
                letter = "a"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_b):
                letter = "b"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_c):
                letter = "c"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_d):
                letter = "d"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_e):
                letter = "e"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_f):
                letter = "f"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_g):
                letter = "g"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_h):
                letter = "h"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_i):
                letter = "i"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_j):
                letter = "j"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_k):
                letter = "k"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_l):
                letter = "l"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_m):
                letter = "m"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_n):
                letter = "n"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_o):
                letter = "o"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_p):
                letter = "p"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_q):
                letter = "q"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_r):
                letter = "r"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_s):
                letter = "s"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_t):
                letter = "t"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_u):
                letter = "u"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_v):
                letter = "v"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_w):
                letter = "w"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_x):
                letter = "x"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_y):
                letter = "y"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_z):
                letter = "z"
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_SPACE):
                letter = " "
                charactersUsed += 1
                if charactersUsed == 1:
                    firstletter += letter
                    username += letter
                elif charactersUsed == 2:
                    secondletter += letter
                    username += letter
                elif charactersUsed == 3:
                    thirdletter += letter
                    username += letter
                elif charactersUsed == 4:
                    fourthletter += letter
                    username += letter
                elif charactersUsed >= 5:
                    password += letter
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_BACKSPACE):
                if charactersUsed == 1:
                    firstletter = ""
                    username = username[:-1]
                elif charactersUsed == 2:
                    secondletter = ""
                    username = username[:-1]
                elif charactersUsed == 3:
                    thirdletter = ""
                    username = username[:-1]
                elif charactersUsed == 4:
                    fourthletter = ""
                    username = username[:-1]
                elif charactersUsed >= 5:
                    password = password[:-1]
                charactersUsed -= 1
                pass
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_RETURN):

                if len(password) >= 1:
                    a = addAccount(username,password)
                    if a == 1:
                        return a
                    else:
                        Hardest_Game_Login_Front.possibleError = 1
                        #print("There are too many users on this device")
                else:
                    Hardest_Game_Login_Front.possibleError = 2
                    #print("There is no password")
                pass
            else:
                letter = ""
                pass
            #Checking for key inputs and assigning letters to the username and password

            #MOUSE CLICKS
            clicked1,clicked2,clicked3 = pygame.mouse.get_pressed(num_buttons=3)
            if clicked1 == True:
                x,y = pygame.mouse.get_pos()

                #CONFIRM ADDED ACCOUNT BUTTON
                if ((x >= 1170) and (x <= 1270)) and ((y >= 610)and(y <= 710)):
                    if len(password) >= 1:
                        a = addAccount(username,password)

                        if a == 1:
                            return a
                        else:
                            Hardest_Game_Login_Front.possibleError = 1
                            #print("There are too many users on this device")
                            pass
                    else:
                        Hardest_Game_Login_Front.possibleError = 2
                        #print("There is no password")
                        pass

                #GO BACK BUTTON
                if ((x >= 10) and (x <= 110)) and ((y >= 610)and(y <= 710)):
                    return 0
                    pass
                pass
            else:
                #print("button wasn't clicked")
                pass
            #MOUSE CLICKS

        

        #print(firstletter,secondletter,thirdletter,fourthletter,username,password)
        Hardest_Game_Login_Front.addUserScreen(firstletter, secondletter, thirdletter, fourthletter, password)
        
        
    pass

#This function takes in a user name and password, and checks it accross our list of usernames and passwords to see if there is a match or not
#Input: This function takes in u and p as strings
#Output: Returns a 1 if there is a match in username and password, and returns a 0 if there is no match
def loginCheck(u,p):

    for x in range(Hardest_Game_Login_Front.numOfAccounts):
        if (u == Hardest_Game_Login_Front.listOfUsernames[x]) and (p == Hardest_Game_Login_Front.listOfPasswords[x]):
            return 1
    return 0
    pass

#This function takes in a username and password and makes a new account in the text document for the given user | opens for appending
#Input: u and p are strings that represent the username and password of the player of which are in lowercase
#Output: This function returns 0 if there are already 9 accounts on file, and returns 1 if it has successfully added an account
def addAccount(u,p):
    try:
        if Hardest_Game_Login_Front.numOfAccounts >= 9:
            return 0
        userLogins = open(Hardest_Game_File_Handler.currentTextFile, "a")
    
        username,password,attempts,bestTime = Hardest_Game_File_Handler.encryptData(u,p,0)
        userLogins.write("z"+username+"z"+password+"z"+attempts+"z"+bestTime)
        userLogins.close()

        Hardest_Game_Login_Front.numOfAccounts += 1
        Hardest_Game_Login_Front.listOfUsernames.append(u)
        Hardest_Game_Login_Front.listOfPasswords.append(p)
        Hardest_Game_Login_Front.listOfAttempts.append(0)
        Hardest_Game_Login_Front.listOfTimes.append("N/A")
        
        return 1
    except:
        print("\n\n\n!!! Was unable to add the user to the document !!!\n\n\n")
    pass

#Deleted encrypt data and decrypt data here. May need to re implement