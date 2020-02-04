/*
AircraftModel.h
Will Chapman

09/07/2019
25/07/2019

	CPP file for defining the properties of an aircraft

*/


#include "CockpitModel.h"

// Sets default values
ACockpitModel::ACockpitModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
		PHYSICAL CONSTRUCTION OF COCKPIT
	*/

	//Setup cockpit root
	m_mCockpitRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Cockpit Root"));
	m_mCockpitRoot->SetupAttachment(RootComponent);

	//Setup Cockpit Mesh
	m_mCockpitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cockpit Mesh"));
	m_mCockpitMesh->SetupAttachment(m_mCockpitRoot);

	//Setup Throttle root
	m_mThrottleRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Throttle Root"));
	m_mThrottleRoot->SetupAttachment(m_mCockpitRoot);

	//Setup Throttle Mesh
	m_mThrottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Throttle Mesh"));
	m_mThrottleMesh->SetupAttachment(m_mThrottleRoot);

	//Setup Stick Base Root
	m_mStickBaseRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Stick Base Root"));
	m_mStickBaseRoot->SetupAttachment(m_mCockpitRoot);

	//Setup Stick Base Mesh
	m_mStickBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stick Base Mesh"));
	m_mStickBaseMesh->SetupAttachment(m_mStickBaseRoot);

	//Setup Stick Root
	m_mStickRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Stick Root"));
	m_mStickRoot->SetupAttachment(m_mStickBaseMesh);

	//Setup Stick Mesh
	m_mStickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stick Mesh"));
	m_mStickMesh->SetupAttachment(m_mStickRoot);

	//Setup Left Pedal Root
	m_mLeftPedalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Pedal Root"));
	m_mLeftPedalRoot->SetupAttachment(m_mCockpitRoot);

	//Setup Left Pedal Mesh
	m_mLeftPedalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Pedal Mesh"));
	m_mLeftPedalMesh->SetupAttachment(m_mLeftPedalRoot);

	//Setup Right Pedal Root
	m_mRightPedalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Pedal Root"));
	m_mRightPedalRoot->SetupAttachment(m_mCockpitRoot);

	//Setup Right Pedal Mesh
	m_mRightPedalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Pedal Mesh"));
	m_mRightPedalMesh->SetupAttachment(m_mRightPedalRoot);

	/*
		CONTROLS DEFAULTS
	*/
	m_fMaxStickPitch = 25.f;
	m_fMaxStickRoll = 20.f;
	m_fMaxPedalYaw = 10.f;
	m_fMaxThrottleAngle = 40.f;
}

// Called when the game starts or when spawned
void ACockpitModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACockpitModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
	Set Control Rotations
*/
void ACockpitModel::SetStickPitchAngle(float a_fAngle)
{
	m_vVector.Set(m_fMaxStickPitch * a_fAngle, 0.0f, 0.0f);
	m_mStickBaseMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
}
void ACockpitModel::SetStickRollAngle(float a_fAngle)
{
	m_vVector.Set(0.0f, 0.0f, m_fMaxStickRoll * a_fAngle);
	m_mStickMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
}
void ACockpitModel::SetThrottleAngle(float a_fAngle)
{
	m_vVector.Set(m_fMaxThrottleAngle * a_fAngle, 0.0f, 0.0f);
	m_mThrottleMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
}
void ACockpitModel::SetPedalPositions(float a_fAngle)
{
	m_vVector.Set(0.0f, m_fMaxPedalYaw * a_fAngle, 0.0f);
	m_mLeftPedalMesh->SetRelativeLocation(m_vVector);
	m_mRightPedalMesh->SetRelativeLocation(-m_vVector);
}