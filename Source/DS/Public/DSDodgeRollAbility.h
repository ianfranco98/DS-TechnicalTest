#pragma once

#include "CoreMinimal.h"
#include "DSBaseAnimMontageAbility.h"
#include "DSDodgeRollAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;

UCLASS()
class DS_API UDSDodgeRollAbility : public UDSBaseAnimMontageAbility
{
	GENERATED_BODY()

public:

	UDSDodgeRollAbility();

protected:

	void OnNotify(const FGameplayTag& Tag, bool bTagActive) override;

	void OnMontageCompleted() override;

	UPROPERTY(Transient)
	bool bTagAdded = false;

};
