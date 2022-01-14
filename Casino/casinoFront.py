import pygame
import time

pygame.init()
pygame.font.init()

#Variables
surface = pygame.display.set_mode((1920,1080)) 
pygame.display.set_caption("Legendary Casino")
colors = {"dark red":(139,0,0),"forest green":(34,139,34), "roman silver": (131,137,150),"white": (255,255,255), "black": (0,0,0),"dark green":(0,100,0),"firebrick":(178,34,34),"golden rod":(218,165,32),"blue violet":(138,43,226),"dark violet":(148,0,211),"royal blue":(65,105,225),"maroon":(128,0,0)}
font = {"freesansboldXXXL" : pygame.font.Font('freesansbold.ttf', 110),"freesansboldXXL" : pygame.font.Font('freesansbold.ttf', 90),"freesansboldXL" : pygame.font.Font('freesansbold.ttf', 80),"freesansboldL" : pygame.font.Font('freesansbold.ttf', 60),"freesansboldLRG" : pygame.font.Font('freesansbold.ttf', 40), "freesansboldMED" : pygame.font.Font('freesansbold.ttf', 30), "freesansboldXXS" : pygame.font.Font('freesansbold.ttf', 15)}
currentPosition = None
currentCredits = None
backgroundDrawn = False
currentBet = 60
leftTop = (330,70)
leftMiddle = (330,385)
leftBottom = (330,705)
middleTop = (645,70)
middleMiddle = (645,385)
middleBottom = (645,705)
rightTop = (965,70)
rightMiddle = (965,385)
rightBottom = (965,705)
#Variables


def startCasino():
    surface.fill(colors["blue violet"])
    pygame.display.init()

    #Jackpot corners
    pygame.draw.rect(surface,colors["black"],[1375,60,450,610])
    pygame.draw.rect(surface,colors["maroon"],[1380,66,440,599])
    pygame.draw.line(surface,colors["black"],(1377,190),(1505,60),7)
    pygame.draw.line(surface,colors["black"],(1695,668),(1822,540),7)
    pygame.draw.line(surface,colors["blue violet"],(1313,187),(1450,45),125)
    pygame.draw.line(surface,colors["blue violet"],(1762,669),(1890,540),130)
    #Jackpot corners

    pygame.draw.rect(surface,colors["black"],[320,60,960,960])
    pygame.display.update()
    pass

