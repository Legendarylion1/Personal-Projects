import pygame
import loginFront
pygame.init()

def addCredentials():
    #Credentials for username
    #First we check if the username has been done already
    if loginFront.usernameDone == False:
        letter, tfn = credentials()
        #TFN Returns true false or none.
        #True - Adds the letter to the end of the string
        #False - Removes a letter from the end of the string
        #None - means that nothing was selected in that instance of the string
        # "1" - is returned when enter is pressed and stops the while x == True loop
        if letter == "1":
            loginFront.usernameDone = True
            return True
        if tfn == False and (len(loginFront.usernameCredentials) > 0):
            loginFront.usernameCredentials = loginFront.usernameCredentials.rstrip(loginFront.usernameCredentials[-1])
        if tfn == None:
            pass
        if letter != "1" and tfn == True:
            loginFront.usernameCredentials += letter
    #Credentials for username


    #Credentials for password
    #If username is done we then check to see if the password is done
    elif loginFront.passwordDone == False:
        letter,tfn = credentials()
        #TFN Returns true false or none.
        #True - Adds the letter to the end of the string
        #False - Removes a letter from the end of the string
        #None - means that nothing was selected in that instance of the string
        # "1" - is returned when enter is pressed and stops the while x == True loop
        if letter == "1":
            loginFront.passwordDone = True
            return False
        if tfn == False and (len(loginFront.passwordCredentials) > 0):
            loginFront.passwordCredentials = loginFront.passwordCredentials.rstrip(loginFront.passwordCredentials[-1])
        if tfn == None:
            pass
        if letter != "1" and tfn == True:
            loginFront.passwordCredentials += letter
    #Credentials for password


    return True
    pass

def credentials():
    for event in pygame.event.get():
        #Checks for all letter inputs
        #Returns true to mean to add it to the string
        #Returns false to remove a letter from the string
        #Returns 1 and None for having pressed enter
        #Returns "" and None by default so that nothing is changed in the string
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
            pygame.quit()
            exit()
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_a):
            return "a", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_b):
            return "b", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_c):
            return "c", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_d):
            return "d", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_e):
            return "e", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_f):
            return "f", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_g):
            return "g", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_h):
            return "h", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_i):
            return "i", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_j):
            return "j", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_k):
            return "k", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_l):
            return "l", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_m):
            return "m", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_n):
            return "n", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_o):
            return "o", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_p):
            return "p", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_q):
            return "q", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_r):
            return "r", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_s):
            return "s", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_t):
            return "t", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_u):
            return "u", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_v):
            return "v", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_w):
            return "w", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_x):
            return "x", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_y):
            return "y", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_z):
            return "z", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_SPACE):
            return " ", True
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_BACKSPACE):
            return "", False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_RETURN):
            return "1", None

        #Checks to see if the the mouse was clicked on the box for new user
        clicked1,clicked2,clicked3 = pygame.mouse.get_pressed(num_buttons=3)
        if clicked1 == True:
            x,y = pygame.mouse.get_pos()
            if ((x >= 580) and (x <= 700)) and ((y >= 500)and(y <= 520)):
                #adds a new user if the click was within the box using the name already in the username/password entries
                addNewUser(loginFront.usernameCredentials,loginFront.passwordCredentials)
            else:
                #print("button wasn't clicked")
                pass
        #Checks to see if the the mouse was clicked on the box for new user

    return "", None

def addNewUser(u="",p=""):
    try:
        userLogins = open("userLogins.txt", "x")
        #Tries to open a new doc in order to see if there is one already
        #If this fails that means there is a doc with users on it and we go to the except
        #If there is no doc one will be created and we will call the function again recursively
        #With it failing as expected and going to the except
        userLogins.close()
        addNewUser(u,p)
        pass
    except:
        userLogins = open("userLogins.txt", "a")
        #user logins are stored on the doc like this. ,username,password,1000
        #1000 is the default credits for any user
        userLogins.write(","+u+","+p+",1000")
        #print("Text doc exists")
        loginFront.userAdded = True
        loginFront.usernameDone = True
        loginFront.passwordDone = True
        loginFront.madeItOut = True
        #This made it out check makes sure we leave the x loop and check for existing user
        #In existingUser we then check as to whether or not a user was added
        return False
        pass
    pass

def existingUser(u="",p=""):
    #The returns work like this
    #The first true/false is for the x==True in order to get back into the main loop for username/password
    #setting it to True means that we want to go back into the loop which means if they arent logged in it
    #should become true
    #The second value that gets returned is an integer 1, 2 or 3
    #1 means that there was a successful login
    #2 means that there was a failed login
    #3 means that a user was added
    #These integers are being returned for sf which displays the success, fail, and added user

    #If a user was added we then need to reset the username and password so they can be input
    if loginFront.userAdded == True:
        #We also need to set user added and made it out back so that we can get back in the loop
        #and not come back to existing user with userAdded still being true. Its an infinite loop
        loginFront.usernameDone = False
        loginFront.passwordDone = False
        loginFront.usernameCredentials = ""
        loginFront.passwordCredentials = ""
        loginFront.userAdded = False
        loginFront.madeItOut = False
        return True, 3
        pass
    else:
        try:
            #Some may try to login without ever creating a user on the device
            #This doesnt create the doc we just check if it was able to be opened or not
            #The doc will only open if there is atleast one user in the system. If not it will not open
            #And we will display the fail if we go to the except
            userLogins = open("userLogins.txt","r")
            userLogins.close()
            
            #goes to check if their login was successful
            #Returns True if it was
            #returns False if it wasnt
            #print("File opened successfully")
            x = verifyLogin(loginFront.usernameCredentials,loginFront.passwordCredentials)
            #print("Not in verify login")
            if x == True:
                #Here we return False and 1 because we want to exit the while x== True
                #and we want to display the success of sf
                return False, 1

            elif x == False:
                #False we return true to re-enter the loop and 2 to indicate a failure of some kind
                #We also need to reset all of the usernames and passwords
                loginFront.usernameDone = False
                loginFront.passwordDone = False
                loginFront.usernameCredentials = ""
                loginFront.passwordCredentials = ""
                return True, 2
            else:
                pass
            pass
        except:
            #This except is entered if there was a problem opening the folder with users on it above
            #We then return true to re-enter the loop and send back a 2 to indicate a failure
            #while also resetting the usernames and passwords
            print("There are no accounts on this device")
            loginFront.usernameDone = False
            loginFront.passwordDone = False
            loginFront.usernameCredentials = ""
            loginFront.passwordCredentials = ""
            return True, 2
            pass

    pass

