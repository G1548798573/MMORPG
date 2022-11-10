// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "PRGAbilityTask_PMAW.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMontageWaitSimpleForDamageEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);
/**
 * 
 */
UCLASS()
class GASTEST_API UPRGAbilityTask_PMAW : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:
	UPRGAbilityTask_PMAW();

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleForDamageEventDelegate DamageEventReceived;

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	static UPRGAbilityTask_PMAW* CreatePMAWDamageEventProxy(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* InMontageToPlay,
		FGameplayTagContainer InEventTags,
		float Rate=1.f,
		FName StartSection=NAME_None,
		bool bStopWhenAbilityEnds=true ,
		float AnimRootMotionTranslationScale=1.f,
		float StartTimeSeconds=0.f);

private:
	//
	void OnDamageGameplayEvent(FGameplayTag InGameplayTag,const FGameplayEventData* Payload);

private:
	FDelegateHandle EventHandle;
	

private:
	UPROPERTY()
	FGameplayTagContainer EventTags;
};
