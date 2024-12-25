// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungerComponent.generated.h"

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHungerZero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHungerRecovered);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROS_API UHungerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHungerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hunger", meta = (AllowPrivateAccess = "true"))
    float MaxHunger;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hunger", meta = (AllowPrivateAccess = "true"))
    float CurrentHunger;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hunger", meta = (AllowPrivateAccess = "true"))
    float HungerDecayRate;

    FTimerHandle HungerTimerHandle;

    void DecayHunger();

    bool bIsHungerZero;

public:
    // Start/Stop hunger decay
    UFUNCTION(BlueprintCallable, Category = "Hunger")
    void StartHungerDecay();

    UFUNCTION(BlueprintCallable, Category = "Hunger")
    void StopHungerDecay();

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Hunger")
    FOnHungerZero OnHungerZero;

    UPROPERTY(BlueprintAssignable, Category = "Hunger")
    FOnHungerRecovered OnHungerRecovered;
};
