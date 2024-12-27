// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UHungerComponent::UHungerComponent()
{
	MaxHunger = 100.f;
	CurrentHunger = MaxHunger;
	HungerDecayRate = 1.f; // Decay per second
	bIsHungerZero = false;
}


// Called when the game starts
void UHungerComponent::BeginPlay()
{
	Super::BeginPlay();
	StartHungerDecay();
}

void UHungerComponent::DecayHunger()
{
    if (CurrentHunger > 0.f)
    {
        CurrentHunger = FMath::Clamp(CurrentHunger-HungerDecayRate, 0.f, MaxHunger);

        if (CurrentHunger == 0.f && !bIsHungerZero)
        {
            bIsHungerZero = true;
            OnHungerZero.Broadcast(); // Notify that hunger has reached zero
            UE_LOG(LogTemp, Log, TEXT("Hunger zero broadcast"));
        }
        else if (CurrentHunger > 0.f && bIsHungerZero)
        {
            bIsHungerZero = false;
            OnHungerRecovered.Broadcast(); // Notify that hunger has recovered
            UE_LOG(LogTemp, Log, TEXT("Hunger Recovred broadcast"));
        }

        UE_LOG(LogTemp, Log, TEXT("Current Hunger: %f"), CurrentHunger);
    }
}

void UHungerComponent::StartHungerDecay()
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HungerTimerHandle, this, &UHungerComponent::DecayHunger, 1.f, true);
    }
}

void UHungerComponent::StopHungerDecay()
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HungerTimerHandle);
    }
}



