/*
WeaponPoolBase.h
Will Chapman

29/07/2019
07/08/2019

	Header file for generating a pool of weapons, so that a new one isn't instantiated every time one is needed

*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.h"

#include "WeaponPoolBase.generated.h"

UCLASS()
class ANGELSHIGHWF_API AWeaponPoolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPoolBase();

	//Pointer to the next free position in the pool
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Pool")
		TSubclassOf<AWeaponBase> m_aBaseObject;

	//The size of the pool
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Pool")
		int m_iSize;

	//A cache used to temporarily hold an outgoing weapon, otherwise more than one may be extracted
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Pool")
		AWeaponBase* m_aCache;
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Generates the pool of objects
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pool")
		void GeneratePool();

	//Returns a weapon from the pool
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pool")
		AWeaponBase* GetNext();

	//Releases a weapon back to the pool
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pool")
		void Release(AWeaponBase* a_pAddress);
};
