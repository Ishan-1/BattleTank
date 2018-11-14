// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTank.h"
#include "Public/UObject/Class.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TankAIController.generated.h"


class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	float AcceptanceRadius =3000.0f;//how close AI tank goes to player tank before stopping
};
