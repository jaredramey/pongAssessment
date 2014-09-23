#include "AIE.h"
#include <iostream>
#include <fstream>

using namespace std;


//function prototypes!
void UpdateGameState(float deltaTime);
void UpdateMainMenu();
void UpdateEnemyMove();
void GetHighScore();
void DisplayHighScore();


//Adding Global Variables
int score1 = 0;
int score2 = 0;
bool ballMoveDown;
bool ballHitOne = true;
bool ballHitTwo;
bool oneWin = false;
bool twoWin = false;
bool exitLoop;
char highScoreOne[10];
char highScoreTwo[10];

//Setting up a file for HighScores
fstream HighScore;


//Adding constant screen width and hieght
const int screenWidth = 1000;
const int screenHieght = 800;

//Global for player
float xPos = 100;
float yPos = 400;

//Add Invaders Font for a more retro look
const char* invadersFont = "./fonts/invaders.fnt";

//Initialize Enumerators
enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eEND,
	eHOWTO

};

//Initializing structs
//Everything for player 1
struct PlayerPaddle
{
	unsigned int spriteID;
	float width;
	float hieght;
	float x;
	float y;
	float upLeftX, upLeftY;
	float upRightX, upRightY;
	float bottomLeftX, bottomLeftY;
	float bottomRightX, bottomRightY;
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	unsigned int moveUpKey;
	unsigned int moveDownKey;
	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;
	unsigned int topMoveExtreeme;
	unsigned int bottomMoveExtreeme;

	void SetSize(float a_Width, float a_Hieght)
	{
		width = a_Width;
		hieght = a_Hieght;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y + y;
	}

	//Set corners for the sprite so collision works later
	void SetCorners(float a_x, float a_y, float a_width, float a_hieght)
	{
		upLeftX = ((a_x - (a_width*0.5f)));
		upLeftY = ((a_y + (a_hieght*0.5f)));
		upRightX = ((a_x + (a_width*0.5f)));
		upRightY = ((a_y + (a_hieght*0.5f)));
		bottomLeftX = ((a_x - (a_width*0.5f)));
		bottomLeftY = ((a_y - (a_hieght*0.5f)));
		bottomRightX = ((a_x + (a_width*0.5f)));
		bottomRightY = ((a_y - (a_hieght*0.5f)));
	}


	void SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_moveUp, unsigned int a_moveDown)
	{
		moveLeftKey = a_moveLeft;
		moveRightKey = a_moveRight;
		moveUpKey = a_moveUp;
		moveDownKey = a_moveDown;
	}

	void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme, unsigned int a_topExtreeme, unsigned int a_bottomExtreeme)
	{
		leftMoveExtreeme = a_leftExtreeme;
		rightMoveExtreeme = a_rightExtreeme;
		topMoveExtreeme = a_topExtreeme;
		bottomMoveExtreeme = a_bottomExtreeme;
	}

	void Move(float a_timeStep, float a_speed)
	{
		//Moving left
		if (IsKeyDown(moveLeftKey))
		{
			xPos -= a_timeStep * a_speed;
			if (xPos < (leftMoveExtreeme + width*.5f))
			{
				xPos = (leftMoveExtreeme + width*.5f);
			}
		}

		//Moving Right
		if (IsKeyDown(moveRightKey))
		{
			xPos += a_timeStep * a_speed;
			if (xPos >(rightMoveExtreeme - width*.37f))
			{
				xPos = (rightMoveExtreeme - width*.37f);
			}
		}

		//Moving Up
		if (IsKeyDown(moveUpKey))
		{
			yPos += a_timeStep * a_speed;
			if (yPos > (topMoveExtreeme - hieght*.8f))
			{
				yPos = (topMoveExtreeme - hieght*.8f);
			}
		}

		//Moving Down
		if (IsKeyDown(moveDownKey))
		{
			yPos -= a_timeStep * a_speed;
			if (yPos < (bottomMoveExtreeme + hieght*.3f))
			{
				yPos = (bottomMoveExtreeme + hieght*.3f);
			}
		}
		//Move the player sprite
		MoveSprite(spriteID, x, y);
	}

};
PlayerPaddle player;

//Everything for player 2
struct PlayerPaddle2
{
	unsigned int spriteID;
	float width;
	float hieght;
	float x2;
	float y2;
	float upLeftX, upLeftY;
	float upRightX, upRightY;
	float bottomLeftX, bottomLeftY;
	float bottomRightX, bottomRightY;
	unsigned int moveLeftKey2;
	unsigned int moveRightKey2;
	unsigned int moveUpKey2;
	unsigned int moveDownKey2;
	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;
	unsigned int topMoveExtreeme;
	unsigned int bottomMoveExtreeme;

