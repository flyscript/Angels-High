/*
PlayerAircraft.cpp
Will Chapman

09/07/2019
07/08/2019

	CPP file for a class that handles all of the player interaction with an aircraft

*/



#include "PlayerAircraft.h"

APlayerAircraft::APlayerAircraft()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*
		SETUP COMPONENTS
	*/
	
	//Setup cockpit model
	m_aCockpitComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Cockpit Model"));
	m_aCockpitComponent->SetupAttachment(m_mSceneRoot);

	//Setup Cockpit UI
	m_wCockpitHUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("Cockpit HUD"));
	m_wCockpitHUD->SetupAttachment(m_aCockpitComponent);

	//Setup Third Person UI
	m_wThirdPersonHUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("Third Person HUD"));
	m_wThirdPersonHUD->SetupAttachment(m_aAircraftComponent);

	//Setup Third Person Camera
	m_mThirdCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Third Person Camera Root"));
	m_mThirdCameraRoot->SetupAttachment(m_aAircraftComponent);
	m_mThirdCameraVRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Third Person VR Root"));
	m_mThirdCameraVRRoot->SetupAttachment(m_mThirdCameraRoot);
	m_vVector.Set(0.0f, 2000.0f, 700.0f);
	m_mThirdCameraVRRoot->SetRelativeLocation(m_vVector);
	m_cThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	m_cThirdCamera->SetupAttachment(m_mThirdCameraVRRoot);

	//Setup Cockpit Camera
	m_mCockpitCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Cockpit Camera Root"));
	m_mCockpitCameraRoot->SetupAttachment(m_aCockpitComponent);
	m_cCockpitCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Cockpit Camera"));
	m_cCockpitCamera->SetupAttachment(m_mCockpitCameraRoot);
	m_cCockpitCamera->SetAutoActivate(false);

	//Setup Pool
	m_aBulletPoolComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Bullet Pool"));
	m_aBulletPoolComponent->SetupAttachment(m_mSceneRoot);
	
	/*
		DEFAULTS
	*/
	m_fThrustIncrAmount = 0.033333f;
	m_fControlSmoothing = 5.0f;
	m_f1stCameraTurningDeflection = 8.0f;
	m_f3rdCameraTurningDeflection = 5.0f;
	m_bTrackThrustAxis = true;
	m_fCameraShake = 0.01f;
	m_bIsFirstPerson = true; //set to the opposite of what the default will be
	m_bLookingBehind = false;
	m_bCanChangeCamera = true;
	m_v1stCameraTurningDeflection.Set(0.f, 0.f, 0.f);
	m_v3rdCameraTurningDeflection.Set(0.f, 0.f, 0.f);
	m_v1stCameraCurrentRotation.Set(0.f, 0.f, 0.f);
	m_v1stCameraTargetRotation.Set(0.f, 0.f, 0.f);
	m_v3rdCameraCurrentRotation.Set(0.f, 0.f, 0.f);
	m_v3rdCameraTargetRotation.Set(0.f, 0.f, 0.f);

	/*
		WEAPONS DEFAULTS
	*/
	m_bCannonFiring = false;
	m_fCannonHeat = 0.f;
	m_iCurrentWeapon = 0;
}

