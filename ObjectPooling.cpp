// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooling.h"

// Sets default values for this component's properties
UObjectPooling::UObjectPooling()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

APooledActor* UObjectPooling::SpawnPooledObject()
{
	for(APooledActor* p : SpawnedObjects)
	{
		if(p != nullptr && !p->isActive())
		{
			p->TeleportTo(FVector(0,0,0),FRotator(0,0,0));
			p->setLifeSpan(pooledObjectLifeSpawn);
			p->SetActive(true);
			spawnIndex.Add(p->getPoolIndex());

			return p;
		}
	}

	if(spawnIndex.Num() > 0)
	{
		int PooledObjectIndex = spawnIndex[0];
		spawnIndex.RemoveAt(PooledObjectIndex);
		APooledActor* poolableActor = SpawnedObjects[PooledObjectIndex];
		
		if(poolableActor != nullptr)
		{
			poolableActor->SetActive(false);
			poolableActor->TeleportTo(FVector(0,0,0),FRotator(0,0,0));
			poolableActor->setLifeSpan(pooledObjectLifeSpawn);
			poolableActor->SetActive(true);
			spawnIndex.Add(poolableActor->getPoolIndex());

			return poolableActor;
		}
	}
	return nullptr;
}


void UObjectPooling::OnPooledObjectDespawn(APooledActor* poolActor)
{
	spawnIndex.Remove(poolActor->getPoolIndex());
}

// Called when the game starts
void UObjectPooling::BeginPlay()
{
	Super::BeginPlay();
	if(PoolClass!= nullptr)
	{
		UWorld* const World = GetWorld();
		if(World!= nullptr)
		{
			for(int i  = 0; i < poolSize; i ++)
			{
				APooledActor* pooledActor = World->SpawnActor<APooledActor>(PoolClass,FVector().ZeroVector,FRotator().ZeroRotator);
				if(pooledActor != nullptr)
				{
					pooledActor->SetActive(false);
					pooledActor->setPoolIndex(i);
					pooledActor->OnPooledActorAdded.AddDynamic(this,&UObjectPooling::OnPooledObjectDespawn);
					SpawnedObjects.Add(pooledActor);
				}
			}
		}
	}
	
}


// Called every frame
void UObjectPooling::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

