#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cassert>
#include <windows.h> // for sleep


/**
 * @namespace sq
 * @brief Namespace for defining Square struct and its functions.
 */
namespace sq {

	/**
	 * @struct Square
	 * @brief Represents a square on a checkers game board.
	 *
	 * This struct is used to represent each square on a checkers board,
	 * storing information about the piece on the square, its position, and
	 * possible movements.
	 */
	struct Square {
		/**
		 * @brief Gets the color of the piece on the square.
		 * @return Character representing the color of the piece.
		 */
		char color() const { return c; }

		/**
		 * @brief Gets the name of the square.
		 * @return String representing the square's name (e.g., "a1", "e5").
		 */
		std::string square() const { return s; }

		/**
		 * @brief Gets the row number of the square.
		 * @return Character representing the row number.
		 */
		char row() const { return r; }

		/**
		 * @brief Gets the adjacent squares in front of the current square.
		 * @return Vector of strings representing front adjacent squares.
		 */
		std::vector<std::string> getFrtAdjSqs() const { return frtAdjSqs; }

		/**
		 * @brief Gets the adjacent squares behind the current square.
		 * @return Vector of strings representing back adjacent squares.
		 */
		std::vector<std::string> getBacAdjSqs() const { return bacAdjSqs; }

		/**
		 * @brief Gets the squares for forward jumps from the current square.
		 * @return Vector of strings representing forward jump squares.
		 */
		std::vector<std::string> getFrtJmpSqs() const { return frtJmpSqs; }

		/**
		 * @brief Gets the squares for backward jumps from the current square.
		 * @return Vector of strings representing backward jump squares.
		 */
		std::vector<std::string> getBacJmpSqs() const { return bacJmpSqs; }

		/**
		 * @brief Checks if the piece on the square is crowned.
		 * @return True if the piece is crowned, false otherwise.
		 */
		bool isCrowned() const { return crowned; }

		/**
		 * @brief Sets the crowned status of the piece on the square.
		 * @param status: True to crown the piece, false to uncrown.
		 */
		void switchCrown(bool status) { crowned = status; return; }

		/**
		 * @brief Checks if the piece on the square is captured.
		 * @return True if the piece is captured, false otherwise.
		 */
		bool isCaptured() const { return captured; }

		/**
		 * @brief Sets the captured status of the piece on the square.
		 * @param status: True to mark the piece as captured, false otherwise.
		 */
		void switchCap(bool status) { captured = status; return; }

		/**
		 * @brief Changes the color of the piece on the square.
		 * @param newColor: New color character for the piece.
		 */
		void changeColor(char newColor);

		/**
		 * @brief Default constructor for Square.
		 */
		Square();

		/**
		 * @brief Constructor for Square with color, square name, and row.
		 * @param c_: Color of the piece.
		 * @param s_: Name of the square.
		 * @param r_: Row of the square.
		 */
		Square(char c_, std::string s_, char r_);

		/**
		 * @brief Sets the adjacent squares in front of the square.
		 * @param sq: Name of the square for which to set adjacent squares.
		 * @return Vector of strings representing front adjacent squares.
		 */
		std::vector<std::string> setFrtAdjSqs(std::string sq);

		/**
		 * @brief Sets the adjacent squares behind the square.
		 * @param sq: Name of the square for which to set adjacent squares.
		 * @return Vector of strings representing back adjacent squares.
		 */
		std::vector<std::string> setBacAdjSqs(std::string sq);

		/**
		 * @brief Sets the squares for forward jumps from the square.
		 * @param sq: Name of the square for which to set jump squares.
		 * @return Vector of strings representing forward jump squares.
		 */
		std::vector<std::string> setFrtJmpSqs(std::string sq);

		/**
		 * @brief Sets the squares for backward jumps from the square.
		 * @param sq: Name of the square for which to set jump squares.
		 * @return Vector of strings representing backward jump squares.
		 */
		std::vector<std::string> setBacJmpSqs(std::string sq);

	private:
		char c;  ///< Color of the piece on the square ('r', 'R', 'b', 'B', ' ').
		std::string s;  ///< Square name (e.g., "a1", "e5").
		char r;  ///< Row number (1 to 8).
		std::vector<std::string> frtAdjSqs; ///< Front adjacent squares.
		std::vector<std::string> bacAdjSqs; ///< Back adjacent squares.
		std::vector<std::string> frtJmpSqs; ///< Squares for forward jumps.
		std::vector<std::string> bacJmpSqs; ///< Squares for backward jumps.
		bool crowned; ///< Indicates if the piece on the square is crowned.
		bool captured; ///< Indicates if the piece on the square is captured.
	};

}
using namespace sq;

/**
 * @namespace checkers
 * @brief defines global variables for Checkers game
 */
namespace checkers {

	/**
	 * @var extern std::vector<Square> squares
	 * @brief Represents all squares on the checkers board.
	 *
	 * This vector stores instances of the Square struct, each representing
	 * a square on the checkers board.
	 */
	extern std::vector<Square> squares;

	/**
	 * @var extern std::string selection
	 * @brief Holds all user input.
	 *
	 * This string variable is used to store the input provided by the user
	 * during the game.
	 */
	extern std::string selection;

	/**
	 * @var extern char turn
	 * @brief Indicates whose turn it is to play.
	 *
	 * This character can be either 'r' (Red) or 'b' (Black) to represent
	 * which player's turn it is.
	 */
	extern char turn;

	/**
	 * @var extern char captureDirection
	 * @brief Indicates the direction of capture.
	 *
	 * This character can be either 'R' (right) or 'L' (left) to specify
	 * the direction in which a capture is made.
	 */
	extern char captureDirection;

	/**
	 * @var extern char initialRowParity
	 * @brief Represents the parity of the initial row.
	 *
	 * This character can be either 'O' (odd) or 'E' (even), indicating the
	 * parity of the row where a move starts.
	 */
	extern char initialRowParity;

	/**
	 * @var extern bool wasCapture
	 * @brief Indicates if there was a capture this turn.
	 *
	 * This boolean is used to determine whether a capture has been made
	 * during the current turn.
	 */
	extern bool wasCapture;

	/**
	 * @var extern char loser
	 * @brief Indicates the loser of the game.
	 *
	 * This character can be either 'r' (Red), 'b' (Black) of 'x' (in case of draw),
	 * identifying which player has lost the game.
	 */
	extern char loser;

	/**
	 * @var extern int selector
	 * @brief Holds the game mode selected by the user.
	 *
	 * This integer stores the game mode selected by the user, which is used
	 * to determine the game's difficulty.
	 */
	extern int selector;

	/**
	 * @var extern int selected
	 * @brief Holds the vector address of the selected piece's square.
	 *
	 * This integer stores the index of the square in the 'squares' vector
	 * where the currently selected piece is located.
	 */
	extern int selected;

	/**
	 * @var extern int targeted
	 * @brief Holds the vector address of the target square for a piece's move.
	 *
	 * This integer stores the index of the square in the 'squares' vector
	 * where the currently selected piece is intended to move.
	 */
	extern int targeted;

	/**
	 * @var extern int inBetween
	 * @brief Holds the vector address of the square between the selected and targeted squares.
	 *
	 * This integer stores the index of the square in the 'squares' vector that
	 * lies between the selected and targeted squares, particularly in case of a capture move.
	 */
	extern int inBetween;

}
using namespace checkers;

/**
 * @namespace constants
 * @brief Namespace for defining constants used in the checkers game.
 */
namespace constants {
	/** @brief Constant for red game piece. */
	extern const char Red = 'r';

	/** @brief Constant for crowned red game piece. */
	extern const char cRed = 'R';

	/** @brief Constant for black game piece. */
	extern const char Black = 'b';

	/** @brief Constant for crowned black game piece. */
	extern const char cBlack = 'B';

	/** @brief Constant used in case of a tie. */
	extern const char Both = 'x';

	/** @brief Constant representing the left direction. */
	extern const char Left = 'L';

	/** @brief Constant representing the right direction. */
	extern const char Right = 'R';

	/** @brief Constant for odd number identifier. */
	extern const char Odd = 'O';

	/** @brief Constant for even number identifier. */
	extern const char Even = 'E';

	/** @brief The lowest valid subscript within a vector's range. */
	extern const int lowVectorRange = 0;

	// Constants representing board positions for promotion detection
	extern const int b8 = 28; ///< Position for b8 square.
	extern const int d8 = 29; ///< Position for d8 square.
	extern const int f8 = 30; ///< Position for f8 square.
	extern const int h8 = 31; ///< Position for h8 square.
	extern const int a1 = 0;  ///< Position for a1 square.
	extern const int c1 = 1;  ///< Position for c1 square.
	extern const int e1 = 2;  ///< Position for e1 square.
	extern const int g1 = 3;  ///< Position for g1 square.

	/**
	  * @brief Distance from start to landing square if piece starts on an odd row heading right.
	  *
	  * Represents the jump distance for a red piece when the first capture condition is true,
	  * starting from an odd row and moving right.
	  */
	extern const int rOddRightCapJmp = 9;

	/**
	 * @brief Distance from start to in-between square if piece starts on an odd row heading right.
	 *
	 * Represents the intermediate distance for a red piece under the first capture condition,
	 * starting from an odd row and moving right.
	 */
	extern const int rOddRightHafJmp = 4;

	/**
	 * @brief Red's second capture condition for even rows heading right.
	 *
	 * Represents the jump distance for a red piece when the second capture condition is true,
	 * starting from an even row and moving right.
	 */
	extern const int rEvenRightCapJmp = 9;

	/**
	 * @brief Intermediate jump distance for red's second capture condition on even rows.
	 *
	 * Represents the intermediate distance for a red piece under the second capture condition,
	 * starting from an even row and moving right.
	 */
	extern const int rEvenRightHafJmp = 5;

	/**
	 * @brief Red's third capture condition for odd rows heading left.
	 *
	 * Represents the jump distance for a red piece when the third capture condition is true,
	 * starting from an odd row and moving left.
	 */
	extern const int rOddLeftCapJmp = 7;

	/**
	 * @brief Intermediate jump distance for red's third capture condition on odd rows.
	 *
	 * Represents the intermediate distance for a red piece under the third capture condition,
	 * starting from an odd row and moving left.
	 */
	extern const int rOddLeftHafJmp = 3;

	/**
	 * @brief Red's fourth capture condition for even rows heading left.
	 *
	 * Represents the jump distance for a red piece when the fourth capture condition is true,
	 * starting from an even row and moving left.
	 */
	extern const int rEvenLeftCapJmp = 7;

	/**
	 * @brief Intermediate jump distance for red's fourth capture condition on even rows.
	 *
	 * Represents the intermediate distance for a red piece under the fourth capture condition,
	 * starting from an even row and moving left.
	 */
	extern const int rEvenLeftHafJmp = 4;

	/**
	 * @brief Black's first capture condition for odd rows heading left.
	 *
	 * Represents the jump distance for a black piece when the first capture condition is true,
	 * starting from an odd row and moving left.
	 */
	extern const int bOddLeftCapJmp = -9;

	/**
	 * @brief Intermediate jump distance for black's first capture condition on odd rows.
	 *
	 * Represents the intermediate distance for a black piece under the first capture condition,
	 * starting from an odd row and moving left.
	 */
	extern const int bOddLeftHafJmp = -5;

	/**
	 * @brief Black's second capture condition for even rows heading left.
	 *
	 * Represents the jump distance for a black piece when the second capture condition is true,
	 * starting from an even row and moving left.
	 */
	extern const int bEvenLeftCapJmp = -9;

	/**
	 * @brief Intermediate jump distance for black's second capture condition on even rows.
	 *
	 * Represents the intermediate distance for a black piece under the second capture condition,
	 * starting from an even row and moving left.
	 */
	extern const int bEvenLeftHafJmp = -4;

	/**
	 * @brief Black's third capture condition for odd rows heading right.
	 *
	 * Represents the jump distance for a black piece when the third capture condition is true,
	 * starting from an odd row and moving right.
	 */
	extern const int bOddRightCapJmp = -7;

	/**
	 * @brief Intermediate jump distance for black's third capture condition on odd rows.
	 *
	 * Represents the intermediate distance for a black piece under the third capture condition,
	 * starting from an odd row and moving right.
	 */
	extern const int bOddRightHafJmp = -4;

	/**
	 * @brief Black's fourth capture condition for even rows heading right.
	 *
	 * Represents the jump distance for a black piece when the fourth capture condition is true,
	 * starting from an even row and moving right.
	 */
	extern const int bEvenRightCapJmp = -7;