// Called when the game starts or when spawned
void APlayerAircraft::BeginPlay()
{
	AAircraftBase::BeginPlay();
	
	//Set cockpit model pointer to the child actor component's template
	m_aCockpitModel = Cast<ACockpitModel>(m_aCockpitComponent->GetChildActor());

	if (m_aCockpitModel == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FAILED RETRIEVING COCKPIT"));

	//Set bullet pool pointer to the child actor component's template
	m_pBulletPool = Cast<AWeaponPoolBase>(m_aBulletPoolComponent->GetChildActor());

	if (m_pBulletPool == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FAILED RETRIEVING BULLET POOL"));

	m_pBulletPool->GeneratePool();

	//Set up view
	ToggleCamera();

	m_aAircraftModel->m_aLeftContrail->SetVisibility(false);
	m_aAircraftModel->m_aRightContrail->SetVisibility(false);

}

// Called every frame
void APlayerAircraft::Tick(float a_fDeltaTime)
{
	AAircraftBase::Tick(a_fDeltaTime);
	

	//Update controls smoothing
	m_fCurrentPitchInput += (m_fTargetPitchInput - m_fCurrentPitchInput) * a_fDeltaTime * m_fControlSmoothing;
	AAircraftBase::SetPitch(m_fCurrentPitchInput);
	m_aCockpitModel->SetStickPitchAngle(m_fCurrentPitchInput);

	m_fCurrentRollInput += (m_fTargetRollInput - m_fCurrentRollInput) * a_fDeltaTime * m_fControlSmoothing;
	AAircraftBase::SetRoll(m_fCurrentRollInput);
	m_aCockpitModel->SetStickRollAngle(m_fCurrentRollInput);

	m_fCurrentYawInput += (m_fTargetYawInput - m_fCurrentYawInput) * a_fDeltaTime * m_fControlSmoothing;
	AAircraftBase::SetYaw(m_fCurrentYawInput);
	m_aCockpitModel->SetPedalPositions(m_fCurrentYawInput);

	m_fCurrentThrustInput += (m_fTargetThrustInput - m_fCurrentThrustInput) * a_fDeltaTime * m_fControlSmoothing;
	AAircraftBase::SetThrust(m_fCurrentThrustInput);
	m_aCockpitModel->SetThrottleAngle(-m_fCurrentThrustInput);


	//Update camera rotation and smoothing

	m_fCameraShake = m_fCurrentSpeed / (850000.0f - (m_bAfterburner||m_bAirbrake) * 600000.0f);

	if (m_bIsFirstPerson)
	{
		m_v1stCameraCurrentRotation += (m_v1stCameraTargetRotation - m_v1stCameraCurrentRotation) * a_fDeltaTime * 2.f;

		m_v1stCameraTurningDeflection.Set(m_fCurrentRollInput * m_f1stCameraTurningDeflection, -m_fCurrentPitchInput* m_f1stCameraTurningDeflection, -90.0f + m_fCurrentYawInput*m_f1stCameraTurningDeflection*0.25);

		m_vVector.Set(FMath::FRandRange(-m_fCameraShake, m_fCameraShake), FMath::FRandRange(-m_fCameraShake, m_fCameraShake), FMath::FRandRange(-m_fCameraShake, m_fCameraShake));

		m_mCockpitCameraRoot->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector + (m_v1stCameraCurrentRotation * (1 + m_bLookingBehind)) + m_v1stCameraTurningDeflection));
	}
	else
	{
		m_v3rdCameraCurrentRotation += (m_v3rdCameraTargetRotation - m_v3rdCameraCurrentRotation) * a_fDeltaTime * 2.f;

		m_v3rdCameraTurningDeflection.Set(-m_fCurrentPitchInput * m_f3rdCameraTurningDeflection, -m_fCurrentRollInput * m_f3rdCameraTurningDeflection, m_fCurrentYawInput*m_f3rdCameraTurningDeflection);

		m_vVector.Set(FMath::FRandRange(-m_fCameraShake, m_fCameraShake), FMath::FRandRange(-m_fCameraShake, m_fCameraShake), FMath::FRandRange(-m_fCameraShake, m_fCameraShake));

		m_mThirdCameraRoot->SetRelativeRotation(m_rRotator.MakeFromEuler(m_vVector + m_v3rdCameraTurningDeflection + m_v3rdCameraCurrentRotation + (m_bLookingBehind * FVector::UpVector * 180.0f)));
	}

	if (!m_bCanChangeCamera)
	{
		if (m_bTweenIntoFirstPerson)
		{
			m_vVector.Set(0.0f, -500.0f, 100.0f);
			m_mThirdCameraVRRoot->SetRelativeLocation(m_mThirdCameraVRRoot->RelativeLocation + (m_vVector - m_mThirdCameraVRRoot->RelativeLocation)*a_fDeltaTime*7.5f);
			if (m_mThirdCameraVRRoot->RelativeLocation.Z < 150.0f)
			{
				m_mThirdCameraVRRoot->SetRelativeLocation(m_vVector);
				m_bCanChangeCamera = true;
				ToggleCamera();
			}
		}
		else
		{
			m_vVector.Set(0.0f, 2000.0f, 700.0f);
			m_mThirdCameraVRRoot->SetRelativeLocation(m_mThirdCameraVRRoot->RelativeLocation + (m_vVector - m_mThirdCameraVRRoot->RelativeLocation)*a_fDeltaTime*7.5f);
			if (m_mThirdCameraVRRoot->RelativeLocation.Z > 650.0f)
			{
				m_mThirdCameraVRRoot->SetRelativeLocation(m_vVector);
				m_bCanChangeCamera = true;
			}
		}
	}


	/*
		CANNON FIRE
	*/
	if (m_bCannonFiring && !m_bCannonCooling && m_fLastCannonFire + m_aAircraftModel->m_fCannonFireRate < UGameplayStatics::GetTimeSeconds(GetWorld()))
	{
		m_fLastCannonFire = UGameplayStatics::GetTimeSeconds(GetWorld());

		m_fCannonHeat += (m_aAircraftModel->m_fCannonHeatIncr);

		if (m_fCannonHeat >= 1.f)
		{
			m_bCannonCooling = true;
			m_bCannonFiring = false;
			m_fCannonHeat = 1.f;
		}
		
		FireBullet();
		
	}
	else if (m_fCannonHeat > 0.f)
	{
		//cool down
		m_fCannonHeat -= (m_aAircraftModel->m_fCannonHeatDecr * a_fDeltaTime);

		if (m_fCannonHeat <= 0.f)
		{
			m_fCannonHeat = 0.f;
			m_bCannonCooling = false;
		}
	}

	//Contrails
	if (UGameplayStatics::GetTimeSeconds(GetWorld()) > 3.0f)
	{
		m_aAircraftModel->m_aLeftContrail->SetVisibility(true);
		m_aAircraftModel->m_aRightContrail->SetVisibility(true);
		//EquipLoadout();
	}
}

