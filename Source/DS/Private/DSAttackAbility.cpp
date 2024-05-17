#include "DSAttackAbility.h"
#include "DSAbilitySystemGlobals.h"
#include "DSCharacter.h"
#include "DSWeapon.h"

UDSAttackAbility::UDSAttackAbility()
{
	TagNotifiesToCheck.Add(UDSAbilitySystemGlobals::GetGlobalGameplayTags().ActiveAttack);
}

void UDSAttackAbility::OnNotify(const FGameplayTag& Tag, bool bTagActive)
{
	ADSCharacter* DSCharacter = CastChecked<ADSCharacter>(GetActorInfo().AvatarActor);

	if (!ensure(DSCharacter))
	{
		return;
	}

	ADSWeapon* Weapon = DSCharacter->GetWeapon();

	const FGameplayTag& ActiveAttackTag = UDSAbilitySystemGlobals::GetGlobalGameplayTags().ActiveAttack;

	if (Tag.MatchesTagExact(ActiveAttackTag))
	{
		if (bTagActive)
		{
			Weapon->StartAttack(AttackType);
		}
		else
		{
			Weapon->StopAttack();
		}
	}
}