	/**
	 * @brief Intermediate jump distance for black's fourth capture condition on even rows.
	 *
	 * Represents the intermediate distance for a black piece under the fourth capture condition,
	 * starting from an even row and moving right.
	 */
	extern const int bEvenRightHafJmp = -3;

};
using namespace constants;

void abcd();
void Run_All_Tests();

/**
 * @brief Displays the game board.
 * @param sqVect: The vector of Square objects representing the game board.
 */
void displayBoard(const std::vector<Square>& sqVect);

/**
 * @brief Prepares the game for play.
 *
 * This function initializes the game by setting up the checkers board
 * and other necessary variables.
 */
void prepareGame();

/**
 * @brief Saves the game state to a file.
 *
 * @param squares: Pointer to the vector of Square objects representing the game board.
 * @param turn_: The current turn ('r' for Red, 'b' for Black).
 * @param selector_: The game mode selected by the user.
 * @return True if the game was successfully saved, false otherwise.
 */
bool saveGame(std::vector<Square>* squares, char turn_, int selector_);

/**
 * @brief Loads the game state from a file.
 *
 * This function loads the game state from a file and updates the provided
 * vector of squares, turn, and selector variables accordingly.
 *
 * @param squares: Pointer to the vector of squares representing the game board.
 * @param turn_: Pointer to the variable representing the current player's turn.
 * @param selector_: Pointer to the variable representing the game mode selected.
 * @return True if the game state was successfully loaded, false otherwise.
 */
bool loadGame(std::vector<Square>* squares, char* turn_, int* selector_);

/**
 * @brief Checks if a given string represents a valid square on the checkers board.
 * @param square: The string representing the square.
 * @return True if the string is a valid square, false otherwise.
 */
bool isSquare(std::string square);
void isSquare_Test();

/**
 * @brief Reverses the crown status of a given color.
 * @param color: The color character ('r' or 'b').
 * @return The crowned version of the color ('R' or 'B') if uncrowned, or the uncrowned version ('r' or 'b') if crowned.
 */
char reverseCrown(char color);
void reverseCrown_Test();

/**
 * @brief Checks if the current player cannot make any valid moves.
 * @return True if the current player cannot make any moves, false otherwise.
 */
bool cannotMakeMove();

/**
 * @brief Checks if a movement from the initial square to the target square is possible.
 * @param: initSq: Pointer to the initial square.
 * @return True if the movement is possible, false otherwise.
 */
bool possibleMovement(Square* initSq);
void possibleMovement_Test();

/**
 * @brief Gets the user's input for the square.
 *
 * This function gets the user's input for the square to select.
 * If the input is invalid, the function calls itself recursively.
 * Otherwise, the function returns.
 */
void getSquare();

/**
 * @brief Checks if a given string represents a valid square on the checkers board.
 * @param sq: The string representing the square.
 * @return True if the string is a valid square, false otherwise.
 */
bool goodSquare(std::string sq);
void goodSquare_Test();

/**
 * @brief Gets the user's input for the target square.
 *
 * This function gets the user's input for the target square.
 * If the input is invalid, the function calls itself recursively.
 * Otherwise, the function returns.
 */
void getTarget();

/**
 * @brief Checks if a given string represents a valid target square on the checkers board.
 * @param sq: The string representing the target square.
 * @return True if the string is a valid target square, false otherwise.
 */
bool goodTarget(std::string sq);
void goodTarget_Test();

/**
 * @brief Checks if the initial square is one square away from the target square in the forward direction.
 * @return True if the initial square is one square away from the target square in the forward direction, false otherwise.
 */
bool oneFrSqAway();
void oneFrSqAway_Test();

/**
 * @brief Checks if the initial square is one square away from the target square in the backward direction.
 * @return True if the initial square is one square away from the target square in the backward direction, false otherwise.
 */
bool oneBcSqAway();
void oneBcSqAway_Test();

/**
 * @brief Checks if the initial square is two squares away from the target square in the forward direction.
 * @return True if the initial square is two squares away from the target square in the forward direction, false otherwise.
 */
bool twoFrSqAway();
void twoFrSqAway_Test();

/**
 * @brief Checks if the initial square is two squares away from the target square in the backward direction.
 * @return True if the initial square is two squares away from the target square in the backward direction, false otherwise.
 */
bool twoBcSqAway();
void twoBcSqAway_Test();

/**
 * @brief Gets the index of the square in the 'squares' vector based on its name.
 * @param sq: The name of the square.
 * @return The index of the square in the 'squares' vector.
 */
int getAddress(std::string sq);
void getAddress_Test();

/**
 * @brief Gets the letter coordinate of a square.
 * @param sq1: The name of the square.
 * @return The letter coordinate of the square.
 */
char getLetCoordinate(std::string sq1);
void getLetCoordinate_Test();

/**
 * @brief Gets the name of the square between the initial square and the target square.
 * @param initSq: Pointer to the initial square.
 * @param targetSq: Pointer to the target square.
 * @return The name of the square between the initial square and the target square.
 */
std::string getSqInBetween(Square* initSq, Square* targetSq);
void getSqInBetween_Test();

/**
 * @brief Gets the direction of capture between the initial square and the target square.
 * @param initSq: Pointer to the initial square.
 * @param targetSq: Pointer to the target square.
 * @return The direction of capture ('R' for right, 'L' for left).
 */
char getCapDirection(std::string* initSq, std::string* targetSq);
void getCapDirection_Test();

/**
 * @brief Gets the parity (oddness or evenness) of a row.
 * @param row: The row number.
 * @return The parity of the row ('O' for odd, 'E' for even).
 */
char getRowParity(char row);
void getRowParity_Test();

/**
 * @brief Checks if the capture is going upward (from our view) for a crowned piece.
 * @param initSq: Pointer to the initial square.
 * @param targetSq: Pointer to the target square.
 * @return True if the capture is going upward, false otherwise.
 */
bool upCapture(Square* initSq, Square* targetSq);
void upCapture_Test();

/**
 * @brief Checks if the capture is going downward for a crowned piece.
 * @param initSq: Pointer to the initial square.
 * @param targetSq: Pointer to the target square.
 * @return True if the capture is going downward, false otherwise.
 */
bool downCapture(Square* initSq, Square* targetSq);
void downCapture_Test();

/**
 * @brief Checks if the first capture condition for red pieces is met.
 * @return True if the first capture condition is met, false otherwise.
 */
bool R_Capture1();
void R_Capture1_Test();

/**
 * @brief Checks if the second capture condition for red pieces is met.
 * @return True if the second capture condition is met, false otherwise.
 */
bool R_Capture2();
void R_Capture2_Test();

/**
 * @brief Checks if the third capture condition for red pieces is met.
 * @return True if the third capture condition is met, false otherwise.
 */
bool R_Capture3();
void R_Capture3_Test();

/**
 * @brief Checks if the fourth capture condition for red pieces is met.
 * @return True if the fourth capture condition is met, false otherwise.
 */
bool R_Capture4();
void R_Capture4_Test();

/**
 * @brief Checks if the first capture condition for black pieces is met.
 * @return True if the first capture condition is met, false otherwise.
 */
bool B_Capture1();
void B_Capture1_Test();

/**
 * @brief Checks if the second capture condition for black pieces is met.
 * @return True if the second capture condition is met, false otherwise.
 */
bool B_Capture2();
void B_Capture2_Test();

/**
 * @brief Checks if the third capture condition for black pieces is met.
 * @return True if the third capture condition is met, false otherwise.
 */
bool B_Capture3();
void B_Capture3_Test();

/**
 * @brief Checks if the fourth capture condition for black pieces is met.
 * @return True if the fourth capture condition is met, false otherwise.
 */
bool B_Capture4();
void B_Capture4_Test();

/**
 * @brief Gets the opposite color of a given color.
 * @param color: The color character ('r' or 'b').
 * @return The opposite color character ('b' or 'r').
 */
char oppoColor(char color);
void oppoColor_Test();

/**
 * @brief Checks if a capture is occurring.
 * @return True if a capture is occurring, false otherwise.
 */
bool isCapture();
void isCapture_Test();

/**
 * @brief Updates the checkers board after a move.
 */
void updateBoard();

/**
 * @brief Checks if a promotion (to a crowned piece) is occurring.
 * @return True if a promotion is occurring, false otherwise.
 */
bool isPromotion();
void isPromotion_Test();

/**
 * @brief Checks if a capture is possible from the initial square.
 * @param initSq: Pointer to the initial square.
 * @return True if a capture is possible, false otherwise.
 */
bool possibleCapture(Square* initSq);
void possibleCapture_Test();

/**
 * @brief Gets the user's input for the target square in consecutive captures.
 */
void getConsecutiveJmpTarget();

/**
 * @brief Checks if a given string represents a valid target square in consecutive captures.
 * @param sq: The string representing the target square.
 * @return True if the string is a valid target square, false otherwise.
 */
bool goodConsecutiveJmpTarget(std::string sq);
void goodConsecutiveJmpTarget_Test();

/**
 * @brief Displays the help information.
 */
void displayHelp();

/**
 * @brief Displays the main menu.
 */
void displayMenu();

/**
 * @brief Displays the game mode options.
 */
void displayMods();

/**
 * @brief Handles the player's turn.
 */
void playerTurn();

/**
 * @brief Handles the AI's turn.
 */
void AI_Turn();

/**
 * @brief Checks if the game is over.
 * @return True if the game is over, false otherwise.
 */
bool gameOver();
void gameOver_Test();

/**
 * @brief Handles the end of the game.
 *
 *
 */
void checkersGame(int selector_);

/**
 * @brief Handles the loss of a player.
 */
void handleLoss();

/**
 * @brief Asks the player if they want to play again.
 * @return True if the player wants to play again, false otherwise.
 */
bool playAgain();

/**
 * @brief Exits the game.
 */
void exit();

/**
 * @brief Shuffles an array.
 * @param array: The array to shuffle.
 * @param size: The size of the array.
 */
void shuffleArray(int* array, int size);
void shuffleArray_Test();

/**
 * @brief Displays an error message.
 * @param message: The error message to display.
 */
void error(std::string message);


std::vector<Square> checkers::squares(32, Square(' ', "a1", '1')); //initialized to "a1" and '1' to get through 
//constructor's error handling
std::string checkers::selection = " "; //all input by the user is held by this variable
char checkers::turn = ' '; //either 'r' (Red) or 'b' (Black)
char checkers::captureDirection = ' '; //either 'R' (right) or 'L' (left)
char checkers::initialRowParity = ' '; //either 'O' (odd) or 'E' (even)
bool checkers::wasCapture = false; //was there a capture this turn?
//used to determine whether to check for consecutive capture
char checkers::loser = ' '; //either 'r' (Red) or 'b' (Black)
//who is the loser?

int checkers::selector = 0;
//for vector location:
int checkers::selected = 0; //holds vector address of square of selected piece
int checkers::targeted = 0; //holds vector address of square to move a piece to
int checkers::inBetween = 0; //holds vector address of square in between the
//selected and targeted squares (in case of capture)

int main()
try {
	static bool test_run = false;
	if (!test_run)
	{
		Run_All_Tests();
		test_run = true;
		system("cls");
	}
	displayMenu();
	std::cout << ">> ";
	std::cin >> selection;
	//new game
	if (selection == "1")
	{
		displayMods();
		std::cout << ">> ";
		std::cin >> selection;
		if (selection == "1" || selection == "2" || selection == "3")
		{
			//int selector = std::stoi(selection);
			selector = std::stoi(selection);
			prepareGame();
			checkersGame(selector);
		}

	}
	//load previous game
	else if (selection == "2")
	{
		if (!loadGame(&squares, &turn, &selector)) { main(); }
		checkersGame(selector);
	}
	//display help
	else if (selection == "3")
	{
		displayHelp(); main();
	}
	//exit
	else if (selection == "4")
	{
		return 0;
	}
	else if (selection == "h" || selection == "help")
	{
		displayHelp(); main();
	}
	else
	{
		std::cout << "Invalid input.\n";
		main();
	}
	return 0;
}
catch (std::string message) {
	std::cerr << message << '\n';
	exit();
	return 1;
}
catch (...) {
	std::cerr << "Unknown exception\n";
	exit();
	return 2;
}

void abcd()
{
	std::cout << "abcd";
}

