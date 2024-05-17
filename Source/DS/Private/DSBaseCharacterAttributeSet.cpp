#include "DSBaseCharacterAttributeSet.h"

UDSBaseCharacterAttributeSet::UDSBaseCharacterAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UDSBaseCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UDSBaseCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}