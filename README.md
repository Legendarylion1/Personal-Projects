## Pong Game
#### Completed Dec 29, 2022

Fun project creating pong with openGL32 and glfw. The thing that I can say I learned the most while creating this was abstraction. As I created more things in the project I found myself needing to use similar functionality more often meaning that I should try to refactor my old code to work with the new code that I was trying to write. This led to the creation of the objectRenderer class. I also left up the square renderer class as a look of what I started with but there was a lot of refactoring with this project once I realized what I was doing.

Something I would do better. For the numbers, I had the idea to create a function that just takes in the score, figures out the number of digits in the score, for spacing purposes, and displays the correct score to the screen with only the need for numbers 0-9. There is no need to implement this for this project though but it will be in the next one.

One last thing I would've done differently is to have the game render the objects rather than the objects each having their own renderer. I don't think it is the object's responsibility to render themselves, but the game should do that. 

Thanks for checking it out!