def casinoBackground(username,credits,bet = 60):
    if backgroundDrawn == False:


        #main board
            #Horizontals
        pygame.draw.rect(surface,colors["dark violet"], [320,60,960,10])  #Top Band
        pygame.draw.rect(surface,colors["dark violet"], [320,375,960,10]) #First Hor
        pygame.draw.rect(surface,colors["dark violet"], [320,695,960,10]) #Second Hor
        pygame.draw.rect(surface,colors["dark violet"], [320,1010,960,10])#Bottom Band
            #Horizontals

            #Verticals
        pygame.draw.rect(surface,colors["dark violet"], [320,60,10,960]) #Left Band
        pygame.draw.rect(surface,colors["dark violet"], [635,60,10,960]) #First Vert
        pygame.draw.rect(surface,colors["dark violet"], [955,60,10,960]) #Second Vert
        pygame.draw.rect(surface,colors["dark violet"], [1270,60,10,960])#Right Band
            #Verticals
        #main board
    


        #spin button
        pygame.draw.rect(surface,colors["blue violet"],[1445,710,310,310])
        pygame.draw.circle(surface,colors["firebrick"],(1600,865),155)
        spinText = font["freesansboldXXL"].render("SPIN!", True, colors["white"])
        spinRect = spinText.get_rect()
        spinRect.center = (1600,865)
        surface.blit(spinText,spinRect)
        #spin button



        #Username Display
        pygame.draw.rect(surface,colors["black"],[1445,1035,310,30])
        userText = font["freesansboldMED"].render(username.upper(), True, colors["white"])
        userRect = userText.get_rect()
        userRect.center = (1600,1052)
        surface.blit(userText,userRect)
        #Username Display

        #JackPot

        #1375 + 450 = 1825    60 + 610 = 670

        percent = font["freesansboldL"].render("Jackpots", True, colors["golden rod"])
        percentRect = percent.get_rect()
        percentRect.center = (1680,110)
        percentb = font["freesansboldL"].render("Jackpots", True, colors["black"])
        percentbRect = percentb.get_rect()
        percentbRect.center = (1676,114)

        surface.blit(percentb,percentbRect)
        surface.blit(percent,percentRect)
      

            #Lion
        lionImage3 = pygame.image.load("images/lion3.png")
        lionW = font["freesansboldL"].render("3X", True, colors["golden rod"])
        lionWRect = lionW.get_rect()
        lionWRect.center = (1420,220)
        lionWB = font["freesansboldL"].render("3X", True, colors["black"])
        lionWBRect = lionWB.get_rect()
        lionWBRect.center = (1416,224)
        pygame.draw.rect(surface,colors["black"],[1591,219,30,10])
        pygame.draw.rect(surface,colors["golden rod"],[1595,215,30,10])
        percent = font["freesansboldL"].render("1085%", True, colors["golden rod"])
        percentRect = percent.get_rect()
        percentRect.center = (1720,220)
        percentb = font["freesansboldL"].render("1085%", True, colors["black"])
        percentbRect = percentb.get_rect()
        percentbRect.center = (1716,224)

        surface.blit(percentb,percentbRect)
        surface.blit(percent,percentRect)
        surface.blit(lionImage3,(1370,75))
        surface.blit(lionWB,lionWBRect)
        surface.blit(lionW,lionWRect)
            #Lion

            #Sharingan
        sharinganImage3 = pygame.image.load("images/sharingan3.png")
        sharinganW = font["freesansboldL"].render("4X", True, colors["golden rod"])
        sharinganWRect = sharinganW.get_rect()
        sharinganWRect.center = (1420,345)
        sharinganWB = font["freesansboldL"].render("4X", True, colors["black"])
        sharinganWBRect = sharinganWB.get_rect()
        sharinganWBRect.center = (1416,349)
        pygame.draw.rect(surface,colors["black"],[1591,344,30,10])
        pygame.draw.rect(surface,colors["golden rod"],[1595,340,30,10])
        percent = font["freesansboldL"].render("125%", True, colors["golden rod"])
        percentRect = percent.get_rect()
        percentRect.center = (1700,345)
        percentb = font["freesansboldL"].render("125%", True, colors["black"])
        percentbRect = percentb.get_rect()
        percentbRect.center = (1696,349)

        surface.blit(percentb,percentbRect)
        surface.blit(percent,percentRect)
        surface.blit(sharinganImage3,(1370,225))
        surface.blit(sharinganWB,sharinganWBRect)
        surface.blit(sharinganW,sharinganWRect)
            #Sharingan

            #Jersey
        jerseyImage3 = pygame.image.load("images/jersey3.png")
        jerseyW = font["freesansboldL"].render("3X", True, colors["golden rod"])
        jerseyWRect = jerseyW.get_rect()
        jerseyWRect.center = (1420,465)
        jerseyWB = font["freesansboldL"].render("3X", True, colors["black"])
        jerseyWBRect = jerseyWB.get_rect()
        jerseyWBRect.center = (1416,469)
        pygame.draw.rect(surface,colors["black"],[1591,459,30,10])
        pygame.draw.rect(surface,colors["golden rod"],[1595,455,30,10])
        percent = font["freesansboldL"].render("75%", True, colors["golden rod"])
        percentRect = percent.get_rect()
        percentRect.center = (1685,465)
        percentb = font["freesansboldL"].render("75%", True, colors["black"])
        percentbRect = percentb.get_rect()
        percentbRect.center = (1681,469)

        surface.blit(percentb,percentbRect)
        surface.blit(percent,percentRect)
        surface.blit(jerseyImage3,(1370,305))
        surface.blit(jerseyWB,jerseyWBRect)
        surface.blit(jerseyW,jerseyWRect)
            #Jersey

            #Watermelon
        watermelonImage3 = pygame.image.load("images/watermelon3.png")
        watermelonW = font["freesansboldL"].render("4X", True, colors["golden rod"])
        watermelonWRect = watermelonW.get_rect()
        watermelonWRect.center = (1420,585)
        watermelonWB = font["freesansboldL"].render("4X", True, colors["black"])
        watermelonWBRect = watermelonWB.get_rect()
        watermelonWBRect.center = (1416,589)
        pygame.draw.rect(surface,colors["black"],[1591,583,30,10])
        pygame.draw.rect(surface,colors["golden rod"],[1595,579,30,10])
        percent = font["freesansboldL"].render("55%", True, colors["golden rod"])
        percentRect = percent.get_rect()
        percentRect.center = (1690,585)
        percentb = font["freesansboldL"].render("55%", True, colors["black"])
        percentbRect = percentb.get_rect()
        percentbRect.center = (1686,589)

        surface.blit(percentb,percentbRect)
        surface.blit(percent,percentRect)        
        surface.blit(watermelonImage3,(1370,435))
        surface.blit(watermelonWB,watermelonWBRect)
        surface.blit(watermelonW,watermelonWRect)
            #Watermelon
    
        #JackPot

    #Credit display
    pygame.draw.rect(surface,colors["black"],[50,960,220,110])
    pygame.draw.rect(surface,colors["dark violet"],[100,1014,120,6])

    wordCredits = font["freesansboldLRG"].render("CREDITS", True, colors["white"])
    wordCreditsRect = wordCredits.get_rect()
    wordCreditsRect.center = (160,990)

    creditsDisplay = font["freesansboldLRG"].render(str(currentCredits), True, colors["white"])
    creditsDisplayRect = creditsDisplay.get_rect()
    creditsDisplayRect.center = (160,1050)

    surface.blit(wordCredits,wordCreditsRect)
    surface.blit(creditsDisplay,creditsDisplayRect)
    #Credit display

    betDisplay(bet)
    pass

