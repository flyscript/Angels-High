/*
CockpitModel.h
Will Chapman

09/07/2019
24/07/2019

	Header file for defining the components of a cockpit

*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CockpitModel.generated.h"

UCLASS()
class ANGELSHIGHWF_API ACockpitModel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACockpitModel();

	/*
		COCKPIT BODY COMPONENTS
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mCockpitRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mCockpitMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mThrottleRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mThrottleMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mStickBaseRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mStickBaseMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mStickRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mStickMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mLeftPedalRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mLeftPedalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mRightPedalRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mRightPedalMesh;

	/*
		CONTROLS VALUES
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Controls")
		float m_fMaxStickPitch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Controls")
		float m_fMaxStickRoll;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Controls")
		float m_fMaxPedalYaw;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Controls")
		float m_fMaxThrottleAngle;
private:

	/*
		This is a rotator for class-wide use - not creating or using a new rotator each tick and each thing
	*/
	FVector m_vVector;
	FRotator m_rRotator;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/*
		Set Control Rotations
	*/
	void SetStickPitchAngle(float a_fAngle);
	void SetStickRollAngle(float a_fAngle);
	void SetThrottleAngle(float a_fAngle);
	void SetPedalPositions(float a_fAngle);

};
