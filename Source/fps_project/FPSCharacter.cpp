// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

#include "AbilitySystemComponent.h"
#include "FPSAttributeSet.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UFPSAttributeSet>("AttributeSet");

}

UAbilitySystemComponent* AFPSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		if (DefaultAttributeEffect)
		{
			FGameplayEffectContextHandle effectHandle = AbilitySystemComponent->MakeEffectContext();
			effectHandle.AddSourceObject(this);
			FGameplayEffectSpecHandle spectHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, effectHandle);

			if (spectHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*spectHandle.Data.Get());
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No abilitySistemLoad"));
			}
		}
		if (HasAuthority())
		{
			for (TSubclassOf<UGameplayAbility>& f : defaultAbilities)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(f.GetDefaultObject(), 1, 10));
			}
		}
	}
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

