encryptedDictS = {"a":"d", "b": "l", "c":"e", "f":"o", "m":"x", "q":"f", "d":"c", "e":"i", "g":"v", "w":"a", "t":"j", "z":"r", "i":"k", "r":"7", "h":"g", "s":"q", "j":"y", "k":"m", "x":"n", "o":"p", "p":"s", "v":"h", "u":"b", "n":"t", "y":"u", "l":"w"}
decryptedDictS = {"d":"a", "l": "b", "e":"c", "o":"f", "x":"m", "f":"q", "c":"d", "i":"e", "v":"g", "a":"w", "j":"t", "r":"z", "k":"i", "7":"r", "g":"h", "q":"s", "y":"j", "m":"k", "n":"x", "p":"o", "s":"p", "h":"v", "b":"u", "t":"n", "u":"y", "w":"l"}
encryptedDictI = {"1":"b","2":"l","3":"u","4":"v","5":"e","6":"s","7":"m","8":"g","9":"r","0":"w",":":"y","N/A":"q"}
decryptedDictI = {"b":"1","l":"2","u":"3","v":"4","e":"5","s":"6","m":"7","g":"8","r":"9","w":"0","y":":","q":"N/A"}
currentTextFile = "Hardest_Game_v0.9.txt"

#This function takes in 4 variables and encrypts them according to the cypher in Login_Front
#Input: u and p are strings for username and password, a is an integer for the number of attempts, t is an integer for seconds to complete a run
#Output: returns every varaible encrypted into letters according to dict in Login_Front. If there is no time("N/A") a "q" is returned
def encryptData(u,p,a,t = "N/A"):
    try:
        curUsername = list(u)
        curPassword = list(p)
        curAttempts = list(str(a))
        curBestTime = None
        encryptedUsername = ""
        encryptedPassword = ""
        encryptedAttempts = ""
        encryptedTime = ""

        for x in range(len(curUsername)):
            encryptedUsername += encryptedDictS[curUsername[x]]
        for x in range(len(curPassword)):
            encryptedPassword += encryptedDictS[curPassword[x]]
        for x in range(len(curAttempts)):
            encryptedAttempts += encryptedDictI[curAttempts[x]]

        #q is the return value for no current best time
        #y is the seperator in times that represents the ":"    -    for example 1:12:13 is 1y12y13 encrypted of course
        if t == "N/A":
            return encryptedUsername, encryptedPassword, encryptedAttempts, "q"
        else:

            # Here the time that t is taking in may not be an integer, and may already be formatted from main so we check if it is a string or an integer that needs formatting
            if str(type(t)) == "<class 'str'>":
                curBestTime = t
            else:
                curBestTime = formatTime(t)
            splitTime = list(curBestTime)
            for x in range(len(splitTime)):
                encryptedTime += encryptedDictI[splitTime[x]]

            return encryptedUsername, encryptedPassword, encryptedAttempts, encryptedTime

    except:
        print("\n\n\n!!! Was Unable to encrypt Data!!! \n\n\n")
        pass
    pass

#This function takes in 4 variables and encrypts them according to the cypher in Login_Front
#Input: u, p, and T are strings for username, password, and time to complete a run . a is an integer for the number of attempts
#Output: returns every varaible decrypted into letters according to dict in Login_Front. If there is no time("q") "N/A" is returned
def decryptData(u,p,a,t = "q"):
    try:
        
        curUsername = list(u)
        curPassword = list(p)
        curAttempts = list(str(a))
        decryptedUsername = ""
        decryptedPassword = ""
        decryptedAttempts = ""
        decryptedTime = ""

        for x in range(len(curUsername)):
            decryptedUsername += decryptedDictS[curUsername[x]]
        for x in range(len(curPassword)):
            decryptedPassword += decryptedDictS[curPassword[x]]
        for x in range(len(curAttempts)):
            decryptedAttempts += decryptedDictI[curAttempts[x]]


        if t == "q":
            return decryptedUsername, decryptedPassword, int(decryptedAttempts), "N/A"
        else:
            curTime = list(t)
            for x in range(len(curTime)):
                decryptedTime += decryptedDictI[curTime[x]]
            return decryptedUsername, decryptedPassword, int(decryptedAttempts), decryptedTime
    except:
        print("\n\n\n!!!Was unable to decrypt Data!!!\n\n\n")
        pass
    pass

#This function takes in the lists of account details and writes them to file
#Input: Takes in lists of usernames, passwords, attempts, bestTimes, file to write to
#Output: There is no output for this function. If it fails to write to file the game will close
def writeToFile(u,p,a,t,file = currentTextFile):
    try:
        fileToOpen = open(file,"w")
        toWrite = ""

        for x in range(len(u)):
            username, password, attempts, bestTime = encryptData(u[x],p[x],a[x],t[x])
            toWrite += "z"+username+"z"+password+"z"+attempts+"z"+bestTime
            pass
        fileToOpen.write(toWrite)
        fileToOpen.close()
        pass
    except:
        print("There was an error writing times to the file")
        exit()
    pass

#This function takes a time in seconds and a decrypted time in colon format to determine which time is less
#Input: Takes in a time in seconds, and a decrypted time in the decrypted time format
#Output: Returns a 1 if the new time in seconds is less than the decTime, and a 0 otherwise
def timeComparison(inSecs,decTime):
    try:
        if decTime == "N/A":
            return 1

        else:

            a = list(decTime)
            colonCount = 0
            hours = ""
            minutes = ""
            seconds = ""

            for x in range(len(a)):
                #print("a["+str(x)+"] : " + str(a[x]))
                if a[x] != ":":
                    if colonCount == 0:
                        hours += a[x]
                    elif colonCount == 1:
                        minutes += a[x]
                    elif colonCount == 2:
                        seconds += a[x]
                else:
                    colonCount += 1

            secondTime = int((int(hours) * 3600) + (int(minutes) * 60) + (int(seconds)))

            if inSecs <= secondTime:
                return 1
            else:
                return 0
    except:
        print("\n\n Error in Time Comparison \n\n")
        

    pass

#Takes in time in seconds and formats it into colon style i.e. 1:23:45
#Input: Takes in time in seconds
#Output: returns the formatted time in colon style i.e. 1:23:45
def formatTime(t):
    hours = int(t / 3600)
    minutes = int((t - (hours * 3600)) / 60)
    seconds = int(t - (hours * 3600) - (minutes * 60))
    formattedTime = ""
    if minutes < 10:
        if seconds < 10:
            formattedTime = str(hours) + ":0" + str(minutes) + ":0" + str(seconds)
        else:
            formattedTime = str(hours) + ":0" + str(minutes) + ":" + str(seconds)
    elif seconds < 10:
        formattedTime = str(hours) + ":" + str(minutes) + ":0" + str(seconds)
    else:
        formattedTime = str(hours) + ":" + str(minutes) + ":" + str(seconds)
    return formattedTime