void APlayerAircraft::FireBullet()
{
	AWeaponBase* l_aBullet = m_pBulletPool->GetNext();

	if (l_aBullet != nullptr)
	{
		l_aBullet->SetActorTransform(m_aAircraftModel->m_uCannonHardPoint->GetComponentToWorld());

		AWeaponModel* l_aBulletModel = Cast<AWeaponModel>(l_aBullet->m_aWeaponComponent->GetChildActor());

		m_vVector.Set(FMath::RandRange(-0.005f, 0.005f), FMath::RandRange(-0.005f, 0.005f), FMath::RandRange(-0.005f, 0.005f));

		l_aBullet->SetWeaponVelocity(
			m_vVelocity + (
				(l_aBulletModel->GetActorForwardVector() + m_vVector) * l_aBulletModel->m_fInitialVelocity
			)
		);

		l_aBullet->SetOwner(this);

		l_aBullet->Fire();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BULLET FROM POOL NULL"));
	}
}

void APlayerAircraft::ReleaseBullet(AWeaponBase* a_aBullet)
{
	m_pBulletPool->Release(a_aBullet);

}

bool APlayerAircraft::CannonCooling()
{
	
	return m_bCannonCooling;
}

float APlayerAircraft::GetCannonHeat()
{
	return m_fCannonHeat;
}

FName APlayerAircraft::CurrentWeaponName()
{
	if (m_pLoadout==nullptr || !m_pLoadout->Ready())
		return "";

	AWeaponMapping* l_pMapping = m_pLoadout->m_aWeaponMappings[m_iCurrentWeapon];

	return l_pMapping->GetWeapon()->m_fName;
}

// Called to bind functionality to input
void APlayerAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("FireCannonAxis", this, &APlayerAircraft::SetCannon);
	InputComponent->BindAxis("PitchAxis", this, &APlayerAircraft::SetPitch);
	InputComponent->BindAxis("RollAxis", this, &APlayerAircraft::SetRoll);
	InputComponent->BindAxis("YawAxis", this, &APlayerAircraft::SetYaw);
	InputComponent->BindAxis("ThrustAxis", this, &APlayerAircraft::SetThrust);
	InputComponent->BindAction("GamePause", IE_Pressed, this, &APlayerAircraft::TogglePause);
	InputComponent->BindAction("ThrustIncrement", IE_Pressed, this, &APlayerAircraft::IncrThrust);
	InputComponent->BindAction("ThrustDecrement", IE_Pressed, this, &APlayerAircraft::DecrThrust);
	InputComponent->BindAction("CameraViewCycle", IE_Pressed, this, &APlayerAircraft::ChangeCamera);
	InputComponent->BindAction("LookBehind", IE_Pressed, this, &APlayerAircraft::ToggleLookBehind);
	InputComponent->BindAction("LookBehind", IE_Released, this, &APlayerAircraft::ToggleLookBehind);
	InputComponent->BindAction("WeaponCycleForward", IE_Pressed, this, &APlayerAircraft::WeaponCycleForward);
	InputComponent->BindAction("WeaponCycleBackward", IE_Pressed, this, &APlayerAircraft::WeaponCycleBackward);
	InputComponent->BindAxis("CameraPanAxis", this, &APlayerAircraft::SetCameraPan);
	InputComponent->BindAxis("CameraTiltAxis", this, &APlayerAircraft::SetCameraTilt);
}

/*
	Input Functions
*/
void APlayerAircraft::TogglePause()
{	
	//UGameplayStatics::SetGamePaused(GetWorld(), !UGameplayStatics::IsGamePaused(GetWorld()));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.00001f + (UGameplayStatics::GetGlobalTimeDilation(GetWorld()) < 0.5f));
	
}