void Run_All_Tests()
{
	isSquare_Test();
	reverseCrown_Test();
	possibleMovement_Test();
	goodSquare_Test();
	goodTarget_Test();
	oneFrSqAway_Test();
	oneBcSqAway_Test();
	twoFrSqAway_Test();
	twoBcSqAway_Test();
	getAddress_Test();
	getLetCoordinate_Test();
	getSqInBetween_Test();
	getCapDirection_Test();
	getRowParity_Test();
	upCapture_Test();
	downCapture_Test();
	R_Capture1_Test();
	R_Capture2_Test();
	R_Capture3_Test();
	R_Capture4_Test();
	B_Capture1_Test();
	B_Capture2_Test();
	B_Capture3_Test();
	B_Capture4_Test();
	oppoColor_Test();
	isCapture_Test();
	isPromotion_Test();
	possibleCapture_Test();
	goodConsecutiveJmpTarget_Test();
	gameOver_Test();
	shuffleArray_Test();

	std::cout << "All tests passed!\n";
	Sleep(1500);
}

void Square::changeColor(char newColor) {
	if (c != newColor) c = newColor;
}

Square::Square() {
	c = ' ';
	s = "a1";
	r = '1';
	frtAdjSqs = setFrtAdjSqs(s);
	bacAdjSqs = setBacAdjSqs(s);
	frtJmpSqs = setFrtJmpSqs(s);
	bacJmpSqs = setBacJmpSqs(s);
	crowned = false;
	captured = false;
	return;
}

Square::Square(char c_, std::string s_, char r_)
	:c(c_), s(s_), r(r_)
{
	//the 5 vector members (frtAdjSqs, bacAdjSqs, etc.) are
	//not in the arguments because they are dependent on std::string s_

	//check for constructor errors:
	if (c_ != Red && c_ != cRed && c_ != Black && c_ != cBlack && c_ != ' ')
		error("Exception: constructor use without correct color ('r','R','b','B',' ')");
	if (!isSquare(s_))
		error("Exception: constructor use without correct square");
	switch (r_) {
	case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':
		break;
	default:
		error("Exception: constructor use without correct row");
	}

	//initialize 7 other members
	frtAdjSqs = setFrtAdjSqs(s);
	bacAdjSqs = setBacAdjSqs(s);
	frtJmpSqs = setFrtJmpSqs(s);
	bacJmpSqs = setBacJmpSqs(s);
	if (c_ == cRed || c_ == cBlack)
		crowned = true; //'R' and 'B' indicate the piece is crowned
	else
		crowned = false;  //'r' and 'b' (and ' ') indicate the piece is uncrowned
	captured = false;
	return;
}

std::vector<std::string> Square::setFrtAdjSqs(std::string sq) {
	//sets std::vector<std::string> frtAdjSqs

	std::vector<std::string> sqs(2, " "); //holds the squares to give to frtAdjSqs

	if (sq == "a1") { sqs[0] = "b2"; return sqs; }
	if (sq == "a3") { sqs[0] = "b4"; return sqs; }
	if (sq == "a5") { sqs[0] = "b6"; return sqs; }
	if (sq == "a7") { sqs[0] = "b8"; return sqs; }

	if (sq == "b2") { sqs[0] = "a3"; sqs[1] = "c3"; return sqs; }
	if (sq == "b4") { sqs[0] = "a5"; sqs[1] = "c5"; return sqs; }
	if (sq == "b6") { sqs[0] = "a7"; sqs[1] = "c7"; return sqs; }
	if (sq == "b8") return sqs;	//a piece on b8 cannot move forward

	if (sq == "c1") { sqs[0] = "b2"; sqs[1] = "d2"; return sqs; }
	if (sq == "c3") { sqs[0] = "b4"; sqs[1] = "d4"; return sqs; }
	if (sq == "c5") { sqs[0] = "b6"; sqs[1] = "d6"; return sqs; }
	if (sq == "c7") { sqs[0] = "b8"; sqs[1] = "d8"; return sqs; }

	if (sq == "d2") { sqs[0] = "c3"; sqs[1] = "e3"; return sqs; }
	if (sq == "d4") { sqs[0] = "c5"; sqs[1] = "e5"; return sqs; }
	if (sq == "d6") { sqs[0] = "c7"; sqs[1] = "e7"; return sqs; }
	if (sq == "d8") return sqs;	//a piece on d8 cannot move forward

	if (sq == "e1") { sqs[0] = "d2"; sqs[1] = "f2"; return sqs; }
	if (sq == "e3") { sqs[0] = "d4"; sqs[1] = "f4"; return sqs; }
	if (sq == "e5") { sqs[0] = "d6"; sqs[1] = "f6"; return sqs; }
	if (sq == "e7") { sqs[0] = "d8"; sqs[1] = "f8"; return sqs; }

	if (sq == "f2") { sqs[0] = "e3"; sqs[1] = "g3"; return sqs; }
	if (sq == "f4") { sqs[0] = "e5"; sqs[1] = "g5"; return sqs; }
	if (sq == "f6") { sqs[0] = "e7"; sqs[1] = "g7"; return sqs; }
	if (sq == "f8") return sqs;	//a piece on f8 cannot move forward

	if (sq == "g1") { sqs[0] = "f2"; sqs[1] = "h2"; return sqs; }
	if (sq == "g3") { sqs[0] = "f4"; sqs[1] = "h4"; return sqs; }
	if (sq == "g5") { sqs[0] = "f6"; sqs[1] = "h6"; return sqs; }
	if (sq == "g7") { sqs[0] = "f8"; sqs[1] = "h8"; return sqs; }

	if (sq == "h2") { sqs[0] = "g3"; return sqs; }
	if (sq == "h4") { sqs[0] = "g5"; return sqs; }
	if (sq == "h6") { sqs[0] = "g7"; return sqs; }
	if (sq == "h8") return sqs;	//a piece on h8 cannot move forward

	error("Exception: constructor use without an accessible square");
}

std::vector<std::string> Square::setBacAdjSqs(std::string sq) {
	//sets std::vector<std::string> bacAdjSqs

	std::vector<std::string> sqs(2, " "); //holds the squares to give to bacAdjSqs

	if (sq == "a1") return sqs;	//a piece on a1 cannot move backward
	if (sq == "a3") { sqs[0] = "b2"; return sqs; }
	if (sq == "a5") { sqs[0] = "b4"; return sqs; }
	if (sq == "a7") { sqs[0] = "b6"; return sqs; }

	if (sq == "b2") { sqs[0] = "a1"; sqs[1] = "c1"; return sqs; }
	if (sq == "b4") { sqs[0] = "a3"; sqs[1] = "c3"; return sqs; }
	if (sq == "b6") { sqs[0] = "a5"; sqs[1] = "c5"; return sqs; }
	if (sq == "b8") { sqs[0] = "a7"; sqs[1] = "c7"; return sqs; }

	if (sq == "c1") return sqs;	//a piece on c1 cannot move backward
	if (sq == "c3") { sqs[0] = "b2"; sqs[1] = "d2"; return sqs; }
	if (sq == "c5") { sqs[0] = "b4"; sqs[1] = "d4"; return sqs; }
	if (sq == "c7") { sqs[0] = "b6"; sqs[1] = "d6"; return sqs; }

	if (sq == "d2") { sqs[0] = "c1"; sqs[1] = "e1"; return sqs; }
	if (sq == "d4") { sqs[0] = "c3"; sqs[1] = "e3"; return sqs; }
	if (sq == "d6") { sqs[0] = "c5"; sqs[1] = "e5"; return sqs; }
	if (sq == "d8") { sqs[0] = "c7"; sqs[1] = "e7"; return sqs; }

	if (sq == "e1") return sqs;	//a piece on e1 cannot move backward
	if (sq == "e3") { sqs[0] = "d2"; sqs[1] = "f2"; return sqs; }
	if (sq == "e5") { sqs[0] = "d4"; sqs[1] = "f4"; return sqs; }
	if (sq == "e7") { sqs[0] = "d6"; sqs[1] = "f6"; return sqs; }

	if (sq == "f2") { sqs[0] = "e1"; sqs[1] = "g1"; return sqs; }
	if (sq == "f4") { sqs[0] = "e3"; sqs[1] = "g3"; return sqs; }
	if (sq == "f6") { sqs[0] = "e5"; sqs[1] = "g5"; return sqs; }
	if (sq == "f8") { sqs[0] = "e7"; sqs[1] = "g7"; return sqs; }

	if (sq == "g1") return sqs;	//a piece on g1 cannot move backward
	if (sq == "g3") { sqs[0] = "f2"; sqs[1] = "h2"; return sqs; }
	if (sq == "g5") { sqs[0] = "f4"; sqs[1] = "h4"; return sqs; }
	if (sq == "g7") { sqs[0] = "f6"; sqs[1] = "h6"; return sqs; }

	if (sq == "h2") { sqs[0] = "g1"; return sqs; }
	if (sq == "h4") { sqs[0] = "g3"; return sqs; }
	if (sq == "h6") { sqs[0] = "g5"; return sqs; }
	if (sq == "h8") { sqs[0] = "g7"; return sqs; }

	error("Exception: constructor use without an accessible square");
}

std::vector<std::string> Square::setFrtJmpSqs(std::string sq) {
	//sets std::vector<std::string> frtJmpSqs

	std::vector<std::string> sqs(2, " "); //holds the squares to give to frtJmpSqs

	if (sq == "a1") { sqs[0] = "c3"; return sqs; }
	if (sq == "a3") { sqs[0] = "c5"; return sqs; }
	if (sq == "a5") { sqs[0] = "c7"; return sqs; }
	if (sq == "a7") return sqs;	//a piece on a7 cannot jump forward

	if (sq == "b2") { sqs[0] = "d4"; return sqs; }
	if (sq == "b4") { sqs[0] = "d6"; return sqs; }
	if (sq == "b6") { sqs[0] = "d8"; return sqs; }
	if (sq == "b8") return sqs;	//a piece on b8 cannot jump forward

	if (sq == "c1") { sqs[0] = "a3"; sqs[1] = "e3"; return sqs; }
	if (sq == "c3") { sqs[0] = "a5"; sqs[1] = "e5"; return sqs; }
	if (sq == "c5") { sqs[0] = "a7"; sqs[1] = "e7"; return sqs; }
	if (sq == "c7") return sqs;	//a piece on c7 cannot jump forward

	if (sq == "d2") { sqs[0] = "b4"; sqs[1] = "f4"; return sqs; }
	if (sq == "d4") { sqs[0] = "b6"; sqs[1] = "f6"; return sqs; }
	if (sq == "d6") { sqs[0] = "b8"; sqs[1] = "f8"; return sqs; }
	if (sq == "d8") return sqs;	//a piece on d8 cannot jump forward

	if (sq == "e1") { sqs[0] = "c3"; sqs[1] = "g3"; return sqs; }
	if (sq == "e3") { sqs[0] = "c5"; sqs[1] = "g5"; return sqs; }
	if (sq == "e5") { sqs[0] = "c7"; sqs[1] = "g7"; return sqs; }
	if (sq == "e7") return sqs;	//a piece on e7 cannot jump forward

	if (sq == "f2") { sqs[0] = "d4"; sqs[1] = "h4"; return sqs; }
	if (sq == "f4") { sqs[0] = "d6"; sqs[1] = "h6"; return sqs; }
	if (sq == "f6") { sqs[0] = "d8"; sqs[1] = "h8"; return sqs; }
	if (sq == "f8") return sqs;	//a piece on f8 cannot jump forward

	if (sq == "g1") { sqs[0] = "e3"; return sqs; }
	if (sq == "g3") { sqs[0] = "e5"; return sqs; }
	if (sq == "g5") { sqs[0] = "e7"; return sqs; }
	if (sq == "g7") return sqs;	//a piece on g7 cannot jump forward

	if (sq == "h2") { sqs[0] = "f4"; return sqs; }
	if (sq == "h4") { sqs[0] = "f6"; return sqs; }
	if (sq == "h6") { sqs[0] = "f8"; return sqs; }
	if (sq == "h8") return sqs;	//a piece on h8 cannot jump forward

	error("Exception: constructor use without an accessible square");
}

