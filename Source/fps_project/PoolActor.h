// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledActorAdded, APoolActor*, PoolActor);

UCLASS()
class FPS_PROJECT_API APoolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolActor();

	FOnPooledActorAdded OnPooledActorAdded;

	void SetActive(bool bIsActive);
	void setLifeSpan(float lifespan);
	void setPoolIndex(int index);

	UFUNCTION(BlueprintCallable, Category = "PooledActor")
	void Deactivate();

	bool isActive();
	int getPoolIndex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool Active;
	float lifeSpawn = 0;
	int PoolIndex;

	FTimerHandle lifeSpawnTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
