// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
    MaxStamina = 100.f;    // Default max stamina
    CurrentStamina = MaxStamina;
    StaminaDrainAmount = 1.f;
    StaminaRecoverAmount = 20.f;
    bIsStaminaDepleted = false;
    bIsStaminaRecovred = false;
}


bool UStaminaComponent::OnStaminaCosumed()
{
    if (CurrentStamina <= 0.f)
    {
        bIsStaminaDepleted = false;
        DrainStamina();
        return true;
    }
    return false;
}

// Recovers stamina
void UStaminaComponent::RecoverStamina(float Amount)
{
    if (Amount <= 0.f || CurrentStamina >= MaxStamina)
    {
        return; // Ignore invalid amounts or if stamina is full
    }

    CurrentStamina = FMath::Clamp(CurrentStamina + Amount, 0.f, MaxStamina);
    if (CurrentStamina > 0.f && bIsStaminaDepleted)
    {
        bIsStaminaDepleted = false;
        OnStaminaRecovered.Broadcast();
    }
}
void UStaminaComponent::StartStaminaDrain()
{
    if (!GetWorld())
    {
        return;
    }

    // Stop recovery to avoid conflicts
    StopStaminaRecover();

    // Reset stamina recovery flag
    bIsStaminaRecovred = false;

    // Start a timer to drain stamina every second
    GetWorld()->GetTimerManager().SetTimer(StaminaDrainTimerHandle, this, &UStaminaComponent::DrainStamina, 1.f, true);
    UE_LOG(LogTemp, Log, TEXT("Stamina drain started."));
}

void UStaminaComponent::DrainStamina()
{
    if (bIsStaminaDepleted)
    {
        return; // Do nothing if stamina is already depleted
    }
    
    // Reduce stamina
    CurrentStamina = FMath::Clamp(CurrentStamina - StaminaDrainAmount, 0.f, MaxStamina);

    // Check if stamina has been depleted
   
    if (CurrentStamina <= 0.f)
    {
        bIsStaminaDepleted = true;
        OnStaminaDepleted.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Stamina depleted!"));

        // Stop the timer to prevent further draining
        StopStaminaDrain();
    }
}

void UStaminaComponent::StopStaminaDrain()
{
    if (!GetWorld())
    {
        return;
    }

    // Clear the timer to stop draining stamina
    GetWorld()->GetTimerManager().ClearTimer(StaminaDrainTimerHandle);
    UE_LOG(LogTemp, Log, TEXT("Stamina drain stopped."));
}

void UStaminaComponent::StartStaminaRecover()
{
    if (!GetWorld())
    {
        return;
    }

    // Stop drain to avoid conflicts
    StopStaminaDrain();

    // Reset stamina depletion flag
    bIsStaminaDepleted = false;

    // Start a timer to recover stamina every second
    GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimerHandle, this, &UStaminaComponent::RecoverStaminaOnTime, 1.f, true);
    UE_LOG(LogTemp, Log, TEXT("Stamina recovery started."));
}

void UStaminaComponent::RecoverStaminaOnTime()
{
    if (bIsStaminaRecovred)
    {
        return;
    }

    // Recover stamina
    CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRecoverAmount, 0.f, MaxStamina);

    // Check if stamina is fully recovered
    if (CurrentStamina >= MaxStamina)
    {
        bIsStaminaRecovred = true;
        OnStaminaRecovered.Broadcast();
        CurrentStamina = MaxStamina;
        UE_LOG(LogTemp, Warning, TEXT("Stamina fully recovered!"));

        // Stop the timer to prevent further recovery
        StopStaminaRecover();
    }
}

void UStaminaComponent::StopStaminaRecover()
{
    if (!GetWorld())
    {
        return;
    }

    // Clear the timer to stop recovery
    GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimerHandle);
    UE_LOG(LogTemp, Log, TEXT("Stamina recovery stopped."));
}
