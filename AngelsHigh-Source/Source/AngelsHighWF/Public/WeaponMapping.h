/*
WeaponMapping.h
Will Chapman

09/08/2019
11/08/2019

	Header file for a class that describes where on an aircraft weapons are located

*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.h"
#include "WeaponMapping.generated.h"

UCLASS()
class ANGELSHIGHWF_API AWeaponMapping : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponMapping();

	/**
		This an actor representing the weapon that will be used
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		UChildActorComponent* m_aWeaponActor;
	
	/**
		Array of hardpoint locations that describe how weapons fit onto the aircraft
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Hardpoints")
		TArray<int> m_aHardpoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Holds reference to the actual weapon used
	AWeaponBase* m_pWeapon;

	//Whether or not the mapping is ready for use
	bool m_bReady;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns the weapon to be used in these locations
	AWeaponBase* GetWeapon();

	//Returns whether or not the mapping is ready for use
	bool Ready();

	//Gets the mapping ready
	void Generate();
};