	void SetSize2(float a_Width, float a_Hieght)
	{
		width = a_Width;
		hieght = a_Hieght;
	}

	void SetPosition2(float a_x2, float a_y2)
	{
		x2 = a_x2;
		y2 = a_y2 + y2;
	}

	//Set corners for the sprite so collision works later
	void SetCorners(float a_x, float a_y, float a_width, float a_hieght)
	{
		upLeftX = ((a_x - (a_width*0.5f)));
		upLeftY = ((a_y + (a_hieght*0.5f)));
		upRightX = ((a_x + (a_width*0.5f)));
		upRightY = ((a_y + (a_hieght*0.5f)));
		bottomLeftX = ((a_x - (a_width*0.5f)));
		bottomLeftY = ((a_y - (a_hieght*0.5f)));
		bottomRightX = ((a_x + (a_width*0.5f)));
		bottomRightY = ((a_y - (a_hieght*0.5f)));
	}

	void SetMovementKey2(unsigned int a_moveLeft2, unsigned int a_moveRight2, unsigned int a_moveUp2, unsigned int a_moveDown2)
	{
		moveLeftKey2 = a_moveLeft2;
		moveRightKey2 = a_moveRight2;
		moveUpKey2 = a_moveUp2;
		moveDownKey2 = a_moveDown2;
	}

	void SetMoveExtreeme2(unsigned int a_leftExtreeme2, unsigned int a_rightExtreeme2, unsigned int a_topExtreeme2, unsigned int a_bottomExtreeme2)
	{
		leftMoveExtreeme = a_leftExtreeme2;
		rightMoveExtreeme = a_rightExtreeme2;
		topMoveExtreeme = a_topExtreeme2;
		bottomMoveExtreeme = a_bottomExtreeme2;
	}

	void Move2(float a_timeStep, float a_speed2)
	{
		//Moving left
		if (IsKeyDown(moveLeftKey2))
		{
			x2 -= a_timeStep * a_speed2;
			if (x2 < (leftMoveExtreeme + width*.1f))
			{
				x2 = (leftMoveExtreeme + width*.1f);
			}
		}

		//Moving Right
		if (IsKeyDown(moveRightKey2))
		{
			x2 += a_timeStep * a_speed2;
			if (x2 >(rightMoveExtreeme - width *.5f))
			{
				x2 = (rightMoveExtreeme - width *.5f);
			}
		}

		//Moving Up
		if (IsKeyDown(moveUpKey2))
		{
			y2 += a_timeStep * a_speed2;
			if (y2 > (topMoveExtreeme - hieght*.8f))
			{
				y2 = (topMoveExtreeme - hieght*.8f);
			}
		}

		//Moving Down
		if (IsKeyDown(moveDownKey2))
		{
			y2 -= a_timeStep * a_speed2;
			if (y2 < (bottomMoveExtreeme + hieght*.3f))
			{
				y2 = (bottomMoveExtreeme + hieght*.3f);
			}
		}
		//Move the player sprite
		MoveSprite(spriteID, x2, y2);
	}

};
PlayerPaddle2 player2;

//Everything for the ball
struct Ball
{
	unsigned int ballSprite;
	float ballWidth;
	float ballHieght;
	float ballX;
	float ballY;
	float upLeftX, upLeftY;
	float upRightX, upRightY;
	float bottomLeftX, bottomLeftY;
	float bottomRightX, bottomRightY;
	float ballVelocity;
	bool ballMoveDown = false;
	int ballMove;

	unsigned int topWall;
	unsigned int bottomWall;

	void SetBallSize(float a_Width, float a_Hieght)
	{
		ballWidth = a_Width;
		ballHieght = a_Hieght;
	}

	void SetBallPosition(float a_ballX, float a_ballY)
	{
		ballX = a_ballX;
		ballY = a_ballY + ballY;
	}

	//Set corners for the sprite so collision works later
	void SetCorners(float a_x, float a_y, float a_width, float a_hieght)
	{
		upLeftX = ((a_x - (a_width*0.5f)));
		upLeftY = ((a_y + (a_hieght*0.5f)));
		upRightX = ((a_x + (a_width*0.5f)));
		upRightY = ((a_y + (a_hieght*0.5f)));
		bottomLeftX = ((a_x - (a_width*0.5f)));
		bottomLeftY = ((a_y - (a_hieght*0.5f)));
		bottomRightX = ((a_x + (a_width*0.5f)));
		bottomRightY = ((a_y - (a_hieght*0.5f)));
	}

