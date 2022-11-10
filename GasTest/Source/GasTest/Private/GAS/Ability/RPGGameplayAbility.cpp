// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/RPGGameplayAbility.h"

#include "GASCharacter.h"
#include "GAS/AbilityTask/PRGAbilityTask_PMAW.h"

URPGGameplayAbility::URPGGameplayAbility()
{
	UE_LOG(LogTemp, Log, TEXT("成功激活GA"));
}

void URPGGameplayAbility::OnCompleted()
{
	K2_OnCompleted();
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnBlendOut()
{
	K2_OnBlendOut();
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnInterrupted()
{
	K2_OnInterrupted();
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnCancelled()
{
	void K2_OnCancelled();
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload)
{
	//
	UE_LOG(LogTemp,Log,TEXT("URPGGameplayAbility::OnDamageGameplayEvent"));
	//一
	//先创建一个数组
	FGameplayAbilityTargetData_ActorArray* NewTargetData_ActorArray=new FGameplayAbilityTargetData_ActorArray();
	//把我们的命中传递过来的数据中的目标添加进数组
	NewTargetData_ActorArray->TargetActorArray.Add(const_cast<AActor*> (Payload.Instigator));
	//创建目标数据的Handle
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	//把我们的数据添加到处理目标数据的Handle里面
	TargetDataHandle.Add(NewTargetData_ActorArray);

	//二
	//创建我们的GE Handle
	//拿到我们所有要激活的GE，遍历（或者Find去找对应的GE激活）
	
	for (auto &Tmp:EffectMap)
	{
		//1.创建GEHandle
		//拿到我们的Gas组件（通过GA 激活信息）
		//创建GE的实例，传入阐述，GE本体 ，GE等级，GE的上下文信息。
		FGameplayEffectSpecHandle NewHandle
		=GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Tmp.Value,1,MakeEffectContext(CurrentSpecHandle,CurrentActorInfo));
		//是否创建成功
		if (NewHandle.IsValid())
		{
			//找到GA的实例(现在的)
			FGameplayAbilitySpec* AbilitySpec=
				GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);

			ApplyAbilityTagsToGameplayEffectSpec(*NewHandle.Data.Get(),AbilitySpec);
			if (AbilitySpec)
			{
				NewHandle.Data->SetByCallerTagMagnitudes=AbilitySpec->SetByCallerTagMagnitudes;
			}
		}
	}
	
	
}

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		return;
	}
	//增加保护
	if (AGASCharacter* Character=Cast<AGASCharacter>(ActorInfo->OwnerActor))
	{
		if (PlayMontage(*FString::FromInt(0)))
		{
		
		}
	}
	

	
}

void URPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::CreatePlayMontageAndWaitProxy(
	FName TaskInstanceName,
	UAnimMontage* InMontageToPlay,
	float Rate,
	FName StartSection,
	bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale,
	float StartTimeSeconds)
{
	UPRGAbilityTask_PMAW* InWait =UPRGAbilityTask_PMAW::CreatePMAWDamageEventProxy(
		this,
		TaskInstanceName,
		InMontageToPlay,
		AbilityTags,
		Rate,
		StartSection,
		bStopWhenAbilityEnds,
		AnimRootMotionTranslationScale,
		StartTimeSeconds);
	if (InWait)
	{
		InWait->OnCompleted.AddDynamic(this,&URPGGameplayAbility::OnCompleted);
		InWait->OnBlendOut.AddDynamic(this,&URPGGameplayAbility::OnBlendOut);
		InWait->OnCancelled.AddDynamic(this,&URPGGameplayAbility::OnCancelled);
		InWait->OnInterrupted.AddDynamic(this,&URPGGameplayAbility::OnInterrupted);

		InWait->DamageEventReceived.AddDynamic(this,&URPGGameplayAbility::OnDamageGameplayEvent);

		InWait->Activate();
		return InWait;
	}
	return nullptr;
}

UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::PlayMontage(FName StartSection)
{
	return CreatePlayMontageAndWaitProxy(NAME_None,MontageToPlay,1.f,StartSection);
}
