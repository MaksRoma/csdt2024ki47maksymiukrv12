#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

namespace sq {
	
	struct Square
	{
		char color() const { return c; }
		std::string square() const { return s; }
		char row() const { return r; }
		std::vector<std::string> getFrtAdjSqs() const { return frtAdjSqs; }
		std::vector<std::string> getBacAdjSqs() const { return bacAdjSqs; }
		std::vector<std::string> getFrtJmpSqs() const { return frtJmpSqs; }
		std::vector<std::string> getBacJmpSqs() const { return bacJmpSqs; }
		bool isCrowned() const { return crowned; }
		void switchCrown(bool status) { crowned = status; return; }
		bool isCaptured() const { return captured; }
		void switchCap(bool status) { captured = status; return; }

		void changeColor(char newColor);

		Square();
		Square(char c_, std::string s_, char r_);

		std::vector<std::string> setFrtAdjSqs(std::string sq); //sets std::vector<std::string> FrtAdjSqs
		std::vector<std::string> setBacAdjSqs(std::string sq); //sets std::vector<std::string> BacAdjSqs
		std::vector<std::string> setFrtJmpSqs(std::string sq); //sets std::vector<std::string> frontJumpSqs
		std::vector<std::string> setBacJmpSqs(std::string sq); //sets std::vector<std::string> backJumpSqs

	private:
		//10 members
		char c;
		//color of piece on it
			//'r' for red
			//'R' for crowned red
			//'b' for black
			//'B' for crowned black
			//' ' for none
		std::string s;  //square name; could be a1, e5, etc.
		char r;  //row; could be 1,2,3,...8
		std::vector<std::string> frtAdjSqs; //holds adjacent squares in front
		std::vector<std::string> bacAdjSqs; //holds adjacent squares in back
		//std::vector<std::string> adjSqs; //holds adjacent squares
		std::vector<std::string> frtJmpSqs; //holds squares that are two away in front
		//used to detect a capture
		std::vector<std::string> bacJmpSqs; //holds squares that are two away in back
		//used to detect a capture by crowned pieces
		bool crowned; //is the piece on this square crowned?
		//if a piece is crowned, it can move backwards in default game mode
		bool captured; //is the piece on this square captured?
	};

} // namespace sq
using namespace sq;

namespace checkers {
	extern std::vector<Square> squares;
	extern std::string selection; //all input by the user is held by this variable
	extern char turn; //either 'r' (Red) or 'b' (Black)
	extern char captureDirection; //either 'R' (right) or 'L' (left)
	extern char initialRowParity; //either 'O' (odd) or 'E' (even)
	extern bool wasCapture; //was there a capture this turn?
	//used to determine whether to check for consecutive capture
	extern char loser; //either 'r' (Red) or 'b' (Black)
	//who is the loser?


	extern int selector; //for debugging
	//for vector location:
	extern int selected; //holds vector address of square of selected piece
	extern int targeted; //holds vector address of square to move a piece to
	extern int inBetween; //holds vector address of square in between the
	//selected and targeted squares (in case of capture)
} // namespace checkers
using namespace checkers;

namespace constants {
	extern const char Red = 'r';
	extern const char cRed = 'R'; //crowned red
	extern const char Black = 'b';
	extern const char cBlack = 'B'; //crowned black
	extern const char Both = 'x'; //in case of a tie, char loser = Both
	extern const char Left = 'L';
	extern const char Right = 'R';
	extern const char Odd = 'O';
	extern const char Even = 'E';
	extern const int lowVectorRange = 0; //lowest subscript within range of vector

	//addresses of squares at ends of board (for detecting promotion):
	extern const int b8 = 28;
	extern const int d8 = 29;
	extern const int f8 = 30;
	extern const int h8 = 31;
	extern const int a1 = 0;
	extern const int c1 = 1;
	extern const int e1 = 2;
	extern const int g1 = 3;

	//for capturing (see description at top of mainGame.cpp for explanation):
	extern const int rOddRightCapJmp = 9; //distance from start to landing square if
	//piece starts on odd row heading right
	//red's first capture condition true
	extern const int rOddRightHafJmp = 4; //distance from start to in-between square if
	//piece starts on odd row heading right
	//red's first capture condition true
//following constants follow same pattern
	extern const int rEvenRightCapJmp = 9; //red's second capture condition
	extern const int rEvenRightHafJmp = 5;

	extern const int rOddLeftCapJmp = 7; //red's third capture condition
	extern const int rOddLeftHafJmp = 3;

	extern const int rEvenLeftCapJmp = 7; //red's fourth capture condition
	extern const int rEvenLeftHafJmp = 4;

	extern const int bOddLeftCapJmp = -9; //black's first capture condition
	extern const int bOddLeftHafJmp = -5;

	extern const int bEvenLeftCapJmp = -9; //black's second capture condition
	extern const int bEvenLeftHafJmp = -4;

	extern const int bOddRightCapJmp = -7; //black's third capture condition
	extern const int bOddRightHafJmp = -4;

	extern const int bEvenRightCapJmp = -7; //black's fourth capture condition
	extern const int bEvenRightHafJmp = -3;
}
using namespace constants;

void displayBoard(const std::vector<Square>& sqVect);

void prepareGame();
bool saveGame(std::vector<Square>* squares, char turn_, int selector_);
bool loadGame(std::vector<Square>* squares, char* turn_, int* selector_);

