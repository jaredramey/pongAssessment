#include "AIE.h"
#include <iostream>


//function prototypes!
void UpdateGameState(float deltaTime);
void UpdateMainMenu();
void UpdateEnemyMove();


//Adding Global Variables
const char* scoreOne = "0000";
const char* scoreTwo = "0000";
bool ballMoveDown;
bool ballHitOne;
bool ballHitTwo;


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
	eEND

};

//Initializing structs
struct PlayerPaddle
{
	unsigned int spriteID;
	float width;
	float hieght;
	float x;
	float y;
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
			if (yPos > (topMoveExtreeme - hieght*.01f))
			{
				yPos = (topMoveExtreeme - hieght*.01f);
			}
		}

		//Moving Down
		if (IsKeyDown(moveDownKey))
		{
			yPos -= a_timeStep * a_speed;
			if (yPos < (bottomMoveExtreeme + hieght*.5f))
			{
				yPos = (bottomMoveExtreeme + hieght*.5f);
			}
		}
		//Move the player sprite
		MoveSprite(spriteID, x, y);
	}

};
PlayerPaddle player;

struct PlayerPaddle2
{
	unsigned int spriteID;
	float width;
	float hieght;
	float x2;
	float y2;
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
			if (x2 < (leftMoveExtreeme + width*.5f))
			{
				x2 = (leftMoveExtreeme + width*.5f);
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
			if (y2 > (topMoveExtreeme - hieght*.01f))
			{
				y2 = (topMoveExtreeme - hieght*.01f);
			}
		}

		//Moving Down
		if (IsKeyDown(moveDownKey2))
		{
			y2 -= a_timeStep * a_speed2;
			if (y2 < (bottomMoveExtreeme + hieght*.5f))
			{
				y2 = (bottomMoveExtreeme + hieght*.5f);
			}
		}
		//Move the player sprite
		MoveSprite(spriteID, x2, y2);
	}

};
PlayerPaddle2 player2;

struct Ball
{
	unsigned int ballSprite;
	float ballWidth;
	float ballHieght;
	float ballX;
	float ballY;
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


int main( int argc, char* argv[] )
{	

	//build the screen
    Initialise(1000, 800, false, "Pong clone");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//Set up all the variables for Player1
	//origional demensions 59, 89
	player.x = screenWidth * 0.2f;
	player.y = screenHieght * 0.1f;
	player.SetMoveExtreeme(0.0f, screenWidth *0.4f, screenHieght * 1.2f, screenHieght - screenHieght);
	player.SetMovementKey(65, 68, 87, 83);
	player.SetSize(69, 300);
	//Setting player sprite to Invaders bullet as place holder till I get/ make an actual asset
	player.spriteID = CreateSprite("./images/invaders/invaders_5_00.png",player.width, player.hieght, true);

	player2.x2 = screenWidth * 0.9f;
	player2.y2 = 400;
	player2.SetMoveExtreeme2(390, screenWidth, screenHieght * 1.2f, screenHieght - screenHieght);
	player2.SetMovementKey2(263, 262, 265, 264);
	player2.SetSize2(69, 300);
	//Setting player sprite to Invaders bullet as place holder till I get/ make an actual asset
	player2.spriteID = CreateSprite("./images/invaders/invaders_5_00.png", player2.width, player2.hieght, true);


	//set all variables for Ball
	ball.ballX = 500;
	ball.ballY = 400;
	ball.SetBallMoveExtreeme(screenHieght, 0);
	ball.SetBallSize(69, 64);
	ball.ballSprite = CreateSprite("./images/crate_sideup.png", ball.ballWidth, ball.ballHieght, true);

	//set bool values for ball movement
	ballMoveDown = false;
	ballHitOne = true;

	//Set gamestate to Main menu
	GAMESTATES eCurrentState = eMAIN_MENU;
	

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

			//if enter is pressed change state to gameplay
			if (IsKeyDown(257))
			{
				eCurrentState = eGAMEPLAY;
			}

			break;

		case eGAMEPLAY:
			//Game function
			//Get a Random number to decide wich way the ball heads first
			ball.ballMove = 1; //(rand() % 6);
			UpdateGameState(deltaT);

			//if ESC is pressed then exit to main menu
			if (IsKeyDown(256))
			{
				eCurrentState = eMAIN_MENU;
				goto start;
			}

			break;

		case eEND:
			break;

		default:
			break;
		}

	} while (FrameworkUpdate() != true);

    Shutdown();

    return 0;
}


//Initialize functions

void UpdateMainMenu()
{
	//Everything to make main menu
	SetFont(invadersFont);
	DrawString("PRESS ENTER YOU FOOL", screenWidth * 0.25f, screenHieght * 0.5);
	
}

void UpdateGameState(float deltaTime)
{
	//playing the game
	//player movement handled by player struct
	player.Move(GetDeltaTime(), 500.f);
	MoveSprite(player.spriteID, xPos, yPos);
	DrawSprite(player.spriteID);

	player2.Move2(GetDeltaTime(), 500.f);
	MoveSprite(player2.spriteID, player2.x2, player2.y2);
	DrawSprite(player2.spriteID);

	//ball.BallMovement(GetDeltaTime(), 100.f);
	UpdateEnemyMove();
	MoveSprite(ball.ballSprite, ball.ballX, ball.ballY);
	DrawSprite(ball.ballSprite);

	SetFont(invadersFont);
	//DrawString(scoreOne, screenWidth * 0.2f, screenHieght * 0.9f);
	
}

void UpdateEnemyMove()
{

	//Beyond this point collision detection for player paddles
	if (ballHitOne == true)
	{
		ball.ballX += 0.1f;
	}

	if (ballHitTwo == true)
	{
		ball.ballX -= 0.1f;
	}

	if ((ball.ballY + (ball.ballWidth * 0.5)) == (player2.y2 + (player2.width * 0.5)) && ball.ballWidth == (player2.y2 + (player2.hieght * 0.5)))
	{
		ballHitOne = false;
		ballHitTwo = true;
	}

	if (ball.ballX == xPos && ball.ballY == yPos)
	{
		ballHitTwo = false;
		ballHitOne = true;
	}


		//Beyond this point collision detection for top & bottom wall
			if (ballMoveDown == false)
			{
				ball.ballY += 0.1f;
			}

			if (ball.ballY >= ball.topWall + ball.ballHieght * .5f)
			{
				ballMoveDown = true;
			}

			if (ballMoveDown == true)
			{
				ball.ballY -= 0.1f;
	
				if (ball.ballY <= ball.bottomWall + ball.ballHieght *.5f)
				{
					ballMoveDown = false;
				}
			}

	MoveSprite(ball.ballSprite, ball.ballX, ball.ballY);
}
