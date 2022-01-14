import pygame
import loginBack
import time

pygame.init()
pygame.font.init()

#Variables
surface = pygame.display.set_mode((1280,720)) 
pygame.display.set_caption("Legendary Login")
colors = {"forest green":(34,139,34), "white": (255,255,255), "black": (0,0,0),"dark green":(0,100,0),"firebrick":(178,34,34),"golden rod":(218,165,32)}
font = {"freesansboldLRG" : pygame.font.Font('freesansbold.ttf', 40), "freesansboldSML" : pygame.font.Font('freesansbold.ttf', 35), "freesansboldXXS" : pygame.font.Font('freesansbold.ttf', 15)}
surface.fill(colors["forest green"])
usernameCredentials = ""
usernameDone = False
passwordCredentials = ""
passwordDone = False
userAdded = False
madeItOut = False
username = None
password = None
credits = None
posInUserInfo = None
#Variables

def login():
    background()
    #this x and is for the while loop inside
    #sf is the variable for whether a user was added, failed to login, logged in, or added a user
    sf = None
    x = True
    while True:
        for event in pygame.event.get():
            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE) or (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_q):
                pygame.quit()
                exit()

        #Checking for credentials
        #made it out is an extra one of check I will admit. It is changed in the back end for login
        #This is to make sure that we truly dont go back into the loop, because we cant access the
        #x variable from the back end and we can't pull the x out of login for some reason
        while (x == True) and (madeItOut == False):

            #these are for moving the user inputs right for every character entered / ie. The username and password
            usernameXPOS = 9.5
            passwordXPOS = 9.5
            x = loginBack.addCredentials()
            if len(usernameCredentials) > 0:
                usernameXPOS = usernameXPOS * (len(usernameCredentials) - 1)
            if len(passwordCredentials) > 0:
                passwordXPOS = passwordXPOS * (len(passwordCredentials) - 1)
            #these are for moving the user inputs right for every character entered / ie. The username and password

            #background has sf inside of it this time in order to update with the sf that is below this
            #so that we continuously display the status of the last login
            background(sf)
            showCredentials(usernameCredentials, passwordCredentials, usernameXPOS, passwordXPOS)
            pygame.display.update()
            pass
        #Credential Check is over and x = True

        x,sf = loginBack.existingUser(usernameCredentials,passwordCredentials)

        #This is for when a login is fully completed.
        #We enter this statement so that we can go back to main
        if sf == 1:
            background(sf)
            showCredentials(usernameCredentials, passwordCredentials, usernameXPOS, passwordXPOS)
            pygame.display.update()
            time.sleep(2)
            pygame.display.quit()
            return username,password,credits,posInUserInfo

        #This background also has an sf in it to reflect the sf from the existing user call
        #It tells the display what message to show for the login
        background(sf)
        showCredentials(usernameCredentials, passwordCredentials, usernameXPOS, passwordXPOS)
        pygame.display.update()

def showCredentials(u = "",p = "", ux = 0, px = 0):
    

    #User's username
    userName = font["freesansboldSML"].render(u, True, colors["black"])
    userNameRect = userName.get_rect()
    userNameRect.center = (((1280//2) - 105) + ux, (720//2) + 2)
    #User's username

    #User's password
    password = font["freesansboldSML"].render(p, True, colors["black"])
    passwordRect = password.get_rect()
    passwordRect.center = (((1280//2) - 105) + px, (720//2) + 102)
    #User's password



    surface.blit(userName, userNameRect)
    surface.blit(password, passwordRect)
    #ux and px are how far right to shift the center of text to fit in the box
    pass

def background(sf = None):

    #The literal word login
    wordLogin = font["freesansboldLRG"].render("Login", True, colors["white"])
    loginRect = wordLogin.get_rect()
    loginRect.center = ((1280//2), (720//2) - 100)
    #The literal word login

    #Username Text
    username = font["freesansboldLRG"].render("Username", True, colors["white"])
    usernameRect = wordLogin.get_rect()
    usernameRect.center = ((1280//2) // 2, (720//2))
    #Username Text

    #Password Text
    password = font["freesansboldLRG"].render("Password", True, colors["white"])
    passwordRect = wordLogin.get_rect()
    passwordRect.center = ((1280//2) // 2, (720//2) + 100)
    #Password Text

    surface.fill(colors["forest green"])
    surface.blit(wordLogin, loginRect)
    surface.blit(username, usernameRect)
    surface.blit(password, passwordRect)
    
    #Username then Password Box
    pygame.draw.rect(surface,colors["white"], [(1280//2) - 120, (720//2) - 20, 240, 40])
    pygame.draw.rect(surface,colors["white"], [(1280//2) - 120, (720//2) + 80, 240, 40])
    #Username and Password Boxes

    #background also draw the new user and logincheck
    newUserButton()
    loginCheck(sf)
    #background also draw the new user and logincheck
    pass

def newUserButton():

    #New user box
    pygame.draw.rect(surface,colors["white"], [(1280//2) - 60, (720//2) + 140, 120, 20])
    #New user box

    #New User Text
    newUserTXT = font["freesansboldXXS"].render("New User", True, colors["black"])
    newUserRect = newUserTXT.get_rect()
    newUserRect.center = ((1280//2) - 0, (720//2) + 150)
    #New User Text

    surface.blit(newUserTXT,newUserRect)

def loginCheck(x = None):
    #The variables of X do as follows
    #1 = Means there was a successful login
    #2 = Means there was a failed login
    #3 = Means that there was a user added

    #Draws Check for successful login
    if x == 1: 
        pygame.draw.line(surface,colors["dark green"], (810,500),(830,520),20)
        pygame.draw.line(surface,colors["dark green"], (830,520),(860,470),20)
        loggedIn = font["freesansboldSML"].render("Logged In", True, colors["dark green"])
        loggedInRect = loggedIn.get_rect()
        loggedInRect.center = (950, 500)
        surface.blit(loggedIn,loggedInRect)
    #Draws Check for successful login

    #Draws X for failed login
    elif x == 2:
        pygame.draw.line(surface,colors["firebrick"], (830,520),(860,470),20)
        pygame.draw.line(surface,colors["firebrick"], (830,470),(860,520),20)
        tryAgain = font["freesansboldSML"].render("Try Again", True, colors["firebrick"])
        tryAgainRect = tryAgain.get_rect()
        tryAgainRect.center = (950, 500)
        surface.blit(tryAgain,tryAgainRect)
    #Draws X for failed login

    elif x == 3:
        pygame.draw.line(surface,colors["golden rod"], (845,520),(845,470),20)
        pygame.draw.line(surface,colors["golden rod"], (820,495),(870,495),20)
        added = font["freesansboldSML"].render("Added", True, colors["golden rod"])
        addedRect = added.get_rect()
        addedRect.center = (950, 500)
        surface.blit(added,addedRect)
    else:
        pass

    pass