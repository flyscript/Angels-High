/*
EngineNozzle.h
Will Chapman

29/07/2019
01/08/2019

	Header file for describing engine nozzles animating

*/

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"

#include "EngineNozzle.generated.h"

UCLASS()
class ANGELSHIGHWF_API AEngineNozzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEngineNozzle();

	/*
		Curve shows thrust amount to openness of nozzle
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UCurveVector* m_cNozzleApertureCurve;
	
	/*
		Exhaust particle effect
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UParticleSystemComponent* m_aEmitter;

	/*
		Components of nozzle
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mSceneRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mEngine;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle1Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle2Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle3Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle4Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle5Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle6Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle6;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle7Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle7;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle8Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle8;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle9Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle9;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle10Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle11Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle11;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle12Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle12;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle13Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle13;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		USceneComponent* m_mNozzle14Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Model")
		UStaticMeshComponent* m_mNozzle14;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float m_fThrustScalar;

	FRotator m_rRotator;

	FVector m_vThrust;

public:	
	// Called every frame
	virtual void Tick(float a_fDeltaTime) override;

	void SetThrust(float a_fThrust);

};
