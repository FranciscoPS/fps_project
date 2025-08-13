// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolActor.h"
#include "Components/ActorComponent.h"
#include "PoolingObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_PROJECT_API UPoolingObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoolingObject();

	UFUNCTION(BlueprintCallable, Category = "ObjectPool")
	APoolActor* SpawnPooledObject();

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	TSubclassOf<APoolActor> PoolClass;

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	int poolSize = 20;

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	float pooledObjectLifeSpawn = 0.0f;

	UFUNCTION()
	void OnPooledObjectDespawn(APoolActor* poolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APoolActor*> SpawnedObjects;
	TArray<int> spawnIndex;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