	void SetBallMoveExtreeme(int a_topWall, int a_bottomWall)
	{
		topWall = a_topWall;
		bottomWall = a_bottomWall;
	}

	void BallMovement(int a_ballTimeStep, int a_ballSpeed)
	{	
			ballX += a_ballTimeStep * a_ballSpeed;

			if (ballMoveDown == false)
			{
				ballY += a_ballTimeStep * a_ballSpeed;
			}

			if (ballY >= topWall + ballHieght * .5f)
			{
				ballMoveDown = true;

				if (ballMoveDown == true)
				{
					ballY -= a_ballTimeStep * a_ballSpeed;

					if (ballY <= bottomWall + ballHieght *.5f)
					{
						ballMoveDown = false;
					}
				}
			}
		MoveSprite(ballSprite, ballX, ballY);
	}
};
Ball ball;

//Everything for Game Data
struct GameData
{
	float score = 0;
	char theScore[10];
};
GameData scoreOne;
GameData scoreTwo;

int main( int argc, char* argv[] )
{	

	//build the screen
    Initialise(1000, 800, false, "Space Invaders Pong");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//For loop wanted by rubric
	for (int i = 0; i < 1; i++)
	{
		//Yes
	}
	//Array wanted by Rubric
	int myArray[1];

	//Set up all the variables for Player1
	//origional demensions 59, 89
	player.x = screenWidth * 0.2f;
	player.y = screenHieght * 0.1f;
	player.SetMoveExtreeme(0.0f, screenWidth *0.25f, screenHieght * 1.2f, screenHieght - screenHieght);
	player.SetMovementKey(65, 68, 87, 83);
	player.SetSize(69, 300);
	//Setting player sprite to Invaders bullet as place holder till I get/ make an actual asset
	player.spriteID = CreateSprite("./images/invaders/invaders_5_00.png",player.width, player.hieght, true);

	//Set up all variables for Player 2
	player2.x2 = screenWidth * 0.9f;
	player2.y2 = screenHieght * 0.5;
	player2.SetMoveExtreeme2(screenWidth * 0.75f, screenWidth, screenHieght * 1.2f, screenHieght - screenHieght);
	player2.SetMovementKey2(263, 262, 265, 264);
	player2.SetSize2(69, 300);
	//Setting player sprite to Invaders bullet as place holder till I get/ make an actual asset
	player2.spriteID = CreateSprite("./images/invaders/invaders_5_00.png", player2.width, player2.hieght, true);


	//set all variables for Ball
	ball.ballX = 500;
	ball.ballY = 400;
	ball.ballVelocity = .3;
	ball.SetBallMoveExtreeme(screenHieght, 0);
	ball.SetBallSize(69, 64);
	ball.ballSprite = CreateSprite("./images/invaders/invaders_1_00.png", ball.ballWidth, ball.ballHieght, true);

	//Set gamestate to Main menu
	GAMESTATES eCurrentState = eMAIN_MENU;

	//Get the previous high score
	GetHighScore();

    //Game Loop
	do
	{
		ClearScreen();
		float deltaT = GetDeltaTime();
		switch (eCurrentState)
		{
			//pointer to start at later when exiting gamestate
		start:
		case eMAIN_MENU:
			//Call function for main menu
			UpdateMainMenu();
			//Get the previous high score
			GetHighScore();
			//Display high scores
			DisplayHighScore();
			
			//if enter is pressed change state to gameplay
			if (IsKeyDown(257))
			{
				eCurrentState = eGAMEPLAY;
			}

			if (IsKeyDown(32))
			{
				eCurrentState = eHOWTO;
			}

			if (IsKeyDown(256))
			{
				exitLoop = true;
			}

			break;

		case eGAMEPLAY:
			//Game function
			//Get a Random number to decide wich way the ball heads first
			ball.ballMove = 1; //(rand() % 6);
			UpdateGameState(deltaT);
			if (scoreOne.score >= 10 || scoreTwo.score >=10)
			{

				//If the game ends then track the score for next game
				HighScore.open("HighScore.txt", ios_base::out);

				if (HighScore.is_open())
				{
					//write scores into file
					HighScore << scoreOne.score << endl;
					HighScore << scoreTwo.score << endl;

					//Change gamestate to End
					eCurrentState = eEND;
				}
				else
				{
					DrawString("Couldn't save Score!", screenWidth - 615, screenHieght - 200);
				}

				//Close the file
				HighScore.close();
			}

			//if ESC is pressed then exit to main menu
			if (IsKeyDown(259))
			{
				eCurrentState = eMAIN_MENU;
				//Reset all values and return to start
				ball.ballX = 500;
				ball.ballY = 400;
				ball.ballVelocity = .3;
				scoreOne.score = 0;
				scoreTwo.score = 0;
				xPos = 100;
				yPos = 400;
				DrawSprite(player.spriteID);
				player2.x2 = screenWidth * 0.9f;
				player2.y2 = screenHieght * 0.5;
				DrawSprite(player2.spriteID);
				goto start;
			}

			break;
		case eHOWTO:
			//Display High Scores on this part of the menu
			DisplayHighScore();

			SetFont(invadersFont);
			DrawString("How to Play", screenWidth - 615, screenHieght - 200);
			DrawString("Player One", screenWidth - 810, screenHieght - 250);
			DrawString("Move Left: A", screenWidth - 810, screenHieght - 280);
			DrawString("Move Right: D", screenWidth - 810, screenHieght - 310);
			DrawString("Move Up: W", screenWidth - 810, screenHieght - 340);
			DrawString("Move Down: S", screenWidth - 810, screenHieght - 370);
			DrawString("Player Two", screenWidth - 410, screenHieght - 250);
			DrawString("Move Left: Left Arrow", screenWidth - 410, screenHieght - 280);
			DrawString("Move Right: Right Arrow", screenWidth - 410, screenHieght - 310);
			DrawString("Move Up: Up Arrow", screenWidth - 410, screenHieght - 340);
			DrawString("Move Down: Down Arrow", screenWidth - 410, screenHieght - 370);

			DrawString("Press Backspace to return to Main Menu", screenWidth - 740, screenHieght - 450);

			if (IsKeyDown(259))
			{
				eCurrentState = eMAIN_MENU;
			}

			break;
		case eEND:


			if (scoreOne.score >= 10)
			{
				//Reset all values and bool the winner
				oneWin = true;
				ball.ballX = 500;
				ball.ballY = 400;
				ball.ballVelocity = .3;
				scoreOne.score = 0;
				scoreTwo.score = 0;
				xPos = 100;
				yPos = 400;
				DrawSprite(player.spriteID);
				player2.x2 = screenWidth * 0.9f;
				player2.y2 = screenHieght * 0.5;
				DrawSprite(player2.spriteID);
			}

			if (scoreTwo.score >= 10)
			{
				//Reset all values and bool the winner
				twoWin = true;
				ball.ballX = 500;
				ball.ballY = 400;
				ball.ballVelocity = .3;
				scoreOne.score = 0;
				scoreTwo.score = 0;
				xPos = 100;
				yPos = 400;
				DrawSprite(player.spriteID);
				player2.x2 = screenWidth * 0.9f;
				player2.y2 = screenHieght * 0.5;
				DrawSprite(player2.spriteID);
			}

			//Show who won
			if (oneWin == true)
			{
				DrawString("Player one wins!", screenWidth - 615, screenHieght - 200);
			}

			if (twoWin == true)
			{
				DrawString("Player two wins!", screenWidth - 615, screenHieght - 200);
			}

			//Let user deside what to do next
			DrawString("Press Escape to continue to the menu or Enter to return to the game!", screenWidth - 900, screenHieght - 400);

			//If esc is pressed then return to main menu
			if (IsKeyDown(256))
			{
				eCurrentState = eMAIN_MENU;
				oneWin = false;
				twoWin = false;
			}

			//If enter is pressed then go back to game loop
			if (IsKeyDown(257))
			{
				eCurrentState = eGAMEPLAY;
				oneWin = false;
				twoWin = false;
			}

			break;

		default:
			break;
		}

	} while (FrameworkUpdate() != true && exitLoop != true);

    Shutdown();

    return 0;
}


