import os
import pygame
import time
from mutagen.mp3 import MP3


mp3Folder = 'C:/Users/Torin Middlebrooks/Desktop/PersonalIsh/MP3 Project'
listOfSongs = []
songQueue = []
songPlaying = False

#Populates the list of songs with mp3s from the folder
with os.scandir(mp3Folder) as entries:
    for entry in entries:
        if  entry.is_dir() and (entry.name == 'Music Files'):
            with os.scandir(mp3Folder + "/" + entry.name) as songs:
                for song in songs:
                    if song.is_file() :
                        listOfSongs.append(song.name)
#Populates the list of songs with mp3s from the folder

#Re-displays the options of the main menu
def mainMenu(x = 1):
    if x == 1:
        os.system("cls")
    print("\n~~~ What would you like to do ~~~")
    print("1. Pick a song \n2. Display Current Song\n3. Skip Current Song\n4. Length Test N/A\n5. Word Search Test\n6. Queue a song\n")
#Re-displays the options of the main menu

#Called to pick the users song
def pickSong(playOrQueue = 1):
    #playOrQueue = 1 means insta play and 0 is add to Q
    print("\n~~Songs In Library~~")
    for x in range(len(listOfSongs)):
        print(str(x + 1) + ".", listOfSongs[x])
        #Prints out a list of the songs availible numbered ~Algorithm not implemented yet~
    a = int(input("\nWhich song would you like: "))
    a -= 1
    currentSong = listOfSongs[a]
    
    #again playOrQueue == 1 plays the song now and playOrQueue == 0 adds it to q
    if playOrQueue == 1:
        pygame.mixer.music.load('Music Files/' + currentSong)
        pygame.mixer.music.play()
        print("\nNow Playing: "+ currentSong)
        return currentSong
    elif playOrQueue == 0:
        addToQueue(currentSong)
        

def displaySong(x):
    os.system("cls")
    print("\nCurrently Playing:", x)
    pass

def skipSong(currentSong):
    for i in range (len(listOfSongs)):
        if (currentSong == listOfSongs[i]) and (i != (len(listOfSongs) - 1)):
            return listOfSongs[i + 1], True
        elif (currentSong == listOfSongs[i]) and (i == (len(listOfSongs) - 1)):
            return listOfSongs[0], True
        #else:
        #print("\nThere was an problem skipping the song\n")
    return "Error", False
    pass

def songLength(path):
    try:
        audio = MP3(path)
        length = audio.info.length
        return length
    except:
        return None


def addToQueue(songToAdd):
    songQueue.append(songToAdd)
    pass

def useQueue():
    nextSong = songQueue[0]
    pygame.mixer.music.load('Music Files/' + nextSong)
    pygame.mixer.music.play()
    songQueue.pop(0)
    return nextSong


#NOT FINISHED YET Need options for adding the song to queue or playing it outright
def searchAlgorithm(playOrQueue = "play"):
    searching = True
    a = ""
    if len(listOfSongs) > 0:
        while searching == True:
            print("Search: " + a)
            songsViable = 0
            tempList = []
            for x in range(len(listOfSongs)):
                if listOfSongs[x].lower().find(a) != -1:
                    print(listOfSongs[x])
                    tempList.append(listOfSongs[x])
                    songsViable += 1
                for event in pygame.event.get():
                    print("In pygame forloop")
                    if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_RETURN) and songsViable <= 9:
                        os.system("cls")
                        pickingSong = True
                        while pickingSong == True:
                            print("\nWhich song would you like")
                            for x in range(len(tempList)):
                                print(str(x + 1)+ ". " + tempList[x])
                                
                            numNotSelected = True
                            while numNotSelected == True:
                                songSelection, numNotSelected = numsToNine()
                            if (playOrQueue == "play"):
                                if songSelection == 1:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 2:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 3:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 4:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 5:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 6:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 7:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 8:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                if songSelection == 9:
                                    subOne = songSelection - 1
                                    pygame.mixer.music.load('Music Files/' + tempList[subOne])
                                    pygame.mixer.music.play()
                                    pickingSong = False
                                else:
                                    pass

                            elif (playOrQueue == "Queue"):
                                if songSelection == 1:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 2:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 3:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 4:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 5:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 6:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 7:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 8:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                if songSelection == 9:
                                    subOne = songSelection - 1
                                    addToQueue(tempList[subOne])
                                    pickingSong = False
                                else:
                                    pass
            
            os.system("cls")
            a = wordBeingSearched(a)
    else:
        print("List hasn't been populated yet")
#NOT FINISHED YET Need options for adding the song to queue or playing it outright

def numsToNine():
    for event in pygame.event.get():
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_1):
            return 1, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_2):
            return 2, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_3):
            return 3, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_4):
            return 4, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_5):
            return 5, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_6):
            return 6, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_7):
            return 7, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_8):
            return 8, False
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_9):
            return 9, False
        else:
            return 0, True
    return 0, True

def wordBeingSearched(x):
    #print("Inside word search")
    wordToSearch = x
    for event in pygame.event.get():
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_ESCAPE):
            pygame.quit()
            exit()
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_a):
            wordToSearch += "a"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_b):
            wordToSearch += "b"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_c):
            wordToSearch += "c"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_d):
            wordToSearch += "d"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_e):
            wordToSearch += "e"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_f):
            wordToSearch += "f"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_g):
            wordToSearch += "g"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_h):
            wordToSearch += "h"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_i):
            wordToSearch += "i"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_j):
            wordToSearch += "j"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_k):
            wordToSearch += "k"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_l):
            wordToSearch += "l"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_m):
            wordToSearch += "m"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_n):
            wordToSearch += "n"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_o):
            wordToSearch += "o"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_p):
            wordToSearch += "p"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_q):
            wordToSearch += "q"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_r):
            wordToSearch += "r"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_s):
            wordToSearch += "s"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_t):
            wordToSearch += "t"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_u):
            wordToSearch += "u"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_v):
            wordToSearch += "v"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_w):
            wordToSearch += "w"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_x):
            wordToSearch += "x"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_y):
            wordToSearch += "y"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_z):
            wordToSearch += "z"
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_SPACE):
            wordToSearch += " "
            return wordToSearch
        if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_BACKSPACE) and (len(wordToSearch) > 0):
            wordToSearch = wordToSearch.rstrip(wordToSearch[-1])
            return wordToSearch
        else:
            return wordToSearch
    return wordToSearch
        #if (event.type == pygame.KEYDOWN and event.__dict__['key'] == pygame.K_RETURN):
            #print("Enter was pressed")
            #print(wordToSearch)
            #searching = False
                
