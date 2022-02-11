# TicTacToeBot
This is a Tic-Tac-Toe bot that will win or tie every time in 3x3 games (it can also play 2x2 and theoretically 4x4, but the latter generally takes too much computing power and therefore execution time).
The algorithm implemented is a general solution to the game, by which the program recursively finds the best move by checking all future possibilities.
This is pretty inefficient, as the algorithm recursively computes the same sub-problems over and over again --> several million calculations are necessary for the algorithm to play a single move in 4x4.
The issue can be solved with dynamic programming, which is something I may implement in the future. 
I also might attempt to use neural networks and machine learning to create a new bot.
