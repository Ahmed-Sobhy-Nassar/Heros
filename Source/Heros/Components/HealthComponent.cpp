// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::OnConsumHealth(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	if (CurrentHealth <= 0)
	{
		OnDead.Broadcast();
		return;
	}
}

void UHealthComponent::OnRecover(float Amount)
{
	if (CurrentHealth >= MaxHealth) return;

	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
}

