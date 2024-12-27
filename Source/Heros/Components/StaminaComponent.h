// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaRecovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaChanged);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEROS_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

private:
    // Properties
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
    float MaxStamina;

    UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
    float CurrentStamina;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
    float StaminaDrainAmount;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
    float StaminaRecoverAmount;

    // Timer for stamina drain
    FTimerHandle StaminaDrainTimerHandle;
    FTimerHandle StaminaRecoverTimerHandle;
    // State tracking
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
    bool bIsStaminaDepleted;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
    bool bIsStaminaRecovred;

    // Methods
    void DrainStamina(); // Drains by amount stamina every second

public:
    // Stamina management
   
    UFUNCTION(BlueprintCallable, Category = "Stamina")
    bool OnStaminaCosumed();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void RecoverStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void RecoverStaminaOnTime();
    // Hunger-related stamina drain control
    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void StartStaminaDrain(); // Start consuming stamina (e.g., when hunger is zero)

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void StopStaminaDrain(); // Stop consuming stamina (e.g., when hunger recovers)

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void StartStaminaRecover();
    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void StopStaminaRecover();
    // Events
    UPROPERTY(BlueprintAssignable, Category = "Stamina")
    FOnStaminaDepleted OnStaminaDepleted;

    UPROPERTY(BlueprintAssignable, Category = "Stamina")
    FOnStaminaRecovered OnStaminaRecovered;

    UPROPERTY(BlueprintAssignable, Category = "Stamina")
    FOnStaminaChanged OnStaminaChanged;
		
};