bool isSquare(std::string square);
char reverseCrown(char color); //return crowned version of color ('R' or 'B')
//or uncrowned version ('r' or 'b')
bool cannotMakeMove();
bool possibleMovement(Square* initSq);

void getSquare();
//void AI_GetSquare();
bool goodSquare(std::string sq);
void getTarget();
//void AI_GetTarget();
bool goodTarget(std::string sq);

bool oneFrSqAway();
bool oneBcSqAway();
bool twoFrSqAway();
bool twoBcSqAway();

int getAddress(std::string sq);
char getLetCoordinate(std::string sq1);
std::string getSqInBetween(Square* initSq, Square* targetSq);
char getCapDirection(std::string* initSq, std::string* targetSq);
char getRowParity(char row); //parity is oddness or evenness

//these two functions are for crowned pieces in function Square getSqInBetween(...)
bool upCapture(Square* initSq, Square* targetSq); //is the capture going upward (from our view)?
bool downCapture(Square* initSq, Square* targetSq); //is the capture going downward?

bool R_Capture1();
bool R_Capture2();
bool R_Capture3();
bool R_Capture4();
bool B_Capture1();
bool B_Capture2();
bool B_Capture3();
bool B_Capture4();

char oppoColor(char color);
bool isCapture(); //is a capture occuring?
void updateBoard();
bool isPromotion(); //is there a promotion (to a crowned piece)?
bool possibleCapture(Square* initSq); //is a capture possible?
void getConsecutiveJmpTarget(); //get user's target for consecutive captures
bool goodConsecutiveJmpTarget(std::string sq);

void displayHelp();
void displayMenu();
void displayMods();

void playerTurn();
void AI_Turn();

bool gameOver(); //is it game over?

void checkersGame(int selector_);
void handleLoss();
bool playAgain();
void exit();

void shuffleArray(int* array, int size);

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

char reverseCrown(char color) {
	//returns either the crowned version of a color ('R' or 'B')
	//or uncrowned version ('r' or 'b')
	if (color == Red) return cRed;
	if (color == Black) return cBlack;
	if (color == cRed) return Red;
	if (color == cBlack) return Black;
	error("Exception: reverseCrown() used on a char that is not 'r', 'b', 'R', or 'B'\n");
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

bool oneFrSqAway()
{
	//is the target one square away in front?
	for (size_t i = 0; i < squares[selected].getFrtAdjSqs().size(); ++i) //size() will always equal 2
	{
		if (squares[selected].getFrtAdjSqs()[i] == squares[targeted].square()) return true;
	}

	return false;
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

bool twoFrSqAway()
{
	//is the target two squares away and in front?
	for (size_t i = 0; i < squares[selected].getFrtJmpSqs().size(); ++i) //size() will always equal 2
	{
		if (squares[selected].getFrtJmpSqs()[i] == squares[targeted].square()) return true;
	}

	return false;
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

bool upCapture(Square* initSq, Square* targetSq) {
	if (initSq->row() < targetSq->row()) return true;
	return false;
}

bool downCapture(Square* initSq, Square* targetSq) {
	if (initSq->row() > targetSq->row()) return true;
	return false;
}

bool R_Capture1()
{
	//is red's first capture condition satisfied?
	//this condition is described at the top of this file as:
		// 1) start odd-numbered row, going right
	if (initialRowParity == Odd && captureDirection == Right) return true;
	return false;
}

bool R_Capture2()
{
	//is red's second capture condition satisfied?
	//this condition is described at the top of this file as:
		// 2) start even-numbered row, going right
	if (initialRowParity == Even && captureDirection == Right) return true;
	return false;
}

bool R_Capture3()
{
	//is red's third capture condition satisfied?
	//this condition is described at the top of this file as:
		// 3) start odd-numbered row, going left
	if (initialRowParity == Odd && captureDirection == Left) return true;
	return false;
}

bool R_Capture4()
{
	//is red's fourth capture condition satisfied?
	//this condition is described at the top of this file as:
		// 4) start even-numbered row, going left
	if (initialRowParity == Even && captureDirection == Left) return true;
	return false;
}

bool B_Capture1()
{
	//is black's first capture condition satisfied?
	//this condition is described at the top of this file as:
		// 1) start odd-numbered row, going left
	if (initialRowParity == Odd && captureDirection == Left) return true;
	return false;
}

bool B_Capture2()
{
	//is black's second capture condition satisfied?
	//this condition is described at the top of this file as:
		// 2) start even-numbered row, going left
	if (initialRowParity == Even && captureDirection == Left) return true;
	return false;
}

bool B_Capture3()
{
	//is black's third capture condition satisfied?
	//this condition is described at the top of this file as:
		// 3) start odd-numbered row, going right
	if (initialRowParity == Odd && captureDirection == Right) return true;
	return false;
}

bool B_Capture4()
{
	//is black's fourth capture condition satisfied?
	//this condition is described at the top of this file as:
		// 4) start even-numbered row, going right
	if (initialRowParity == Even && captureDirection == Right) return true;
	return false;
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

bool isCapture() {
	//is a capture occuring?

	//check for the capture conditions described at the top of this file
	// 1) color held by char turn

	// 2) determine oddness/evenness of initial square's row
	initialRowParity = getRowParity(squares[selected].row());

	// 3) determine capture direction
	//captureDirection = getCapDirection(&squares[selected].square(), &squares[targeted].square());
	auto squares_selected = squares[selected].square();
	auto squares_targeted = squares[targeted].square();
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

void error(std::string message)
{
	throw message;
}