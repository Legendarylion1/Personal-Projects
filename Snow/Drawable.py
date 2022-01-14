import pygame
from abc import ABC, abstractmethod

class Drawable(ABC):
    def __init__(self, x = 0, y = 0):
        self.__x = x
        self.__y = y
        
    def getLoc(self):
        return (self.__x, self.__y)
        
    def setLoc(self, p):
        self.__x = p[0]
        self.__y = p[1]
    
    
    @abstractmethod
    def draw(self, surface):
        pass
    
class Rectangle(Drawable):
    
    def __init__(self, x = 0, y = 0, width = 1, height = 1, color = (255,255,255)):
        self.__x = x
        self.__y = y
        self.__width = width
        self.__height = height
        self.__color = color
        super().__init__(x,y)
        
    def draw(self, surface):
        location = self.getLoc()
        pygame.draw.rect(surface, self.__color, [location[0], location[1], self.__width, self.__height])
        
        
class Snowflake(Drawable):
    
    def __init__(self, x = 0, y = 0, color = (255,255,255)):
        self.__x = x
        self.__y = y
        self.__color = color
        super().__init__(x,y)
        
    def draw(self, surface):
        location = self.getLoc()
        pygame.draw.line(surface, self.__color, (location[0] -5, location[1]),(location[0] + 5, location[1]))
        pygame.draw.line(surface, self.__color, ( location[0], location[1] - 5), (location[0], location[1] + 5))
        pygame.draw.line(surface, self.__color, (location[0] - 5, location[1] - 5), (location[0] + 5, location[1] + 5))
        pygame.draw.line(surface, self.__color, (location[0] - 5, location[1] + 5), (location[0] + 5, location[1] -5))
        
        
    def fall(self):
        a = self.getLoc()
        b = (a[0], a[1])
        if a[1] != 720:
            b = (a[0], a[1] + 1)
        self.setLoc(b)
        
    
    
    
    
    