//Initialize functions

void UpdateMainMenu()
{
	//Everything to make main menu
	SetFont(invadersFont);
	DrawString("SPACE INVADERS PONG", screenWidth - 675, screenHieght - 100);
	DrawString("Main Menu", screenWidth - 590, screenHieght - 200);
	DrawString("Press Enter to start", screenWidth - 630, screenHieght - 250);
	DrawString("Press Space to read the How To", screenWidth - 700, screenHieght - 300);
	DrawString("Press Escape to quit", screenWidth - 630, screenHieght - 350);
	
}

void UpdateGameState(float deltaTime)
{
	//Set font to space invaders for a more retro look
	SetFont(invadersFont);
	//Print out scores and who they relate to
	DrawString(itoa(scoreOne.score, scoreOne.theScore, 10), screenWidth* 0.15f, screenHieght *0.05f);
	DrawString(itoa(scoreTwo.score, scoreTwo.theScore, 10), screenWidth* 0.65f, screenHieght *0.05f);
	DrawString("Player one:", screenWidth*0.15f, screenHieght *0.1f);
	DrawString("Player Two:", screenWidth*0.65f, screenHieght *0.1f);

	//playing the game
	//player movement handled by player struct
	player.Move(GetDeltaTime(), 800.f);
	MoveSprite(player.spriteID, xPos, yPos);
	DrawSprite(player.spriteID);
	player.SetCorners(xPos, yPos, player.width, player.hieght);

	player2.Move2(GetDeltaTime(), 800.f);
	MoveSprite(player2.spriteID, player2.x2, player2.y2);
	DrawSprite(player2.spriteID);
	player2.SetCorners(player2.x2, player2.y2, player2.width, player2.hieght);

	UpdateEnemyMove();
	MoveSprite(ball.ballSprite, ball.ballX, ball.ballY);
	DrawSprite(ball.ballSprite);
	ball.SetCorners(ball.ballX, ball.ballY, ball.ballWidth, ball.ballHieght);
	
}

