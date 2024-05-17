#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DSInteract.generated.h"


UCLASS()
class DS_API UDSInteractAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
};
