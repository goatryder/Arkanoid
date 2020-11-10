// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UProjectileMovementComponent;

UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	virtual void Launch();

	bool BallLaunched;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Ball;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent* ProjectileMovement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float BallVelocityModifierOnBounce = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float MaxBounceXNormalAngle = 60.0f;

	UFUNCTION()
		UStaticMeshComponent* GetBall();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector LaunchImpulse = FVector(50.f, 0.f, 140.f);

	float VelocitySizeCache = LaunchImpulse.Size();
	
	UFUNCTION()
		//void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
		void OnBounce(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

};
