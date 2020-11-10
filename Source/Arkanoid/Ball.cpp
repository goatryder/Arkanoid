// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));

	SM_Ball->SetSimulatePhysics(true);
	SM_Ball->SetEnableGravity(false);
	SM_Ball->SetConstraintMode(EDOFMode::XZPlane);

	// SM_Ball->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Ball->SetCollisionProfileName(TEXT("PhysicsActor"));
	
	SM_Ball->SetNotifyRigidBodyCollision(true);
	SM_Ball->SetGenerateOverlapEvents(false);

	RootComponent = SM_Ball;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->Friction = 0.f;
	ProjectileMovement->Velocity.X = 0.f;

	Tags.Push(FName("Ball"));

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	AActor::BeginPlay();
	
	// ProjectileMovement->OnProjectileBounce.AddDynamic(this, &ABall::OnBounce);

	SM_Ball->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnBounce);

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Velocity Len: %f"),
	//	SM_Ball->GetPhysicsLinearVelocity().Size());

}

void ABall::Launch()
{

	if (!BallLaunched) {

		SM_Ball->AddImpulse(LaunchImpulse, FName(), true);

		BallLaunched = true;

	}

}

UStaticMeshComponent* ABall::GetBall()
{
	return SM_Ball;
}

void ABall::OnBounce(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{

	FVector BallPhysicsVelocity = SM_Ball->GetPhysicsLinearVelocity();

	//UE_LOG(LogTemp, Warning, TEXT("Ball Velocity Before: %s, size: %f"),
	//	*BallPhysicsVelocity.ToString(), BallPhysicsVelocity.Size());

	BallPhysicsVelocity.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("BallPhysicsVelocity Normalized: %s,  size: %f"),
	//	*BallPhysicsVelocity.ToString(), BallPhysicsVelocity.Size());

	VelocitySizeCache += BallVelocityModifierOnBounce;

	SM_Ball->SetPhysicsLinearVelocity(
		BallPhysicsVelocity * VelocitySizeCache, false);

	//UE_LOG(LogTemp, Warning, TEXT("Ball Velocity After: %s, Size: %f"),
	//	*SM_Ball->GetPhysicsLinearVelocity().ToString(), SM_Ball->GetPhysicsLinearVelocity().Size());


}

