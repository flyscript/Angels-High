/*
AModule11_GameMode.h
Will Chapman

12/07/2019
12/07/2019

	Header file for defining the game mode and default pawn, HUD, etc

*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AHWF_GameMode.generated.h"


/**
 * Creates the basic game mode used for the game
 */

UCLASS()
class ANGELSHIGHWF_API AAHWF_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AAHWF_GameMode();
};
