// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolingObject.h"

// Sets default values for this component's properties
UPoolingObject::UPoolingObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

APoolActor* UPoolingObject::SpawnPooledObject()
{
	for (APoolActor* p : SpawnedObjects)
	{
		if (p != nullptr && !p->isActive())
		{
			p->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			p->setLifeSpan(pooledObjectLifeSpawn);
			p->SetActive(true);
			spawnIndex.Add(p->getPoolIndex());

			return p;
		}
	}

	if (spawnIndex.Num() > 0)
	{
		int PooledObjectIndex = spawnIndex[0];
		spawnIndex.RemoveAt(PooledObjectIndex);
		APoolActor* poolableActor = SpawnedObjects[PooledObjectIndex];

		if (poolableActor != nullptr)
		{
			poolableActor->SetActive(false);
			poolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			poolableActor->setLifeSpan(pooledObjectLifeSpawn);
			poolableActor->SetActive(true);
			spawnIndex.Add(poolableActor->getPoolIndex());

			return poolableActor;
		}
	}
	return nullptr;
}


void UPoolingObject::OnPooledObjectDespawn(APoolActor* poolActor)
{
	spawnIndex.Remove(poolActor->getPoolIndex());
}

// Called when the game starts
void UPoolingObject::BeginPlay()
{
	Super::BeginPlay();

	if (PoolClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < poolSize; i++)
			{
				APoolActor* pooledActor = World->SpawnActor<APoolActor>(PoolClass, FVector().ZeroVector, FRotator().ZeroRotator);
				if (pooledActor != nullptr)
				{
					pooledActor->SetActive(false);
					pooledActor->setPoolIndex(i);
					pooledActor->OnPooledActorAdded.AddDynamic(this, &UPoolingObject::OnPooledObjectDespawn);
					SpawnedObjects.Add(pooledActor);
				}
			}
		}
	}
	
}


// Called every frame
void UPoolingObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

