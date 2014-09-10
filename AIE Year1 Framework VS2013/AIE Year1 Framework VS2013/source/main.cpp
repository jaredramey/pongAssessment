#include "AIE.h"
#include <iostream>


//function prototypes!
void UpdateGameState(float deltaTime);
void UpdateMainMenu();


//Adding Global Variables

//Adding constant screen width and hieght
const int screenWidth = 700;
const int screenHieght = 600;

//Global for player
float xPos = 100;
float yPos = 300;

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
			if (xPos >(rightMoveExtreeme - width*.5f))
			{
				xPos = (rightMoveExtreeme - width*.5f);
			}
		}

		//Moving Up
		if (IsKeyDown(moveUpKey))
		{
			yPos += a_timeStep * a_speed;
			if (yPos > (topMoveExtreeme + hieght*.5f))
			{
				yPos = (topMoveExtreeme + hieght*.5f);
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
			if (xPos >(rightMoveExtreeme - width*.5f))
			{
				xPos = (rightMoveExtreeme - width*.5f);
			}
		}

		//Moving Up
		if (IsKeyDown(moveUpKey))
		{
			yPos += a_timeStep * a_speed;
			if (yPos > (topMoveExtreeme + hieght*.5f))
			{
				yPos = (topMoveExtreeme + hieght*.5f);
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
PlayerPaddle2 player2;


int main( int argc, char* argv[] )
{	

	//build the screen
    Initialise(700, 800, false, "Pong clone");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//Set up all the variables for Player1
	//origional demensions 59, 89
	player.x = screenWidth * 0.2f;
	player.y = screenHieght * 0.5f;
	player.SetMoveExtreeme(0.0f, screenWidth *0.4f, screenHieght * 1.2f, screenHieght - screenHieght);
	player.SetMovementKey('A', 'D', 'W', 'S');
	player.SetSize(69, 96);
	//Setting player sprite to Invaders bullet as place holder till I get/ make an actual asset
	player.spriteID = CreateSprite("./images/invaders/invaders_5_00.png",player.width, player.hieght, true);

	player2.x = screenWidth - 100;
	player2.y = 350;
	player2.SetMoveExtreeme(0.0f, screenWidth *0.4f, screenHieght * 1.2f, screenHieght - screenHieght);
	player2.SetMovementKey(263, 262, 265, 264);
	player2.SetSize(69, 96);
	//Setting player sprite to Invaders bullet as place holder till I get/ make an actual asset
	player.spriteID = CreateSprite("./images/invaders/invaders_5_00.png", player.width, player.hieght, true);

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
	DrawString("PRESS ENTER YOU FOOL", screenWidth * 0.2f, screenHieght * 0.5);
	
}

void UpdateGameState(float deltaTime)
{
	//playing the game
	//player movement handled by player struct
	player.Move(GetDeltaTime(), 150.f);
	MoveSprite(player.spriteID, xPos, yPos);
	DrawSprite(player.spriteID);


	SetFont(invadersFont);
	DrawString("It's working", screenWidth * 0.35f, screenHieght * 0.1f);

}
