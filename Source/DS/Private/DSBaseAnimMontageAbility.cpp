#include "DSBaseAnimMontageAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DSGameplayTagAnimNotify.h"


void UDSBaseAnimMontageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName("DodgeRollMontage"), AnimMontage, AnimRate);
	PlayMontageTask->OnCompleted.AddDynamic(this, &UDSBaseAnimMontageAbility::OnMontageCompleted);
	PlayMontageTask->OnCancelled.AddDynamic(this, &UDSBaseAnimMontageAbility::OnMontageCompleted);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UDSBaseAnimMontageAbility::OnMontageCompleted);

	for (FAnimNotifyEvent& NotifyEvent : AnimMontage->Notifies)
	{
		UDSGameplayTagAnimNotify* GameplayTagAnimNotify = Cast<UDSGameplayTagAnimNotify>(NotifyEvent.Notify);

		if (!GameplayTagAnimNotify)
		{
			continue;
		}

		for (const FGameplayTag& Tag : TagNotifiesToCheck)
		{	
			if (Tag.MatchesTagExact(GameplayTagAnimNotify->GetGameplayTag()))
			{
				const FDelegateHandleWrapper NewHandleWrapper = FDelegateHandleWrapper(GameplayTagAnimNotify->OnNotified.AddUObject(this, &UDSBaseAnimMontageAbility::NotifyFilterOwner));
				OnNotifyDelegateHandle.Add(NewHandleWrapper);
			}
		}
	}

	PlayMontageTask->ReadyForActivation();
}

void UDSBaseAnimMontageAbility::OnNotify(const FGameplayTag& Tag, bool bTagActive)
{
}

void UDSBaseAnimMontageAbility::OnMontageCompleted()
{
	PlayMontageTask->OnCompleted.RemoveDynamic(this, &UDSBaseAnimMontageAbility::OnMontageCompleted);

	for (FAnimNotifyEvent& NotifyEvent : AnimMontage->Notifies)
	{
		if (UDSGameplayTagAnimNotify* GameplayTagAnimNotify = Cast<UDSGameplayTagAnimNotify>(NotifyEvent.Notify))
		{
			for (const FDelegateHandleWrapper& NotifyDelegateHandle : OnNotifyDelegateHandle)
			{
				GameplayTagAnimNotify->OnNotified.Remove(NotifyDelegateHandle.DelegateHandle);
			}
		}
	}

	OnNotifyDelegateHandle.Empty();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UDSBaseAnimMontageAbility::NotifyFilterOwner(const AActor* NotifyOwner, const FGameplayTag& Tag, bool bTagActive)
{
	if (NotifyOwner == GetActorInfo().AvatarActor)
	{
		OnNotify(Tag, bTagActive);
	}
}
