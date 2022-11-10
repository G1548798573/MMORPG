// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class GASTEST_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	URPGGameplayAbility();
	
	UPROPERTY(EditDefaultsOnly,Category=MontageAbility)
	UAnimMontage* MontageToPlay;

	//带有的Buff
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=GameplayEffect)
	TMap<FGameplayTag,TSubclassOf<UGameplayEffect>> EffectMap;




	
	UFUNCTION()
	virtual void OnCompleted();
	UFUNCTION()
	virtual void OnBlendOut();
	UFUNCTION()
	virtual void OnInterrupted();
	UFUNCTION()
	virtual void OnCancelled();
	UFUNCTION()
	virtual void OnDamageGameplayEvent(FGameplayTag InGameplayTag,FGameplayEventData Payload);

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

	UFUNCTION(BlueprintImplementableEvent,Category=Ability,DisplayName="OnCompleted",meta=(ScriptName="OnCompleted"))
	void K2_OnCompleted();

	UFUNCTION(BlueprintImplementableEvent,Category=Ability,DisplayName="OnCompleted",meta=(ScriptName="OnCompleted"))
	void K2_OnBlendOut();

	UFUNCTION(BlueprintImplementableEvent,Category=Ability,DisplayName="OnCompleted",meta=(ScriptName="OnCompleted"))
	void K2_OnInterrupted();

	UFUNCTION(BlueprintImplementableEvent,Category=Ability,DisplayName="OnCompleted",meta=(ScriptName="OnCompleted"))
	void K2_OnCancelled();

	UFUNCTION(BlueprintCallable,Category="MMOARPGGameplayAbility|Tasks",meta=(DisplayName="PlayMontageAndWait"))
	UAbilityTask_PlayMontageAndWait* CreatePlayMontageAndWaitProxy(
			FName TaskInstanceName,
			UAnimMontage* InMontageToPlay,
			float Rate=1.f,
			FName StartSection=NAME_None,
			bool bStopWhenAbilityEnds=true,
			float AnimRootMotionTranslationScale=1.f,
			float StartTimeSeconds=0.f);

	
	
	UFUNCTION(BlueprintCallable,Category="MMOARPGGameplayAbility|Tasks")
	UAbilityTask_PlayMontageAndWait* PlayMontage(FName StartSection=NAME_None);
	
};
