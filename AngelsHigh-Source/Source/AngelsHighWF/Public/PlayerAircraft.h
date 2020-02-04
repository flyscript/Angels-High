/*
PlayerAircraft.h
Will Chapman

09/07/2019
19/08/2019

	Header file for a class that handles all of the player interaction with an aircraft

*/

#pragma once

#include "AircraftBase.h"
#include "CockpitModel.h"
#include "Components/WidgetComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "WeaponBase.h"
#include "WeaponPoolBase.h"

#include "PlayerAircraft.generated.h"

/**
 * Handles all of the player interaction with an aircraft
 */
UCLASS()
class ANGELSHIGHWF_API APlayerAircraft : public AAircraftBase
{
	GENERATED_BODY()

public:
	APlayerAircraft();
	
	/**
		Child Actor that will contain cockpit model
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UChildActorComponent* m_aCockpitComponent;
	
	/**
		Cockpit HUD
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "UI")
		UWidgetComponent* m_wCockpitHUD;

	/**
		3rd Person HUD
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "UI")
		UWidgetComponent* m_wThirdPersonHUD;

	/**
		Bullet Pool
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UChildActorComponent* m_aBulletPoolComponent;

	//Holds the actual bullet pool
	AWeaponPoolBase* m_pBulletPool;


	/*
		Cameras
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Cameras")
		bool m_bIsFirstPerson;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mCockpitCameraRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Cameras")
		UCameraComponent* m_cCockpitCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mThirdCameraRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mThirdCameraVRRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Cameras")
		UCameraComponent* m_cThirdCamera;

	/**
		How much the angle of the camera will be deflected during a turn in the cockpit
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Cameras")
		float m_f1stCameraTurningDeflection;

	/**
		How much the angle of the camera will be deflected during a turn in third person
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Cameras")
		float m_f3rdCameraTurningDeflection;
	
	/*
		SETTINGS
	*/

	/**
		The amount that thrust (a 0-1 scalar) is incremented when the relevant key is pressed
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Input_Settings")
		float m_fThrustIncrAmount;

	/**
		A scalar value that describes how quickly the smoothing action on player input acts
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Input_Settings")
		float m_fControlSmoothing;

	/**
		Sound Settings
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Sound")
		USoundAttenuation* m_aCockpitAttenuation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Sound")
		USoundAttenuation* m_aThirdPersonAttenuation;

	//Cannon heat
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		float m_fCannonHeat;
	
	//The kind of particle effect given off by the cannon
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapons")
		UParticleSystem* m_pCannonParticleEffect;


private:

	/**
		Reference to the cockpit model
	*/
	ACockpitModel* m_aCockpitModel;

	/**
		This is a rotator for class-wide use - not creating or using a new rotator each tick and each thing
	*/
	FRotator m_rRotator;

	/**
		This is a vector for class-wide use - not creating or using a new vector each tick
	*/
	FVector m_vVector;
	
	/*
		Camera Smoothing values
	*/
	bool m_bLookingBehind;
	bool m_bCanChangeCamera;
	bool m_bTweenIntoFirstPerson;
	float m_fCameraShake;
	FVector m_v1stCameraTurningDeflection;
	FVector m_v3rdCameraTurningDeflection;
	FVector m_v1stCameraTargetRotation;
	FVector m_v3rdCameraTargetRotation;
	FVector m_v1stCameraCurrentRotation;
	FVector m_v3rdCameraCurrentRotation;

	//Whether to track the axis or the increments
	bool m_bTrackThrustAxis;

	/*
		Basic reloading values
	*/
	bool m_bCannonFiring;
	bool m_bCannonCooling;
	float m_fLastCannonFire;
	int m_iCurrentWeapon;

	/*
		Input tracking values
	*/
	float m_fCurrentPitchInput;
	float m_fTargetPitchInput;
	float m_fCurrentRollInput;
	float m_fTargetRollInput;
	float m_fCurrentYawInput;
	float m_fTargetYawInput;
	float m_fCurrentThrustInput;
	float m_fTargetThrustInput;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireBullet();

	UFUNCTION(BlueprintCallable)
		void ReleaseBullet(AWeaponBase* a_aBullet);

	UFUNCTION(BlueprintCallable)
		bool CannonCooling();

	UFUNCTION(BlueprintCallable)
		FName CurrentWeaponName();

	/*
		Input setting functions
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void TogglePause();
	virtual void SetCannon(float a_fAxisValue);
	virtual void SetPitch(float a_fAxisValue) override;
	virtual void SetRoll(float a_fAxisValue) override;
	virtual void SetYaw(float a_fAxisValue) override;
	virtual void SetThrust(float a_fAxisValue) override;
	void IncrThrust();
	void DecrThrust();
	void WeaponCycleForward();
	void WeaponCycleBackward();

	/*
		Camera functions
	*/
	void ToggleCamera();
	void ChangeCamera();
	void SetCameraPan(float a_fAxisValue);
	void SetCameraTilt(float a_fAxisValue);
	void ToggleLookBehind();
	
	/*
		Getters
	*/
	float GetCannonHeat();
};
