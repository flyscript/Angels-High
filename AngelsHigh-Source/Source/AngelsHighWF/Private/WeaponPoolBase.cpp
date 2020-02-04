/*
WeaponPoolBase.CPP
Will Chapman

29/07/2019
07/08/2019

	CPP file for generating a pool of weapons, so that a new one isn't instantiated every time one is needed

*/


#include "WeaponPoolBase.h"
#include "Engine/Classes/engine/World.h"

// Sets default values
AWeaponPoolBase::AWeaponPoolBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponPoolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponPoolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponPoolBase::GeneratePool_Implementation()
{
	//create pool
}

AWeaponBase* AWeaponPoolBase::GetNext_Implementation()
{
	/*
	//If we have something free
	if (m_iNext < m_iSize)
	{
		//Get address of object located at next pointer
		const int i_positionPointer = m_iNext;

		//Increase pointer, note: if it's now the size of the array then there aren't any left
		m_iNext++;

		//Return address of object located at the old pointer
		return m_pPool[i_positionPointer];
	}
	else
	{
		//throw std::overflow_error(__FILE__ ": <Pool Error>: No available objects left in pool. Try releasing some objects");
		return nullptr;
	}
	*/
	return m_aCache;
}

void AWeaponPoolBase::Release_Implementation(AWeaponBase* a_pAddress)
{
	/*
	//To hold the position of the given address in the array, if and when we find it
	int i_addressPositionInArray = -1;

	//Loop from start to finish to find location of this address in the array
	for (int i_location = 0; i_location < m_iSize; i_location++)
	{
		if (m_pPool[i_location] == a_pAddress)
		{
			i_addressPositionInArray = i_location;
			break;
		}
	}

	//If found then sort array, otherwise throw an exception
	if (i_addressPositionInArray > -1 && i_addressPositionInArray < m_iNext)
	{
		//Make sure where we're slotting the released object into is valid
		int lastActive = m_iNext - 1;
		if (lastActive < 0)
		{
			//throw std::range_error(__FILE__ ": <Pool Error>: Released object can never be out of pool scope");
		}

		//Swap contents of this array address and last active array address. This sorts array into half active, half free
		AWeaponBase* lastActiveAddress = m_pPool[lastActive];
		m_pPool[lastActive] = a_pAddress;
		m_pPool[i_addressPositionInArray] = lastActiveAddress;

		//Decrement the pointer to the next active object, which will point it to this newly released object as it is now first in the list of free objects
		m_iNext--;

	}
	else
	{
		//throw std::range_error(__FILE__ ": <Pool Error>: Given Address was not found in active pool or was already inactive");
	}
	*/
}