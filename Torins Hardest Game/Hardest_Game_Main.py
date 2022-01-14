import Hardest_Game_Login_Back
import Hardest_Game_Levels
import Hardest_Game_File_Handler
import pygame
import time

gamerunning = True
playingLevels = True
start = (100,540)

#Gets the the listOfUsernames,listOfPasswords,listOfAttempts,listOfTimes, usersposition, userAttempts



while gamerunning == True:

    usernames, passwords, attempts, bestTimes, position, uAttempts = Hardest_Game_Login_Back.main()
    start = time.time()
    


                #GAME LEVELS
    while playingLevels == True:
        currentLevel = 1
        #returning of a 0 means that the level was failed, returning of a 1 means that the level was passed

            #LVL1
        if currentLevel == 1:
            passedLevel = 0
            passedLevel, uAttempts = Hardest_Game_Levels.level1(uAttempts)
            if passedLevel == 0:
                currentLevel = 1
                attempts[position] = uAttempts
                Hardest_Game_File_Handler.writeToFile(usernames,passwords,attempts,bestTimes)
                continue
            else:
                currentLevel += 1
            print("Passed LVL1")

            #LVL2
        if currentLevel == 2:
            passedLevel = 0
            passedLevel, uAttempts = Hardest_Game_Levels.level2(uAttempts)
            if passedLevel == 0:
                currentLevel = 1
                attempts[position] = uAttempts
                Hardest_Game_File_Handler.writeToFile(usernames,passwords,attempts,bestTimes)
                continue
            else:
                currentLevel += 1
            print("Passed LVL2")
            
            #LVL3
        if currentLevel == 3:
            passedLevel = 0
            passedLevel, uAttempts = Hardest_Game_Levels.level3(uAttempts)
            if passedLevel == 0:
                currentLevel = 1
                attempts[position] = uAttempts
                Hardest_Game_File_Handler.writeToFile(usernames,passwords,attempts,bestTimes)
                continue
            else:
                currentLevel += 1
            print("Passed LVL3")

            #LVL4
        if currentLevel == 4:
            passedLevel = 0
            passedLevel, uAttempts = Hardest_Game_Levels.level4(uAttempts)
            if passedLevel == 0:
                currentLevel = 1
                attempts[position] = uAttempts
                Hardest_Game_File_Handler.writeToFile(usernames,passwords,attempts,bestTimes)
                continue
            else:
                currentLevel += 1
            print("Passed LVL4")


                #Finished - Update Best Time
        if currentLevel == 5:
            print("Game complete!")
            end = time.time()
            if (Hardest_Game_File_Handler.timeComparison((end - start),bestTimes[position]) == 1):
                bestTimes[position] = int(end - start)
            Hardest_Game_File_Handler.writeToFile(usernames,passwords,attempts,bestTimes)
            bestTimes[position] = Hardest_Game_File_Handler.formatTime(int(end - start))
                #Finished - Update Best Time

            break
        else:
            continue
        pass
                #GAME LEVELS



    pygame.display.toggle_fullscreen()
    pass