std::vector<std::string> Square::setBacJmpSqs(std::string sq) {
	//sets std::vector<std::string> bacJmpSqs

	std::vector<std::string> sqs(2, " "); //holds the squares to give to bacJumpSqs

	if (sq == "a1") return sqs;	//a crowned piece on a1 cannot jump backward
	if (sq == "a3") { sqs[0] = "c1"; return sqs; }
	if (sq == "a5") { sqs[0] = "c3"; return sqs; }
	if (sq == "a7") { sqs[0] = "c5"; return sqs; }

	if (sq == "b2") return sqs;	//a crowned piece on b2 cannot jump backward
	if (sq == "b4") { sqs[0] = "d2"; return sqs; }
	if (sq == "b6") { sqs[0] = "d4"; return sqs; }
	if (sq == "b8") { sqs[0] = "d6"; return sqs; }

	if (sq == "c1") return sqs;	//a crowned piece on c1 cannot jump backward
	if (sq == "c3") { sqs[0] = "a1"; sqs[1] = "e1"; return sqs; }
	if (sq == "c5") { sqs[0] = "a3"; sqs[1] = "e3"; return sqs; }
	if (sq == "c7") { sqs[0] = "a5"; sqs[1] = "e5"; return sqs; }

	if (sq == "d2") return sqs;	//a crowned piece on d2 cannot jump backward
	if (sq == "d4") { sqs[0] = "b2"; sqs[1] = "f2"; return sqs; }
	if (sq == "d6") { sqs[0] = "b4"; sqs[1] = "f4"; return sqs; }
	if (sq == "d8") { sqs[0] = "b6"; sqs[1] = "f6"; return sqs; }

	if (sq == "e1") return sqs;	//a crowned piece on e1 cannot jump backward
	if (sq == "e3") { sqs[0] = "c1"; sqs[1] = "g1"; return sqs; }
	if (sq == "e5") { sqs[0] = "c3"; sqs[1] = "g3"; return sqs; }
	if (sq == "e7") { sqs[0] = "c5"; sqs[1] = "g5"; return sqs; }

	if (sq == "f2") return sqs;	//a crowned piece on f2 cannot jump backward
	if (sq == "f4") { sqs[0] = "d2"; sqs[1] = "h2"; return sqs; }
	if (sq == "f6") { sqs[0] = "d4"; sqs[1] = "h4"; return sqs; }
	if (sq == "f8") { sqs[0] = "d6"; sqs[1] = "h6"; return sqs; }

	if (sq == "g1") return sqs;	//a crowned piece on g1 cannot jump backward
	if (sq == "g3") { sqs[0] = "e1"; return sqs; }
	if (sq == "g5") { sqs[0] = "e3"; return sqs; }
	if (sq == "g7") { sqs[0] = "e5"; return sqs; }

	if (sq == "h2") return sqs;	//a crowned piece on h2 cannot jump backward
	if (sq == "h4") { sqs[0] = "f2"; return sqs; }
	if (sq == "h6") { sqs[0] = "f4"; return sqs; }
	if (sq == "h8") { sqs[0] = "f6"; return sqs; }

	error("Exception: constructor use without an accessible square");
}

void displayBoard(const std::vector<Square>& sqVect) {
	system("cls");

	std::cout << '\n'
		<< "     | " << sqVect[28].color() << " |   | " << sqVect[29].color() << " |   | " << sqVect[30].color() << " |   | " << sqVect[31].color() << '\n'
		<< "8 ___|___|___|___|___|___|___|___\n"
		<< "   " << sqVect[24].color() << " |   | " << sqVect[25].color() << " |   | " << sqVect[26].color() << " |   | " << sqVect[27].color() << " |\n"
		<< "7 ___|___|___|___|___|___|___|___\n"
		<< "     | " << sqVect[20].color() << " |   | " << sqVect[21].color() << " |   | " << sqVect[22].color() << " |   | " << sqVect[23].color() << '\n'
		<< "6 ___|___|___|___|___|___|___|___\n"
		<< "   " << sqVect[16].color() << " |   | " << sqVect[17].color() << " |   | " << sqVect[18].color() << " |   | " << sqVect[19].color() << " |\n"
		<< "5 ___|___|___|___|___|___|___|___\n"
		<< "     | " << sqVect[12].color() << " |   | " << sqVect[13].color() << " |   | " << sqVect[14].color() << " |   | " << sqVect[15].color() << '\n'
		<< "4 ___|___|___|___|___|___|___|___\n"
		<< "   " << sqVect[8].color() << " |   | " << sqVect[9].color() << " |   | " << sqVect[10].color() << " |   | " << sqVect[11].color() << " |\n"
		<< "3 ___|___|___|___|___|___|___|___\n"
		<< "     | " << sqVect[4].color() << " |   | " << sqVect[5].color() << " |   | " << sqVect[6].color() << " |   | " << sqVect[7].color() << '\n'
		<< "2 ___|___|___|___|___|___|___|___\n"
		<< "   " << sqVect[0].color() << " |   | " << sqVect[1].color() << " |   | " << sqVect[2].color() << " |   | " << sqVect[3].color() << " |\n"
		<< "1 ___|___|___|___|___|___|___|___\n"
		<< "   a   b   c   d   e   f   g   h \n"
		<< '\n';
	return;
}

void prepareGame() {
	//prepare variables:
	selection = " ";
	turn = Red;
	captureDirection = ' ';
	initialRowParity = ' ';
	wasCapture = false;
	loser = ' ';
	selected = 0;
	targeted = 0;
	inBetween = 0;

	//prepare squares and pieces:
	squares[0] = Square(Red, "a1", '1'); squares[1] = Square(Red, "c1", '1');
	squares[2] = Square(Red, "e1", '1'); squares[3] = Square(Red, "g1", '1');
	squares[4] = Square(Red, "b2", '2'); squares[5] = Square(Red, "d2", '2');
	squares[6] = Square(Red, "f2", '2'); squares[7] = Square(Red, "h2", '2');
	squares[8] = Square(Red, "a3", '3'); squares[9] = Square(Red, "c3", '3');
	squares[10] = Square(Red, "e3", '3'); squares[11] = Square(Red, "g3", '3');
	squares[12] = Square(' ', "b4", '4'); squares[13] = Square(' ', "d4", '4');
	squares[14] = Square(' ', "f4", '4'); squares[15] = Square(' ', "h4", '4');
	squares[16] = Square(' ', "a5", '5'); squares[17] = Square(' ', "c5", '5');
	squares[18] = Square(' ', "e5", '5'); squares[19] = Square(' ', "g5", '5');
	squares[20] = Square(Black, "b6", '6'); squares[21] = Square(Black, "d6", '6');
	squares[22] = Square(Black, "f6", '6'); squares[23] = Square(Black, "h6", '6');
	squares[24] = Square(Black, "a7", '7'); squares[25] = Square(Black, "c7", '7');
	squares[26] = Square(Black, "e7", '7'); squares[27] = Square(Black, "g7", '7');
	squares[28] = Square(Black, "b8", '8'); squares[29] = Square(Black, "d8", '8');
	squares[30] = Square(Black, "f8", '8'); squares[31] = Square(Black, "h8", '8');
	return;
}

bool saveGame(std::vector<Square>* squares, char turn_, int selector_) {
	std::ofstream saveFile;
	std::cout << "Enter name of file where you want to save game\n";
	std::cout << ">> ";
	std::cin >> selection;
	//check if file ends in .ini
	if (selection.substr(selection.find_last_of(".") + 1) != "ini")
	{
		std::cout << "File must be in .ini format\n";
		return false;
	}
	saveFile.open(selection);
	if (saveFile.is_open())
	{
		saveFile << "[Game]\nTurn=" << turn_ << "\n\n";
		saveFile << "[Selector]\nSelector=" << selector_ << "\n\n";

		for (size_t i = 0; i < squares->size(); ++i) {
			saveFile << "[Square" << i << "]\n";
			saveFile << "Color=" << squares->at(i).color() << "\n";
			saveFile << "Square=" << squares->at(i).square() << "\n";
			saveFile << "Row=" << squares->at(i).row() << "\n\n";
		}
		saveFile.close();
	}
	else
	{
		std::cout << "Unable to open file\n";
		return false;
	}

	return true;
}

bool loadGame(std::vector<Square>* squares, char* turn_, int* selector_) {
	std::ifstream loadFile;
	std::cout << "Enter name of file:\n";
	std::cout << ">> ";
	std::cin >> selection;
	loadFile.open(selection);
	std::string line;
	size_t squareIndex = 0;

	if (loadFile.is_open()) {
		while (getline(loadFile, line)) {
			if (line.find("Turn=") != std::string::npos) {
				*turn_ = line.substr(line.find("=") + 1)[0];
			}
			else if (line.find("Selector=") != std::string::npos) {
				*selector_ = std::stoi(line.substr(line.find("=") + 1));
			}
			else if (line.find("[Square") != std::string::npos) {
				char color;
				std::string square;
				char row;

				getline(loadFile, line); // Color line
				color = line.substr(line.find("=") + 1)[0];

				getline(loadFile, line); // Square line
				square = line.substr(line.find("=") + 1);

				getline(loadFile, line); // Row line
				row = line.substr(line.find("=") + 1)[0];

				if (squareIndex < squares->size()) {
					squares->at(squareIndex) = Square(color, square, row);
					squareIndex++;
				}
			}
		}
		loadFile.close();
	}
	else
	{
		std::cout << "Unable to open file\n";
		return false;
	}

	captureDirection = ' ';
	initialRowParity = ' ';
	wasCapture = false;
	loser = ' ';
	selected = 0;
	targeted = 0;
	inBetween = 0;

	return true;
}

bool isSquare(std::string sq) {
	//only used in constructor
	if (sq == "a1" || sq == "c1" || sq == "e1" || sq == "g1"
		|| sq == "b2" || sq == "d2" || sq == "f2" || sq == "h2"
		|| sq == "a3" || sq == "c3" || sq == "e3" || sq == "g3"
		|| sq == "b4" || sq == "d4" || sq == "f4" || sq == "h4"
		|| sq == "a5" || sq == "c5" || sq == "e5" || sq == "g5"
		|| sq == "b6" || sq == "d6" || sq == "f6" || sq == "h6"
		|| sq == "a7" || sq == "c7" || sq == "e7" || sq == "g7"
		|| sq == "b8" || sq == "d8" || sq == "f8" || sq == "h8") return true;
	return false;
}

void isSquare_Test()
{
	std::string test_square = "a1";
	// Test case 1: Square is valid
	assert(isSquare(test_square));

	// Test case 2: Square is invalid
	test_square = "z9";
	assert(!isSquare(test_square));

	// Test case 3: Square is valid
	test_square = "h8";
	assert(isSquare(test_square));

	// Test case 4: Square is invalid
	test_square = "e9";
	assert(!isSquare(test_square));

	// Test case 5: Square is valid
	test_square = "c3";
	assert(isSquare(test_square));

	// Test case 6: Square is invalid
	test_square = "d0";
	assert(!isSquare(test_square));

	// Test case 7: Square is valid
	test_square = "g7";
	assert(isSquare(test_square));

	// Test case 8: Square is invalid
	test_square = "i7";
	assert(!isSquare(test_square));

	// Test case 9: Square is valid
	test_square = "f4";
	assert(isSquare(test_square));

	// Test case 10: Square is invalid
	test_square = "j2";
	assert(!isSquare(test_square));

	std::cout << "isSquare(): All test cases passed!\n";
	Sleep(25);
}

char reverseCrown(char color) {
	//returns either the crowned version of a color ('R' or 'B')
	//or uncrowned version ('r' or 'b')
	if (color == Red) return cRed;
	if (color == Black) return cBlack;
	if (color == cRed) return Red;
	if (color == cBlack) return Black;
	error("Exception: reverseCrown() used on a char that is not 'r', 'b', 'R', or 'B'\n");
}

void reverseCrown_Test()
{
	// Test case 1: Color is Red
	assert(reverseCrown(Red) == cRed);

	// Test case 2: Color is Black
	assert(reverseCrown(Black) == cBlack);

	// Test case 3: Color is cRed
	assert(reverseCrown(cRed) == Red);

	// Test case 4: Color is cBlack
	assert(reverseCrown(cBlack) == Black);

	// Test case 5: Color is Red, cBlack is expected to error
	assert(!(reverseCrown(Red) == cBlack));

	// Test case 6: Color is Black, cRed is expected to error
	assert(!(reverseCrown(Black) == cRed));

	// Test case 7: Color is cRed, Black is expected to error
	assert(!(reverseCrown(cRed) == Black));

	// Test case 8: Color is cBlack, Red is expected to error
	assert(!(reverseCrown(cBlack) == Red));

	std::cout << "reverseCrown(): All test cases passed!\n";
	Sleep(25);
}

bool cannotMakeMove() {
	for (size_t i = 0; i < squares.size(); ++i)
	{
		if (possibleMovement(&squares[i]))
		{
			return false; //a move is possible
		}
		if (possibleCapture(&squares[i])) return false;
	}
	return true;
}

