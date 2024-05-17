#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DSBaseCharacterAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DS_API UDSBaseCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UDSBaseCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(UDSBaseCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UDSBaseCharacterAttributeSet, MaxHealth);

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	UPROPERTY()
	FGameplayAttributeData Health;

	UPROPERTY()
	FGameplayAttributeData MaxHealth;
};
