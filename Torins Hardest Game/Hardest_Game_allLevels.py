import pygame
#All of the levels

    #Variables
pygame.init()
pygame.display.init()
pygame.font.init()
#surface = pygame.display.set_mode((1920,1080))
#pygame.display.set_caption("Torins Hardest Game")
colors = {"forest green":(34,139,34), "white": (255,255,255), "black": (0,0,0),"dark green":(0,100,0),"firebrick":(178,34,34),"golden rod":(218,165,32), "sky blue":(135, 206, 235), "orchid":(218,112,214), "chocolate":(210,105,30)}
font = {"freesansboldXXL" : pygame.font.Font('freesansbold.ttf', 160),"freesansboldLRG" : pygame.font.Font('freesansbold.ttf', 40), "freesansboldSML" : pygame.font.Font('freesansbold.ttf', 35), "freesansboldXXS" : pygame.font.Font('freesansbold.ttf', 15)}
fullscreen = False
    #Variables


pygame.display.toggle_fullscreen()


def levelOneDisplay(a):

    surface = pygame.display.set_mode((1920,1080))
    pygame.display.set_caption("Torins Hardest Game")
    surface.fill(colors["firebrick"])

        #Starting Platform | End Platform
    pygame.draw.rect(surface,colors["black"],   ((0,388),(202,306)))
    pygame.draw.rect(surface,colors["black"],   ((1718,388),(202,306)))
    pygame.draw.rect(surface,colors["sky blue"],((0,390),(200,300)))
    pygame.draw.rect(surface,colors["sky blue"],((1720,390),(200,300)))
        #Starting Platform | End Platform

        #Obstacles
            #Line to Run Across
    pygame.draw.rect(surface,colors["black"],   ((200,528),(1520,26)))
    pygame.draw.rect(surface,colors["sky blue"],((200,530),(1520,20)))
            #Line to Run Across
        #Obstacles


        #Level Display - Top Left
    level = font["freesansboldSML"].render(("Level 1"), True, colors["white"])
    levelRect = level.get_rect()
    levelRect.center = (200, 50)
    levelO = font["freesansboldSML"].render(("Level 1"), True, colors["black"])
    levelORect = levelO.get_rect()
    levelORect.center = (198,52)
    surface.blit(levelO, levelORect)
    surface.blit(level, levelRect)
        #Level Display - Top Left


        #Attempts - Top Right
    attempts = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["white"])
    attemptsRect = attempts.get_rect()
    attemptsRect.center = (1720, 50)
    attemptsO = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["black"])
    attemptsORect = attemptsO.get_rect()
    attemptsORect.center = (1718,52)
    surface.blit(attemptsO, attemptsORect)
    surface.blit(attempts, attemptsRect)
        #Attempts - Top Right

    pygame.display.update()
    pass

def levelTwoDisplay(a):

    surface = pygame.display.set_mode((1920,1080))
    pygame.display.set_caption("Torins Hardest Game")
    surface.fill(colors["firebrick"])

        #Starting Platform | End Platform
    pygame.draw.rect(surface,colors["black"],   ((0,388),(202,306)))
    pygame.draw.rect(surface,colors["black"],   ((1718,388),(202,306)))
    pygame.draw.rect(surface,colors["sky blue"],((0,390),(200,300)))
    pygame.draw.rect(surface,colors["sky blue"],((1720,390),(200,300)))
        #Starting Platform | End Platform


        #Obstacles

            #Line to Run Across
    pygame.draw.rect(surface,colors["black"],   ((200,528),(1520,26)))
    pygame.draw.rect(surface,colors["sky blue"],((200,530),(1520,20)))
            #Line to Run Across

            #Invisibility Pad
    pygame.draw.rect(surface,colors["black"],   ((1419,530),(22,20)))
    pygame.draw.rect(surface,colors["forest green"],((1420,530),(20,20)))
            #Invisibility Pad

        #Obstacles


        #Levels Display - Top Left
    level = font["freesansboldSML"].render(("Level 2"), True, colors["white"])
    levelRect = level.get_rect()
    levelRect.center = (200, 50)
    levelO = font["freesansboldSML"].render(("Level 2"), True, colors["black"])
    levelORect = levelO.get_rect()
    levelORect.center = (198,52)
    surface.blit(levelO, levelORect)
    surface.blit(level, levelRect)
        #Levels Display - Top Left


        #Attempts - Top Right
    attempts = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["white"])
    attemptsRect = attempts.get_rect()
    attemptsRect.center = (1720, 50)
    attemptsO = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["black"])
    attemptsORect = attemptsO.get_rect()
    attemptsORect.center = (1718,52)
    surface.blit(attemptsO, attemptsORect)
    surface.blit(attempts, attemptsRect)
        #Attempts - Top Right

    pygame.display.update()
    pass

