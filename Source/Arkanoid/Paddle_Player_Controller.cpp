// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_Player_Controller.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

#include "Paddle.h"
#include "Ball.h"


APaddle_Player_Controller::APaddle_Player_Controller()
{

	PrimaryActorTick.bCanEverTick = true;

}

void APaddle_Player_Controller::BeginPlay()
{

	APlayerController::BeginPlay();

	// setup first map camera as current camera
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	SetViewTarget(CameraActors[0], FViewTargetTransitionParams());

	// setup owned paddle
	OwnedPaddle = Cast<APaddle>(GetPawn());

	SpawnNewBall();

}

void APaddle_Player_Controller::SetupInputComponent()
{

	APlayerController::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MoveHorizontal", this, &APaddle_Player_Controller::MoveHorizontal);
	InputComponent->BindAction("Launch", IE_Pressed, this, &APaddle_Player_Controller::Launch);

}

void APaddle_Player_Controller::MoveHorizontal(float Val)
{

	if (OwnedPaddle) {

		OwnedPaddle->MoveHorizontal(Val);

	}

}

void APaddle_Player_Controller::Launch()
{

	MapBall->Launch();

}

void APaddle_Player_Controller::SpawnNewBall()
{

	//if (!MapBall)
	//	MapBall = nullptr;

	if (BallObj) {

		MapBall = GetWorld()->SpawnActor<ABall>(BallObj, BallSpawnLocation, BallSpawnRotation, BallSpawnParams);

	}

}
