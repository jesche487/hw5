HW5 - Jesse Chen 11/24/2022
wordle
This wordle.cpp and wordle.h file contain the code
for a function that helps a user check valid words
given existing information on a wordle puzzle. It uses 
recursion to find all possible valid words based on the character
checked during its recursive call. 

To run the wordle-driver.cpp, run `make` and then run the made executable.

To run the extended tests, please cd into the proper `hw5_tests/wordle_tests` folder.
From there, run `make` and then run the made executable.

schedwork
This schedwork.cpp and schedwork.h file contain the code
for a recursive backtracking function that creates a valid 
schedule based off an availability matrix and other needed parameters.
It uses backtracking by checking all possible worker combinations until
a schedule cannot be made, in which it undos all changes by going back.

To run the schedwork-driver.cpp, run `make` and then run the made exectuable.

To run the extended tests, please cd into the proper `hw5_tests/schedwork_tests` folder.
From there, run `make` and then run the made executable.