/*
WeaponModel.cpp
Will Chapman

27/07/2019
06/08/2019

	CPP file for generating the physical properties of an aircraft

*/

#include "WeaponModel.h"

// Sets default values
AWeaponModel::AWeaponModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup scene root
	m_mSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	m_mSceneRoot->SetupAttachment(RootComponent);

	//Setup the mesh of the body
	m_mBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Body"));
	m_mBodyMesh->SetupAttachment(m_mSceneRoot);

	//Defaults:
	m_fInitialVelocity = 50000.0f;
}

// Called when the game starts or when spawned
void AWeaponModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponModel::Tick(float a_fDeltaTime)
{
	Super::Tick(a_fDeltaTime);

}
