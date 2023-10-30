import pygame
import casinoFront
import random
import time
from loginBack import updateValues

def casinoFloor(u,p,c,pos):
    #We need to start up the surface for the casino
    #We also need to keep track of the current position of the user in the
    #text doc along with the number of credits they have.
    #doing it this way is easier than having to re-open the doc to figure
    #it all out
    #Also U = Username  P = Password C = Credits  POS = Position
    casinoFront.startCasino()
    casinoFront.currentPosition = pos
    casinoFront.currentCredits = c

    while True:
        clickCheck(u,p)
        #casino front current bet doesnt need to be there but it is
        casinoFront.casinoBackground(u,c,casinoFront.currentBet)
        casinoFront.backgroundDrawn = True
        pygame.display.update()
    pass

def clickCheck(u,p):

    for event in pygame.event.get():
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
            pygame.quit()
            exit()

        #Like before this returns whether the mouse buttons were clicked
        clicked1,clicked2,clicked3 = pygame.mouse.get_pressed(num_buttons=3)
        if clicked1 == True:

            #Bet Buttons
            x,y = pygame.mouse.get_pos()
            if ((x >= 85) and (x <= 235)) and ((y >= 265)and(y <= 415)):
                casinoFront.currentBet = 60
                pass
            if ((x >= 85) and (x <= 235)) and ((y >= 465)and(y <= 615)):
                casinoFront.currentBet = 90
                pass
            if ((x >= 85) and (x <= 235)) and ((y >= 665)and(y <= 815)):
                casinoFront.currentBet = 120
                pass
            #Bet Buttons

            #Spin Button
            if ((x >= 1445) and (x <= 1755)) and ((y >= 710)and(y <= 1020)):
                if casinoFront.currentCredits < casinoFront.currentBet:
                    pass
                else:
                    casinoFront.spinShrink()
                    pygame.display.update()
                    
                    #Lowers the current credits and gets the new position from the updatedValues function
                    casinoFront.currentCredits = casinoFront.currentCredits - casinoFront.currentBet
                    newPos = updateValues(u,p,casinoFront.currentCredits,casinoFront.currentPosition)
                    casinoFront.currentPosition = newPos
                    spin(u,p)
            #Spin Button

    pass

