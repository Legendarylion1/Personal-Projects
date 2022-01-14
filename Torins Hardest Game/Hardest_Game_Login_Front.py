import pygame

#Varaibles
pygame.init()
pygame.display.init()
pygame.font.init()
surface = pygame.display.set_mode((1280,720))
pygame.display.set_caption("Torins Hardest Game")
colors = {"forest green":(34,139,34), "white": (255,255,255), "black": (0,0,0),"dark green":(0,100,0),"firebrick":(178,34,34),"golden rod":(218,165,32), "sky blue":(135, 206, 235), "orchid":(218,112,214), "chocolate":(210,105,30)}
font = {"freesansboldXXL" : pygame.font.Font('freesansbold.ttf', 160),"freesansboldLRG" : pygame.font.Font('freesansbold.ttf', 40), "freesansboldSML" : pygame.font.Font('freesansbold.ttf', 35), "freesansboldXXS" : pygame.font.Font('freesansbold.ttf', 15)}
encryptedDictS = {"a":"d", "b": "l", "c":"e", "f":"o", "m":"x", "q":"f", "d":"c", "e":"i", "g":"v", "w":"a", "t":"j", "z":"r", "i":"k", "r":"7", "h":"g", "s":"q", "j":"y", "k":"m", "x":"n", "o":"p", "p":"s", "v":"h", "u":"b", "n":"t", "y":"u", "l":"w"}
decryptedDictS = {"d":"a", "l": "b", "e":"c", "o":"f", "x":"m", "f":"q", "c":"d", "i":"e", "v":"g", "a":"w", "j":"t", "r":"z", "k":"i", "7":"r", "g":"h", "q":"s", "y":"j", "m":"k", "n":"x", "p":"o", "s":"p", "h":"v", "b":"u", "t":"n", "u":"y", "w":"l"}
encryptedDictI = {"1":"b","2":"l","3":"u","4":"v","5":"e","6":"s","7":"m","8":"g","9":"r","0":"w",":":"y"}
decryptedDictI = {"b":"1","l":"2","u":"3","v":"4","e":"5","s":"6","m":"7","g":"8","r":"9","w":"0","y":":","q":"N/A"}
numOfAccounts = 0
listOfUsernames = []
listOfPasswords = []
listOfAttempts = []
listOfTimes = []
possibleError = 0
#Variables



#This screen takes no input. It uses the default lists to display the
#credentials of each user profile
def defaultScreen():
    surface = pygame.display.set_mode((1280,720))
    surface.fill(colors["sky blue"])
    if numOfAccounts <= 3:
        firstRow()
    elif numOfAccounts <= 6:
        secondRow()
    elif numOfAccounts <= 9:
        thirdRow()

    plusButton()
    
    pygame.display.update()

