#include "DSAbilitySystemGlobals.h"

FDSNativeTags::FDSNativeTags()
{
	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

	AddNativeTag(TagsManager, Invincible, FName("State.Invincible"));
	AddNativeTag(TagsManager, ActiveAttack, FName("State.ActiveAttack"));
	AddNativeTag(TagsManager, ActionsBlocked, FName("State.ActionsBlocked"));
	AddNativeTag(TagsManager, LightAttackDamageType, FName("DamageType.LightAttack"));
	AddNativeTag(TagsManager, HeavyAttackDamageType, FName("DamageType.HeavyAttack"));
	AddNativeTag(TagsManager, DamageMagnitude, FName("Magnitude.Damage"));
}

void FDSNativeTags::AddNativeTag(UGameplayTagsManager& TagManager, FGameplayTag& Tag, FName TagName)
{
	// For editor builds, hot reload triggers an ensure because it clears static variables and such.
#if WITH_EDITOR
	Tag = TagManager.RequestGameplayTag(TagName, false);
	if (!Tag.IsValid())
	{
		Tag = TagManager.AddNativeGameplayTag(TagName);
	}
#else
	Tag = TagManager.AddNativeGameplayTag(TagName);
#endif // WITH_EDITOR
}

UDSAbilitySystemGlobals::UDSAbilitySystemGlobals()
{
	// Make sure to initialize tags.
	GetGlobalGameplayTags();
}

const FDSNativeTags& UDSAbilitySystemGlobals::GetGlobalGameplayTags()
{
	static FDSNativeTags NativeTags;
	return NativeTags;
}
