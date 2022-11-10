// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"
#include "RPGAbilitySystemComponent.h"

// Sets default values
AGASCharacter::AGASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent=CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("RPGAbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	
	RPGAttributeSet=CreateDefaultSubobject<URPGAttributeSet>(TEXT("RPGAttributeSet"));
}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent&&GetLocalRole()==ENetRole::ROLE_Authority)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
	TArray<UAttributeSet*> RPGAttributeSets;
	RPGAttributeSets.Add(RPGAttributeSet);
	AbilitySystemComponent->SetSpawnedAttributes(RPGAttributeSets);
	RegisterGameAbility();
	
}

// Called every frame
void AGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FGameplayAbilitySpecHandle AGASCharacter::RegisterGameAbility()
{
	if (AbilitySystemComponent&& IsValid(InGameplayAbility))
	{
		FGameplayAbilitySpecHandle Handle=AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InGameplayAbility));

		const FString String=Cast<UGameplayAbility>(InGameplayAbility->GetDefaultObject())->AbilityTags.ToStringSimple();
		
		Skills.Add(FName(String),Handle);
		
		return Handle;
	}
	
	return FGameplayAbilitySpecHandle();
}

bool AGASCharacter::ActiveSkill(FGameplayTag  SkillName)
{
	if (AbilitySystemComponent)
	{
		if (const FGameplayAbilitySpecHandle* Handle=Skills.Find(FName(*SkillName.ToString())))
		{
			
			UE_LOG(LogTemp, Log, TEXT("成功"));
			return AbilitySystemComponent->TryActivateAbility(*Handle);
	
		}
	}
	UE_LOG(LogTemp, Log, TEXT("失败"));
	return false;
}


