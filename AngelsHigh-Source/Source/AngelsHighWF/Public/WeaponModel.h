/*
WeaponModel.h
Will Chapman

27/07/2019
01/30/2019

	Header file for defining the basic properties of a weapon

*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WeaponModel.generated.h"

UCLASS()
class ANGELSHIGHWF_API AWeaponModel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponModel();

	/**
		The main root of this weapon
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mSceneRoot;

	/**
		The main static mesh of this weapon
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mBodyMesh;

	/**
		The maximum damage that this weapon will inflict on something
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		float m_fDamage;

	/**
		The maximum effective radius of this weapon
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		float m_fDamageRadius;

	/**
		The initial velocity that this fires at
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
		float m_fInitialVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float a_fDeltaTime) override;


};