def verifyLogin(usernameCreds="",passwordCreds=""):
    #We cant reach this point without have tried opening the doc earlier so we dont need a try and except
    userLogins = open("userLogins.txt","r")
    #userInfo holds the split up values from the users in the doc.
    #Every time this is opened it gets reset with all of the new accounts and values of their credits
    userInfo = []

    #Have it pass in the credentials of username and password
    #import main and set the username in main as well as credits
    #Return something in order to break out of the loop as shown at the bottom
    #If it doesnt meet the criteria and username or password is still None then restart the loop with a failed x symbol

    for x in userLogins:
        splitInfo = x.split(",")
        pass
    #print("Past the split")
    #we split them based on their commas
    splitInfo.pop(0)
    #then I need to pop the first one because there is technically a [" "] from the first comma
    for x in range(len(splitInfo)):
        userInfo.append(splitInfo[x])
    #User info gets all of the elements from the splitInfo and we initialize the variables
    #print("Past user info append")
    confirmedUsername = None
    confirmedPassword = None
    credits = None
    posInUserInfo = None


    #Checks if the username and password match what we have on file one after the other
    #If so we store that as our confirmed username and password and leave the for loop with the first instance
    
    for x in range(len(userInfo)):
        if (userInfo[x] == usernameCreds) and (userInfo[(x+1)] == passwordCreds):
            confirmedUsername = userInfo[x]
            confirmedPassword = userInfo[(x+1)]
            credits = int(userInfo[(x+2)])
            posInUserInfo = x
            break


    #print("Paired all information successfully")
    #Checks if the username and password match what we have on file one after the other
    #If so we store that as our confirmed username and password and leave the for loop with the first instance

    #Responsible programming
    userLogins.close()
    #Responsible programming


    #chekcs for what to return. If either of them are still set to None then we return false as the creds were wrong
    #If they both have values then that means that they have successfully logged in and we change the variables in
    #the main loginFront file for the return of the information

    #print("Made it to the end")
    if (confirmedUsername == None) or (confirmedPassword == None):
        return False
    else:
        loginFront.username = confirmedUsername 
        loginFront.credits = credits
        loginFront.posInUserInfo = posInUserInfo
        loginFront.password = confirmedPassword
        return True
    #print("IDK WHERE THE PROBLEM IS!")
    pass

def updateValues(u="",p="",c=0,pos=0):
    #When called it returns the new position of the user playing
    #Im not commenting this entire thing again
    #only new things will be commented

    #to add to user info
    userLogins = open("userLogins.txt","r")
    userInfo = []
    #splitInfo = None

    for x in userLogins:
        #print("In user login")
        splitInfo = x.split(",")
        pass
    splitInfo.pop(0)

    for x in range(len(splitInfo)):
        userInfo.append(splitInfo[x])
    userLogins.close()
        #to add to user info

    #Current User Data is now erased
    for x in range(3):
        userInfo.pop(pos)
    #print("User Info:",userInfo)
    #Current User Data is now erased

    #Need to erase the whole file
    userLogins = open("userLogins.txt","w")
    userLogins.write("")
    userLogins.close()
    #print("File erased")
    #Need to erase the whole file


    #The way this works is something
    #So numOfProfiles is the list of elements divided by 3 because there are
    #3 parts to each person's profile
    #Then we do a for loop based on how many profiles there are here
    #starting with 0 we are able to get every user profile from the list
    #We multiply by 0 to increment it and add one or two to move over the 
    #places that we need to move. Then the for loop increments and goes again
    numOfProfiles = int((len(userInfo) / 3))
    userLogins = open("userLogins.txt","a")
    for x in range(numOfProfiles):
        first = str(userInfo[(x * 3)])
        second = str(userInfo[(x * 3) + 1])
        third = str(userInfo[(x * 3) + 2])
        userLogins.write(","+first+","+second+","+third)
        #userLogins.write(","+userLogins[first]+","+userLogins[second]+","+userLogins[third])

    #We finally add back in the profile that we are using again
    userLogins.write(","+u+","+p+","+str(c))
    userLogins.close()
    #print("file updated")


    #I then do the entire process again in order to get the position of the username in the file
    userLogins = open("userLogins.txt","r")
    userInfo = []
    #splitInfo = None

    for x in userLogins:
        #print("In user login")
        splitInfo = x.split(",")
        pass
    splitInfo.pop(0)

    for x in range(len(splitInfo)):
        userInfo.append(splitInfo[x])

    count = 0
    for x in range (len(userInfo)):
        count += 1
    #print("New Credits Saved\n")
    userLogins.close()
    #I then do the entire process again in order to get the position of the username in the file
    return (count - 3)