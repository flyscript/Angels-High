// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MissileBase.generated.h"

/**
 * 
 */
UCLASS()
class ANGELSHIGHWF_API AMissileBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SimpleDisplay, Category = "Weapon")
	AActor* m_aTarget;
	
};
