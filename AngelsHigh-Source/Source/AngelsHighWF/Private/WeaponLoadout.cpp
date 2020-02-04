/*
WeaponLoadout.cpp
Will Chapman

09/08/2019
19/08/2019

	CPP file for a class that describes how weapons are loaded onto an aircraft

*/

#include "WeaponLoadout.h"

// Sets default values
AWeaponLoadout::AWeaponLoadout()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_bMapped = false;


	m_aSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	m_aSceneRoot->SetupAttachment(RootComponent);
	
	/*
	m_aMappings.SetNum(4);

	int l_iIt = 0;
	for (UChildActorComponent* l_aMapping : m_aMappings)
	{
		l_iIt++;

		FString NewString = FString(TEXT("Weapon Mapping "));
		NewString.Append(FString::FromInt(l_iIt));
		FName NewName = FName(*NewString);

		l_aMapping = CreateDefaultSubobject<UChildActorComponent>(NewName);
		l_aMapping->SetupAttachment(m_aSceneRoot);
	}
	*/

	m_aWeaponMapping1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Mapping 1"));
	m_aWeaponMapping1->SetupAttachment(m_aSceneRoot);
	m_aWeaponMapping2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Mapping 2"));
	m_aWeaponMapping2->SetupAttachment(m_aSceneRoot);
	m_aWeaponMapping3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Mapping 3"));
	m_aWeaponMapping3->SetupAttachment(m_aSceneRoot);
	m_aWeaponMapping4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Mapping 4"));
	m_aWeaponMapping4->SetupAttachment(m_aSceneRoot);

}

// Called when the game starts or when spawned
void AWeaponLoadout::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponLoadout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AWeaponLoadout::MapSize()
{
	return m_iSize;
}

/*TArray<AWeaponMapping*>**/
void AWeaponLoadout::GenerateMap()
{
// 	m_pWeaponMapping1 = Cast<AWeaponMapping>(m_aWeaponMapping1->GetChildActor());
// 		//m_pWeaponMapping2 = Cast<AWeaponMapping>(m_aWeaponMapping2->GetChildActor());
// 		//m_pWeaponMapping3 = Cast<AWeaponMapping>(m_aWeaponMapping3->GetChildActor());
// 		//m_pWeaponMapping4 = Cast<AWeaponMapping>(m_aWeaponMapping4->GetChildActor());
// 	
// 		//m_pWeaponMapping1 = nullptr;
// 		//m_pWeaponMapping2 = nullptr;
// 		//m_pWeaponMapping3 = nullptr;
// 		//m_pWeaponMapping4 = nullptr;
// 	
// 		if (m_pWeaponMapping1 != nullptr)
// 		{
// 			m_pWeaponMapping1->Generate();
// 			m_aWeaponMappings.Add(m_pWeaponMapping1);
// 		}
// 	
// 		if (m_pWeaponMapping2 != nullptr)
// 		{
// 			m_pWeaponMapping2->Generate();
// 			m_aWeaponMappings.Add(m_pWeaponMapping2);
// 		}
// 	
// 		if (m_pWeaponMapping3 != nullptr)
// 		{
// 			m_pWeaponMapping3->Generate();
// 			m_aWeaponMappings.Add(m_pWeaponMapping3);
// 		}
// 	
// 		if (m_pWeaponMapping4 != nullptr)
// 		{
// 			m_pWeaponMapping4->Generate();
// 			m_aWeaponMappings.Add(m_pWeaponMapping4);
// 		}
// 	
// 		//m_bMapped = true;
// 		
// 		//return m_aWeaponMappings;

	m_pWeaponMapping1 = Cast<AWeaponMapping>(m_aWeaponMapping1->GetChildActor());
	m_pWeaponMapping2 = Cast<AWeaponMapping>(m_aWeaponMapping2->GetChildActor());
	m_pWeaponMapping3 = Cast<AWeaponMapping>(m_aWeaponMapping3->GetChildActor());
	m_pWeaponMapping4 = Cast<AWeaponMapping>(m_aWeaponMapping4->GetChildActor());
	m_iSize = 0;

	if (m_pWeaponMapping1 != nullptr)
	{
		m_pWeaponMapping1->Generate();
		m_aWeaponMappings.Add(m_pWeaponMapping1);
	}

	if (m_pWeaponMapping2 != nullptr)
	{
		m_pWeaponMapping2->Generate();
		m_aWeaponMappings.Add(m_pWeaponMapping2);
	}

	if (m_pWeaponMapping3 != nullptr)
	{
		m_pWeaponMapping3->Generate();
		m_aWeaponMappings.Add(m_pWeaponMapping3);
	}

	if (m_pWeaponMapping4 != nullptr)
	{
		m_pWeaponMapping4->Generate();
		m_aWeaponMappings.Add(m_pWeaponMapping4);
	}

	m_iSize = m_aWeaponMappings.Num();

	m_bMapped = true;
}


bool AWeaponLoadout::Ready()
{
	return m_bMapped;
}