def spinRedraw():
    pygame.draw.rect(surface,colors["blue violet"],[1445,710,310,310])
    pygame.draw.circle(surface,colors["firebrick"],(1600,865),155)
    spinText = font["freesansboldXXL"].render("SPIN!", True, colors["white"])
    spinRect = spinText.get_rect()
    spinRect.center = (1600,865)
    surface.blit(spinText,spinRect)

def boardReset():
    pygame.draw.rect(surface,colors["black"],[320,60,960,960])

    #main board
        #Horizontals
    pygame.draw.rect(surface,colors["dark violet"], [320,60,960,10])  #Top Band
    pygame.draw.rect(surface,colors["dark violet"], [320,375,960,10]) #First Hor
    pygame.draw.rect(surface,colors["dark violet"], [320,695,960,10]) #Second Hor
    pygame.draw.rect(surface,colors["dark violet"], [320,1010,960,10])#Bottom Band
        #Horizontals

        #Verticals
    pygame.draw.rect(surface,colors["dark violet"], [320,60,10,960]) #Left Band
    pygame.draw.rect(surface,colors["dark violet"], [635,60,10,960]) #First Vert
    pygame.draw.rect(surface,colors["dark violet"], [955,60,10,960]) #Second Vert
    pygame.draw.rect(surface,colors["dark violet"], [1270,60,10,960])#Right Band
        #Verticals
    #main board

    #Credit gain reset
    pygame.draw.rect(surface,colors["blue violet"],[40,900,200,60])
    #Credit gain reset
    pass

