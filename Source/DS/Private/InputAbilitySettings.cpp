#include "InputAbilitySettings.h"

const TSet<FGameplayInputAbilityInfo>& UDSInputAbilitySettings::GetInputAbilities() const
{
	return InputAbilities;
}

#if WITH_EDITOR
void UDSInputAbilitySettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FProperty* Property = PropertyChangedEvent.Property;
	if (Property && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UDSInputAbilitySettings, InputAbilities) && !InputAbilities.IsEmpty())
	{
		TArray<FGameplayInputAbilityInfo> InputAbilitiesArray = InputAbilities.Array();
		InputAbilities.Reset();

		for (int32 i = 0; i < InputAbilitiesArray.Num(); ++i)
		{
			FGameplayInputAbilityInfo& Info = InputAbilitiesArray[i];
			Info.InputID = i;
			InputAbilities.Add(Info);
		}
	}
}
#endif