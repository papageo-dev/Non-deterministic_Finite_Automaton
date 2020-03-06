# Non-deterministic_Finite_Automaton

 Creates a Non-deterministic Finite Automaton, from input file description, in C programming language.

# Code Information

 The code were created using "Code :: Blocks IDE" and I used "GNU Compiler for C / C ++".

# General Description

 -Initially, program asks for the input file's name. This file should contains the description of automaton,                                  
  that you want to create.                                                                                   
 -After the input file is entered correctly, creates the automaton and prints all edges, states and the automaton's alphabet.
 -Display message "Insert characters" and waits for user input characters.                                                   
 -After user enters a string of characters, the program checks if automaton terminates in final or non-final state           
  and displays an appropriate message.                                                                                   
 -Finally, asks user if wants to enter other characters and the process is repeated using the same automaton.

# About Input Files

 -First Line: Initial States                                                                                               
 -Second Line: Final States                                                                                                 
 -Trird Line and below: Description of transitions(For example: "a c 1" = From state "a" to state "b", with character "1".)              
