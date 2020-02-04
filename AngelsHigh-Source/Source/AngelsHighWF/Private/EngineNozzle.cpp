/*
EngineNozzle.cpp
Will Chapman

29/07/2019
01/08/2019

	CPP file for describing engine nozzles animating

*/


#include "EngineNozzle.h"

// Sets default values
AEngineNozzle::AEngineNozzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_fThrustScalar = 0.0f;

	/*
		Setup components
	*/
	m_mSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	m_mSceneRoot->SetupAttachment(RootComponent);
	m_mEngine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine"));
	m_mEngine->SetupAttachment(m_mSceneRoot);
	m_aEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Emitter"));
	m_aEmitter->SetupAttachment(m_mSceneRoot);
	m_mNozzle1Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 1 Root"));
	m_mNozzle1Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 1"));
	m_mNozzle1->SetupAttachment(m_mNozzle1Root);
	m_mNozzle2Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 2 Root"));
	m_mNozzle2Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 2"));
	m_mNozzle2->SetupAttachment(m_mNozzle2Root);
	m_mNozzle3Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 3 Root"));
	m_mNozzle3Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 3"));
	m_mNozzle3->SetupAttachment(m_mNozzle3Root);
	m_mNozzle4Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 4 Root"));
	m_mNozzle4Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 4"));
	m_mNozzle4->SetupAttachment(m_mNozzle4Root);
	m_mNozzle5Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 5 Root"));
	m_mNozzle5Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 5"));
	m_mNozzle5->SetupAttachment(m_mNozzle5Root);
	m_mNozzle6Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 6 Root"));
	m_mNozzle6Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 6"));
	m_mNozzle6->SetupAttachment(m_mNozzle6Root);
	m_mNozzle7Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 7 Root"));
	m_mNozzle7Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 7"));
	m_mNozzle7->SetupAttachment(m_mNozzle7Root);
	m_mNozzle8Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 8 Root"));
	m_mNozzle8Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 8"));
	m_mNozzle8->SetupAttachment(m_mNozzle8Root);
	m_mNozzle9Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 9 Root"));
	m_mNozzle9Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 9"));
	m_mNozzle9->SetupAttachment(m_mNozzle9Root);
	m_mNozzle10Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 10 Root"));
	m_mNozzle10Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 10"));
	m_mNozzle10->SetupAttachment(m_mNozzle10Root);
	m_mNozzle11Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 11 Root"));
	m_mNozzle11Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle11 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 11"));
	m_mNozzle11->SetupAttachment(m_mNozzle11Root);
	m_mNozzle12Root = CreateDefaultSubobject<USceneComponent>(TEXT("Nozzle 12 Root"));
	m_mNozzle12Root->SetupAttachment(m_mSceneRoot);
	m_mNozzle12 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nozzle 12"));
	m_mNozzle12->SetupAttachment(m_mNozzle12Root);

}

// Called when the game starts or when spawned
void AEngineNozzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEngineNozzle::Tick(float a_fDeltaTime)
{
	Super::Tick(a_fDeltaTime);

	m_rRotator = m_rRotator.MakeFromEuler(m_cNozzleApertureCurve->GetVectorValue(m_fThrustScalar));

	m_mNozzle1->SetRelativeRotation(m_rRotator);
	m_mNozzle2->SetRelativeRotation(m_rRotator);
	m_mNozzle3->SetRelativeRotation(m_rRotator);
	m_mNozzle4->SetRelativeRotation(m_rRotator);
	m_mNozzle5->SetRelativeRotation(m_rRotator);
	m_mNozzle6->SetRelativeRotation(m_rRotator);
	m_mNozzle7->SetRelativeRotation(m_rRotator);
	m_mNozzle8->SetRelativeRotation(m_rRotator);
	m_mNozzle9->SetRelativeRotation(m_rRotator);
	m_mNozzle10->SetRelativeRotation(m_rRotator);
	m_mNozzle11->SetRelativeRotation(m_rRotator);
	m_mNozzle12->SetRelativeRotation(m_rRotator);

	m_vThrust.Set(0.0f, 0.0f, m_fThrustScalar);

	m_aEmitter->SetVectorParameter("ThrustSize", m_vThrust);
	m_aEmitter->SetVectorParameter("ThrustVelocity", m_vThrust);

}

void AEngineNozzle::SetThrust(float a_fThrust)
{
	m_fThrustScalar = a_fThrust;
}