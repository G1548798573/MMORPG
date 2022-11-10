// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RPGAttributeMacros.h"
#include "RPGAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class GASTEST_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	URPGAttributeSet();
	
	UPROPERTY(BlueprintReadOnly,Category="Attribute",ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	
	PROPERTY_FUNCTION_REGISTRATION(URPGAttributeSet,Health);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
