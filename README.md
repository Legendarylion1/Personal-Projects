# Personal-Projects
Thanks for coming to check out my personal projects. In this repository are my 3 favorite projects I have worked on so far. Each project had a different goal or challenge that I was trying to overcome. For Pong, I wanted to test my knowledge of C++ and of using OpenGL for the first time. For the Casino, I wanted to spend real time working on a project to see if I could complete something of considerable size in my favorite language. Lastly, for “Torin’s Hardest Game” I wanted to try my best to complete an original game idea working about 3 hours a day in the 4 days leading up to Christmas. Lastly, I want to say that I am proud of everything that I have worked on and I hope you can appreciate my journey as a programmer alongside me.

## Projects
- [Pong Game](#pong-game)
- [Torin's Hardest Game](#torins-hardest-game)
- [Casino](#casino)

# Pong Game
#### Completed Dec 29, 2022
[Pong Game Branch](../Pong-Game)

Fun project creating pong with openGL32 and glfw. The thing that I can say I learned the most while creating this was abstraction. As I created more things in the project I found myself needing to use similar functionality more often meaning that I should try to refactor my old code to work with the new code that I was trying to write. This led to the creation of the objectRenderer class. I also left up the square renderer class as a look of what I started with but there was a lot of refactoring with this project once I realized what I was doing.

Something I would do better. For the numbers, I had the idea to create a function that just takes in the score, figures out the number of digits in the score, for spacing purposes, and displays the correct score to the screen with only the need for numbers 0-9. There is no need to implement this for this project though but it will be in the next one.

One last thing I would've done differently is to have the game render the objects rather than the objects each having their own renderer. I don't think it is the object's responsibility to render themselves, but the game should do that. 

Thanks for checking it out!


# Torin's Hardest Game
#### Completed Dec 25, 2021
[Torin's Hardest Game Branch](../Torins-Hardest-Game)

This is a project that I wanted to try and make over my holiday break. I wanted to make a game for my friends and I to speedrun, and it worked out pretty well for the time spent on it. The file system from my casino game was being abused by my friends so I changed how that worked as well as the login in general. The attempt counter may be off. I ran out of time to debug that problem. The main point of the game is to try and complete it as fast as possible. Also, another part of the game is that I am not supposed to explain to you how to play. So have fun, and don't cheat!

# Casino
#### Completed Sept 13, 2021
[Casino Branch](../Casino)

This casino project was inspired by a trip I took with my grandma to the casinos. I don’t know much about gambling but every time I saw the spin on the digital computer screen I thought to myself. I think I can do that. I would brainstorm the entire trip home, and then I got to work. I had a fun time completing that project. Writing this description a year later I can look back on the project and say that I wish I had used classes a lot more. It would've saved me so much time and headache lol. In “casinoBack.py” the spin function is 600 lines longer than it needs to be if I had just used a class, but that comes with learning. Again, thanks for supporting my journey as a programmer.
