#include "DSInteract.h"

#include "DSInteractableInterface.h"


void UDSInteractAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (ActorInfo->OwnerActor.IsValid())
	{
		AActor* Owner = ActorInfo->OwnerActor.Get();

		TSet<AActor*> OverlappingActors;
		Owner->GetOverlappingActors(OverlappingActors);

		for (AActor* ActorFound : OverlappingActors)
		{
			TScriptInterface<IDSInteractableInterface> InteractableActor(ActorFound);
			if (InteractableActor)
			{
				InteractableActor->Interact(Owner);
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}