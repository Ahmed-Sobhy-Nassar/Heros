// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

public:
	// Events
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDead OnDead;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnConsumHealth(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnRecover(float Amount);


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
		
};
