// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolActor.h"

// Sets default values
APoolActor::APoolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APoolActor::SetActive(bool bIsActive)
{
	Active = bIsActive;
	SetActorHiddenInGame(!bIsActive);
	GetWorldTimerManager().SetTimer(lifeSpawnTimer, this, &APoolActor::Deactivate, lifeSpawn, false);
}

void APoolActor::setLifeSpan(float lifespan)
{
	lifeSpawn = lifespan;
}

void APoolActor::setPoolIndex(int index)
{
	PoolIndex = index;
}

void APoolActor::Deactivate()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledActorAdded.Broadcast(this);
}

bool APoolActor::isActive()
{
	return Active;
}

int APoolActor::getPoolIndex()
{
	return PoolIndex;
}

// Called when the game starts or when spawned
void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

