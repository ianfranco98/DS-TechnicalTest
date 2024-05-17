#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Delegates/IDelegateInstance.h"
#include "DSBaseAnimMontageAbility.generated.h"

USTRUCT()
struct FDelegateHandleWrapper
{
	GENERATED_BODY()

	FDelegateHandleWrapper() {}

	FDelegateHandleWrapper(FDelegateHandle InDelegateHandle) : DelegateHandle(InDelegateHandle) {}

	FDelegateHandle DelegateHandle;
};

class UAbilityTask_PlayMontageAndWait;

UCLASS()
class DS_API UDSBaseAnimMontageAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

protected:

	UFUNCTION()
	virtual void OnNotify(const FGameplayTag& Tag, bool bTagActive);

	UFUNCTION()
	virtual void OnMontageCompleted();

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	TArray<FGameplayTag> TagNotifiesToCheck;

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	float AnimRate = 1.0f;

	TObjectPtr<UAbilityTask_PlayMontageAndWait> PlayMontageTask;

private:

	// note: Although all abilities are instanced per actor, all the usages of AnimMontage points to
	// the same montage instance, resulting in all abilities sharing the same Notify events.
	// This is a workaround to avoid that issue.
	void NotifyFilterOwner(const AActor* NotifyOwner, const FGameplayTag& Tag, bool bTagActive);

	UPROPERTY(Transient)
	TArray<FDelegateHandleWrapper> OnNotifyDelegateHandle;
};
