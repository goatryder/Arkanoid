// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Paddle_Player_Controller.generated.h"

class ABall;

class APaddle;

UCLASS()
class ARKANOID_API APaddle_Player_Controller : public APlayerController
{
	GENERATED_BODY()

	APaddle_Player_Controller();

	UFUNCTION()
		virtual void SetupInputComponent() override;

protected:

	virtual void BeginPlay() override;

	void MoveHorizontal(float Val);

	APaddle* OwnedPaddle;

	// ball references

	void Launch();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABall> BallObj;

	ABall* MapBall;

	FVector BallSpawnLocation = FVector(10.f, 0.f, 40.f);
	FRotator BallSpawnRotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters BallSpawnParams;

public:

	void SpawnNewBall();

};
