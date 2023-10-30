#import Hardest_Game_Login_Back
#import Hardest_Game_Login_Front
import Hardest_Game_File_Handler
import Hardest_Game_Levels
import time
import pygame

uattempts = 0
success = 0
surface = pygame.display.set_mode((1920,1080))
pygame.display.set_caption("Torins Hardest Game")
surface.fill((178,34,34))

while success == 0:
    success,uattempts = Hardest_Game_Levels.level4(uattempts)
#print(Hardest_Game_File_Handler.timeComparison(8,Hardest_Game_File_Handler.formatTime(9)))