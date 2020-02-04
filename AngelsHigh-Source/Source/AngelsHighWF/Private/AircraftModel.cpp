/*
AircraftModel.cpp
Will Chapman

09/07/2019
19/08/2019

	CPP file for generating the physical properties of an aircraft

*/


#include "AircraftModel.h"
#include "EngineNozzle.h"

// Sets default values
AAircraftModel::AAircraftModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/*
		PHYSICAL CONSTRUCTION OF AIRCRAFT
	*/

	//Setup scene root
	m_mSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	m_mSceneRoot->SetupAttachment(RootComponent);
	   
	//Setup the mesh of the body
	m_mBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aircraft Body"));
	m_mBodyMesh->SetupAttachment(m_mSceneRoot);

	//Setup Engines
	m_mLeftEngine = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Engine"));
	m_mLeftEngine->SetupAttachment(m_mBodyMesh);
	m_mRightEngine = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Engine"));
	m_mRightEngine->SetupAttachment(m_mBodyMesh);

	//Setup contrails
	m_aLeftContrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Left Contrail"));
	m_aLeftContrail->SetupAttachment(m_mBodyMesh);
	m_aLeftContrail->SetVisibility(false);
	m_aRightContrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Right Contrail"));
	m_aRightContrail->SetupAttachment(m_mBodyMesh);
	m_aRightContrail->SetVisibility(false);

	//Setup control surfaces root
	m_mControlSurfacesRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Control Surface Root"));
	m_mControlSurfacesRoot->SetupAttachment(m_mBodyMesh);

	//Setup Left Aileron Root
	m_mLeftAileronRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Aileron Root"));
	m_mLeftAileronRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Left Aileron Mesh
	m_mLeftAileronMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Aileron Mesh"));
	m_mLeftAileronMesh->SetupAttachment(m_mLeftAileronRoot);

	//Setup Right Aileron Root
	m_mRightAileronRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Aileron Root"));
	m_mRightAileronRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Right Aileron Mesh
	m_mRightAileronMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Aileron Mesh"));
	m_mRightAileronMesh->SetupAttachment(m_mRightAileronRoot);

	//Setup Left Rudder Root
	m_mLeftRudderRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Rudder Root"));
	m_mLeftRudderRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Left Rudder Mesh
	m_mLeftRudderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Rudder Mesh"));
	m_mLeftRudderMesh->SetupAttachment(m_mLeftRudderRoot);

	//Setup Right Rudder Root
	m_mRightRudderRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Rudder Root"));
	m_mRightRudderRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Right Rudder Mesh
	m_mRightRudderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Rudder Mesh"));
	m_mRightRudderMesh->SetupAttachment(m_mRightRudderRoot);

	//Setup Left Elevator Root
	m_mLeftElevatorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Elevator Root"));
	m_mLeftElevatorRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Left Elevator Mesh
	m_mLeftElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Elevator Mesh"));
	m_mLeftElevatorMesh->SetupAttachment(m_mLeftElevatorRoot);

	//Setup Right Elevator Root
	m_mRightElevatorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Elevator Root"));
	m_mRightElevatorRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Right Elevator Mesh
	m_mRightElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Elevator Mesh"));
	m_mRightElevatorMesh->SetupAttachment(m_mRightElevatorRoot);

	//Setup Up Airbrake Root
	m_mAirbrakeUpRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Airbrake Root"));
	m_mAirbrakeUpRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Up Airbrake
	m_mAirbrakeUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Airbrake Mesh"));
	m_mAirbrakeUpMesh->SetupAttachment(m_mAirbrakeUpRoot);

	//Setup Down Airbrake Root
	m_mAirbrakeDownRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Airbrake Up Root"));
	m_mAirbrakeDownRoot->SetupAttachment(m_mControlSurfacesRoot);

	//Setup Down Airbrake
	m_mAirbrakeDownMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Airbrake Down Mesh"));
	m_mAirbrakeDownMesh->SetupAttachment(m_mAirbrakeDownRoot);

	/**
		Sound Settings
	*/
	m_aEngineNoise = CreateDefaultSubobject<UAudioComponent>(TEXT("Engine Noise"));
	m_aEngineNoise->SetupAttachment(m_mSceneRoot);

	/*
		WEAPONS HARDPOINTS
	*/
	m_mHardPointsRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Hardpoints Root"));
	m_mHardPointsRoot->SetupAttachment(m_mSceneRoot);
	m_uCannonHardPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon Hardpoint"));
 	m_uCannonHardPoint->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 1"));
	m_uHardPoint1->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 2"));
	m_uHardPoint2->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 3"));
	m_uHardPoint3->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint4 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 4"));
	m_uHardPoint4->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint5 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 5"));
	m_uHardPoint5->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint6 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 6"));
	m_uHardPoint6->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint7 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 7"));
	m_uHardPoint7->SetupAttachment(m_mHardPointsRoot);
	m_uHardPoint8 = CreateDefaultSubobject<UArrowComponent>(TEXT("Hardpoint 8"));
	m_uHardPoint8->SetupAttachment(m_mHardPointsRoot);
	
	/*
		WEAPONS DEFAULTS
	*/
	m_fCannonFireRate = 0.01f;
	m_fCannonHeatIncr = 0.01f;
	m_fCannonHeatDecr = 0.05f;
	m_iCannonAmmo = 500;


	/*
		PHYSICS DEFAULTS - defaults based on the FA18 flight model
	*/
	m_fPitchCE = 40.f;
	m_fRollCE = 80.f;
	m_fYawCE = 7.5f;
	m_fDragCESimplified = 1.325f;
	m_fLiftCESimplified = 0.0035f;
	m_fEmptyMass = 19000.f;
	m_fPhysicsMass = 19000.f;
	m_fWingArea = 38.f;
	m_fThrustAcceleration = 0.5f;
	m_fMaxThrust = 980000000.f;
	m_fABThrust = 15800000.f;

}

// Called when the game starts or when spawned
void AAircraftModel::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void AAircraftModel::Tick(float a_fDeltaTime)
{
	Super::Tick(a_fDeltaTime);

	//look after airbrake
	m_fCurrentAirbrake += (m_fTargetAirbrake - m_fCurrentAirbrake) * a_fDeltaTime * 10.f;
	m_vVector.Set(m_fMaxAirbrakeAngle * m_fCurrentAirbrake, 0.0f, 0.0f);
	m_mAirbrakeUpMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(-m_vVector));
	m_mAirbrakeDownMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
}

/*
	Set Control Surface Rotations
*/
void AAircraftModel::SetAileronAngle(float a_fAngle)
{
	m_vVector.Set(m_fMaxAileronAngle * a_fAngle, 0.0f, 0.0f);
	m_mLeftAileronMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
	m_mRightAileronMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(-m_vVector));
}
void AAircraftModel::SetElevatorAngle(float a_fAngle)
{
	m_vVector.Set(m_fMaxElevatorAngle * a_fAngle * (-1 + 2 * m_bCanards), 0.0f, 0.0f);
	m_mLeftElevatorMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
	m_mRightElevatorMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
}
void AAircraftModel::SetRudderAngle(float a_fAngle)
{
	m_vVector.Set(0.0f, -m_fMaxRudderAngle * a_fAngle, 0.0f);
	m_mLeftRudderMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
	m_mRightRudderMesh->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector));
}
void AAircraftModel::SetAirbrakeAngle(float a_fAngle)
{
	m_fTargetAirbrake = a_fAngle;
}