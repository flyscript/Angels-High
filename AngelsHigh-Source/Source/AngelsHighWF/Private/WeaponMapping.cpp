/*
WeaponMapping.h
Will Chapman

09/08/2019
11/08/2019

	Header file for a class that describes where on an aircraft weapons are located

*/

#include "WeaponMapping.h"

// Sets default values
AWeaponMapping::AWeaponMapping()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_aWeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon1"));
	m_aWeaponActor->SetupAttachment(RootComponent);

	m_bReady = false;
}

// Called when the game starts or when spawned
void AWeaponMapping::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponMapping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AWeaponBase* AWeaponMapping::GetWeapon()
{
	return m_pWeapon;
}


void AWeaponMapping::Generate()
{
	//Set reference
	m_pWeapon = Cast<AWeaponBase>(m_aWeaponActor->GetChildActor());

	m_bReady = true;
}

bool AWeaponMapping::Ready()
{
	return m_bReady;
}
