// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/RPGAttributeSet.h"

#include "Net/UnrealNetwork.h"


URPGAttributeSet::URPGAttributeSet():Health(100.f)
{
	
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);
	//属性改变之后要做的工作，比如UI。
	
	
}

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet,Health,OldValue);
	
	
}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URPGAttributeSet,Health);
}
