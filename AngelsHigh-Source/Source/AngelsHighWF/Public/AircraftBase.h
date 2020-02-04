/*
AircraftBase.h
Will Chapman

05/06/2019
12/08/2019

	Header file for a class that handles aircraft physics and animation

*/

#pragma once

#include "AircraftModel.h"
#include "WeaponBase.h"
#include "CoreMinimal.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Core/Public/Math/Rotator.h"
#include "WeaponLoadout.h"

#include "AircraftBase.generated.h"

/**
 * Handles aircraft physics and animation
 */

//class AAircraftModel;

UCLASS()
class ANGELSHIGHWF_API AAircraftBase : public APawn
{
	GENERATED_BODY()

public:

	//Constructor
	AAircraftBase();

	/**
		Main root for the aircraft
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mSceneRoot;

	/**
		Child Actor component that will hold the aircraft model
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UChildActorComponent* m_aAircraftComponent;
	
	/**
		Child Actor component that will hold the aircraft model
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aLoadout;

	/*
		PHYSICS PROPERTIES
	*/
	
	/**
		This is the current speed of the aircraft
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics_Properties")
		float m_fCurrentSpeed;

	/**
		This is the thrust scalar 0-1 that the aircraft is attempting to reach (engines spin up at different rates)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics_Properties")
		float m_fTargetThrust;

	/**
		This is the thrust scalar 0-1 that the aircraft is _currently_ at
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics_Properties")
		float m_fCurrentThrust;

	/**
		This is the current velocity of the aircraft
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics_Properties")
		FVector m_vVelocity;

	/**
		This is the current rotational velocity of the aircraft
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics_Properties")
		FVector m_vRotVelocity;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aWeapon8;

	//The current stress on the pilot and aircraft
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics")
		float m_fGForce;

	/*
		Input tracking values
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Control")
		float m_fPitchInput;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Updates the physics of the aircraft
	virtual void PhysicsUpdate(float a_fDeltaTime);

	//Aircraft states
	bool m_bAfterburner;
	bool m_bAirbrake;

	/**
		Reference to the aircraft model
	*/
	AAircraftModel *m_aAircraftModel;

	//This is the real loudout, the above is a childactor. m_pLoadout will be set to the childactor's actor and we will access it this way.
	//Because for some stupid reason it's the only way to do this without TSubclassOf nonsense that causes crashes.
	AWeaponLoadout* m_pLoadout;


private:
	
	/**
		This is a rotator for class-wide use - not creating or using a new rotator each tick and each thing
	*/
	FRotator m_rRotator;

	/**
		The amount of thrust produced by the engine right now
	*/
	FVector m_vThrust;

	/*
		Input tracking values
	*/
	float m_fRollInput;
	float m_fYawInput;
	float m_fThrustInput;
			
	/**
		Pointers to engines
	*/
	AEngineNozzle* m_aLeftEngine;
	AEngineNozzle* m_aRightEngine;


public:	

	//Sets up loadout
	void EquipLoadout();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/*
		Input setting functions
	*/
	virtual void SetPitch(float a_fAxisValue);
	virtual void SetRoll(float a_fAxisValue);
	virtual void SetYaw(float a_fAxisValue);
	virtual void SetThrust(float a_fAxisValue);
		
};
