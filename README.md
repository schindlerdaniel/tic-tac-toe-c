# tic-tac-toe-c
A simple tic-tac-toe game implemented in C.


# Tic-Tac-Toe Game in C

This is a console-based Tic-Tac-Toe (Amőba) game written in C, originally created as a university project. The project follows a modular structure and demonstrates fundamental C programming and memory management techniques.

## Key Features
- Customizable game board: The size of the grid can be freely adjusted.
- Dynamic winning conditions: The number of symbols required to win automatically scales with the board size.
- Diagonal wins: Optional setting that can be enabled or disabled at the start of the game.
- Undo function: Players can undo their last move by typing the 'u' character during the game.
- File saving: The list of winners is automatically saved to a file by the program.

## Technical Details
- Dynamic arrays: Used for storing move history (with realloc-based dynamic memory resizing).
- Linked lists: Used for managing and tracking past winners.
- Modular architecture: The code is split into separate source files (.c) and header files (.h) for a clean structure.

















