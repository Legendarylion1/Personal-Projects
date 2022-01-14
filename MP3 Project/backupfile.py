import pygame
import os
import time
import musicOptions
from mutagen.mp3 import MP3

#By Torin Middlebrooks
#Start Date: 8/9/21
#"End" Date: TBD

currentSong = "Error"
success = None

pygame.init()
surface = pygame.display.set_mode((1280,720)) 
pygame.display.set_caption("Torin's Spotify")  

musicOptions.mainMenu()

while True:
    for event in pygame.event.get():
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
            pygame.quit()
            exit()
        
        #1
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_1):
            os.system("cls")
            currentSong = musicOptions.pickSong()
            #Sets song duration for the playing of the next song
            songDuration = musicOptions.songLength("Music Files/"+currentSong)
            startTime = time.time()
            musicOptions.displaySong(currentSong)
            musicOptions.mainMenu(0)
        #1
        
        #2
        elif (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_2):
            musicOptions.displaySong(currentSong)
            musicOptions.mainMenu(0)
        #2
        
        #3
        elif (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_3):
            os.system("cls")
            currentSong,success = musicOptions.skipSong(currentSong)
            #Function returns the current song and whether or not the skip was successful
            if success == True:
                #If successful we load the new current song and if not we print an error
                pygame.mixer.music.load("Music Files/" + currentSong)
                pygame.mixer.music.play()
                print("\nNow Playing: " + currentSong)
                songDuration = musicOptions.songLength("Music Files/"+currentSong)
                startTime = time.time()
            else:
                print("There was an error skipping the song")
            musicOptions.mainMenu(0)
        
        #3
            
        #4
        elif (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_4):
            try:
                if (time.time() - startTime) > songDuration:
                    #Checks time difference to see if the length of the song has passed
                    print("Song Has ended")
                else:
                    print("Song is still playing")
                #print("Duration in seconds: ", a)
                #print("Song analyzed was: ", currentSong)
                musicOptions.mainMenu()
            except:
                print("Length test cannot be completed")
                musicOptions.mainMenu()
        #4
            
        #5
        elif (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_5):
            musicOptions.searchAlgorithm()
            musicOptions.mainMenu()
            pass
        #5
        
        else:
            pass
    pygame.display.update()
