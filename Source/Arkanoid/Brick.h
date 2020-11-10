// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

// class UBoxComponent;
class UStaticMeshComponent;
// class ABall;


UCLASS()
class ARKANOID_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Brick;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	UBoxComponent* BoxCollision;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//	float BallVelocityModifierOnBounce = 5.0f;

	/*
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	*/

	UFUNCTION()
		void OnMyActorHit(AActor* SelfActor, AActor* OtherActor,
			FVector NormalImpulse, const FHitResult& Hit);

	// void AffectBallVelocity();
	void DestroyBrick();

	// ABall* Ball;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
