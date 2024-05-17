#include "DSDodgeRollAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemComponent.h"
#include "DSAbilitySystemGlobals.h"
#include "DSGameplayTagAnimNotify.h"

UDSDodgeRollAbility::UDSDodgeRollAbility()
{
	TagNotifiesToCheck.Add(UDSAbilitySystemGlobals::GetGlobalGameplayTags().Invincible);
}

void UDSDodgeRollAbility::OnNotify(const FGameplayTag& Tag, bool bTagActive)
{
	// Assuming Tag is always the invincible tag.
	if (bTagActive)
	{
		GetActorInfo().AbilitySystemComponent->AddLooseGameplayTag(Tag);

	}
	else
	{
		GetActorInfo().AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
	}

	bTagAdded = bTagActive;
}

void UDSDodgeRollAbility::OnMontageCompleted()
{ 
	GetActorInfo().AbilitySystemComponent->RemoveLooseGameplayTag(UDSAbilitySystemGlobals::GetGlobalGameplayTags().Invincible);

	Super::OnMontageCompleted();
}
