#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GameplayTagsManager.h"
#include "DSAbilitySystemGlobals.generated.h"

struct FDSNativeTags
{

	FDSNativeTags();

	FGameplayTag Invincible;
	FGameplayTag ActiveAttack;
	FGameplayTag ActionsBlocked;

	FGameplayTag LightAttackDamageType;
	FGameplayTag HeavyAttackDamageType;

	FGameplayTag DamageMagnitude;

private:

	void AddNativeTag(UGameplayTagsManager& TagManager, FGameplayTag& Tag, FName TagName);

};

UCLASS()
class DS_API UDSAbilitySystemGlobals : public UAbilitySystemGlobals
{

	GENERATED_BODY()

public:

	UDSAbilitySystemGlobals();

	static const FDSNativeTags& GetGlobalGameplayTags();
};
