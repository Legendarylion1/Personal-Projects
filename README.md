# Pokemon Game

This pokemon game is a passion project for me. I was in love with the pokemon games as a kid, and being able to recreate my favorite game is a dream come true. I got into programming because of the endless possibilites of creation. Through my job experience and messing around at home I have learned so much, and it has given me the experience to make a game like this. This is a very fun project that is really testing my organizational skills when it comes to coding. The original scope of this project was for it to be a console battler. I had created a console pokemon game in which you keep battling in the "Pokemon Tower" until you lose when I was in my ID tech camp at Princeton University. I had created the console version of this game in about 4 days with about 4 hours of work into each day. You can see some of the remnant of the console application with my cout statements. When I was done I thought to myself. I can do more. I want to make a full pokemon game. So thats what I did. I've refactored the entire code base twice now, because my original scaffolding of a text based battler was not working well with my graphical components. But I think the code I have right now is pretty decent. It is readable and pretty easy to follow. The game is still in development so things are subject to change but I hope you enjoy my pokemon game.

## Contents
   - [How To Build](#how-to-build)
   - [How To Play](#how-to-play)
      - [Key Binds](#key-binds)
      - [Map Movement](#map-movement)
      - [Interactions](#interactions)
      - [PC](#pc)
      - [Pokemart Purchasing](#pokemart-purchasing)
      - [Trainers](#trainers)
      - [Battles](#battles)
      - [Pokemon](#pokemon)
      - [Dialogue](#dialogue)
      - [Menu Options](#menu-options)
         - [Pokemon](#menu-pokemon)
         - [Bag](#menu-bag)
         - [Save](#save)
         - [Settings](#settings)
         - [Exit](#exit)
   - [Challenges and Lessons Learned](#challenges-and-lessons-learned)
      - [Renderer](#renderer)
      - [Code Structure](#code-structure)
      - [Movement](#movement)

## How to build
1. git clone the repository to your local computer
2. I do not yet have makefiles for this project yet, so you will need to run the Visual Studio community solution
   - The file is "`Pokemon Adventure.sln`"
3. When you open the solution set the build platform to win32 or x86 at the top middle
   - I believe that it defaults to x64
   - If you are having trouble finding it. It is under that menu tab at the top that says "`Test`"
   - It is also to the left of the green arrow for the "`local windows debugger`"
4. Now you can navigate to the build tab at the top middle and select "`build solution`"
5. This creates an executable for you to run and play the game
6. You can find the executable in the Debug folder created.
   - The executable should be named "`Pokemon Adventure.exe`"

## How to play

### Key Binds

* **W - Up**

* **A - Left**

* **S - Down**

* **D - Right**

* **E - Interact**


### Map Movement
You can move around the map using the wasd keys as shown in keybinds

You can walk just about anywhere that looks like you should be able to walk on. Some tiles look like you may be able to squeeze in, but if there is even a tiny bit of rock in the tile, then you are not permitted to walk on that tile. You can walk in and out of the red and blue buildings as well.

### Interactions
Your interaction key is set to E by default. However not all interactions need to be triggered with the key.

   -  Pokemon Centers currently have a blue roof and will be changed to have a red roof. You can enter a pokemon center by walking through the front door. 

   - Pokemarts currently have a red roof and will be changed to have a blue roof. You can enter a pokemart by walking through the front door.

   - Inside of a pokecenter there is a lady at the desk. She is the nurse and if you press interact while facing her she will fully heal your pokemon.

   - Inside of the pokecenter at the top right there is a computer. This is the PC. all pokemon that you have caught and sent to the PC will be inside. You can press interact to access the PC

   - Inside of the pokemart there are two cashiers at the front desk. The one on the left sells potions and pokeballs. The one on the right will later on sell you moves and other miscellanious items. You can press interact on the cashier to the left and he will offer you items to buy.

   - Trainers are scattered across the pokemon world. Trainers will sometimes spot you if you walk in front of them triggering a battle. If a trainer is not facing you, and a trainer has not been defeated already, then you can press interact on the trainer to trigger a battle as well. Finally, you can trigger dialogue with the trainer by also pressing interact on the trainer. 

   - Pokemon can spawn in the wild grass outside. By walking through the grass you have a chance at encountering a random pokemon from that area. Upon encountering a pokemon a battle is triggered.

### PC

* The PC shows all pokemon sent into boxes in the grid to the left. The pokemon that you currently have in your party are displayed in the 6 boxes to the right. 
* You can swap pokemon in and out of boxes by clicking them and then clicking a location to place them. You can move pokemon between boxes, from the boxes to your roster, and from one roster slot to another. Pokemon only need to be clicked once to select them, and clicked once to place them. 
* Click outside of the PC boxes to close the PC and return to the pokemon world.

### Pokemart Purchasing

* With any money that obtain, you can buy items from the pokemart. Simply click the item that you want in the list at the top right. The item will be added to your bag, and your balance will decrease.

### Trainers

* Different trainers can have different distances for spotting you so watch out. When spotted a trainer will walk over and begin dialogue before finally challenging you to a battle. When a trainer is defeated you will gain money, and you do not have to fight that trainer again.

## Battles

Battles with trainers and battles with pokemon three have slight differences.
1. In a trainer battle you cannot run. You have no choice but to fight
2. In a trainer battle you are not able to catch their pokemon
3. Trainer battles only end when one party is completely defeated

Other than that the mechanics are the same. Pokemon is a turn based game. You select your option by clicking with your mouse, and then the AI will also make a decision on what to do.

Your options during battle are to fight, select an item, select a pokemon, and to run

To deselect any of these options you can click outside of it. Clicking a corner, or clicking anywhere outside of an option will deselect the option.

* If you select fight, you can then also click a move in one of the gray boxes displayed. If you run out of PP for a move you can no longer use it. If you run out of PP on all of your moves then you will be forced to use a really weak attack called struggle.

* If you select Item, you can choose from a heal, a pokeball or a mischillanious item. Pokeballs will be automatically thrown when selected. If you select heal, then you must select a pokemon to use the item on. Mischillanious items are not yet added to the game, but you will also have to select a pokemon to use that on

* If you want to switch out to another pokemon, then you only need to select another pokemon to switch into.

* Running from a battle will be successful 100% of the time if your pokemon has more speed than the opposing pokemon. If you do not have more speed there is a 50% chance that you will be allowed to run

## Pokemon
I dont have much to say about pokemon here. It is really hard to differentiate pokemon at the moment as a lot of the art hasn't been done. One thing to note is that the health stats of the pokemon are really really high right now due to testing purposes. All stats will be balanced when I am finished the project.

## Dialogue
If you enter dialogue with an NPT(Non playable trainer) as my friend named them. You have to wait for all text to be displayed and click whenever you see the down arrow on the right appear. The down arrow is a v, but I am using it as a down arrow for now.

## Menu Options

Menu options can be accessed by pressing the escape key "`ESC`". To close menu options and to really close everything in this game you can click outside of any of the options to return to the previous screen.

### Menu Pokemon
In this menu option you are able to swap the position of the pokemon in your party. Click one pokemon, and that will select them. Then click another pokemon or a vacant slot to move your pokemon to that slot.
### Menu Bag
The bag has access to all of your items. Here you can find your heals, your pokeballs, and your miscillanious items. If you select an item that can be used on one of your pokemon, you will be sent to the pokemon selection screen.
### Save
Save just saves the current state of the game. I personally think that the save happens a little too quickly and people may not understand that their game was saved, so I am going to add a popup and indicator that shows that the save occurred. For now just know that if the game sends you back to the main world without crashing, then the save was complete.
### Settings
Settings is not yet implemented and will not do anything. Settings in the future will allow you to change what buttons perform each action. I will need to refactor the way I handle input so I am putting that off towards the end of development. Settings will also allow you to turn on or off auto save for different features of the game. Lastly, I would like to add a setting for displaying framerate, and changing the speed of text with dialogue.
### Exit
Exit closes the game. Please note that the game does not save on exit. This is by design. I will add a setting that will allow for saving on exit.

## Challenges and Lessons Learned
My three biggest challenges right now are the renderer, code structure, and movement

All three of these problems should be fine by the time I'm done. I really need to refactor to fix these changes. If you see anything in my code that you think can be improved. Please do not hesistate to contact me and suggest improvements. I am here to grow and I always welcome constructive criticism. Here are some of the things that I think are the biggest issues with my code at the moment. Here is an insight on my thoughts as a software engineer.

### Renderer
My idea for the renderer is that it is going to be a state machine. The renderer will not compute any logic. I plan for it to recieve a set of states and variables and just know what to do with them. This solution has made my renderer code very look and it looks a little messy to me. There are a lot of variables that can be set and there are a lot of functions. I do not have a problem with the number of things that there are, but I want the inputs to the state machine to be more apparent and the steps that the statemachine is going to follow to be more apparent too. If you look at the code now, you will be able to follow the state machine, but the code an clearly be cleaned up to be more presentable and readable.

### Code Structure
There are classes that take in classes only to use one function of the class. My cutscene class does not renderer pokemon encounters at all, but it uses the awaitClick() function that I wrote in my encounter class. I do not like this. But there are examples of this in a few other parts of my code as well which need to be taken out and repackaged. I also do not like the random variables that I have scattered in my code. I plan on adding them to a struct or a namespace. I also feel like my game engine class is getting bloated. Some of the functions in there do not need to be there, or atleast can be placed into a different class that is supposed to do the thing that the game engine is doing. There are other small things here and there, but my TODOs tell a pretty good portion of what I would like to change. I also have a whiteboard next to my desk that I use as my issue tracker and as my project management tool to keep me on track.

### Movement
Movement is an interesting one because there isn't anything wrong per say, but changes need to be made so that my future ideas can be implented. For example, if I want the user to be able to change what button to press in order to move, then I can't code it as if they press "`W`", then set up to true. It cant work like that because that code literally can't be changed. Instead Im going to change it to an event based system. If you press "`W`" then it will trigger an "`UP`" event. This event will make it so that each key isnt hard coded to setting a boolean true or false. I also want to change how I do the movement calculations in the first place. The code uses a timer system that I came up with. However, that same timer system is used for other functions like dialogue or AI animations. This means that it can be pulled out and help out code clarity. There are no bugs with movement so this task is going to wait until we get to the end.