bool possibleMovement(Square* initSq) {
	//can the piece on initSq move one square?

	//if initSq's color is wrong, return false
	if (turn != initSq->color() && reverseCrown(turn) != initSq->color())
	{
		return false;
	}

	switch (initSq->color()) {
	case Red:
		//if red, can the piece move one square forward
		for (size_t i = 0; i < initSq->getFrtAdjSqs().size(); ++i)
		{
			//size_t i holds the address of an adjacent square
			//check if the square with the same address as the
			//adjacent square is blank (meaning a piece can move
			//there and movement is possible)
			if (initSq->getFrtAdjSqs()[i] != " " && //prevent using getAddress on non-square
				squares[getAddress(initSq->getFrtAdjSqs()[i])].color() == ' ')
			{
				return true;
			}
		}
		break;
	case Black:
		//if black, can the piece move one square backward (from our view)
		for (size_t i = 0; i < initSq->getBacAdjSqs().size(); ++i)
		{
			//size_t i holds the address of an adjacent square
			//check if the square with the same address as the
			//adjacent square is blank (meaning a piece can move
			//there and movement is possible)
			if (initSq->getBacAdjSqs()[i] != " " && //prevent using getAddress on non-square
				squares[getAddress(initSq->getBacAdjSqs()[i])].color() == ' ')
			{
				return true;
			}
		}
		break;
	case cRed: case cBlack:
		//if crowned, can the piece move one square any direction
		for (size_t i = 0; i < initSq->getFrtAdjSqs().size(); ++i) //here, size() returns 2 and works for both
			//getFrtAdjSqs and getBacAdjSqs
		{
			//size_t i holds the address of an adjacent square
			//check if the square with the same address as the
			//adjacent square is blank (meaning a piece can move
			//there and movement is possible)
			if (initSq->getFrtAdjSqs()[i] != " " && //prevent using getAddress on non-square
				squares[getAddress(initSq->getFrtAdjSqs()[i])].color() == ' ')
			{
				return true;
			}
			if (initSq->getBacAdjSqs()[i] != " " && //prevent using getAddress on non-square
				squares[getAddress(initSq->getBacAdjSqs()[i])].color() == ' ')
			{
				return true;
			}
		}
		break;
	}
	return false;
}

void possibleMovement_Test()
{
	prepareGame();
	// Test case 1: Square is Red, movement is possible
	assert(possibleMovement(&squares[9]));

	// Test case 2: Square is Black, movement is impossible
	assert(!possibleMovement(&squares[20]));

	// Test case 4: Square is Black, movement is impossible
	assert(!possibleMovement(&squares[31]));

	// Test case 3: Square is Red, movement is possible
	assert(possibleMovement(&squares[11]));

	std::cout << "possibleMovement(): All test cases passed!\n";
	Sleep(25);
}

void getSquare() {
	std::cout << "Current turn: " << turn << "\n";
	std::cout << "Enter coordinate of piece you want to move (ex. a1, f8):\n";
	std::cin >> selection;
	// selection = get_GUI_Input();
	// std::cout << selection << std::endl;

	//std::cout << selection << '\n';
	if (selection == "h" || selection == "help")
	{
		displayHelp(); getSquare();
	}
	if (selection == "d" || selection == "display")
	{
		displayBoard(squares); getSquare();
	}
	if (selection == "sv" || selection == "save")
	{
		if (!saveGame(&squares, turn, selector))
		{
			std::cout << "Save failed.\n";
		}
		getSquare();
	}
	if (selection == "r" || selection == "reset")
	{
		displayBoard(squares); std::cout << "\nCannot reset! No selected piece.\n"; getSquare();
	}
	if (selection == "q" || selection == "quit") return;
	if (!goodSquare(selection)) getSquare();
	return;
}

bool goodSquare(std::string sq) {
	//checks if color of piece on the square is correct and
	//if square is accessible

	if (!isSquare(sq)) { std::cout << "\nError: You did not select an accessible square\n"; return false; }

	selected = getAddress(selection); //getAddress(...) after isSquare to prevent crash
	//(i.e. There's no address for non-squares)

	if (turn != squares[selected].color() && reverseCrown(turn) != squares[selected].color())
	{
		std::cout << "\nError: Picked wrong color.\n"; return false;
	}

	return true; //Success!
}

void goodSquare_Test()
{
	prepareGame();
	// Test case 1: Square is Red, color is correct
	selection = "c3";
	assert(goodSquare(selection));

	// Test case 2: Square is Black, color is incorrect
	selection = "b6";
	assert(!goodSquare(selection));

	// Test case 3: Square is Red
	selection = "a1";
	assert(goodSquare(selection));

	// Test case 4: Square is Black, color is incorrect
	selection = "c7";
	assert(!goodSquare("c7"));

	std::cout << "goodSquare(): All test cases passed!\n";
	Sleep(25);
}

void getTarget() {
	if (selection == "q" || selection == "quit") return;
	std::cout << "Enter coordinate of target square (ex. a1, f8):\n";
	std::cin >> selection;
	// selection = get_GUI_Input();
	// std::cout << selection << '\n';

	if (selection == "h" || selection == "help")
	{
		displayHelp(); getTarget();
	}
	if (selection == "d" || selection == "display")
	{
		displayBoard(squares); getTarget();
	}
	if (selection == "r" || selection == "reset")	//reset option in case no possible target
	{
		displayBoard(squares); getSquare();
		if (selection == "q" || selection == "quit") return; getTarget();
	}

	if (selection == "q" || selection == "quit") return;
	if (!goodTarget(selection)) getTarget();
	return;
}

bool goodTarget(std::string sq) {

	//check if sq is a square
	if (!isSquare(sq))
	{
		std::cout << "\nError: Targeted square is not a square\n";
		return false;
	}

	targeted = getAddress(selection); //getAddress(...) after isSquare to prevent crash
	//(i.e. There's no address for non-squares)

//check if targeted is different from selected
	if (targeted == selected)
	{
		std::cout << "\nError: Targeted square and selected square are the same?\n";
		return false;
	}

	//check if sq is empty
	if (squares[targeted].color() != ' ')
	{
		std::cout << "\nError: The target square is not empty.\n";
		return false;
	}

	if (!squares[selected].isCrowned())
	{
		if (turn == Red)
		{
			if (!oneFrSqAway() && !twoFrSqAway())
			{
				std::cout << "\nError: The target square is not within reach.\n";
				return false;
			}
			if (twoFrSqAway())
			{
				//if target is two squares away in front, 
				//then there has to be a capture
				if (!isCapture())
				{
					std::cout << "\nError: The target square is two squares away, but there is no captured piece.\n";
					return false;
				}
			}
		}
		if (turn == Black)
		{
			if (!oneBcSqAway() && !twoBcSqAway())
			{
				std::cout << "\nError: The target square is not within reach.\n";
				return false;
			}
			if (twoBcSqAway())
			{
				//if target is two squares away in front (or behind from our view),
				//then there has to be a capture
				if (!isCapture())
				{
					std::cout << "\nError: The target square is two squares away, but there is no piece to capture.\n";
					return false;
				}
			}
		}
	}
	if (squares[selected].isCrowned())
	{
		//crowned pieces can move forward or backward
		if (!oneFrSqAway() && !oneBcSqAway() && !twoFrSqAway() && !twoBcSqAway())
		{
			std::cout << "\nError: The target square is not within reach.\n";
			return false;
		}
		if (twoFrSqAway() || twoBcSqAway())
		{
			//if target is two squares away, 
			//then there has to be capture
			if (!isCapture())
			{
				std::cout << "\nError: The target square is two squares away, but there is no piece to capture.\n";
				return false;
			}
		}
	}

	return true; //Success!
}

void goodTarget_Test()
{
	prepareGame();

	// Test case 1: Square is Red, target is one square away
	turn = Red;
	selection = "c3";
	assert(goodSquare(selection));
	selection = "d4";
	assert(goodTarget(selection));

	// Test case 2: Square is Black, target is one square away
	turn = Black;
	selection = "b6";
	assert(goodSquare(selection));
	selection = "a5";
	assert(goodTarget(selection));

	// Test case 3: Square is Red, target will be two squares away, but there is no capture
	turn = Red;
	selection = "c3";
	assert(goodSquare(selection));
	selection = "e5";
	assert(!goodTarget(selection));

	// Test case 4: Square is Black, target will be two squares away, but there is no capture
	turn = Black;
	selection = "b6";
	assert(goodSquare(selection));
	selection = "d4";
	assert(!goodTarget(selection));

	std::cout << "goodTarget(): All test cases passed!\n";
	Sleep(25);
}

int getAddress(std::string sq)
{
	for (int i = 0; i < squares.size(); ++i)
	{
		if (sq == squares[i].square())
		{
			return i;
		}
	}
	error("Exception: used getAddress on non-square\n");
}

void getAddress_Test()
{
	prepareGame();
	// Test case 1: Square is Red
	selection = "c3";
	assert(getAddress(selection) == 9);

	// Test case 2: Square is Black
	selection = "b6";
	assert(getAddress(selection) == 20);

	// Test case 3: Square is Red
	selection = "a1";
	assert(getAddress(selection) == 0);

	// Test case 4: Square is Black
	selection = "c7";
	assert(getAddress(selection) == 25);

	std::cout << "getAddress(): All test cases passed!\n";
	Sleep(25);
}

bool oneFrSqAway()
{
	//is the target one square away in front?
	for (size_t i = 0; i < squares[selected].getFrtAdjSqs().size(); ++i) //size() will always equal 2
	{
		if (squares[selected].getFrtAdjSqs()[i] == squares[targeted].square()) return true;
	}

	return false;
}

void oneFrSqAway_Test()
{
	prepareGame();
	// Test case 1: Square is Red, target is one square away
	selection = "c3";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(oneFrSqAway());

	// Test case 2: Square is Black, target is one square away (but since it is front for red, it is back for black)
	selection = "b6";
	selected = getAddress(selection);
	selection = "a5";
	targeted = getAddress(selection);
	assert(!oneFrSqAway());

	std::cout << "oneFrSqAway(): All test cases passed!\n";
	Sleep(25);
}

bool oneBcSqAway()
{
	//is the target one square away in back?
	for (size_t i = 0; i < squares[selected].getBacAdjSqs().size(); ++i) //size() will always equal 2
	{
		if (squares[selected].getBacAdjSqs()[i] == squares[targeted].square()) return true;
	}

	return false;
}

void oneBcSqAway_Test()
{
	prepareGame();
	// Test case 1: Square is Red, target is one square away (but since it is back for black, it is front for red)
	selection = "c3";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(!oneBcSqAway());

	// Test case 2: Square is Black, target is one square away
	selection = "b6";
	selected = getAddress(selection);
	selection = "a5";
	targeted = getAddress(selection);
	assert(oneBcSqAway());

	std::cout << "oneBcSqAway(): All test cases passed!\n";
	Sleep(25);
}

bool twoFrSqAway()
{
	//is the target two squares away and in front?
	for (size_t i = 0; i < squares[selected].getFrtJmpSqs().size(); ++i) //size() will always equal 2
	{
		if (squares[selected].getFrtJmpSqs()[i] == squares[targeted].square()) return true;
	}

	return false;
}

void twoFrSqAway_Test()
{
	prepareGame();
	// Test case 1: Square is Red, target is two squares away
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(twoFrSqAway());

	// Test case 2: Square is Black, target is two squares away (but since it is front for red, it is back for black)
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(!twoFrSqAway());

	std::cout << "twoFrSqAway(): All test cases passed!\n";
	Sleep(25);
}

bool twoBcSqAway()
{
	//is the target two squares away and behind? (for crowned pieces)
	for (size_t i = 0; i < squares[selected].getBacJmpSqs().size(); ++i) //size() will always equal 2
	{
		if (squares[selected].getBacJmpSqs()[i] == squares[targeted].square()) return true;
	}

	return false;
}

void twoBcSqAway_Test()
{
	prepareGame();
	// Test case 1: Square is Red, target is two squares away (but since it is back for black, it is front for red)
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(!twoBcSqAway());

	// Test case 2: Square is Black, target is two squares away
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(twoBcSqAway());

	std::cout << "twoBcSqAway(): All test cases passed!\n";
	Sleep(25);
}

char getLetCoordinate(std::string sq)
//returns letter coordinate of any square
{
	if (sq == "a1" || sq == "a3" || sq == "a5" || sq == "a7") return 'a';
	if (sq == "b2" || sq == "b4" || sq == "b6" || sq == "b8") return 'b';
	if (sq == "c1" || sq == "c3" || sq == "c5" || sq == "c7") return 'c';
	if (sq == "d2" || sq == "d4" || sq == "d6" || sq == "d8") return 'd';
	if (sq == "e1" || sq == "e3" || sq == "e5" || sq == "e7") return 'e';
	if (sq == "f2" || sq == "f4" || sq == "f6" || sq == "f8") return 'f';
	if (sq == "g1" || sq == "g3" || sq == "g5" || sq == "g7") return 'g';
	if (sq == "h2" || sq == "h4" || sq == "h6" || sq == "h8") return 'h';
	error("Exception: The argument of getLetCoordinate is not a square\n");
}

