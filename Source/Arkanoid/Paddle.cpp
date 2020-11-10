// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SM_Padle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// SM_Padle->SetEnableGravity(false);
	SM_Padle->SetConstraintMode(EDOFMode::XZPlane);

	// SM_Padle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Padle->SetCollisionProfileName(TEXT("PhysicsActor"));

	SM_Padle->SetNotifyRigidBodyCollision(true);
	SM_Padle->SetGenerateOverlapEvents(false);

	RootComponent = SM_Padle;

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
	InitialPosition = GetActorLocation();

	// SM_Padle->OnComponentBeginOverlap.AddDynamic(this, &APaddle::OnOverlap);

	OnActorHit.AddDynamic(this, &APaddle::OnMyActorHit);

}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APaddle::MoveHorizontal(float Val)
{

	if (Val == 0.f)
		return;

	FloatingMovement->AddInputVector(FVector(Val, 0.f, 0.f), false);

}

/*
// NOT WORKED WHEN COLLISION TYPE IS PHYSICS BODY
void APaddle::OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("On Paddle Overlap"));

	FVector Loc = SM_Padle->GetComponentLocation();
	Loc.Y = InitialPosition.Y;
	Loc.Z = InitialPosition.Z;

	SM_Padle->SetWorldLocation(Loc);

}*/


void APaddle::OnMyActorHit(AActor* SelfActor, AActor* OtherActor, 
	FVector NormalImpulse, const FHitResult& Hit)
{

	// UE_LOG(LogTemp, Warning, TEXT("On My Actor Hit"));

	FVector Loc = SM_Padle->GetComponentLocation();
	Loc.Y = InitialPosition.Y;
	Loc.Z = InitialPosition.Z;

	SM_Padle->SetWorldLocation(Loc);

}
