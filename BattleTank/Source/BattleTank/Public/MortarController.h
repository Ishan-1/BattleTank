// Copyright Idiocy

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTank.h"
#include "Public/UObject/Class.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MortarController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMortarController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
		void OnPossessedMortarDeath();
	
};
