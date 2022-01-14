#Torin Middlebrooks
#I would just like to point out that the image in zybooks does not load for me so I have no example to go off of.
#I am assuming that what I have is correct and please be lenient if it is not.

import pygame
import Drawable
import random

pygame.init()
surface = pygame.display.set_mode((1280, 720))
pygame.display.set_caption("It's SNOWING!!!!!")

green = (0, 128, 0)
white = (255,255,255)
blue = (0,0,255)

Drawables = []
groundPlane = Drawable.Rectangle(0, 0, 1280, 400, blue)
skyPlane = Drawable.Rectangle(0,400, 1280, 320, green)
snowflake = Drawable.Snowflake(80,0,white)

Drawables.append(groundPlane)
Drawables.append(skyPlane)
Drawables.append(snowflake)

fpsclock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
        if ((event.type == pygame.QUIT) or (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_q)):
            pygame.quit()
            exit()
        
    for x in Drawables:
        x.draw(surface)
        if isinstance(x, Drawable.Snowflake):
            x.fall()
    x = random.randint(0,1280)
    newsnowflake = Drawable.Snowflake(x,0,white)
    Drawables.append(newsnowflake)
    pygame.display.update()
    fpsclock.tick(30)
