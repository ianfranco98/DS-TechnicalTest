#pragma once

#include "CoreMinimal.h"
#include "DSBaseAnimMontageAbility.h"
#include "GameplayTagContainer.h"
#include "DSAttackAbility.generated.h"

UCLASS()
class DS_API UDSAttackAbility : public UDSBaseAnimMontageAbility
{
	GENERATED_BODY()

public:

	UDSAttackAbility();

protected:

	void OnNotify(const FGameplayTag& Tag, bool bTagActive) override;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AttackType;

};