def spin(u,p):

    casinoFront.boardReset()
    lion = 0
    sharingan = 0
    jersey = 0
    watermelon = 0
    winnings = 0
    loc = (0,0)
    won = False

    #Rolling of the odds here
    #Fuck ton of code that basically brings the animations in and out based on the rollings
    #of the rng inside of it. It picks 3 different images to roll throught for each square
    #It finally lands on the actual result(Third) and adds it to the tally above
    #The tally above reports to the winnings below. Every possibility is calculated in the
    #for loop which is the reason for so much code.

    #Random rolling
    for x in range(9):
        first = random.randint(1,10)
        second = random.randint(1,10)
        third = random.randint(1,10)

        if x == 0:
            loc = casinoFront.leftTop
        elif x==1:
            loc = casinoFront.leftMiddle
        elif x==2:
            loc = casinoFront.leftBottom
        elif x==3:
            loc = casinoFront.middleTop
        elif x==4:
            loc = casinoFront.middleMiddle
        elif x==5:
            loc = casinoFront.middleBottom
        elif x==6:
            loc = casinoFront.rightTop
        elif x==7:
            loc = casinoFront.rightMiddle
        elif x==8:
            loc = casinoFront.rightBottom

        #print("\n"+str(x)+":")

        #Rolling the DIE!
        if first == 1:
            #print("LION")
            casinoFront.lionIn(loc)
            if second == 1:
                casinoFront.lionOut(loc)
                #print("LION")
                casinoFront.lionIn(loc)
                if third == 1:
                    casinoFront.lionOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.lionOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.lionOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.lionOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 2) and (second <= 3):
                casinoFront.lionOut(loc)
                #print("Sharingan")
                casinoFront.sharinganIn(loc)
                if third == 1:
                    casinoFront.sharinganOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.sharinganOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.sharinganOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.sharinganOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 4) and (second <= 6):
                casinoFront.lionOut(loc)
                #print("Jersey")
                casinoFront.jerseyIn(loc)
                if third == 1:
                    casinoFront.jerseyOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.jerseyOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.jerseyOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.jerseyOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 7) and (second <= 10):
                casinoFront.lionOut(loc)
                #print("Watermelon")
                casinoFront.watermelonIn(loc)
                if third == 1:
                    casinoFront.watermelonOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion += 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.watermelonOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan += 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.watermelonOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey += 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.watermelonOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon+=1
                    pass
                pass
            pass
        elif (first >= 2) and (first <= 3):
            #print("Sharingan")
            casinoFront.sharinganIn(loc)
            if second == 1:
                casinoFront.sharinganOut(loc)
                #print("LION")
                casinoFront.lionIn(loc)
                if third == 1:
                    casinoFront.lionOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.lionOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.lionOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.lionOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 2) and (second <= 3):
                casinoFront.sharinganOut(loc)
                #print("Sharingan")
                casinoFront.sharinganIn(loc)
                if third == 1:
                    casinoFront.sharinganOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.sharinganOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.sharinganOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.sharinganOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 4) and (second <= 6):
                casinoFront.sharinganOut(loc)
                #print("Jersey")
                casinoFront.jerseyIn(loc)
                if third == 1:
                    casinoFront.jerseyOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.jerseyOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.jerseyOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.jerseyOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 7) and (second <= 10):
                casinoFront.sharinganOut(loc)
                #print("Watermelon")
                casinoFront.watermelonIn(loc)
                if third == 1:
                    casinoFront.watermelonOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion += 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.watermelonOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan += 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.watermelonOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey += 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.watermelonOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon+=1
                    pass
                pass
            pass
        elif (first >= 4) and (first <= 6):
            #print("Jersey")
            casinoFront.jerseyIn(loc)
            if second == 1:
                casinoFront.jerseyOut(loc)
                #print("LION")
                casinoFront.lionIn(loc)
                if third == 1:
                    casinoFront.lionOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.lionOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.lionOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.lionOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 2) and (second <= 3):
                casinoFront.jerseyOut(loc)
                #print("Sharingan")
                casinoFront.sharinganIn(loc)
                if third == 1:
                    casinoFront.sharinganOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.sharinganOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.sharinganOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.sharinganOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 4) and (second <= 6):
                casinoFront.jerseyOut(loc)
                #print("Jersey")
                casinoFront.jerseyIn(loc)
                if third == 1:
                    casinoFront.jerseyOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.jerseyOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.jerseyOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.jerseyOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 7) and (second <= 10):
                casinoFront.jerseyOut(loc)
                #print("Watermelon")
                casinoFront.watermelonIn(loc)
                if third == 1:
                    casinoFront.watermelonOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion += 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.watermelonOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan += 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.watermelonOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey += 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.watermelonOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon+=1
                    pass
                pass
            pass
        elif (first >= 7) and (first <= 10):
            #print("Watermelon")
            casinoFront.watermelonIn(loc)
            if second == 1:
                casinoFront.watermelonOut(loc)
                #print("LION")
                casinoFront.lionIn(loc)
                if third == 1:
                    casinoFront.lionOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.lionOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.lionOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.lionOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 2) and (second <= 3):
                casinoFront.watermelonOut(loc)
                #print("Sharingan")
                casinoFront.sharinganIn(loc)
                if third == 1:
                    casinoFront.sharinganOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.sharinganOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.sharinganOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.sharinganOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 4) and (second <= 6):
                casinoFront.watermelonOut(loc)
                #print("Jersey")
                casinoFront.jerseyIn(loc)
                if third == 1:
                    casinoFront.jerseyOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion = lion + 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.jerseyOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan = sharingan + 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.jerseyOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey = jersey + 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.jerseyOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon = watermelon + 1
                    pass
                pass
            elif (second >= 7) and (second <= 10):
                casinoFront.watermelonOut(loc)
                #print("Watermelon")
                casinoFront.watermelonIn(loc)
                if third == 1:
                    casinoFront.watermelonOut(loc)
                    #print("LION")
                    casinoFront.lionIn(loc)
                    lion += 1
                    pass
                elif (third >= 2) and (third <= 3):
                    casinoFront.watermelonOut(loc)
                    #print("Sharingan")
                    casinoFront.sharinganIn(loc)
                    sharingan += 1
                    pass
                elif (third >= 4) and (third <= 6):
                    casinoFront.watermelonOut(loc)
                    #print("Jersey")
                    casinoFront.jerseyIn(loc)
                    jersey += 1
                    pass
                elif (third >= 7) and (third <= 10):
                    casinoFront.watermelonOut(loc)
                    #print("Watermelon")
                    casinoFront.watermelonIn(loc)
                    watermelon+=1
                    pass
                pass
            pass
        #Rolling the DIE!
        pass
    #Random rolling

    casinoFront.spinRedraw()

    #Winnings and rates are demonstrated in the spin Notes text file
    #It is also reflected here in the winnings handling
    #All of the winnings get added up and added to your credits if 
    #you win. If not basically nothing happens
    #Won = False doesnt need to be there, but I dont want to touch lol
    #I will probably remove it later, but for now it is just a nice touch
    #Winnings are based on your bet multiplied by the percent we want you
    #to get back for landing on it.

    #Winnings Handling
    if lion >= 3:
        won = True
        winnings += int(casinoFront.currentBet * 10.85)
        #print("WINNINGS: LION")
    if sharingan >= 4:
        winnings += int(casinoFront.currentBet * 1.75)
        won = True
        #print("WINNIGNS: SHARINGAN")
    if jersey >= 3:
        winnings += int(casinoFront.currentBet * .75)
        won = True
        #print("WINNINGS: JERSEY")
    if watermelon >= 4:
        winnings += int(casinoFront.currentBet * .55)
        won = True
        #print("WINNINGS: WATERMELON")
    if won == False:
        #print("WINNINGS: NO WINNINGS")
        pass
    if won == True:
        casinoFront.creditGain(winnings)
        casinoFront.currentCredits += winnings
        newPos = updateValues(u,p,casinoFront.currentCredits,casinoFront.currentPosition)
        casinoFront.currentPosition = newPos
    won = False
    #Winnings Handling

    pass