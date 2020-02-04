/*
AModule11_GameMode.cpp
Will Chapman

12/07/2019
19/08/2019

	CPP file for defining the game mode and default pawn, HUD, etc

*/

//#include "PlayerAircraft.h"
#include "AHWF_GameMode.h"

#include "UObject/ConstructorHelpers.h"


AAHWF_GameMode::AAHWF_GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Aircraft/FA18/FA18_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//static ConstructorHelpers::FClassFinder<APawn> HUDClassFinder(TEXT("/Game/UI/Widgets/MainScreen_HUD"));
	//HUDClass = HUDClassFinder.Class;
}