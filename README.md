# A-Maze-ing
This project, titled A-Maze-ing, is a challenge to create a program that can generate complex mazes from scratch. While the original instructions specify Python, I have translated the logic into C using a TUI (Terminal User Interface) approach as requested.

# Gemini explanation
## 1. Project Summary & Problem Statement
### The Problem
How do you create a "perfect" maze—one where every point is reachable, but there is only one unique path between any two points—using code?. The goal is to move from "chaos" (a grid of walls) to a structured puzzle using randomness and graph theory.
### Requirements (from amazing-task.pdf)
Generation: The maze must be randomly generated but reproducible using a "seed".
### Structure: 
Each cell has 4 potential walls (North, East, South, West).
### Connectivity: 
No isolated cells; entry and exit must be valid and inside bounds.
### Output: 
The maze must be saved to a file using hexadecimal digits to represent walls.
### Visuals: 
A way to display the maze in the terminal (ASCII).
Special Pattern: A "42" must be visible in the walls (if the maze is large enough).

## 2. Task Decomposition
To build this, we break the "big" problem into small, manageable chores:
    Data Setup: Create a grid (a 2D array) where each cell "remembers" which walls it has.
    The Algorithm: Use a "Recursive Backtracker" (like a traveler exploring a cave and leaving a breadcrumb trail).
    The Config Parser: Read a text file to find out how big the maze should be.

Hex Converter: Turn the wall data into numbers (0-9, A-F) for the output file.
The TUI (User Interface): Print the maze to the screen using characters like # for walls and for paths.

## 3. Simplified C Implementation
This code uses a Recursive Backtracker algorithm. Imagine you are in a dark grid. You move to a random neighbor, break the wall between you, and keep going until you hit a dead end. Then, you "backtrack" to the last spot that had an unvisited neighbor.

# ChapGPT explanation
Below is a beginner-friendly, structured response that does three things, in the order you asked:
Convert the PDF into text (already done) and restate the problem clearly
Summarize what needs to be done (plain language, no jargon)
Decompose the task step-by-step
Provide a simplified C implementation using a TUI (terminal ASCII), not MiniLibX, with very gentle explanations, as if you never programmed before
All technical requirements are taken from the provided PDF.
## 1. What this exercise is about (problem statement, simplified)
Goal:
You must create a program that generates a maze, saves it to a file, and shows it in the terminal.
Think of it like this:
The computer must invent a maze, make sure it is valid, write it down using numbers, and draw it using text characters.
The maze:
Has a width and height
Has an entry and an exit
Is made of cells, and each cell has walls (north, east, south, west)
Can be perfect (only one possible path from entry to exit)
You control everything using a configuration file (config.txt).
## 2. What is required (in very simple words)
From the subject, the mandatory requirements are:

Input 
A text file like:

WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
PERFECT=True
OUTPUT_FILE=maze.txt

Your program must:
Read this configuration file
Generate a random maze

Make sure:
Entry and exit exist
All cells are connected
Walls are consistent between neighbors
Save the maze in a hexadecimal format
Display the maze visually:
We will use ASCII in the terminal (TUI) instead of MiniLibX

Optionally:
Show the solution path
Regenerate a new maze

## 3. Output format (important)
Each cell is written as one hexadecimal digit (0–F).

Each bit means a wall:
Bit	Direction
0	North
1	East
2	South
3	West

Example:
F (1111) → all walls closed
0 (0000) → all walls open

The file contains:
Maze rows (hex digits)
Empty line
Entry coordinates
Exit coordinates
Shortest path (N E S W)

## 4. Task decomposition (how to build it step by step)
This is how you should think, not code yet:
### Step 1 – Read config file
Open file
Read line by line
Extract numbers and strings
### Step 2 – Store the maze in memory 
Use a 2D array
Each cell stores walls using bits
### Step 3 – Generate the maze
We use a simple algorithm:
Recursive Backtracking (DFS)
Why?
Easy to understand
Produces a perfect maze
Used everywhere
### Step 4 – Save maze to file
Convert walls to hex
Write one row per line
### Step 5 – Display maze in terminal (TUI)
Use:
+, -, |
E for entry
X for exit
J for joker 
