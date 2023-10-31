# Casino
   As I said in the main readme I created this project as an inspiration from a trip to the casino with my grandmom. I coded this a long time ago now, but I still remember how much fun I had coding it. I put in a lot of time for this project and this is the biggest project that I have fully finished in Python. This is my favorite Python project that I have created and the one that I am most proud of. This is a casino application that performs just like a casino. My friend Watson really likes the casino. Even to this day if he is bored he will sometimes run the code and just spin the casino for 30 minutes. There is literally no monetary gain but he finds it fun nonetheless. The odds of winning are a little too in favor of the player because he manages to always win, but for some reason when I play, I always lose my money. Maybe I am just unlucky lol. But I hope you enjoy my first big project.

## Contents
   - [How To Build](#how-to-build)
   - [How To Play](#how-to-play)
   - [Challenges and Lessons Learned](#challenges-and-lessons-learned)
      - [Login Screen](#login-screen)
      - [Spin Function](#spin-function)

## How to build
1. Be sure to have Python with PIP installed
2. Git clone the project to your local computer
3. Open the command prompt within the casino folder provided
4. Install the pip requirements using `pip install -r requirements.txt`
5. Now we can test the installation by running Python on main.py
   
   This can be different depending on your version of Python and setup but here are some options to help. \*version\* refers to your version of Python. All of the following commands are run within the Casino folder on the command line.
   - `py main.py`
   - `Python main.py`
   - `Python*version* main.py`
   - Lastly, I use Visual Studio Code for Python so you can run `code .` and launch Python with the green arrow in Visual Studio

## How to play
1. When playing please make sure that your computer resolution is set to 1920x1080. Otherwise, functions will not work as expected
2. Playing the casino is very simple. When you launch the casino the first step is to create an account.
3. The username box is selected by default so you can begin typing your username
4. Be careful because once you hit enter you cannot change your username
5. Hit Enter and begin to type in your password
6. For first-time users you need to click new user here. And for returning players, you can press enter after entering your password.
   - First-time users should receive a message that says the account has been added
   - First-time users can go back and repeat steps 3-6 as a returning user.
7. Now that you are in the game you can click the big red button to test your odds in the casino
8. On the left is a set of buttons that allow you to change the amount you are betting
9. To close the application you can use the command line by either closing the command prompt or by stopping the program with `CTRL+C`. You can also hit `ESC` on your keyboard with the application up to close the program
10. The final step is to HAVE FUN. Try and make as much money as you can

## Challenges and Lessons Learned
I remember the two biggest challenges for me were the login screen and the spin function.

### Login Screen
For the login screen, I wanted to take the data and send it to the main game so that it could be used to save and render the user's data. For example, I would need to load the user's credits from their profile so that I could display them in the main casino game. The solution I came up with was a very Pythonic solution in which I would have the function return a tuple of 4 values, each of which I would feed to the main game of the casino. One thing I didn't seem to realize at the time is that because I wasn't using a class almost all of my variables were global. This means that I didn't technically need to return anything because I had access to the variables in question already. Having those values be global anyway isn't a good idea either, but that is one of the ways I could have solved that problem. Looking back at the login screen code it feels very messy which I find funny. I feel like it helps me see the growth I've made as a programmer when I can see how I used to code vs how I code now.

### Spin Function
Now, for the spin function. This function right here *sigh*. I can't even describe how long I thought of this problem when I was first writing the code. I spent probably about three hours thinking of a solution to this problem. The problem was that in a casino the grid is a 3x3. I wanted the grid to roll through 2 possible selections before finally landing on the actual result on the third roll. This means that in each grid there were 4<sup>3</sup> or 64 possibilities of what a roll could look like. On top of that, I needed to do the animation for each possibility as it rolled on the screen. So I didn't know what to do. I remember trying for so long to write a for-loop, but my solution didn't work. Finally, I came up with the genius decision to hardcode every possibility. This took me probably about two hours to do. I honestly may have done it wrong at some point with a bug lingering, but I do not know because I did not stress-test it lol. Technically this is a viable solution because there are only a set number of possibilities and depending on the implementation hardcoding every possibility could be the fastest solution. But nowadays I wouldn't have done it like that. I can think of so many solutions that could make this easier to maintain and check for bugs. For starters, my first idea of a for loop would've worked just fine. I could create a for loop similar to the following line of code below.

```
# Note I would have a hashmap of the values for the options and it would link to their in and out animations stored in a class for each possibility
# There would be a class for each possibility and the class would contain the probability, the animations, and the images for the object

selection = 0

prev = 0
for x in range(3):
   selection = random.randint(1,10)

   if x != 0:
      map[prev].outAnimation()

   map[selection].inAnimation()
   prev = selection
   
```

I came up with this solution in less than a minute, and it is about 600 lines shorter than my current implementation. That is okay though, because I was learning. I was stepping out and trying something new. I am really proud of everything that I learned when creating this project. This implementation is a lot clearer to read and debug. This is probably how I would do it if I were to refactor the project. I would also take advantage of more object-oriented techniques making a class for each of the possibilities and managing their odds and animations from there. My last comment on my challenges here is that I find it funny how I am coding in Python and I didn't write a single class. Making classes for these objects would've made my life a lot easier, but as stated before it was a learning experience. Thanks for reading this section on my casino project.
