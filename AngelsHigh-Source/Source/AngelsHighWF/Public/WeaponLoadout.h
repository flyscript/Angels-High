/*
WeaponLoadout.h
Will Chapman

09/08/2019
19/08/2019

	Header file for a class that describes how weapons are loaded onto an aircraft
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponMapping.h"
#include "WeaponLoadout.generated.h"

UCLASS()
class ANGELSHIGHWF_API AWeaponLoadout : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponLoadout();

	/**
		Array of weapon mappings that describe how weapons fit onto the aircraft
	
		NOTE: This was going to be a TArray of SubclassOf<AWeaponMapping> so that I could select as many different mappings as
				I wanted from a dropdown in UE4 editor when setting up loadouts, but that makes the values impossible to deal
				with because they're class TYPES, not objects.

				So, instead, I've had to make them UChildActorComponents, who I then set the class type of to the correct mapping
				in UE4 editor, and in code on the BeinPlay I cast its child actor to a weaponmapping. The issue here is that I can't
				do this with a TArray of ChildActorComponents, because I can't then set them to anything. So, instead, the best option
				seems to be to create 3 or 4 separate ChildActorComponents and then cast and put them into a TArray of WeaponMappings
				as appropriate that can then be iterated through later.

				I would do this via an array to avoid repetitive code in the constructor, but that would result in the same issue of not
				being able to set the actual class type of the child actor, so reptitive code it is :(

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		TArray<AWeaponMapping*> m_aWeaponMappings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		TArray<UChildActorComponent*> m_aMappings;
	*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		USceneComponent* m_aSceneRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		UChildActorComponent* m_aWeaponMapping1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		UChildActorComponent* m_aWeaponMapping2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		UChildActorComponent* m_aWeaponMapping3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
		UChildActorComponent* m_aWeaponMapping4;

	//Container of weapon mappings
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Mapping")
	TArray<AWeaponMapping*> m_aWeaponMappings;

private:

	//Container of weapon mappings
	//TArray<AWeaponMapping*>* m_aWeaponMappings;

	AWeaponMapping* m_pWeaponMapping1;
	AWeaponMapping* m_pWeaponMapping2;
	AWeaponMapping* m_pWeaponMapping3;
	AWeaponMapping* m_pWeaponMapping4;

	//Whether or not the mapping has been registered into the array yet
	bool m_bMapped;

	//How many weapons there are in this laodout, autofilled by generateMap()
	int m_iSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns the array of mappings
	/*TArray<AWeaponMapping*>**/ void GenerateMap();

	//Returns the number of weapons in the loadout when ready
	int MapSize();
	
	//Returns whether or not the loadout is ready for use
	bool Ready();

};
