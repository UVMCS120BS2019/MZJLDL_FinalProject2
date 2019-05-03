# Group Members
* Jace Laquerre
* Matt Zahar
* Dale Larie

# Tower of Hanoi
The goal of the puzzle is to move all the disks from the leftmost peg to the rightmost peg, adhering to the following rules: 
* Move only one disk at a time. 
* A larger disk may not be placed ontop of a smaller disk. 
* All disks, except the one being moved, must be on a peg.

# How to Play:
* Select the amount of disks you want to play with
* Hit the "Enter" key
* The game will begin and show your current amount of moves and the minimum moves it takes to complete 
* Click to select the disk then move your mouse the the pef you desire to move it to, then click again
* Hit the Reset button to move all pegs to their orignal position and to reset the number of moves 
* If you complete the game, it will bring you to and end screen with a Replay button

# Polymorphism
If the player completes the game, confetti will be displayed on the end screen. The confetti consists of Quads and Circles, which are all stored in a vector of Shape pointers. Polymorphism is used to draw all of these shapes in a for loop, calling the appropriate drawing method depending on the class of the shape.
