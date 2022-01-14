import pygame
import time

#level one

start = (100,540)


def level1(ua):
    import Hardest_Game_allLevels

    userAttempts = ua

    #returning of a 0 means that the level was failed, returning of a 1 means that the level was passed
    pygame.mouse.set_pos(start)
    while True:
        Hardest_Game_allLevels.levelOneDisplay(userAttempts)

        for event in pygame.event.get():

            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()

        x,y = pygame.mouse.get_pos()


        #Checking Start BOX
        if (x >= 0) and (x <= 199):
            if (y <= 390) or (y >= 690):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
        #Checking Start BOX

        #Checking inside of tube. If it touches the outside of the tube then it returns 0
        if (x >= 200) and (x <= 1720):
            if (y <= 530) or (y >= 550):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
        #Checking inside of tube. If it touches the outside of the tube then it returns 0

        #Checking End Box
        if (x >= 1721) and (x <= 1920):
            if (y >= 390) and (y <= 690):
                pygame.mouse.set_pos(start)
                return 1, userAttempts
        #Checking End Box

        time.sleep(.1)
    
        
    pass

def level2(ua):
    import Hardest_Game_allLevels
    userAttempts = ua

    pygame.mouse.set_pos(start)
    pygame.mouse.set_visible(True)

    while True:
        Hardest_Game_allLevels.levelTwoDisplay(userAttempts)

        for event in pygame.event.get():

            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()

        x,y = pygame.mouse.get_pos()


        #Checking Start BOX
        if (x >= 0) and (x <= 199):
            if (y <= 390) or (y >= 690):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                pygame.mouse.set_visible(True)
                return 0, userAttempts
        #Checking Start BOX
        pass

        #Checking inside of tube. If it touches the outside of the tube then it returns 0
        if (x >= 200) and (x <= 1720):
            if (y <= 530) or (y >= 550):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                pygame.mouse.set_visible(True)
                return 0, userAttempts
        #Checking inside of tube. If it touches the outside of the tube then it returns 0

        #Checking for invisbox
        if (x >= 1420):
            pygame.mouse.set_visible(False)
        else:
            pygame.mouse.set_visible(True)
        #Checking for invisbox

        #Checking End Box
        if (x >= 1721) and (x <= 1920):
            if (y >= 390) and (y <= 690):
                pygame.mouse.set_pos(start)
                pygame.mouse.set_visible(True)
                return 1, userAttempts
        #Checking End Box

    time.sleep(.1)
    pass

def level3(ua):
    import Hardest_Game_allLevels
    userAttempts = ua
    teleporter2 = (1070,540)

    pygame.mouse.set_pos(start)

    while True:
        Hardest_Game_allLevels.levelThreeDisplay(userAttempts)

        for event in pygame.event.get():

            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()

        x,y = pygame.mouse.get_pos()


        #Checking Start BOX
        if (x >= 0) and (x <= 199):
            if (y <= 390) or (y >= 690):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
        #Checking Start BOX
        
            #First Half of Track
        if (x >= 200) and (x <= 861):
            if (y <= 530) or (y >= 550):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
            #First Half of Track


            #Second Half of Track
        if (x >= 1059) and (x <= 1720):
            if (y <= 530) or (y >= 550):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
            #Second Half of Track

            #Purple Teleporter 1-2
        if (x >= 840) and (x <= 850):
            pygame.mouse.set_pos(teleporter2)
            #Purple Teleporter 1-2


        #Checking End Box
        if (x >= 1721) and (x <= 1920):
            if (y >= 390) and (y <= 690):
                pygame.mouse.set_pos(start)
                return 1, userAttempts
        #Checking End Box

    time.sleep(.1)
    pass

def level4(ua):
    import Hardest_Game_allLevels
    userAttempts = ua
    orangeTransporter = 840

    pygame.mouse.set_pos(start)
    timerStart = None
    orangeMoving = False
    #onPlatform = False

    while True:
        Hardest_Game_allLevels.levelFourDisplay(userAttempts,orangeTransporter)
        #print("OrangeTransporter:",orangeTransporter)
        for event in pygame.event.get():

            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()

        x,y = pygame.mouse.get_pos()

        if orangeMoving == False:
            #Checking Start BOX
            if (x >= 0) and (x <= 199):
                if (y <= 390) or (y >= 690):
                    pygame.mouse.set_pos(start)
                    userAttempts += 1
                    return 0, userAttempts
            #Checking Start BOX
        
                #First Half of Track
            if (x >= 200) and (x <= 861):
                if (y <= 530) or (y >= 550):
                    pygame.mouse.set_pos(start)
                    userAttempts += 1
                    return 0, userAttempts
                #First Half of Track


                #Second Half of Track
            if (x >= 1059) and (x <= 1720):
                if (y <= 530) or (y >= 550):
                    pygame.mouse.set_pos(start)
                    userAttempts += 1
                    return 0, userAttempts
                #Second Half of Track
            pass

            #Orange Transporter

                #Start Moving
        if (x >= orangeTransporter) and (x <= (orangeTransporter + 20)):
            if orangeMoving == False:
                print("Time started")
                timerStart = time.time()
            print("Platform moving")
            orangeMoving = True

                #Stop Moving
        if (orangeTransporter == 1060):
            orangeMoving = False

                #Check Outside of Platform
        if (orangeMoving == True) and ((x >= 861)  or (x <= 1059)):
            if (x <= (orangeTransporter - 5)) or (x >= (orangeTransporter + 20)):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
            if (y <= 530) or (y >= 550):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
                #Check Outside of Platform

        elif (orangeMoving == True) and (x < 861):
            if (y <= 530) or (y >= 550):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts

            #Orange Transporter



        #Checking End Box
        if (x >= 1721) and (x <= 1920):
            if (y >= 390) and (y <= 690):
                pygame.mouse.set_pos(start)
                return 1, userAttempts
        #Checking End Box

        timerEnd = time.time()
        
        if orangeMoving == True:
            #print("Timer:",int(timerEnd - timerStart))
            orangeTransporter = 840 + (int(timerEnd - timerStart) * 10)


            #I also need to allow people to get onto the transporter until the end of the blue
    time.sleep(.1)
    pass

def template(ua):
    import Hardest_Game_allLevels
    userAttempts = ua

    pygame.mouse.set_pos(start)

    while True:
        Hardest_Game_allLevels.levelTwoDisplay(userAttempts)

        for event in pygame.event.get():

            if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
                pygame.quit()
                exit()

        x,y = pygame.mouse.get_pos()


        #Checking Start BOX
        if (x >= 0) and (x <= 199):
            if (y <= 390) or (y >= 690):
                pygame.mouse.set_pos(start)
                userAttempts += 1
                return 0, userAttempts
        #Checking Start BOX
        pass

        #Checking End Box
        if (x >= 1721) and (x <= 1920):
            if (y >= 390) and (y <= 690):
                pygame.mouse.set_pos(start)
                return 1, userAttempts
        #Checking End Box

    time.sleep(.1)
    pass