#THESE ARE THE BUBBLE ROWS
def firstRow(all = 0):
    #They look at the lists of users and print their username, attempts, and pb in the bubbles on the default screen
    if all == 0:
        if numOfAccounts == 1:
            userName1 = font["freesansboldLRG"].render(listOfUsernames[0].upper(), True, colors["black"])
            userNameRect1 = userName1.get_rect()
            userNameRect1.center = (245,100)

            attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[0])), True, colors["black"])
            attemptsRect1 = attempts1.get_rect()
            attemptsRect1.center = (245,135)

            pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect1 = pbtxt1.get_rect()
            pbtxtRect1.center = (250,155)
            pb1 = font["freesansboldXXS"].render(str(listOfTimes[0]), True, colors["black"])
            pbRect1 = pb1.get_rect()
            pbRect1.center = (250,170)

            pygame.draw.ellipse(surface,colors["black"],((96,46),(308,158)))
            pygame.draw.ellipse(surface,colors["white"],((100,50),(300,150)))
            surface.blit(userName1, userNameRect1)
            surface.blit(attempts1, attemptsRect1)
            surface.blit(pbtxt1, pbtxtRect1)
            surface.blit(pb1, pbRect1)
        if numOfAccounts == 2:
            userName1 = font["freesansboldLRG"].render(listOfUsernames[0].upper(), True, colors["black"])
            userNameRect1 = userName1.get_rect()
            userNameRect1.center = (245,100)
            userName2 = font["freesansboldLRG"].render(listOfUsernames[1].upper(), True, colors["black"])
            userNameRect2 = userName2.get_rect()
            userNameRect2.center = (645,100)

            attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[0])), True, colors["black"])
            attemptsRect1 = attempts1.get_rect()
            attemptsRect1.center = (245,135)
            attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[1])), True, colors["black"])
            attemptsRect2 = attempts2.get_rect()
            attemptsRect2.center = (645,135)

            pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect1 = pbtxt1.get_rect()
            pbtxtRect1.center = (250,155)
            pb1 = font["freesansboldXXS"].render(str(listOfTimes[0]), True, colors["black"])
            pbRect1 = pb1.get_rect()
            pbRect1.center = (250,170)

            pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect2 = pbtxt2.get_rect()
            pbtxtRect2.center = (650,155)
            pb2 = font["freesansboldXXS"].render(str(listOfTimes[1]), True, colors["black"])
            pbRect2 = pb2.get_rect()
            pbRect2.center = (650,170)

            pygame.draw.ellipse(surface,colors["black"],((96,46),(308,158)))
            pygame.draw.ellipse(surface,colors["black"],((496,46),(308,158)))
            pygame.draw.ellipse(surface,colors["white"],((100,50),(300,150)))
            pygame.draw.ellipse(surface,colors["white"],((500,50),(300,150)))
            surface.blit(userName1, userNameRect1)
            surface.blit(userName2, userNameRect2)
            surface.blit(attempts1, attemptsRect1)
            surface.blit(attempts2, attemptsRect2)
            surface.blit(pbtxt1, pbtxtRect1)
            surface.blit(pb1, pbRect1)
            surface.blit(pbtxt2, pbtxtRect2)
            surface.blit(pb2, pbRect2)
        if numOfAccounts == 3:

            #USERNAMES
            userName1 = font["freesansboldLRG"].render(listOfUsernames[0].upper(), True, colors["black"])
            userNameRect1 = userName1.get_rect()
            userNameRect1.center = (245,100)
            userName2 = font["freesansboldLRG"].render(listOfUsernames[1].upper(), True, colors["black"])
            userNameRect2 = userName2.get_rect()
            userNameRect2.center = (645,100)
            userName3 = font["freesansboldLRG"].render(listOfUsernames[2].upper(), True, colors["black"])
            userNameRect3 = userName3.get_rect()
            userNameRect3.center = (1045,100)
            #USERNAMES

            #ATTEMPTS
            attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[0])), True, colors["black"])
            attemptsRect1 = attempts1.get_rect()
            attemptsRect1.center = (245,135)
            attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[1])), True, colors["black"])
            attemptsRect2 = attempts2.get_rect()
            attemptsRect2.center = (645,135)
            attempts3 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[2])), True, colors["black"])
            attemptsRect3 = attempts1.get_rect()
            attemptsRect3.center = (1045,135)
            #ATTEMPTS

            #PERSONAL BESTS
            pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect1 = pbtxt1.get_rect()
            pbtxtRect1.center = (250,155)
            pb1 = font["freesansboldXXS"].render(str(listOfTimes[0]), True, colors["black"])
            pbRect1 = pb1.get_rect()
            pbRect1.center = (250,170)

            pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect2 = pbtxt2.get_rect()
            pbtxtRect2.center = (650,155)
            pb2 = font["freesansboldXXS"].render(str(listOfTimes[1]), True, colors["black"])
            pbRect2 = pb2.get_rect()
            pbRect2.center = (650,170)

            pbtxt3 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect3 = pbtxt3.get_rect()
            pbtxtRect3.center = (1050,155)
            pb3 = font["freesansboldXXS"].render(str(listOfTimes[2]), True, colors["black"])
            pbRect3 = pb3.get_rect()
            pbRect3.center = (1050,170)
            #PERSONAL BESTS

            pygame.draw.ellipse(surface,colors["black"],((96,46),(308,158)))
            pygame.draw.ellipse(surface,colors["black"],((496,46),(308,158)))
            pygame.draw.ellipse(surface,colors["black"],((896,46),(308,158)))
            pygame.draw.ellipse(surface,colors["white"],((100,50),(300,150)))
            pygame.draw.ellipse(surface,colors["white"],((500,50),(300,150)))
            pygame.draw.ellipse(surface,colors["white"],((900,50),(300,150)))
            surface.blit(userName1, userNameRect1)
            surface.blit(userName2, userNameRect2)
            surface.blit(userName3, userNameRect3)
            surface.blit(attempts1, attemptsRect1)
            surface.blit(attempts2, attemptsRect2)
            surface.blit(attempts3, attemptsRect3)
            surface.blit(pbtxt1, pbtxtRect1)
            surface.blit(pb1, pbRect1)
            surface.blit(pbtxt2, pbtxtRect2)
            surface.blit(pb2, pbRect2)
            surface.blit(pbtxt3, pbtxtRect3)
            surface.blit(pb3, pbRect3)
    else:
        #USERNAMES
        userName1 = font["freesansboldLRG"].render(listOfUsernames[0].upper(), True, colors["black"])
        userNameRect1 = userName1.get_rect()
        userNameRect1.center = (245,100)
        userName2 = font["freesansboldLRG"].render(listOfUsernames[1].upper(), True, colors["black"])
        userNameRect2 = userName2.get_rect()
        userNameRect2.center = (645,100)
        userName3 = font["freesansboldLRG"].render(listOfUsernames[2].upper(), True, colors["black"])
        userNameRect3 = userName3.get_rect()
        userNameRect3.center = (1045,100)
        #USERNAMES

        #ATTEMPTS
        attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[0])), True, colors["black"])
        attemptsRect1 = attempts1.get_rect()
        attemptsRect1.center = (245,135)
        attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[1])), True, colors["black"])
        attemptsRect2 = attempts2.get_rect()
        attemptsRect2.center = (645,135)
        attempts3 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[2])), True, colors["black"])
        attemptsRect3 = attempts1.get_rect()
        attemptsRect3.center = (1045,135)
        #ATTEMPTS

        #PERSONAL BESTS
        pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect1 = pbtxt1.get_rect()
        pbtxtRect1.center = (250,155)
        pb1 = font["freesansboldXXS"].render(str(listOfTimes[0]), True, colors["black"])
        pbRect1 = pb1.get_rect()
        pbRect1.center = (250,170)

        pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect2 = pbtxt2.get_rect()
        pbtxtRect2.center = (650,155)
        pb2 = font["freesansboldXXS"].render(str(listOfTimes[1]), True, colors["black"])
        pbRect2 = pb2.get_rect()
        pbRect2.center = (650,170)

        pbtxt3 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect3 = pbtxt3.get_rect()
        pbtxtRect3.center = (1050,155)
        pb3 = font["freesansboldXXS"].render(str(listOfTimes[2]), True, colors["black"])
        pbRect3 = pb3.get_rect()
        pbRect3.center = (1050,170)
        #PERSONAL BESTS
        
        pygame.draw.ellipse(surface,colors["black"],((96,46),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((496,46),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((896,46),(308,158)))


        pygame.draw.ellipse(surface,colors["white"],((100,50),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((500,50),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((900,50),(300,150)))
        surface.blit(userName1, userNameRect1)
        surface.blit(userName2, userNameRect2)
        surface.blit(userName3, userNameRect3)
        surface.blit(attempts1, attemptsRect1)
        surface.blit(attempts2, attemptsRect2)
        surface.blit(attempts3, attemptsRect3)
        surface.blit(pbtxt1, pbtxtRect1)
        surface.blit(pb1, pbRect1)
        surface.blit(pbtxt2, pbtxtRect2)
        surface.blit(pb2, pbRect2)
        surface.blit(pbtxt3, pbtxtRect3)
        surface.blit(pb3, pbRect3)
    pass
def secondRow(all = 0):
    firstRow(1)
    if all == 0:
        if numOfAccounts == 4:
            userName1 = font["freesansboldLRG"].render(listOfUsernames[3].upper(), True, colors["black"])
            userNameRect1 = userName1.get_rect()
            userNameRect1.center = (245,300)
            attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[3])), True, colors["black"])
            attemptsRect1 = attempts1.get_rect()
            attemptsRect1.center = (245,335)
            pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect1 = pbtxt1.get_rect()
            pbtxtRect1.center = (250,355)
            pb1 = font["freesansboldXXS"].render(str(listOfTimes[3]), True, colors["black"])
            pbRect1 = pb1.get_rect()
            pbRect1.center = (250,370)

            pygame.draw.ellipse(surface,colors["black"],((96,246),(308,158)))
            pygame.draw.ellipse(surface,colors["white"],((100,250),(300,150)))
            surface.blit(userName1, userNameRect1)
            surface.blit(attempts1, attemptsRect1)
            surface.blit(pbtxt1, pbtxtRect1)
            surface.blit(pb1, pbRect1)
        if numOfAccounts == 5:
            userName1 = font["freesansboldLRG"].render(listOfUsernames[3].upper(), True, colors["black"])
            userNameRect1 = userName1.get_rect()
            userNameRect1.center = (245,300)
            userName2 = font["freesansboldLRG"].render(listOfUsernames[4].upper(), True, colors["black"])
            userNameRect2 = userName2.get_rect()
            userNameRect2.center = (645,300)
            attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[3])), True, colors["black"])
            attemptsRect1 = attempts1.get_rect()
            attemptsRect1.center = (245,335)
            attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[4])), True, colors["black"])
            attemptsRect2 = attempts2.get_rect()
            attemptsRect2.center = (645,335)

            pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect1 = pbtxt1.get_rect()
            pbtxtRect1.center = (250,355)
            pb1 = font["freesansboldXXS"].render(str(listOfTimes[3]), True, colors["black"])
            pbRect1 = pb1.get_rect()
            pbRect1.center = (250,370)

            pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect2 = pbtxt2.get_rect()
            pbtxtRect2.center = (650,355)
            pb2 = font["freesansboldXXS"].render(str(listOfTimes[4]), True, colors["black"])
            pbRect2 = pb2.get_rect()
            pbRect2.center = (650,370)

            pygame.draw.ellipse(surface,colors["black"],((96,246),(308,158)))
            pygame.draw.ellipse(surface,colors["black"],((496,246),(308,158)))
            pygame.draw.ellipse(surface,colors["white"],((100,250),(300,150)))
            pygame.draw.ellipse(surface,colors["white"],((500,250),(300,150)))
            surface.blit(userName1, userNameRect1)
            surface.blit(userName2, userNameRect2)
            surface.blit(attempts1, attemptsRect1)
            surface.blit(attempts2, attemptsRect2)
            surface.blit(pbtxt1, pbtxtRect1)
            surface.blit(pb1, pbRect1)
            surface.blit(pbtxt2, pbtxtRect2)
            surface.blit(pb2, pbRect2)
        if numOfAccounts == 6:
            userName1 = font["freesansboldLRG"].render(listOfUsernames[3].upper(), True, colors["black"])
            userNameRect1 = userName1.get_rect()
            userNameRect1.center = (245,300)
            userName2 = font["freesansboldLRG"].render(listOfUsernames[4].upper(), True, colors["black"])
            userNameRect2 = userName2.get_rect()
            userNameRect2.center = (645,300)
            userName3 = font["freesansboldLRG"].render(listOfUsernames[5].upper(), True, colors["black"])
            userNameRect3 = userName3.get_rect()
            userNameRect3.center = (1045,300)
            attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[3])), True, colors["black"])
            attemptsRect1 = attempts1.get_rect()
            attemptsRect1.center = (245,335)
            attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[4])), True, colors["black"])
            attemptsRect2 = attempts2.get_rect()
            attemptsRect2.center = (645,335)
            attempts3 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[5])), True, colors["black"])
            attemptsRect3 = attempts1.get_rect()
            attemptsRect3.center = (1045,335)

            #PERSONAL BESTS
            pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect1 = pbtxt1.get_rect()
            pbtxtRect1.center = (250,355)
            pb1 = font["freesansboldXXS"].render(str(listOfTimes[3]), True, colors["black"])
            pbRect1 = pb1.get_rect()
            pbRect1.center = (250,370)

            pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect2 = pbtxt2.get_rect()
            pbtxtRect2.center = (650,355)
            pb2 = font["freesansboldXXS"].render(str(listOfTimes[4]), True, colors["black"])
            pbRect2 = pb2.get_rect()
            pbRect2.center = (650,370)

            pbtxt3 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
            pbtxtRect3 = pbtxt3.get_rect()
            pbtxtRect3.center = (1050,355)
            pb3 = font["freesansboldXXS"].render(str(listOfTimes[5]), True, colors["black"])
            pbRect3 = pb3.get_rect()
            pbRect3.center = (1050,370)
            #PERSONAL BESTS

            pygame.draw.ellipse(surface,colors["black"],((96,246),(308,158)))
            pygame.draw.ellipse(surface,colors["black"],((496,246),(308,158)))
            pygame.draw.ellipse(surface,colors["black"],((896,246),(308,158)))
            pygame.draw.ellipse(surface,colors["white"],((100,250),(300,150)))
            pygame.draw.ellipse(surface,colors["white"],((500,250),(300,150)))
            pygame.draw.ellipse(surface,colors["white"],((900,250),(300,150)))
            surface.blit(userName1, userNameRect1)
            surface.blit(userName2, userNameRect2)
            surface.blit(userName3, userNameRect3)
            surface.blit(attempts1, attemptsRect1)
            surface.blit(attempts2, attemptsRect2)
            surface.blit(attempts3, attemptsRect3)
            surface.blit(pbtxt1, pbtxtRect1)
            surface.blit(pb1, pbRect1)
            surface.blit(pbtxt2, pbtxtRect2)
            surface.blit(pb2, pbRect2)
            surface.blit(pbtxt3, pbtxtRect3)
            surface.blit(pb3, pbRect3)
    else:
        #USERNAMES
        userName1 = font["freesansboldLRG"].render(listOfUsernames[3].upper(), True, colors["black"])
        userNameRect1 = userName1.get_rect()
        userNameRect1.center = (245,300)
        userName2 = font["freesansboldLRG"].render(listOfUsernames[4].upper(), True, colors["black"])
        userNameRect2 = userName2.get_rect()
        userNameRect2.center = (645,300)
        userName3 = font["freesansboldLRG"].render(listOfUsernames[5].upper(), True, colors["black"])
        userNameRect3 = userName3.get_rect()
        userNameRect3.center = (1045,300)
        #USERNAMES

        #ATTEMPTS
        attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[3])), True, colors["black"])
        attemptsRect1 = attempts1.get_rect()
        attemptsRect1.center = (245,335)
        attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[4])), True, colors["black"])
        attemptsRect2 = attempts2.get_rect()
        attemptsRect2.center = (645,335)
        attempts3 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[5])), True, colors["black"])
        attemptsRect3 = attempts1.get_rect()
        attemptsRect3.center = (1045,335)
        #ATTEMPTS

        #PERSONAL BESTS
        pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect1 = pbtxt1.get_rect()
        pbtxtRect1.center = (250,355)
        pb1 = font["freesansboldXXS"].render(str(listOfTimes[3]), True, colors["black"])
        pbRect1 = pb1.get_rect()
        pbRect1.center = (250,370)

        pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect2 = pbtxt2.get_rect()
        pbtxtRect2.center = (650,355)
        pb2 = font["freesansboldXXS"].render(str(listOfTimes[4]), True, colors["black"])
        pbRect2 = pb2.get_rect()
        pbRect2.center = (650,370)

        pbtxt3 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect3 = pbtxt3.get_rect()
        pbtxtRect3.center = (1050,355)
        pb3 = font["freesansboldXXS"].render(str(listOfTimes[5]), True, colors["black"])
        pbRect3 = pb3.get_rect()
        pbRect3.center = (1050,370)
        #PERSONAL BESTS

        pygame.draw.ellipse(surface,colors["black"],((96,246),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((496,246),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((896,246),(308,158)))
        pygame.draw.ellipse(surface,colors["white"],((100,250),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((500,250),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((900,250),(300,150)))
        surface.blit(userName1, userNameRect1)
        surface.blit(userName2, userNameRect2)
        surface.blit(userName3, userNameRect3)
        surface.blit(attempts1, attemptsRect1)
        surface.blit(attempts2, attemptsRect2)
        surface.blit(attempts3, attemptsRect3)
        surface.blit(pbtxt1, pbtxtRect1)
        surface.blit(pb1, pbRect1)
        surface.blit(pbtxt2, pbtxtRect2)
        surface.blit(pb2, pbRect2)
        surface.blit(pbtxt3, pbtxtRect3)
        surface.blit(pb3, pbRect3)
    pass
def thirdRow():
    secondRow(1)
    
    if numOfAccounts == 7:
        userName1 = font["freesansboldLRG"].render(listOfUsernames[6].upper(), True, colors["black"])
        userNameRect1 = userName1.get_rect()
        userNameRect1.center = (245,500)
        attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[6])), True, colors["black"])
        attemptsRect1 = attempts1.get_rect()
        attemptsRect1.center = (245,535)
        pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect1 = pbtxt1.get_rect()
        pbtxtRect1.center = (250,555)
        pb1 = font["freesansboldXXS"].render(str(listOfTimes[6]), True, colors["black"])
        pbRect1 = pb1.get_rect()
        pbRect1.center = (250,570)

        pygame.draw.ellipse(surface,colors["black"],((96,446),(308,158)))
        pygame.draw.ellipse(surface,colors["white"],((100,450),(300,150)))
        surface.blit(userName1, userNameRect1)
        surface.blit(attempts1, attemptsRect1)
        surface.blit(pbtxt1, pbtxtRect1)
        surface.blit(pb1, pbRect1)
        
    if numOfAccounts == 8:
        userName1 = font["freesansboldLRG"].render(listOfUsernames[6].upper(), True, colors["black"])
        userNameRect1 = userName1.get_rect()
        userNameRect1.center = (245,500)
        userName2 = font["freesansboldLRG"].render(listOfUsernames[7].upper(), True, colors["black"])
        userNameRect2 = userName2.get_rect()
        userNameRect2.center = (645,500)
        attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[6])), True, colors["black"])
        attemptsRect1 = attempts1.get_rect()
        attemptsRect1.center = (245,535)
        attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[7])), True, colors["black"])
        attemptsRect2 = attempts2.get_rect()
        attemptsRect2.center = (645,535)

        pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect1 = pbtxt1.get_rect()
        pbtxtRect1.center = (250,555)
        pb1 = font["freesansboldXXS"].render(str(listOfTimes[6]), True, colors["black"])
        pbRect1 = pb1.get_rect()
        pbRect1.center = (250,570)

        pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect2 = pbtxt2.get_rect()
        pbtxtRect2.center = (650,555)
        pb2 = font["freesansboldXXS"].render(str(listOfTimes[7]), True, colors["black"])
        pbRect2 = pb2.get_rect()
        pbRect2.center = (650,570)

        pygame.draw.ellipse(surface,colors["black"],((96,446),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((496,446),(308,158)))
        pygame.draw.ellipse(surface,colors["white"],((100,450),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((500,450),(300,150)))
        surface.blit(userName1, userNameRect1)
        surface.blit(userName2, userNameRect2)
        surface.blit(attempts1, attemptsRect1)
        surface.blit(attempts2, attemptsRect2)
        surface.blit(pbtxt1, pbtxtRect1)
        surface.blit(pb1, pbRect1)
        surface.blit(pbtxt2, pbtxtRect2)
        surface.blit(pb2, pbRect2)
    if numOfAccounts == 9:
        userName1 = font["freesansboldLRG"].render(listOfUsernames[6].upper(), True, colors["black"])
        userNameRect1 = userName1.get_rect()
        userNameRect1.center = (245,500)
        userName2 = font["freesansboldLRG"].render(listOfUsernames[7].upper(), True, colors["black"])
        userNameRect2 = userName2.get_rect()
        userNameRect2.center = (645,500)
        userName3 = font["freesansboldLRG"].render(listOfUsernames[8].upper(), True, colors["black"])
        userNameRect3 = userName3.get_rect()
        userNameRect3.center = (1045,500)
        attempts1 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[6])), True, colors["black"])
        attemptsRect1 = attempts1.get_rect()
        attemptsRect1.center = (245,535)
        attempts2 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[7])), True, colors["black"])
        attemptsRect2 = attempts2.get_rect()
        attemptsRect2.center = (645,535)
        attempts3 = font["freesansboldXXS"].render(("Attempts: " + str(listOfAttempts[8])), True, colors["black"])
        attemptsRect3 = attempts1.get_rect()
        attemptsRect3.center = (1045,535)

        #PERSONAL BESTS
        pbtxt1 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect1 = pbtxt1.get_rect()
        pbtxtRect1.center = (250,555)
        pb1 = font["freesansboldXXS"].render(str(listOfTimes[6]), True, colors["black"])
        pbRect1 = pb1.get_rect()
        pbRect1.center = (250,570)

        pbtxt2 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect2 = pbtxt2.get_rect()
        pbtxtRect2.center = (650,555)
        pb2 = font["freesansboldXXS"].render(str(listOfTimes[7]), True, colors["black"])
        pbRect2 = pb2.get_rect()
        pbRect2.center = (650,570)

        pbtxt3 = font["freesansboldXXS"].render("Personal Best", True, colors["black"])
        pbtxtRect3 = pbtxt3.get_rect()
        pbtxtRect3.center = (1050,555)
        pb3 = font["freesansboldXXS"].render(str(listOfTimes[8]), True, colors["black"])
        pbRect3 = pb3.get_rect()
        pbRect3.center = (1050,570)
        #PERSONAL BESTS

        pygame.draw.ellipse(surface,colors["black"],((96,446),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((496,446),(308,158)))
        pygame.draw.ellipse(surface,colors["black"],((896,446),(308,158)))
        pygame.draw.ellipse(surface,colors["white"],((100,450),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((500,450),(300,150)))
        pygame.draw.ellipse(surface,colors["white"],((900,450),(300,150)))
        surface.blit(userName1, userNameRect1)
        surface.blit(userName2, userNameRect2)
        surface.blit(userName3, userNameRect3)
        surface.blit(attempts1, attemptsRect1)
        surface.blit(attempts2, attemptsRect2)
        surface.blit(attempts3, attemptsRect3)
        surface.blit(pbtxt1, pbtxtRect1)
        surface.blit(pb1, pbRect1)
        surface.blit(pbtxt2, pbtxtRect2)
        surface.blit(pb2, pbRect2)
        surface.blit(pbtxt3, pbtxtRect3)
        surface.blit(pb3, pbRect3)
    pass
#THESE ARE THE BUBBLE ROWS

    #BUTTONS
def plusButton():
    pygame.draw.circle(surface, colors["black"], (1220,660), 53)
    pygame.draw.circle(surface, colors["white"], (1220,660), 50)
    pygame.draw.line(surface, colors["golden rod"], (1220,700), (1220, 620), 20)
    pygame.draw.line(surface, colors["golden rod"], (1180,660), (1260, 660), 20)
    pass
def checkMarkButton():
    pygame.draw.circle(surface, colors["black"], (1220,660), 53)
    pygame.draw.circle(surface, colors["white"], (1220,660), 50)
    pygame.draw.line(surface, colors["forest green"], (1220,700), (1240, 630), 20) #Vertical
    pygame.draw.line(surface, colors["forest green"], (1195,665), (1220, 700), 20) #Horizontal
    pass
def backButton():
    pygame.draw.circle(surface, colors["black"], (60,660), 53)
    pygame.draw.circle(surface, colors["white"], (60,660), 50)
    pygame.draw.line(surface, colors["chocolate"], (20,660), (60, 620), 20)
    pygame.draw.line(surface, colors["chocolate"], (20,660), (100, 660), 20) #Horizontal
    pygame.draw.line(surface, colors["chocolate"], (20,660), (60,700), 20)
    pass
    #BUTTONS

#Takes in the first second third and fourth letter inputs for the username, and displays them
#It also takes the password and displays it as a "*" for security
def addUserScreen(firstletter = "",secondletter = "", thirdletter = "", fourthletter = "", userInputPassword = ""):
    #SCREEN RESET
    surface.fill(colors["sky blue"])

        #USERNAME STUFF
    userName1 = font["freesansboldSML"].render("USERNAME:", True, colors["white"])
    userNameRect1 = userName1.get_rect()
    userNameRect1.center = (640,25)
    userNameO1 = font["freesansboldSML"].render("USERNAME:", True, colors["black"])
    userNameORect1 = userNameO1.get_rect()
    userNameORect1.center = (638,27)

    letter1 = font["freesansboldXXL"].render(firstletter.upper(), True, colors["white"])
    letterRect1 = letter1.get_rect()
    letterRect1.center = (425,170)
    letterO1 = font["freesansboldXXL"].render(firstletter.upper(), True, colors["black"])
    letterORect1 = letterO1.get_rect()
    letterORect1.center = (423,172)

    letter2 = font["freesansboldXXL"].render(secondletter.upper(), True, colors["white"])
    letterRect2 = letter2.get_rect()
    letterRect2.center = (575,170)
    letterO2 = font["freesansboldXXL"].render(secondletter.upper(), True, colors["black"])
    letterORect2 = letterO2.get_rect()
    letterORect2.center = (573,172)

    letter3 = font["freesansboldXXL"].render(thirdletter.upper(), True, colors["white"])
    letterRect3 = letter3.get_rect()
    letterRect3.center = (725,170)
    letterO3 = font["freesansboldXXL"].render(thirdletter.upper(), True, colors["black"])
    letterORect3 = letterO3.get_rect()
    letterORect3.center = (723,172)

    letter4 = font["freesansboldXXL"].render(fourthletter.upper(), True, colors["white"])
    letterRect4 = letter4.get_rect()
    letterRect4.center = (875,170)
    letterO4 = font["freesansboldXXL"].render(fourthletter.upper(), True, colors["black"])
    letterORect4 = letterO4.get_rect()
    letterORect4.center = (873,172)

    pygame.draw.rect(surface,colors["black"], (338,48,624,264))
    pygame.draw.rect(surface,colors["orchid"], (340,50,620,260))
    pygame.draw.line(surface, colors["white"], (360,240), (490, 240), 30)
    pygame.draw.line(surface, colors["white"], (510,240), (640, 240), 30)
    pygame.draw.line(surface, colors["white"], (660,240), (790, 240), 30)
    pygame.draw.line(surface, colors["white"], (810,240), (940, 240), 30)
    surface.blit(userNameO1, userNameORect1)
    surface.blit(userName1, userNameRect1)
    surface.blit(letterO1, letterORect1)
    surface.blit(letter1, letterRect1)
    surface.blit(letterO2, letterORect2)
    surface.blit(letter2, letterRect2)
    surface.blit(letterO3, letterORect3)
    surface.blit(letter3, letterRect3)
    surface.blit(letterO4, letterORect4)
    surface.blit(letter4, letterRect4)
        #USERNAME STUFF





        #PASSWORD STUFF
    star = font["freesansboldXXL"].render(("*" * len(userInputPassword)), True, colors["white"])
    starRect = star.get_rect()
    starRect.center = ((875 - (30 * (len(userInputPassword) - 1))),545)
    starO = font["freesansboldXXL"].render(("*" * len(userInputPassword)), True, colors["black"])
    starORect= starO.get_rect()
    starORect.center = ((873 - (30 * (len(userInputPassword) - 1))),547)

    password1 = font["freesansboldSML"].render("Password:", True, colors["white"])
    passwordRect1 = password1.get_rect()
    passwordRect1.center = (640,395)
    passwordO1 = font["freesansboldSML"].render("Password:", True, colors["black"])
    passwordORect1 = passwordO1.get_rect()
    passwordORect1.center = (638,397)

    pygame.draw.rect(surface,colors["black"], (338,418,624,164))
    pygame.draw.rect(surface,colors["orchid"], (340,420,620,160))
    surface.blit(passwordO1, passwordORect1)
    surface.blit(password1, passwordRect1)
    surface.blit(starO, starORect)
    surface.blit(star, starRect)
        #PASSWORD STUFF

        #RUNNOFF
    pygame.draw.rect(surface,colors["sky blue"], (0,418,338,164))
    pygame.draw.rect(surface,colors["black"], (338,418,2,164))
        #RUNNOFF

        #Error Display
    if possibleError == 1:
        noSpaceError = font["freesansboldSML"].render("~ No Space ~", True, colors["firebrick"])
        noSpaceErrorRect = noSpaceError.get_rect()
        noSpaceErrorRect.center = (640,690)
        noSpaceErrorO = font["freesansboldSML"].render("~ No Space ~", True, colors["black"])
        noSpaceErrorORect = noSpaceErrorO.get_rect()
        noSpaceErrorORect.center = (639,691)
        surface.blit(noSpaceErrorO, noSpaceErrorORect)
        surface.blit(noSpaceError, noSpaceErrorRect)
    elif possibleError == 2:
        noPasswordError = font["freesansboldSML"].render("~ No Password ~", True, colors["firebrick"])
        noPasswordErrorRect = noPasswordError.get_rect()
        noPasswordErrorRect.center = (640,690)
        noPasswordErrorO = font["freesansboldSML"].render("~ No Password ~", True, colors["black"])
        noPasswordErrorORect = noPasswordErrorO.get_rect()
        noPasswordErrorORect.center = (639,691)
        surface.blit(noPasswordErrorO, noPasswordErrorORect)
        surface.blit(noPasswordError, noPasswordErrorRect)
        #Error Display


    checkMarkButton()
    backButton()
    pygame.display.update()
    pass

#Takes in the four letter username to be displayed, as well as the password which
#will be dispalyed as a "*" for security
def loginScreen(selectedUsername = "", userPassword = ""):

        #TOP HALF SHIT
    surface.fill(colors["sky blue"])
    Login1 = font["freesansboldSML"].render("LOGIN:", True, colors["white"])
    LoginRect1 = Login1.get_rect()
    LoginRect1.center = (640,25)
    LoginO = font["freesansboldSML"].render("LOGIN:", True, colors["black"])
    LoginORect = LoginO.get_rect()
    LoginORect.center = (638,27)


    username = font["freesansboldXXL"].render(selectedUsername.upper(), True, colors["white"])
    usernameRect = username.get_rect()
    usernameRect.center = (645,185)
    usernameO = font["freesansboldXXL"].render(selectedUsername.upper(), True, colors["black"])
    usernameORect = usernameO.get_rect()
    usernameORect.center = (643,187)

    pygame.draw.rect(surface,colors["black"], (338,48,624,264))
    pygame.draw.rect(surface,colors["orchid"], (340,50,620,260))
    surface.blit(usernameO, usernameORect)
    surface.blit(username, usernameRect)
        #TOP HALF SHIT



        #BOTTOM HALF SHIT
    star = font["freesansboldXXL"].render(("*" * len(userPassword)), True, colors["white"])
    starRect = star.get_rect()
    starRect.center = ((875 - (30 * (len(userPassword) - 1))),545)
    starO = font["freesansboldXXL"].render(("*" * len(userPassword)), True, colors["black"])
    starORect= starO.get_rect()
    starORect.center = ((873 - (30 * (len(userPassword) - 1))),547)

    password1 = font["freesansboldSML"].render("Password:", True, colors["white"])
    passwordRect1 = password1.get_rect()
    passwordRect1.center = (640,395)
    passwordO1 = font["freesansboldSML"].render("Password:", True, colors["black"])
    passwordORect1 = passwordO1.get_rect()
    passwordORect1.center = (638,397)

    pygame.draw.rect(surface,colors["black"], (338,418,624,164))
    pygame.draw.rect(surface,colors["orchid"], (340,420,620,160))
    surface.blit(passwordO1, passwordORect1)
    surface.blit(password1, passwordRect1)
    surface.blit(starO, starORect)
    surface.blit(star, starRect)
    surface.blit(LoginO, LoginORect)
    surface.blit(Login1, LoginRect1)
        #BOTTOM HALF SHIT

        #RUNNOFF
    pygame.draw.rect(surface,colors["sky blue"], (0,418,338,164))
    pygame.draw.rect(surface,colors["black"], (338,418,2,164))
        #RUNNOFF

    if possibleError == 1:
        incorrectLoginError = font["freesansboldSML"].render("~ Incorrect Login ~", True, colors["firebrick"])
        incorrectLoginErrorRect = incorrectLoginError.get_rect()
        incorrectLoginErrorRect.center = (640,690)
        incorrectLoginErrorO = font["freesansboldSML"].render("~ Incorrect Login ~", True, colors["black"])
        incorrectLoginErrorORect = incorrectLoginErrorO.get_rect()
        incorrectLoginErrorORect.center = (639,691)
        surface.blit(incorrectLoginErrorO, incorrectLoginErrorORect)
        surface.blit(incorrectLoginError, incorrectLoginErrorRect)

    backButton()
    checkMarkButton()
    pygame.display.update()
    pass