def betDisplay(bet):
    #Will display the bets
    #The idea is that they get a size increase when clicked on to
    #indicate that they are the bet that is active to the user
    #60c is the default bet set in the casinoBackground()

    #60 bet
    pygame.draw.rect(surface,colors["blue violet"],[60,240,200,200])
    pygame.draw.rect(surface,colors["black"],[80,260,160,160])
    if currentCredits < 60:
        pygame.draw.rect(surface,colors["roman silver"], [85,265,150,150])
    else:
        pygame.draw.rect(surface,colors["royal blue"], [85,265,150,150])
    sixty = font["freesansboldXL"].render("60", True, colors["dark violet"])
    sixtyRect = sixty.get_rect()
    sixtyRect.center = (160,340)
    sixtyt = font["freesansboldXL"].render("60", True, colors["black"])
    sixtyRectt = sixtyt.get_rect()
    sixtyRectt.center = (156,344)
    surface.blit(sixtyt,sixtyRectt)
    surface.blit(sixty,sixtyRect)
    #60 bet

    #90 bet
    pygame.draw.rect(surface,colors["blue violet"],[60,440,200,200])
    pygame.draw.rect(surface,colors["black"],[80,460,160,160])
    if currentCredits < 90:
        pygame.draw.rect(surface,colors["roman silver"], [85,465,150,150])
    else:
        pygame.draw.rect(surface,colors["royal blue"], [85,465,150,150])
    ninety = font["freesansboldXL"].render("90", True, colors["dark violet"])
    ninetyRect = ninety.get_rect()
    ninetyRect.center = (160,540)
    ninetyt = font["freesansboldXL"].render("90", True, colors["black"])
    ninetyRectt = ninetyt.get_rect()
    ninetyRectt.center = (156,544)
    surface.blit(ninetyt,ninetyRectt)
    surface.blit(ninety,ninetyRect)
    #90 bet

    #120 bet
    pygame.draw.rect(surface,colors["blue violet"],[60,640,200,200])
    pygame.draw.rect(surface,colors["black"],[80,660,160,160])
    if currentCredits < 120:
        pygame.draw.rect(surface,colors["roman silver"], [85,665,150,150])
    else:
        pygame.draw.rect(surface,colors["royal blue"], [85,665,150,150])
    hund = font["freesansboldXL"].render("120", True, colors["dark violet"])
    hundRect = hund.get_rect()
    hundRect.center = (160,740)
    hundt = font["freesansboldXL"].render("120", True, colors["black"])
    hundRectt = hundt.get_rect()
    hundRectt.center = (156,744)
    surface.blit(hundt,hundRectt)
    surface.blit(hund,hundRect)
    #120 bet

    if bet == 60:
        #80,260,160,160
        pygame.draw.rect(surface,colors["black"],[60,240,200,200])
        if currentCredits < 60:
            pygame.draw.rect(surface,colors["roman silver"], [65,245,190,190])
        else:
            pygame.draw.rect(surface,colors["royal blue"], [65,245,190,190])
        sixty = font["freesansboldXXXL"].render("60", True, colors["dark violet"])
        sixtyRect = sixty.get_rect()
        sixtyRect.center = (160,340)
        sixtyt = font["freesansboldXXXL"].render("60", True, colors["black"])
        sixtyRectt = sixtyt.get_rect()
        sixtyRectt.center = (156,344)
        surface.blit(sixtyt,sixtyRectt)
        surface.blit(sixty,sixtyRect)
        pass

    elif bet == 90:
        pygame.draw.rect(surface,colors["black"],[60,440,200,200])
        if currentCredits < 90:
            pygame.draw.rect(surface,colors["roman silver"], [65,445,190,190])
        else:
            pygame.draw.rect(surface,colors["royal blue"], [65,445,190,190])
        ninety = font["freesansboldXXXL"].render("90", True, colors["dark violet"])
        ninetyRect = ninety.get_rect()
        ninetyRect.center = (160,540)
        ninetyt = font["freesansboldXXXL"].render("90", True, colors["black"])
        ninetyRectt = ninetyt.get_rect()
        ninetyRectt.center = (156,544)
        surface.blit(ninetyt,ninetyRectt)
        surface.blit(ninety,ninetyRect)
        pass
    elif bet == 120:
        pygame.draw.rect(surface,colors["black"],[60,640,200,200])
        if currentCredits < 120:
            pygame.draw.rect(surface,colors["roman silver"], [65,645,190,190])
        else:
            pygame.draw.rect(surface,colors["royal blue"], [65,645,190,190])
        hund = font["freesansboldXXXL"].render("120", True, colors["dark violet"])
        hundRect = hund.get_rect()
        hundRect.center = (160,740)
        hundt = font["freesansboldXXXL"].render("120", True, colors["black"])
        hundRectt = hundt.get_rect()
        hundRectt.center = (156,744)
        surface.blit(hundt,hundRectt)
        surface.blit(hund,hundRect)
        pass
    else:
        #print("something is broken lmfao")
        pass

    pass

def creditGain(inc):
    text = "+"+ str(inc)
    creditsinc = font["freesansboldLRG"].render(text, True, colors["golden rod"])
    creditsincRect = creditsinc.get_rect()
    creditsincRect.center = (160,940)
    creditsincb = font["freesansboldLRG"].render(text, True, colors["black"])
    creditsincbRect = creditsincb.get_rect()
    creditsincbRect.center = (159,941)


    surface.blit(creditsincb,creditsincbRect)
    surface.blit(creditsinc,creditsincRect)
    pass

