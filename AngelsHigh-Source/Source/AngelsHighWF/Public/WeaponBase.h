/*
WeaponBase.h
Will Chapman

27/07/2019
19/08/2019

	Header file for defining the basic properties of a weapon

*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponModel.h"

#include "WeaponBase.generated.h"

UCLASS()
class ANGELSHIGHWF_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeaponBase();

	/**
		The main root of this weapon
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mSceneRoot;
	
	/**
		Child Actor that will contain weapon model
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UChildActorComponent* m_aWeaponComponent;

	/**
		The collision mesh
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UCapsuleComponent* m_aCollisionMesh;
	
	/**
		The velocity of the weapon
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics")
		FVector m_vVelocity;

	/**
		The rotational velocity of the weapon
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Physics")
		FVector m_vRotVelocity;

	/**
		The timestamp of when this weapon was initiated
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		float m_fTimeFired;

	/**
		How long this weapon lasts before disappearing
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		float m_fLifetime;

	/**
		The name of this weapon as an FName
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		FName m_fName;

private:

	/**
		Reference to the weapon model
	*/
	AWeaponModel* m_aWeaponModel;

	/**
		Rotator used by the class so a new one isn't instantiated every tick
	*/
	FRotator m_rRotator;
	
	/**
		Whether or not this weapon is currently active
	*/
	bool m_bActive;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float a_fDeltaTime) override;

	// Instantiates the weapon
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Fire();

	//Usually used inititally, would be done internally in Fire() but it throws an "Unhandled exception" with no further info
	virtual void SetWeaponVelocity(FVector a_vNewVelocity);

	//Called when the capsule hits something
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Detonate();

	// Unique to each kind of weapon (missile, bomb, bullet), this modifies the velocity and rotvelocity of the weapon
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void PhysicsUpdate(float a_fDeltaTime);
};