void getLetCoordinate_Test()
{
	// Test case 1: Square is Red
	selection = "c3";
	assert(getLetCoordinate(selection) == 'c');

	// Test case 2: Square is Black
	selection = "b6";
	assert(getLetCoordinate(selection) == 'b');

	// Test case 3: Square is Red
	selection = "a1";
	assert(getLetCoordinate(selection) == 'a');

	// Test case 4: Square is Black
	selection = "c7";
	assert(getLetCoordinate(selection) == 'c');

	std::cout << "getLetCoordinate(): All test cases passed!\n";
	Sleep(25);
}

std::string getSqInBetween(Square* initSq, Square* targetSq)
{
	//gets square in between by getting letCoord,
	//getting numCoord, then adding them to newSquare at end

	std::string initSq_square = initSq->square();
	std::string targetSq_square = targetSq->square();
	captureDirection = getCapDirection(&initSq_square, &targetSq_square);

	std::string newSquare = " ";
	char letCoord = ' ';
	char numCoord = ' ';

	//get the letter part of the in-between square's name
	switch (getLetCoordinate(initSq->square()))
	{
	case 'a': if (captureDirection == Right) letCoord = 'b'; break;
	case 'b': if (captureDirection == Right) letCoord = 'c'; break;

	case 'c': if (captureDirection == Right) letCoord = 'd';
		if (captureDirection == Left) letCoord = 'b'; break;

	case 'd': if (captureDirection == Right) letCoord = 'e';
		if (captureDirection == Left) letCoord = 'c'; break;

	case 'e': if (captureDirection == Right) letCoord = 'f';
		if (captureDirection == Left) letCoord = 'd'; break;

	case 'f': if (captureDirection == Right) letCoord = 'g';
		if (captureDirection == Left) letCoord = 'e'; break;

	case 'g': if (captureDirection == Left) letCoord = 'f'; break;
	case 'h': if (captureDirection == Left) letCoord = 'g'; break;

	default: error("Exception: getSqInBetween(...) cannot get letter part of name.\n");
	}

	//get the number part of the square name
	if (!initSq->isCrowned())
	{
		switch (turn)
		{
		case Red:
			numCoord = targetSq->row() - 1;
			break;
		case Black:
			numCoord = targetSq->row() + 1;
			break;
		default:
			error("Exception: char turn is neither 'r' nor 'b'\n");
		}
	}
	if (initSq->isCrowned())
	{
		if (upCapture(initSq, targetSq)) numCoord = targetSq->row() - 1; //if capturing upward, treat as red piece capturing
		if (downCapture(initSq, targetSq)) numCoord = targetSq->row() + 1; //if capturing downward, treat as black piece capturing
	}

	//make newSquare out of coordinates
	newSquare = letCoord; //no addition here; that would leave a space at beginning (ex. " a1" instead of "a1")
	//erase the space with assignment instead of addition
	newSquare += numCoord;
	return newSquare;
}

void getSqInBetween_Test()
{
	prepareGame();
	// Test case 1: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(getSqInBetween(&squares[selected], &squares[targeted]) == "d4");

	// Test case 2: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(getSqInBetween(&squares[selected], &squares[targeted]) == "c5");

	// Test case 3: Square is Red
	turn = Red;
	selection = "a1";
	selected = getAddress(selection);
	selection = "c3";
	targeted = getAddress(selection);
	assert(getSqInBetween(&squares[selected], &squares[targeted]) == "b2");

	// Test case 4: Square is Black
	turn = Black;
	selection = "c7";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(getSqInBetween(&squares[selected], &squares[targeted]) == "d6");

	std::cout << "getSqInBetween(): All test cases passed!\n";
	Sleep(25);

}

char getCapDirection(std::string* initSq, std::string* targetSq)
{
	//these two if-statements work for both red and black
	if (getLetCoordinate(*initSq) < getLetCoordinate(*targetSq))
		//ex. with b2 to d4, b is "less" than d, so direction is right
		return Right;

	if (getLetCoordinate(*initSq) > getLetCoordinate(*targetSq))
		return Left;
	error("Exception: The selected and targeted squares are on the same row\n");
}

void getCapDirection_Test()
{
	prepareGame();
	// Test case 1: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	std::string test_squares_selected = squares[selected].square();
	std::string test_squares_targeted = squares[targeted].square();
	assert(getCapDirection(&test_squares_selected, &test_squares_targeted) == Right);

	// Test case 2: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	test_squares_selected = squares[selected].square();
	test_squares_targeted = squares[targeted].square();
	assert(getCapDirection(&test_squares_selected, &test_squares_targeted) == Right);

	// Test case 3: Square is Red
	turn = Red;
	selection = "a1";
	selected = getAddress(selection);
	selection = "c3";
	targeted = getAddress(selection);
	test_squares_selected = squares[selected].square();
	test_squares_targeted = squares[targeted].square();
	assert(getCapDirection(&test_squares_selected, &test_squares_targeted) == Right);

	// Test case 4: Square is Black
	turn = Black;
	selection = "c7";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	test_squares_selected = squares[selected].square();
	test_squares_targeted = squares[targeted].square();
	assert(getCapDirection(&test_squares_selected, &test_squares_targeted) == Right);

	std::cout << "getCapDirection(): All test cases passed!\n";
	Sleep(25);

}

char getRowParity(char row)
{
	//parity is whether a number is odd or even
	//returns Odd ('O') or Even ('E'), depending on the
	//number coordinate of the square
	switch (row)
	{
	case '1': case '3': case '5': case '7':
		return Odd;
	case '2': case '4': case '6': case '8':
		return Even;
	}
	error("Exception: The row argument used in getRowParity is not from 1-8\n");
}

void getRowParity_Test()
{
	// Test case 1: Row is 1
	assert(getRowParity('1') == Odd);

	// Test case 2: Row is 2
	assert(getRowParity('2') == Even);

	// Test case 3: Row is 3
	assert(getRowParity('3') == Odd);

	// Test case 4: Row is 4
	assert(getRowParity('4') == Even);

	// Test case 5: Row is 5
	assert(getRowParity('5') == Odd);

	// Test case 6: Row is 6
	assert(getRowParity('6') == Even);

	// Test case 7: Row is 7
	assert(getRowParity('7') == Odd);

	// Test case 8: Row is 8
	assert(getRowParity('8') == Even);

	std::cout << "getRowParity(): All test cases passed!\n";
	Sleep(25);
}

bool upCapture(Square* initSq, Square* targetSq) {
	if (initSq->row() < targetSq->row()) return true;
	return false;
}

void upCapture_Test()
{
	prepareGame();
	// Test case 1: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(upCapture(&squares[selected], &squares[targeted]));

	// Test case 2: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(!upCapture(&squares[selected], &squares[targeted]));

	// Test case 3: Square is Red
	turn = Red;
	selection = "a1";
	selected = getAddress(selection);
	selection = "c3";
	targeted = getAddress(selection);
	assert(upCapture(&squares[selected], &squares[targeted]));

	// Test case 4: Square is Black
	turn = Black;
	selection = "c7";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(!upCapture(&squares[selected], &squares[targeted]));

	std::cout << "upCapture(): All test cases passed!\n";
	Sleep(25);
}

bool downCapture(Square* initSq, Square* targetSq) {
	if (initSq->row() > targetSq->row()) return true;
	return false;
}

void downCapture_Test()
{
	prepareGame();
	// Test case 1: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(!downCapture(&squares[selected], &squares[targeted]));

	// Test case 2: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(downCapture(&squares[selected], &squares[targeted]));

	// Test case 3: Square is Red
	turn = Red;
	selection = "a1";
	selected = getAddress(selection);
	selection = "c3";
	targeted = getAddress(selection);
	assert(!downCapture(&squares[selected], &squares[targeted]));

	// Test case 4: Square is Black
	turn = Black;
	selection = "c7";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(downCapture(&squares[selected], &squares[targeted]));

	std::cout << "downCapture(): All test cases passed!\n";
	Sleep(25);

}

bool R_Capture1()
{
	//is red's first capture condition satisfied?
	//this condition is described at the top of this file as:
		// 1) start odd-numbered row, going right
	if (initialRowParity == Odd && captureDirection == Right) return true;
	return false;
}

void R_Capture1_Test()
{
	prepareGame();

	// Test case 1: Square is Red, initial row is odd, capture direction is right
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(R_Capture1());

	// Test case 2: Square is Red, initial row is even, capture direction is right
	turn = Red;
	selection = "f2";
	selected = getAddress(selection);
	selection = "h4";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!R_Capture1());

	std::cout << "R_Capture1(): All test cases passed!\n";
	Sleep(25);
}

bool R_Capture2()
{
	//is red's second capture condition satisfied?
	//this condition is described at the top of this file as:
		// 2) start even-numbered row, going right
	if (initialRowParity == Even && captureDirection == Right) return true;
	return false;
}

void R_Capture2_Test()
{
	prepareGame();

	// Test case 1: Square is Red, initial row is odd, capture direction is right
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!R_Capture2());

	// Test case 2: Square is Red, initial row is even, capture direction is right
	turn = Red;
	selection = "f2";
	selected = getAddress(selection);
	selection = "h4";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(R_Capture2());

	std::cout << "R_Capture2(): All test cases passed!\n";
	Sleep(25);
}

bool R_Capture3()
{
	//is red's third capture condition satisfied?
	//this condition is described at the top of this file as:
		// 3) start odd-numbered row, going left
	if (initialRowParity == Odd && captureDirection == Left) return true;
	return false;
}

void R_Capture3_Test()
{
	prepareGame();

	// Test case 1: Square is Red, initial row is odd, capture direction is left
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "a5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(R_Capture3());

	// Test case 2: Square is Red, initial row is even, capture direction is left
	turn = Red;
	selection = "f2";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!R_Capture3());

	std::cout << "R_Capture3(): All test cases passed!\n";
	Sleep(25);
}

bool R_Capture4()
{
	//is red's fourth capture condition satisfied?
	//this condition is described at the top of this file as:
		// 4) start even-numbered row, going left
	if (initialRowParity == Even && captureDirection == Left) return true;
	return false;
}

void R_Capture4_Test()
{
	prepareGame();

	// Test case 1: Square is Red, initial row is odd, capture direction is left
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "a5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!R_Capture4());

	// Test case 2: Square is Red, initial row is even, capture direction is left
	turn = Red;
	selection = "f2";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(R_Capture4());

	std::cout << "R_Capture4(): All test cases passed!\n";
	Sleep(25);
}

bool B_Capture1()
{
	//is black's first capture condition satisfied?
	//this condition is described at the top of this file as:
		// 1) start odd-numbered row, going left
	if (initialRowParity == Odd && captureDirection == Left) return true;
	return false;
}

void B_Capture1_Test()
{
	prepareGame();

	// Test case 1: Square is Black, initial row is odd, capture direction is left
	turn = Black;
	selection = "e7";
	selected = getAddress(selection);
	selection = "c5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(B_Capture1());

	// Test case 2: Square is Black, initial row is even, capture direction is left
	turn = Black;
	selection = "h6";
	selected = getAddress(selection);
	selection = "f4";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!B_Capture1());

	std::cout << "B_Capture1(): All test cases passed!\n";
	Sleep(25);
}

bool B_Capture2()
{
	//is black's second capture condition satisfied?
	//this condition is described at the top of this file as:
		// 2) start even-numbered row, going left
	if (initialRowParity == Even && captureDirection == Left) return true;
	return false;
}

void B_Capture2_Test()
{
	prepareGame();

	// Test case 1: Square is Black, initial row is odd, capture direction is left
	turn = Black;
	selection = "e7";
	selected = getAddress(selection);
	selection = "c5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!B_Capture2());

	// Test case 2: Square is Black, initial row is even, capture direction is left
	turn = Black;
	selection = "h6";
	selected = getAddress(selection);
	selection = "f4";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(B_Capture2());

	std::cout << "B_Capture2(): All test cases passed!\n";
	Sleep(25);
}

bool B_Capture3()
{
	//is black's third capture condition satisfied?
	//this condition is described at the top of this file as:
		// 3) start odd-numbered row, going right
	if (initialRowParity == Odd && captureDirection == Right) return true;
	return false;
}

void B_Capture3_Test()
{
	prepareGame();

	// Test case 1: Square is Red, initial row is odd, capture direction is right
	turn = Red;
	selection = "a7";
	selected = getAddress(selection);
	selection = "c5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(B_Capture3());

	// Test case 2: Square is Red, initial row is even, capture direction is right
	turn = Red;
	selection = "d8";
	selected = getAddress(selection);
	selection = "h6";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!B_Capture3());

	std::cout << "B_Capture3(): All test cases passed!\n";
	Sleep(25);
}

