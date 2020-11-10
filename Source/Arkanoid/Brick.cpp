// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Ball.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//BoxCollision->SetBoxExtent(FVector(25.f, 10.f, 10.f));
	//RootComponent = BoxCollision;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	
	// SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Brick->SetCollisionProfileName(TEXT("PhysicsActor"));

	SM_Brick->SetNotifyRigidBodyCollision(true);
	SM_Brick->SetGenerateOverlapEvents(false);

	RootComponent = SM_Brick;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	AActor::BeginPlay();
	
	OnActorHit.AddDynamic(this, &ABrick::OnMyActorHit);

}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void ABrick::OnMyActorHit(AActor* SelfActor, AActor* OtherActor, 
	FVector NormalImpulse, const FHitResult& Hit)
{

	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, 0.1f, false);

}

/*
void ABrick::AffectBallVelocity()
{
	
	if (!Ball)
		return;

	FVector BallPhysicsVelocity = Ball->GetBall()->GetPhysicsLinearVelocity();

	UE_LOG(LogTemp, Warning, TEXT("Ball Velocity Before: %s, size: %f"),
		*BallPhysicsVelocity.ToString(), BallPhysicsVelocity.Size());

	BallPhysicsVelocity.Normalize();

	UE_LOG(LogTemp, Warning, TEXT("BallPhysicsVelocity Normalized: %s,  size: %f"),
		*BallPhysicsVelocity.ToString(), BallPhysicsVelocity.Size());

	// Ball->VelocitySizeCache += BallVelocityModifierOnBounce;

	Ball->GetBall()->SetPhysicsLinearVelocity(
		BallPhysicsVelocity * Ball->VelocitySizeCache, false);

	UE_LOG(LogTemp, Warning, TEXT("Ball Velocity After: %s, Size: %f"),
		*Ball->GetBall()->GetPhysicsLinearVelocity().ToString(), Ball->GetBall()->GetPhysicsLinearVelocity().Size());
	
}*/

void ABrick::DestroyBrick()
{

	// AffectBallVelocity();
	Destroy();
}

/*
void ABrick::OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Ball")) {

		Ball = Cast<ABall>(OtherActor);

		FTimerHandle UnusedHandle;

		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, 0.1f, false);

	}

}*/