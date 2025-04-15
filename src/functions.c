#include <math.h>
#include "functions.h"

// main idea of blitting functions
//
// 1) Convert input into RPN using shunting yard algorithm
// 2) Build a parser that takes RPN and evaluates it at an input
// 3) Maintain a linked list containing all functions drawn to the screen, sorted
//    to have least time of life to most time of life
// 4) Create a function the walks through the list and draws all functions to the screen
//
// Nice would-haves
// -> Create a chunking system that only renders functions which are visible