bool B_Capture4()
{
	//is black's fourth capture condition satisfied?
	//this condition is described at the top of this file as:
		// 4) start even-numbered row, going right
	if (initialRowParity == Even && captureDirection == Right) return true;
	return false;
}

void B_Capture4_Test()
{
	prepareGame();

	// Test case 1: Square is Red, initial row is odd, capture direction is right
	turn = Red;
	selection = "a7";
	selected = getAddress(selection);
	selection = "c5";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(!B_Capture4());

	// Test case 2: Square is Red, initial row is even, capture direction is right
	turn = Red;
	selection = "d8";
	selected = getAddress(selection);
	selection = "h6";
	targeted = getAddress(selection);
	initialRowParity = getRowParity(squares[selected].row());
	squares_selected = squares[selected].square();
	squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);
	assert(B_Capture4());

	std::cout << "B_Capture4(): All test cases passed!\n";
	Sleep(25);
}

char oppoColor(char color) {
	//also works on crowned colors ('R' or 'B')
	switch (color) {
	case Red: return Black;
	case Black: return Red;
	case cRed: return cBlack;
	case cBlack: return cRed;
	default: error("Exception: oppoColor(...) used on non-color\n");
	}
}

void oppoColor_Test()
{
	// Test case 1: Color is Red
	assert(oppoColor(Red) == Black);

	// Test case 2: Color is Black
	assert(oppoColor(Black) == Red);

	// Test case 3: Color is cRed
	assert(oppoColor(cRed) == cBlack);

	// Test case 4: Color is cBlack
	assert(oppoColor(cBlack) == cRed);

	std::cout << "oppoColor(): All test cases passed!\n";
	Sleep(25);
}

bool isCapture() {
	//is a capture occuring?

	//check for the capture conditions described at the top of this file
	// 1) color held by char turn

	// 2) determine oddness/evenness of initial square's row
	initialRowParity = getRowParity(squares[selected].row());

	// 3) determine capture direction
	std::string squares_selected = squares[selected].square();
	std::string squares_targeted = squares[targeted].square();
	captureDirection = getCapDirection(&squares_selected, &squares_targeted);

	//check if any capture condition is true
	//capture conditions differ for crowned vs. non-crowned
	if (!squares[selected].isCrowned())
	{
		switch (turn)
		{
		case Red:
			if (R_Capture1() && targeted - selected == rOddRightCapJmp ||
				R_Capture2() && targeted - selected == rEvenRightCapJmp ||
				R_Capture3() && targeted - selected == rOddLeftCapJmp ||
				R_Capture4() && targeted - selected == rEvenLeftCapJmp);
			else return false;

			break;
		case Black:
			if (B_Capture1() && targeted - selected == bOddLeftCapJmp ||
				B_Capture2() && targeted - selected == bEvenLeftCapJmp ||
				B_Capture3() && targeted - selected == bOddRightCapJmp ||
				B_Capture4() && targeted - selected == bEvenRightCapJmp);
			else return false;

			break;
		}
	}
	if (squares[selected].isCrowned())
	{
		if (R_Capture1() && targeted - selected == rOddRightCapJmp ||
			R_Capture2() && targeted - selected == rEvenRightCapJmp ||
			R_Capture3() && targeted - selected == rOddLeftCapJmp ||
			R_Capture4() && targeted - selected == rEvenLeftCapJmp ||
			B_Capture1() && targeted - selected == bOddLeftCapJmp ||
			B_Capture2() && targeted - selected == bEvenLeftCapJmp ||
			B_Capture3() && targeted - selected == bOddRightCapJmp ||
			B_Capture4() && targeted - selected == bEvenRightCapJmp);
		else return false;
	}

	//save vector address of inBetween square
	inBetween = getAddress(getSqInBetween(&squares[selected], &squares[targeted]));

	if (squares[inBetween].color() != oppoColor(turn) && squares[inBetween].color() != reverseCrown(oppoColor(turn))) return false;

	//only do this if any of the above capture conditions is true
	//mark the in-between square as captured
	squares[inBetween].switchCap(true);  //this square is now captured
	return true;
}

void isCapture_Test()
{
	/*
		  | b |   | b |   | b |   | b
	8 ___|___|___|___|___|___|___|___
		b |   | b |   | b |   | b |
	7 ___|___|___|___|___|___|___|___
		  | b |   | b |   | b |   | b
	6 ___|___|___|___|___|___|___|___
		  |   |   |   |   |   |   |
	5 ___|___|___|___|___|___|___|___
		  |   |   |   |   |   |   |
	4 ___|___|___|___|___|___|___|___
		r |   | r |   | r |   | r |
	3 ___|___|___|___|___|___|___|___
		  | r |   | r |   | r |   | r
	2 ___|___|___|___|___|___|___|___
		r |   | r |   | r |   | r |
	1 ___|___|___|___|___|___|___|___
		a   b   c   d   e   f   g   h
	*/
	prepareGame();

	// Test case 1: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	squares[13] = Square(Black, "d4", '4');
	assert(isCapture());

	// Test case 2: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	squares[17] = Square(Red, "c5", '5');
	assert(isCapture());

	// Test case 3: Square is Red
	turn = Red;
	selection = "a1";
	selected = getAddress(selection);
	selection = "c3";
	targeted = getAddress(selection);
	assert(!isCapture());

	// Test case 4: Square is Black
	turn = Black;
	selection = "c7";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(!isCapture());

	std::cout << "isCapture(): All test cases passed!\n";
	Sleep(25);
}

void updateBoard() {
	// 1) resolve piece movement:
	//to "move" a piece, change targeted square's color to
	//selected square's color, 
	squares[targeted].changeColor(squares[selected].color());

	//then make the selected square's color blank (no piece on it)
	squares[selected].changeColor(' ');

	//move the crowned "trait" from square to square
	if (squares[selected].isCrowned())
	{
		squares[selected].switchCrown(false);
		squares[targeted].switchCrown(true);
	}

	// 2) resolve captures (make captured pieces disappear):
	for (size_t i = 0; i < squares.size(); ++i)
	{
		if (squares[i].isCaptured())
		{
			squares[i].changeColor(' ');
			squares[i].switchCrown(false);
			squares[i].switchCap(false);
			wasCapture = true;
			std::cout << "\nThe piece on " << squares[i].square() << " has been captured.\n";
		}
	}

	// 3) promote pieces to crowned
	if (isPromotion() && !squares[targeted].isCrowned())
	{
		squares[targeted].switchCrown(true);
		squares[targeted].changeColor(reverseCrown(squares[targeted].color()));
	}
}

bool isPromotion() {
	if (turn == Red) {
		switch (targeted) {
		case b8: case d8: case f8: case h8: return true;
		default: return false;
		}
	}
	if (turn == Black) {
		switch (targeted) {
		case a1: case c1: case e1: case g1: return true;
		default: return false;
		}
	}
}

void isPromotion_Test()
{
	prepareGame();

	// Test case 1: Square is Red
	turn = Red;
	selection = "e5";
	targeted = getAddress(selection);
	assert(!isPromotion());

	// Test case 2: Square is Black
	turn = Black;
	selection = "d4";
	targeted = getAddress(selection);
	assert(!isPromotion());

	// Test case 3: Square is Red
	turn = Red;
	selection = "f8";
	targeted = getAddress(selection);
	assert(isPromotion());

	// Test case 4: Square is Black
	turn = Black;
	selection = "a1";
	targeted = getAddress(selection);
	assert(isPromotion());

	std::cout << "isPromotion(): All test cases passed!\n";
	Sleep(25);

}