def spinShrink():
    #spin button
    #((x >= 1445) and (x <= 1755)) and ((y >= 710)and(y <= 1020))
    pygame.draw.rect(surface,colors["blue violet"],[1445,710,310,310])
    pygame.draw.circle(surface,colors["dark red"],(1600,865),135)
    #1445,710
    spinText = font["freesansboldXL"].render("SPIN!", True, colors["white"])
    spinRect = spinText.get_rect()
    spinRect.center = (1600,865)
    surface.blit(spinText,spinRect)
    #return False
    #print("End of shrink spin")
    #print("Spin:",spin)
    #spin button
    pass

#Animations
def lionIn(loc):
    lionImage1 = pygame.image.load("images/lion1.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(lionImage1,loc)
    pygame.display.update()

    time.sleep(0.05)

    lionImage2 = pygame.image.load("images/lion2.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(lionImage2,loc)
    pygame.display.update()

    time.sleep(0.05)

    lionImage3 = pygame.image.load("images/lion3.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(lionImage3,loc)
    pygame.display.update()
def lionOut(loc):

    time.sleep(0.05)

    lionImage4 = pygame.image.load("images/lion4.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(lionImage4,loc)
    pygame.display.update()

    time.sleep(0.05)

    lionImage5 = pygame.image.load("images/lion5.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(lionImage5,loc)
    pygame.display.update()

    time.sleep(0.05)
    pass

def watermelonIn(loc):

    watermelonImage1 = pygame.image.load("images/watermelon1.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(watermelonImage1,loc)
    pygame.display.update()

    time.sleep(0.05)

    watermelonImage2 = pygame.image.load("images/watermelon2.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(watermelonImage2,loc)
    pygame.display.update()

    time.sleep(0.05)

    watermelonImage3 = pygame.image.load("images/watermelon3.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(watermelonImage3,loc)
    pygame.display.update()
def watermelonOut(loc):

    time.sleep(0.05)

    watermelonImage4 = pygame.image.load("images/watermelon4.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(watermelonImage4,loc)
    pygame.display.update()

    time.sleep(0.05)

    watermelonImage5 = pygame.image.load("images/watermelon5.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(watermelonImage5,loc)
    pygame.display.update()

    time.sleep(0.05)
    pass

def sharinganIn(loc):

    sharinganImage1 = pygame.image.load("images/sharingan1.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(sharinganImage1,loc)
    pygame.display.update()

    time.sleep(0.05)

    sharinganImage2 = pygame.image.load("images/sharingan2.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(sharinganImage2,loc)
    pygame.display.update()

    time.sleep(0.05)

    sharinganImage3 = pygame.image.load("images/sharingan3.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(sharinganImage3,loc)
    pygame.display.update()
def sharinganOut(loc):

    time.sleep(0.05)

    sharinganImage4 = pygame.image.load("images/sharingan4.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(sharinganImage4,loc)
    pygame.display.update()

    time.sleep(0.05)

    sharinganImage5 = pygame.image.load("images/sharingan5.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(sharinganImage5,loc)
    pygame.display.update()

    time.sleep(0.05)

    pass

def jerseyIn(loc):

    jerseyImage1 = pygame.image.load("images/jersey1.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(jerseyImage1,loc)
    pygame.display.update()

    time.sleep(0.05)

    jerseyImage2 = pygame.image.load("images/jersey2.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(jerseyImage2,loc)
    pygame.display.update()

    time.sleep(0.05)

    jerseyImage3 = pygame.image.load("images/jersey3.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(jerseyImage3,loc)
    pygame.display.update()
def jerseyOut(loc):

    time.sleep(0.05)

    jerseyImage4 = pygame.image.load("images/jersey4.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(jerseyImage4,loc)
    pygame.display.update()

    time.sleep(0.05)

    jerseyImage5 = pygame.image.load("images/jersey5.png")
    pygame.draw.rect(surface,colors["black"],[(loc),(305,305)])
    surface.blit(jerseyImage5,loc)
    pygame.display.update()

    time.sleep(0.05)
    pass
#Animations