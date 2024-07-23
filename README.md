# Pokemon Adventure

This is a fan-made Pokemon game that I have spent about 4 months programming. This is a large-scale refactor of my other Pokemon game to fix difficulties in rendering and battle limitations. I am very happy with my accomplishments in this program. The renderer class is a lot smaller than what it was before. My previous implementation was designed to be a state machine, which quickly scaled too large to refactor. This new design allows objects to use the renderer themselves so that the renderer does not need to know how to render each object decoupling the two. Meaning that if I need to make changes to the renderer I do not have to update every single object. The second large change that I made was to the battle system. Previously using object-oriented programming I coded it so that the Pokemon owned their attacks. The problem this caused is that now attacks can't take in the opposing Pokemon to do calculations. This becomes a bigger deal when I want to create moves that trigger special abilities depending on the Pokemon it is being used on. In the new system, the Pokemon holds an integer representing the move, and the battle system will know which move is being used based on the integer. This decoupling has been used in many different aspects of my new Pokemon Game. The classes that I am most proud of are my Menu Class, Renderer Class, Animator Class, and Battle Simulator Class. There is still refactoring that needs to be done specifically for the battle simulator class, but I am very proud of the work that I have accomplished so far. Thanks for checking it out. 


## Contents
   - [How To Build](#how-to-build)
   - [Challenges and Lessons Learned](#challenges-and-lessons-learned)
      - [Memory Management](#memory-management)
      - [Blocking Functions](#blocking-functions)
      - [Code Organization](#code-organization)

## Requirements
* Visual Studio Community
* Windows

## How to build
1. Git clone the repository to your local computer
2. Checkout the Pokemon Game Branch using `git checkout Pokemon-Game`
3. You will need to run the Visual Studio community solution
   - The file is "`PokemonAdventure2.sln`"
4. When you open the solution set the build platform x86 at the top middle
   - If you are having trouble finding it. It is under that menu tab at the top that says "`Test`"
   - It is also to the left of the green arrow for the "`Local Windows Debugger`"
5. Now you can navigate to the build tab at the top middle and select "`build solution`"
6. This creates an executable for you to run and play the game
7. You can find the executable in the Debug folder created.
   - The executable should be named "`PokemonAdventure2.exe`"
   - Note that the executable needs to be placed in the same directory as the solution
8. To build and run in debug click the green arrow at the top middle for Local Windows Debugger

## Challenges and Lessons Learned
Three challenges that are my top priority are memory management, blocking functions, code organization

These challenges are important to any C++ project, but for me they are aspects that I want to master to further myself as a developer. 


### Memory Management
Memory management for this project isn't terrible. The one thing I know that I will get hate for is my use of the new keyword to declare variables without explicitly calling delete. Memory is cleaned up after program executions so I haven't worried about this problem just yet. In the near future I plan on using smart pointers to manage my memory specifically for the Menu class. Almost everything in the Menu class is heap allocated. The button was my first struct created and it utilizes a linked list to reference other buttons on the screen. Therefore I heap allocated the buttons, and I simply repeated the process for the other structs used by the menu. Heap allocation here isn't the end of the world but it’s not necessary. In the future, I plan on stack allocating all that I can unless I need to use the heap for something like object reference in the case of my button.


### Blocking Functions
Blocking functions have become a recent pain point for me. I recently added animations to my game, and some animations can be canceled with a button click handled in the input class. This means that both functions need to be checked at the same time. I could remedy this by having both functions be non-blocking in a loop or thread both functions. In another project, I will thread the renderer, but in this project, I decided to make the functions non-blocking so that both can render and check for input. I wish I thought of this as a design point when I was first creating the game because it would make my code a lot simpler to have an API call to the renderer. Then it would run an animation in another thread using the renderer while I check for input in the main thread. Small things like this are bound to pop up as I increase in scope and complexity, and it helps me know what to consider when I am programming in the future. Another notable point where I "coded myself into a corner" was with the battle simulator. I originally coded the battle simulator to be text-based and then added the renderer to it later. However, I did not yet conceive of the menu class that I would later use in the battle simulator. So the Menu class has code that specifically addresses the battle simulator that shouldn't be there due to the battle simulator not knowing it had to be non-blocking.




### Code Organization
Code organization for this project is going really well. I have a lot of classes that all follow the single responsibility principle for design. Code organization was something that I tried to pay a lot of attention to when developing this project. The only class that I think doesn't directly adhere to this structure is once again the battle simulator. I should have taken more time with the design of the battle simulator so that I could appropriately break up its code. The idea for the battle simulator is that it works in three stages. Stage one is to get the user and AI input. Stage two is to generate all of the battle data for the simulation. Stage three is to simulate the battle for the user to see. I should have broken up these stages into their own separate classes. This would help a lot with debugging the project and testing while also shrinking the class considerably. When I refactor the battle simulator this will be my main focus. The battle simulator technically does what it is supposed to but I do not think the code is clean enough to represent me as a developer so I will have to refactor it.