bool possibleCapture(Square* initSq) {
	//is a capture possible?
	//program can know whether to prompt user for multiple consecutive captures
	//(double jumps, triple jumps, etc.)
	//used after resolution of piece movement in a turn
	//if there is a possible capture, the user may make a second move to capture
	//if there is another capture, the user may again make another move, and so on

	int address = getAddress(initSq->square()); //store this address to check if capture is
	//possible based on vector location
	initialRowParity = getRowParity(initSq->row());

	//int targeted still has address of landing square of piece
	if (initSq->color() == Red || initSq->isCrowned())
	{
		//check if red's first capture conditions are true and allow a capture:
		if (initialRowParity == Odd &&
			address + rOddRightCapJmp < squares.size() && //prevent out-of-range error
			squares[address + rOddRightCapJmp].color() == ' ' &&
			squares[address + rOddRightHafJmp].square() == getSqInBetween(initSq, &squares[address + rOddRightCapJmp]))
		{
			if (squares[address + rOddRightHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + rOddRightHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}

		//check if red's second capture conditions are true and allow a capture:
		if (initialRowParity == Even &&
			address + rEvenRightCapJmp < squares.size() && //prevent out-of-range error
			squares[address + rEvenRightCapJmp].color() == ' ' &&
			squares[address + rEvenRightHafJmp].square() == getSqInBetween(initSq, &squares[address + rEvenRightCapJmp]))
		{
			if (squares[address + rEvenRightHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + rEvenRightHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}

		//check if red's third capture conditions are true and allow a capture:
		if (initialRowParity == Odd &&
			address + rOddLeftCapJmp < squares.size() && //prevent out-of-range error
			squares[address + rOddLeftCapJmp].color() == ' ' &&
			squares[address + rOddLeftHafJmp].square() == getSqInBetween(&squares[address], &squares[address + rOddLeftCapJmp]))
		{
			if (squares[address + rOddLeftHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + rOddLeftHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}

		//check if red's fourth capture conditions are true and allow a capture:
		if (initialRowParity == Even &&
			address + rEvenLeftCapJmp < squares.size() && //prevent out-of-range error
			squares[address + rEvenLeftCapJmp].color() == ' ' &&
			squares[address + rEvenLeftHafJmp].square() == getSqInBetween(&squares[address], &squares[address + rEvenLeftCapJmp]))
		{
			if (squares[address + rEvenLeftHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + rEvenLeftHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}
	}
	if (initSq->color() == Black || initSq->isCrowned())
	{
		//check if black's first capture conditions are true and allow a capture:
		if (initialRowParity == Odd &&
			address + bOddLeftCapJmp >= lowVectorRange && //prevent out-of-range error
			squares[address + bOddLeftCapJmp].color() == ' ' &&
			squares[address + bOddLeftHafJmp].square() == getSqInBetween(&squares[address], &squares[address + bOddLeftCapJmp]))
		{
			if (squares[address + bOddLeftHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + bOddLeftHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}

		//check if black's second capture conditions are true and allow a capture:
		if (initialRowParity == Even &&
			address + bEvenLeftCapJmp >= lowVectorRange && //prevent out-of-range error
			squares[address + bEvenLeftCapJmp].color() == ' ' &&
			squares[address + bEvenLeftHafJmp].square() == getSqInBetween(&squares[address], &squares[address + bEvenLeftCapJmp]))
		{
			if (squares[address + bEvenLeftHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + bEvenLeftHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}

		//check if black's third capture conditions are true and allow a capture:
		if (initialRowParity == Odd &&
			address + bOddRightCapJmp >= lowVectorRange && //prevent out-of-range error
			squares[address + bOddRightCapJmp].color() == ' ' &&
			squares[address + bOddRightHafJmp].square() == getSqInBetween(&squares[address], &squares[address + bOddRightCapJmp]))
		{
			if (squares[address + bOddRightHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + bOddRightHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}

		//check if black's fourth capture conditions are true and allow a capture:
		if (initialRowParity == Even &&
			address + bEvenRightCapJmp >= lowVectorRange && //prevent out-of-range error
			squares[address + bEvenRightCapJmp].color() == ' ' &&
			squares[address + bEvenRightHafJmp].square() == getSqInBetween(&squares[address], &squares[address + bEvenRightCapJmp]))
		{
			if (squares[address + bEvenRightHafJmp].color() == oppoColor(initSq->color()) ||
				squares[address + bEvenRightHafJmp].color() == reverseCrown(oppoColor(initSq->color()))) return true;
		}
	}
	return false;
}

void possibleCapture_Test()
{
	prepareGame();

	// Test case 1: Square is Red
	turn = Red;
	squares[13] = Square(Black, "d4", '4');
	assert(possibleCapture(&squares[9]));

	// Test case 1: Square is Black
	turn = Black;
	squares[17] = Square(Red, "c5", '5');
	assert(possibleCapture(&squares[21]));

	// Test case 1: Square is Red
	assert(!possibleCapture(&squares[1]));

	// Test case 1: Square is Black
	assert(!possibleCapture(&squares[30]));

	std::cout << "possibleCapture(): All test cases passed!\n";
	Sleep(25);
}

void getConsecutiveJmpTarget() {
	if (selection == "q" || selection == "quit") return;
	std::cout << "Current turn is still: " << turn << '\n';
	std::cout << "Piece to move is on " << squares[selected].square() << ".\n";
	std::cout << "Enter coordinate of target square for consecutive jump (ex. a1, f8).\n";
	std::cout << "Or enter 'sk' or 'skip' to skip this consecutive jump.\n";
	// selection = get_GUI_Input();
	// std::cout << selection << '\n';
	std::cin >> selection;

	if (selection == "d" || selection == "display")
	{
		displayBoard(squares); getConsecutiveJmpTarget();
	}
	if (selection == "q" || selection == "quit") return;
	if (selection == "sk" || selection == "skip") return; //enter "s" or "skip" to skip consecutive jump
	if (!goodConsecutiveJmpTarget(selection)) getConsecutiveJmpTarget();
	return;
}

bool goodConsecutiveJmpTarget(std::string sq) {
	//same as bool goodTarget(std::string sq), except:
		//no checking if target is empty (that's done in bool possibleCapture())

	//check if sq is a square
	if (!isSquare(sq))
	{
		std::cout << "\nError: Targeted square is not a square\n";
		return false;
	}

	targeted = getAddress(selection); //getAddress(...) after isSquare to prevent crash
	//(i.e. There's no address for non-squares)

//check if targeted is different from selected
	if (targeted == selected)
	{
		std::cout << "\nError: Targeted square and selected square are the same?\n";
		return false;
	}

	if (!squares[selected].isCrowned())
	{
		if (turn == Red)
		{
			if (oneFrSqAway())
			{
				std::cout << "\nError: A consecutive turn must be a capture.\n" <<
					"Or enter 'sk' to skip the consecutive capture.\n";
				return false;
			}
			else if (twoFrSqAway())
			{
				//if target is two squares away in front, 
				//then there has to be a capture
				if (!isCapture())
				{
					std::cout << "\nError: The target square is two squares away, but there is no captured piece.\n";
					return false;
				}
			}
			else
			{
				std::cout << "\nError: The target is not within reach.\n";
				return false;
			}
		}
		if (turn == Black)
		{
			if (oneBcSqAway())
			{
				std::cout << "\nError: A consecutive turn must be a capture.\n" <<
					"Otherwise, enter 'sk' to skip the consecutive capture.\n";
				return false;
			}
			else if (twoBcSqAway())
			{
				//if target is two squares away in front (or behind from our view),
				//then there has to be a capture
				if (!isCapture())
				{
					std::cout << "\nError: The target square is two squares away, but there is no piece to capture.\n";
					return false;
				}
			}
			else
			{
				std::cout << "\nError: The target is not within reach.\n";
				return false;
			}
		}
	}
	if (squares[selected].isCrowned())
	{
		//crowned pieces can move forward or backward
		if (oneFrSqAway() || oneBcSqAway())
		{
			std::cout << "\nError: A consecutive turn must be a capture.\n" <<
				"Otherwise, enter 'sk' to skip the consecutive capture.\n";
			return false;
		}
		else if (twoFrSqAway() || twoBcSqAway())
		{
			//if target is two squares away, 
			//then there has to be capture
			if (!isCapture())
			{
				std::cout << "\nError: The target square is two squares away, but there is no piece to capture.\n";
				return false;
			}
		}
		else
		{
			std::cout << "\nError: The target square is not within reach.\n";
			return false;
		}
	}

	return true; //Success!
}

void goodConsecutiveJmpTarget_Test()
{
	prepareGame();

	// Test case 1: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	assert(!goodConsecutiveJmpTarget(selection));

	// Test case 2: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	assert(!goodConsecutiveJmpTarget(selection));

	// Test case 3: Square is Red
	turn = Red;
	selection = "c3";
	selected = getAddress(selection);
	selection = "e5";
	targeted = getAddress(selection);
	squares[13] = Square(Black, "d4", '4');
	assert(goodConsecutiveJmpTarget(selection));

	// Test case 4: Square is Black
	turn = Black;
	selection = "b6";
	selected = getAddress(selection);
	selection = "d4";
	targeted = getAddress(selection);
	squares[17] = Square(Red, "c5", '5');
	assert(goodConsecutiveJmpTarget(selection));

	std::cout << "goodConsecutiveJmpTarget(): All test cases passed!\n";
	Sleep(25);
}

void displayHelp() {
	std::cout << "List of key commands:\n"
		<< "\t'q' to quit\n"
		<< "\t'd' to display the game board again\n"
		<< "\t'r' to reset the current turn (to pick a different piece to move)\n"
		<< "\t'sv' to save the game\n\n";
}

void displayMenu() {
	std::cout << "Select one of the following options:\n"
		<< "1) New game\n"
		<< "2) Resume game\n"
		<< "3) Help\n"
		<< "4) Exit\n";
}

void displayMods() {
	std::cout << "Select one of the following options:\n"
		<< "1) Man VS Man\n"
		<< "2) Man VS AI\n"
		<< "3) AI VS AI\n";
}

void playerTurn() {
	displayBoard(squares);
	getSquare();
	if (selection == "q" || selection == "quit") return;
	getTarget();
	if (selection == "q" || selection == "quit") return;
	updateBoard();
	while (wasCapture && possibleCapture(&squares[targeted]))
	{
		selected = targeted;
		displayBoard(squares);
		getConsecutiveJmpTarget();
		if (selection == "q" || selection == "quit") return;
		if (selection == "sk" || selection == "skip") return; //do this before updateBoard()
		//otherwise updateBoard removes squares[selected]
		updateBoard();
	}
}

/*
TO-DO list:
Алгоритм ШІ для рандомних ходів:
1. рандомно обираємо клітинку з доступних (врахувати колір)
2. Обрати доступний (з тих,що не обирались) напрямок ходу (можливі 4 варіанти: вгору-вниз, вліво-вправо)
Якщо не обраний раніше напрямок доступний:
	 3. Перевірити, чи можна зробити СТРИБОК (jump) для вибиття фішки протилежної команди
	 якщо так:
		  4. перевірити чи  не зайнята клітинка фішкою того ж самого кольору
		  Якщо так:
				5. Зробити СТРИБОК
		  Якщо ні: повернутись до п.2
	 Якщо ні:
		  6. перевірити, чи можна зробити ХІД (чи не зайнята клітинка фішкою того ж самого кольору)
		  Якщо так:
				7. Зробити хід
		  Якщо ні: повернутись до п.2
Якщо не обраний раніше напрямок недоступний(закінчились): Повернутись до п.1
*/

void AI_Turn() {
	//getSquare();
	bool isMove = false;
	int index[32] = { 0 };
	for (size_t i = 0; i < squares.size(); ++i)
	{
		for (int i = 0; i < 32; i++) {
			index[i] = i;
		}
		shuffleArray(index, 32);
		if (squares[index[i]].color() == turn || squares[index[i]].color() == reverseCrown(turn))
		{
			selection = squares[index[i]].square();
			if (!goodSquare(selection))
			{
				continue;
			}
		}
		else
			continue;

		for (int j = 0; j < 2; ++j)
		{
			selection = squares[index[i]].getFrtJmpSqs()[j];
			if (goodTarget(selection))
			{
				updateBoard();
				isMove = true;
				break;
			}
			else
			{
				selection = squares[index[i]].getBacJmpSqs()[j];
				if (goodTarget(selection))
				{
					updateBoard();
					isMove = true;
					break;
				}
				else
				{
					selection = squares[index[i]].getFrtAdjSqs()[j];
					if (goodTarget(selection))
					{
						updateBoard();
						isMove = true;
						break;
					}
					else
					{
						selection = squares[index[i]].getBacAdjSqs()[j];
						if (goodTarget(selection))
						{
							updateBoard();
							isMove = true;
							break;
						}
					}
				}
			}
		}

		if (isMove)
			break;
	}
}

bool gameOver() {
	bool rGameOver = true;
	bool bGameOver = true;

	if (loser == Both) return true; //in case of draw

	//it is game over if either side has no pieces remaining
	for (size_t i = 0; i < squares.size(); ++i)
	{
		//if there is a piece of a certain color,
		//then that side has not lost
		if (squares[i].color() == Red || squares[i].color() == cRed) rGameOver = false;
		if (squares[i].color() == Black || squares[i].color() == cBlack) bGameOver = false;
	}
	if (rGameOver && bGameOver) error("Exception: All of the pieces have disappeared\n");
	if (rGameOver) { loser = Red; return true; }
	if (bGameOver) { loser = Black; return true; }
	return false;
}

void gameOver_Test()
{
	prepareGame();

	// Test case 1: there are still pieces on the board
	assert(!gameOver());

	// Test case 2: 0 black pieces on the board, 1 red piece on the board
	for (size_t i = 0; i < squares.size(); ++i)
	{
		if (squares[i].color() == Black || squares[i].color() == cBlack)
			squares[i].changeColor(' ');
	}
	assert(gameOver());

	// Test case 3: 1 black piece on the board, 0 red pieces on the board
	for (size_t i = 0; i < squares.size(); ++i)
	{
		if (squares[i].color() == Red || squares[i].color() == cRed)
			squares[i].changeColor(' ');
	}
	squares[0].changeColor(Black);
	assert(gameOver());

	std::cout << "gameOver(): All test cases passed!\n";
	Sleep(25);
}

void checkersGame(int selector_) {
	bool quit = false;
	bool AI_vs_AI = false;
	bool Man_vs_AI = false;

	switch (selector_) {
	case 1:
	{
		;
	}
	break;
	case 2:
	{
		Man_vs_AI = true;
	}
	break;
	case 3:
	{
		AI_vs_AI = true;
	}
	break;
	}

	while (!gameOver() && !quit)
	{
		if (cannotMakeMove())
		{
			//if there is no possible move for the turn player (which can happen in checkers),
			//then the game is a draw
			loser = Both; //this will cause gameOver() to return true
		}
		else if (turn == Red)
		{
			if (AI_vs_AI)
				AI_Turn();
			else
				playerTurn();
			if (selection == "q" || selection == "quit") quit = true;
			turn = oppoColor(turn);
		}
		else if (turn == Black)
		{
			if (Man_vs_AI || AI_vs_AI)
				AI_Turn();
			else
				playerTurn();
			if (selection == "q" || selection == "quit") quit = true;
			turn = oppoColor(turn);
		}
		wasCapture = false; //prepare for next turn
	}
	if (gameOver() && !quit)
	{
		handleLoss();
	}
	if (playAgain()) {
		prepareGame();
		checkersGame(selector_);
	}
}

void handleLoss() {
	displayBoard(squares);
	if (loser == Red)
	{
		std::cout << "Game over! Red loses. Black wins.\n";
	}
	if (loser == Black)
	{
		std::cout << "Game over! Black loses. Red wins.\n";
	}
	if (loser == Both)
	{
		std::cout << "Game over! The game is a draw.\n";
		if (turn == Red) std::cout << "Red cannot make a move.\n";
		if (turn == Black) std::cout << "Black cannot make a move.\n";
	}
}

bool playAgain() {
	//does the user want another game?
	std::cout << "\nWould you like to play another game?\n";
	while (selection != "yes" && selection != "y" && selection != "no" && selection != "n")
	{
		std::cout << "Type 'y' or 'n':\n"; std::cin >> selection;
	}
	if (selection == "yes" || selection == "y") return true;
	return false;
}

void exit() {
	//handles exit
	std::cout << "Enter a character to exit:\n";
	char c;
	std::cin >> c;
}

void shuffleArray(int* array, int size) {
	for (int i = size - 1; i > 0; --i) {
		//generate random index
		int j = rand() % (i + 1);

		//swap array[i] and array[j]
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

void shuffleArray_Test()
{
	srand(time(NULL)); // Seed for randomness

	const int size = 5;
	int original[size] = { 1, 2, 3, 4, 5 };
	int testArray[size];

	std::copy(original, original + size, testArray);
	shuffleArray(testArray, size);

	// Test 1: Array size should remain the same
	assert(sizeof(testArray) == sizeof(original));

	// Test 2: Test for randomness (not perfect, but a basic check)
	int anotherTestArray[size];
	std::copy(original, original + size, anotherTestArray);
	shuffleArray(anotherTestArray, size);

	bool arraysDiffer = false;
	for (int i = 0; i < size; ++i) {
		if (testArray[i] != anotherTestArray[i]) {
			arraysDiffer = true;
			break;
		}
	}
	assert(arraysDiffer);

	std::cout << "shuffleArray(): All test cases passed!\n";
	Sleep(25);
}

void error(std::string message)
{
	throw message;
}