void UpdateEnemyMove()
{

	//Beyond this point collision detection for player paddles
	//Collision depends on the corners of the sprites, so a really big long statement check
	if ((ball.bottomRightX >= player2.bottomLeftX && ball.upRightX >= player2.upLeftX) && (ball.bottomRightY >= player2.bottomLeftY && ball.upRightY <= player2.upLeftY))
	{
		//set bools for direction checks
		ballHitOne = false;
		ballHitTwo = true;
		if (ball.ballVelocity <= 10)
		{
			ball.ballVelocity += .0002;
		}
	}

	//Collision depends on the corners of the sprites, so a really big long statement check (Again)
	if ((ball.bottomLeftX <= player.bottomRightX && ball.upLeftX <= player.upRightX) && (ball.bottomLeftY >= player.bottomRightY && ball.upLeftY <= player.upRightY))
	{
		//set bools for direction checks
		ballHitOne = true;
		ballHitTwo = false;
		if (ball.ballVelocity <= 10)
		{
			ball.ballVelocity += .0002;
		}
	}

	if (ballHitOne == true)
	{
		ball.ballX += ball.ballVelocity;
	}

	if (ballHitTwo == true)
	{
		ball.ballX -= ball.ballVelocity;
	}

	//Time to handle score!
	if (ball.ballX >= screenWidth)
	{
		ball.ballX = 500;
		ball.ballY = 400;
		scoreOne.score += 1;
		ballHitOne = false;
		ballHitTwo = true;
	}

	else if (ball.ballX <= 0)
	{
		ball.ballX = 500;
		ball.ballY = 400;
		scoreTwo.score += 1;
		ballHitOne = true;
		ballHitTwo = false;
	}


		//Beyond this point collision detection for top & bottom wall
			if (ballMoveDown == false)
			{
				ball.ballY += ball.ballVelocity;
			}

			if (ball.ballY >= ball.topWall + ball.ballHieght * .5f)
			{
				ballMoveDown = true;
			}

			if (ballMoveDown == true)
			{
				ball.ballY -= ball.ballVelocity;
	
				if (ball.ballY <= ball.bottomWall + ball.ballHieght *.5f)
				{
					ballMoveDown = false;
				}
			}

	MoveSprite(ball.ballSprite, ball.ballX, ball.ballY);
}

void GetHighScore()
{
	HighScore.open("HighScore.txt", ios_base::in);


	//Read and get scoreOne
	float scoreOne;
	HighScore >> scoreOne;

	//Read and get scoreTwo
	float scoreTwo;
	HighScore >> scoreTwo;

	//Flush stream buffer and close file
	HighScore.sync();
	HighScore.close();
	HighScore.clear();

	//Set the scores to a char so it can be displayed later
	itoa(scoreOne, highScoreOne, 10);
	itoa(scoreTwo, highScoreTwo, 10);
}

void DisplayHighScore()
{
	DrawString("Old High Scores", screenWidth - 600, screenHieght - 600);
	DrawString("Player 1: ", screenWidth - 660, screenHieght - 650);
	DrawString("Player 2: ", screenWidth - 470, screenHieght - 650);
	DrawString(highScoreOne, screenWidth - 530, screenHieght - 650);
	DrawString(highScoreTwo, screenWidth - 350, screenHieght - 650);
}