def levelThreeDisplay(a):
    surface = pygame.display.set_mode((1920,1080))
    pygame.display.set_caption("Torins Hardest Game")
    surface.fill(colors["firebrick"])

        #Starting Platform | End Platform
    pygame.draw.rect(surface,colors["black"],   ((0,388),(202,306)))
    pygame.draw.rect(surface,colors["black"],   ((1718,388),(202,306)))
    pygame.draw.rect(surface,colors["sky blue"],((0,390),(200,300)))
    pygame.draw.rect(surface,colors["sky blue"],((1720,390),(200,300)))
        #Starting Platform | End Platform


        #Obstacles
            #Left and Right Blue Lines
    pygame.draw.rect(surface,colors["black"],   ((200,528),(662,26)))
    pygame.draw.rect(surface,colors["sky blue"],((200,530),(660,20)))
    pygame.draw.rect(surface,colors["black"],   ((1058,528),(662,26)))
    pygame.draw.rect(surface,colors["sky blue"],((1060,530),(660,20)))
            #Left and Right Blue Lines

            #Purple Teleporter
    pygame.draw.rect(surface,colors["black"],   ((839,530),(22,20)))
    pygame.draw.rect(surface,colors["orchid"],  ((840,530),(20,20)))

    pygame.draw.rect(surface,colors["black"],   ((1059,530),(22,20)))
    pygame.draw.rect(surface,colors["orchid"],  ((1060,530),(20,20)))
            #Purple Teleporter
        #Obstacles


        #Levels Display - Top Left
    level = font["freesansboldSML"].render(("Level 3"), True, colors["white"])
    levelRect = level.get_rect()
    levelRect.center = (200, 50)
    levelO = font["freesansboldSML"].render(("Level 3"), True, colors["black"])
    levelORect = levelO.get_rect()
    levelORect.center = (198,52)
    surface.blit(levelO, levelORect)
    surface.blit(level, levelRect)
        #Levels Display - Top Left


        #Attempts - Top Right
    attempts = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["white"])
    attemptsRect = attempts.get_rect()
    attemptsRect.center = (1720, 50)
    attemptsO = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["black"])
    attemptsORect = attemptsO.get_rect()
    attemptsORect.center = (1718,52)
    surface.blit(attemptsO, attemptsORect)
    surface.blit(attempts, attemptsRect)
        #Attempts - Top Right

    pygame.display.update()
    pass

def levelFourDisplay(a,ox):

    surface = pygame.display.set_mode((1920,1080))
    pygame.display.set_caption("Torins Hardest Game")
    surface.fill(colors["firebrick"])

        #Starting Platform | End Platform
    pygame.draw.rect(surface,colors["black"],   ((0,388),(202,306)))
    pygame.draw.rect(surface,colors["black"],   ((1718,388),(202,306)))
    pygame.draw.rect(surface,colors["sky blue"],((0,390),(200,300)))
    pygame.draw.rect(surface,colors["sky blue"],((1720,390),(200,300)))
        #Starting Platform | End Platform


        #Obstacles
            #Left and Right Blue Lines
    pygame.draw.rect(surface,colors["black"],   ((200,528),(662,26)))
    pygame.draw.rect(surface,colors["sky blue"],((200,530),(660,20)))
    pygame.draw.rect(surface,colors["black"],   ((1058,528),(662,26)))
    pygame.draw.rect(surface,colors["sky blue"],((1060,530),(660,20)))
            #Left and Right Blue Lines

            #Orange Transporter
    pygame.draw.rect(surface,colors["black"],   (((ox-1),530),(22,20)))
    pygame.draw.rect(surface,colors["golden rod"],  ((ox,530),(20,20)))

    #pygame.draw.rect(surface,colors["black"],   ((1059,530),(22,20)))
    #pygame.draw.rect(surface,colors["golden rod"],  ((1060,530),(20,20)))
            #Orange Transporter
        #Obstacles


        #Levels Display - Top Left
    level = font["freesansboldSML"].render(("Level 4"), True, colors["white"])
    levelRect = level.get_rect()
    levelRect.center = (200, 50)
    levelO = font["freesansboldSML"].render(("Level 4"), True, colors["black"])
    levelORect = levelO.get_rect()
    levelORect.center = (198,52)
    surface.blit(levelO, levelORect)
    surface.blit(level, levelRect)
        #Levels Display - Top Left


        #Attempts - Top Right
    attempts = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["white"])
    attemptsRect = attempts.get_rect()
    attemptsRect.center = (1720, 50)
    attemptsO = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["black"])
    attemptsORect = attemptsO.get_rect()
    attemptsORect.center = (1718,52)
    surface.blit(attemptsO, attemptsORect)
    surface.blit(attempts, attemptsRect)
        #Attempts - Top Right

    pygame.display.update()
    pass

def template(a):
    surface = pygame.display.set_mode((1920,1080))
    pygame.display.set_caption("Torins Hardest Game")
    surface.fill(colors["firebrick"])

        #Starting Platform | End Platform
    pygame.draw.rect(surface,colors["black"],   ((0,388),(202,306)))
    pygame.draw.rect(surface,colors["black"],   ((1718,388),(202,306)))
    pygame.draw.rect(surface,colors["sky blue"],((0,390),(200,300)))
    pygame.draw.rect(surface,colors["sky blue"],((1720,390),(200,300)))
        #Starting Platform | End Platform


        #Obstacles
    
        #Obstacles


        #Levels Display - Top Left
    level = font["freesansboldSML"].render(("Level 2"), True, colors["white"])
    levelRect = level.get_rect()
    levelRect.center = (200, 50)
    levelO = font["freesansboldSML"].render(("Level 2"), True, colors["black"])
    levelORect = levelO.get_rect()
    levelORect.center = (198,52)
    surface.blit(levelO, levelORect)
    surface.blit(level, levelRect)
        #Levels Display - Top Left


        #Attempts - Top Right
    attempts = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["white"])
    attemptsRect = attempts.get_rect()
    attemptsRect.center = (1720, 50)
    attemptsO = font["freesansboldSML"].render(("Attempts: " + str(a)), True, colors["black"])
    attemptsORect = attemptsO.get_rect()
    attemptsORect.center = (1718,52)
    surface.blit(attemptsO, attemptsORect)
    surface.blit(attempts, attemptsRect)
        #Attempts - Top Right

    pygame.display.update()
    pass