void APlayerAircraft::SetCannon(float a_fAxisValue)
{
	if (a_fAxisValue >= 1.0f)
	{
		m_bCannonFiring = true;
	}
	else
	{
		m_bCannonFiring = false;
	}
}
void APlayerAircraft::SetPitch(float a_fAxisValue)
{
	m_fTargetPitchInput = a_fAxisValue;
}
void APlayerAircraft::SetRoll(float a_fAxisValue)
{
	m_fTargetRollInput = a_fAxisValue;
}
void APlayerAircraft::SetYaw(float a_fAxisValue)
{
	m_fTargetYawInput = a_fAxisValue;
}

void APlayerAircraft::SetThrust(float a_fAxisValue)
{
	//If we're currently tracking the thrust via an axis, then set thrust accordingly
	if (m_bTrackThrustAxis)
	{
		m_fTargetThrustInput = 0.5f + a_fAxisValue / 2.f;
	}
	
	//Set whether or not we're tracking, based on if the thrust axis has returned to 0
	//Done after setting target thrust so that target thrust can still be set to 0 via the axis
	//A deadzone of 0.01f shouldn't interfere with player-defined deadzones
	m_bTrackThrustAxis = a_fAxisValue * a_fAxisValue > 0.01f;
}
void APlayerAircraft::IncrThrust()
{
	if (!m_bTrackThrustAxis)
	{
		m_fTargetThrustInput = FMath::Clamp<float>(m_fTargetThrustInput + m_fThrustIncrAmount, 0.0f, 1.0f);
	}
}
void APlayerAircraft::DecrThrust()
{
	if (!m_bTrackThrustAxis)
	{
		m_fTargetThrustInput = FMath::Clamp<float>(m_fTargetThrustInput - m_fThrustIncrAmount, 0.0f, 1.0f);
	}
}
void APlayerAircraft::WeaponCycleForward()
{
	m_iCurrentWeapon++;
	if (m_iCurrentWeapon >= m_pLoadout->MapSize())
		m_iCurrentWeapon = 0;
}
void APlayerAircraft::WeaponCycleBackward()
{
	m_iCurrentWeapon--;
	if (m_iCurrentWeapon < 0)
		m_iCurrentWeapon = m_pLoadout->MapSize() - 1;
}

/**
	Toggle camera settings
*/
void APlayerAircraft::ToggleCamera()
{
// 	/*
// 
// 		m_bTween	m_bCanChangeCamera	output
// 		0			0					1
// 		0			1					1
// 		1			0					0
// 		1			1					1
// 
// 	*/

// 	if (!m_bTween || m_bCanChangeCamera)
// 	{
		//Toggle whether or not first person is true
		m_bIsFirstPerson = !m_bIsFirstPerson;
		
		if (m_bIsFirstPerson)
		{
			m_aAircraftModel->m_aEngineNoise->AttenuationSettings = m_aCockpitAttenuation;
		}
		else
		{
			m_aAircraftModel->m_aEngineNoise->AttenuationSettings = m_aThirdPersonAttenuation;
		}

		//Setup cameras, widgets, models as needed
		m_cCockpitCamera->SetActive(m_bIsFirstPerson);
		m_wCockpitHUD->SetActive(m_bIsFirstPerson);
		m_wThirdPersonHUD->SetActive(!m_bIsFirstPerson);
		m_cThirdCamera->SetActive(!m_bIsFirstPerson);
		m_aCockpitComponent->SetVisibility(m_bIsFirstPerson, true);
 		m_aAircraftComponent->SetVisibility(!m_bIsFirstPerson, true);
// 	}
}

/**
	The player-actioned changing of cameras with tweening
*/
void APlayerAircraft::ChangeCamera()
{
	if (m_bCanChangeCamera)
	{
		m_bTweenIntoFirstPerson = !m_bIsFirstPerson;
		m_bCanChangeCamera = false;
	}

	if (m_bIsFirstPerson)
		ToggleCamera();
}


void APlayerAircraft::SetCameraPan(float a_fAxisValue)
{
	if (m_bIsFirstPerson)
	{
		m_v1stCameraTargetRotation.Set(0.0f, m_v1stCameraTargetRotation.Y, 90.0f*a_fAxisValue);
	}
	else
	{
		m_v3rdCameraTargetRotation.Set(m_v3rdCameraTargetRotation.X, 0.0f, 75.0f*a_fAxisValue);
	}
}

void APlayerAircraft::SetCameraTilt(float a_fAxisValue)
{
	if (m_bIsFirstPerson)
	{
		m_v1stCameraTargetRotation.Set(0.0f, 90.0f*a_fAxisValue, m_v1stCameraTargetRotation.Z);
	}
	else
	{
		m_v3rdCameraTargetRotation.Set(75.0f*a_fAxisValue, 0.0f, m_v3rdCameraTargetRotation.Z);
	}
}

void APlayerAircraft::ToggleLookBehind()
{
	m_bLookingBehind = !m_bLookingBehind;
}