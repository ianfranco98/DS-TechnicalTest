

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "InputAbilitySettings.generated.h"

class UInputAction;

USTRUCT()
struct FGameplayInputAbilityInfo
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;

	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TObjectPtr<UInputAction> InputAction;
 
	/** It will be generated automatically. */
	UPROPERTY(VisibleAnywhere, Category = "GameplayInputAbilityInfo")
	int32 InputID;

	bool IsValid() const
	{
		return GameplayAbilityClass != nullptr;
	}
 
	bool operator==(const FGameplayInputAbilityInfo& Other) const
	{
		return GameplayAbilityClass == Other.GameplayAbilityClass && InputAction == Other.InputAction;
	}

	bool operator!=(const FGameplayInputAbilityInfo& Other) const
	{
		return !operator==(Other);
	}

	friend uint32 GetTypeHash(const FGameplayInputAbilityInfo& Item)
	{
		return HashCombine(GetTypeHash(Item.GameplayAbilityClass), GetTypeHash(Item.InputAction));
	}
};

UCLASS()
class DS_API UDSInputAbilitySettings : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const TSet<FGameplayInputAbilityInfo>& GetInputAbilities() const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:

	UPROPERTY(EditAnywhere)
	TSet<FGameplayInputAbilityInfo> InputAbilities;

};