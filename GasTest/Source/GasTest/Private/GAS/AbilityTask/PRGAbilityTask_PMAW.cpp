// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTask/PRGAbilityTask_PMAW.h"

#include "RPGAbilitySystemComponent.h"

UPRGAbilityTask_PMAW::UPRGAbilityTask_PMAW()
{
}

void UPRGAbilityTask_PMAW::Activate()
{
	
	if (Ability==nullptr)
	{
		return;
	}
	if (AbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo=Ability->GetCurrentActorInfo();

		UAnimInstance* AnimInstance=ActorInfo->GetAnimInstance();

		if (AnimInstance!=nullptr)
		{
			//把自己绑定进去
			EventHandle=AbilitySystemComponent->AddGameplayEventTagContainerDelegate(
				EventTags,FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this,&UPRGAbilityTask_PMAW::OnDamageGameplayEvent));
			
		}
	}
	Super::Activate();
}

void UPRGAbilityTask_PMAW::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags,EventHandle);
	}
}

UPRGAbilityTask_PMAW* UPRGAbilityTask_PMAW::CreatePMAWDamageEventProxy(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	UAnimMontage* InMontageToPlay,
	FGameplayTagContainer InEventTags,
	float Rate,
	FName StartSection,
	bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale, 
	float StartTimeSeconds)
{
	//UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UPRGAbilityTask_PMAW* MuObj=NewAbilityTask<UPRGAbilityTask_PMAW>(OwningAbility,TaskInstanceName);
	MuObj ->MontageToPlay = InMontageToPlay;
	MuObj ->Rate=Rate;
	MuObj->StartSection =StartSection;
	MuObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MuObj->bStopWhenAbilityEnds=bStopWhenAbilityEnds;
	MuObj->StartTimeSeconds=StartTimeSeconds;
	MuObj->EventTags = InEventTags;
	
	return MuObj;
}

void UPRGAbilityTask_PMAW::OnDamageGameplayEvent(FGameplayTag InGameplayTag,const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData EventData= *Payload;
		EventData.EventTag=InGameplayTag;

		DamageEventReceived.Broadcast(InGameplayTag,EventData);
	}
}
