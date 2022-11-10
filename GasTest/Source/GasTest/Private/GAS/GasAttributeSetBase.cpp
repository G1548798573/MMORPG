// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GasAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

UGasAttributeSetBase::UGasAttributeSetBase():Health(100.0f),MaxHealth(100.f)
{
	 
}

void UGasAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty()==FindFieldChecked<UProperty>(UGasAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UGasAttributeSetBase,Health)))
	{
		UE_LOG(LogTemp,Error,TEXT("Health is %f"),Health.GetCurrentValue());
		
	}
	Super::PostGameplayEffectExecute(Data);
}
