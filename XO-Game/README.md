Project Title: Tic-Tac-Toe Game Refactoring in C#

This project involves creating a simple Tic-Tac-Toe game in C# using Windows Forms. The game allows two players to alternate marking spaces on a 3x3 grid, aiming to get three of their marks (X or O) in a row, either horizontally, vertically, or diagonally.

The refactor focuses on optimizing event handling. Instead of having nine separate event handlers for each button on the grid, a single event handler is used. This handler utilizes the `sender` parameter to identify which button was clicked, significantly simplifying the code and improving its scalability and maintainability.

Technologies Used:
- **C#**
- **Windows Forms**
- **Event Handling**

