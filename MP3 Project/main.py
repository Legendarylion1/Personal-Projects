import pygame
import os
import time
import musicOptions
from mutagen.mp3 import MP3

#By Torin Middlebrooks
#Start Date: 8/9/21
#"End" Date: TBD

currentSong = "There is no song playing"
success = None
startTime = (time.time() * 2)
songDuration = 0
loopPrevention = 0

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
            print("Test: " + currentSong)
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
            if len(musicOptions.songQueue) >= 1:
                currentSong = musicOptions.useQueue()
                songDuration = musicOptions.songLength("Music Files/"+currentSong)
                startTime = time.time()
                print("\nNow Playing: " + currentSong)
                musicOptions.mainMenu(0)
            else:
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
            #try:
                #if (time.time() - startTime) > songDuration:
                    #Checks time difference to see if the length of the song has passed
                    
                    #print("Song Has ended")
                #else:
                    #print("Song is still playing")
                #print("Duration in seconds: ", a)
                #print("Song analyzed was: ", currentSong)
                #musicOptions.mainMenu()
            #except:
                #print("Length test cannot be completed")
                #musicOptions.mainMenu()
            pass
        #4
            
        #5
        elif (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_5):
            musicOptions.searchAlgorithm()
            musicOptions.mainMenu()
            pass
        #5
        
        elif (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_6):
            os.system("cls")
            #musicOptions.pickSong(0)
            musicOptions.searchAlgorithm("Queue")
            musicOptions.mainMenu()
        else:
            pass
        
    if (time.time() - startTime) > songDuration:
        musicOptions.songPlaying = False
    else:
        musicOptions.songPlaying = True
    
    if len(musicOptions.songQueue) >= 1 and musicOptions.songPlaying == False:
        currentSong = musicOptions.useQueue()
        songDuration = musicOptions.songLength("Music Files/"+currentSong)
        startTime = time.time()
        os.system("cls")
        musicOptions.displaySong(currentSong)
        musicOptions.mainMenu(0)
        loopPrevention = 0
    elif len(musicOptions.songQueue) == 0 and musicOptions.songPlaying == False and loopPrevention == 0:
        loopPrevention = 1
        os.system("cls")
        print("***There is no song playing***")
        musicOptions.mainMenu(0)
        pass
    else:
        pass
            
    pygame.display.update()