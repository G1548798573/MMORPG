// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GasAttributeSetBase.generated.h"

struct FGameplayModifierEvaluatedData;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributrChangedDelegate,float,Health,float,MaxHealth);

UCLASS()
class GASTEST_API UGasAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UGasAttributeSetBase();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AttributSet")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AttributSet")
	FGameplayAttributeData MaxHealth;

	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributrChangedDelegate OnHpChanged;
};
