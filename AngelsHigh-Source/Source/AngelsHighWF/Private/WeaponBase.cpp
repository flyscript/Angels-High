/*
WeaponBase.cpp
Will Chapman

27/07/2019
06/08/2019

	CPP file for generating the physical properties of a weapon

*/

#include "WeaponBase.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup scene root
	m_mSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	m_mSceneRoot->SetupAttachment(RootComponent);

	//Setup the mesh of the body
	m_aWeaponComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Component"));
	m_aWeaponComponent->SetupAttachment(m_mSceneRoot);

	//Setup the mesh of the body
	m_aCollisionMesh = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Mesh"));
	m_aCollisionMesh->SetupAttachment(m_mSceneRoot);
	
	//Set weapon model pointer to the child actor component
	m_aWeaponModel = Cast<AWeaponModel>(m_aWeaponComponent->GetChildActor());

	//if (m_aWeaponModel == nullptr)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FAILED RETRIEVING WEAPON"));

	m_vVelocity.Set(0.0f, 0.0f, 0.0f);
	m_vRotVelocity.Set(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

//Update position and rotation
void AWeaponBase::Tick(float a_fDeltaTime)
{
	Super::Tick(a_fDeltaTime);

	//Update the physics
	if (m_bActive)
	{
		PhysicsUpdate(a_fDeltaTime);

		if (m_fTimeFired + m_fLifetime < UGameplayStatics::GetTimeSeconds(GetWorld()))
		{
			Detonate();
		}

		//Update position and rotation
		this->AddActorWorldOffset(m_vVelocity * a_fDeltaTime);
		this->AddActorLocalRotation(m_rRotator.MakeFromEuler(m_vRotVelocity)*a_fDeltaTime);
	}	
}

void AWeaponBase::Fire_Implementation()
{
	m_fTimeFired = UGameplayStatics::GetTimeSeconds(GetWorld());
	m_bActive = true;
}

void AWeaponBase::SetWeaponVelocity(FVector a_vNewVelocity)
{
	m_vVelocity = a_vNewVelocity;
}

void AWeaponBase::PhysicsUpdate_Implementation(float a_fDeltaTime)
{
	
}

void AWeaponBase::Detonate_Implementation()
{
	m_bActive = false;
}
