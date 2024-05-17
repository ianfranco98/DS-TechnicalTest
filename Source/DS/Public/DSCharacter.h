#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "DSCharacter.generated.h"

class UGameplayEffect;

class ADSWeapon;
class UDSInputAbilitySettings;
class UDSBaseCharacterAttributeSet;
class UWidgetComponent;

struct FInputActionValue;

UCLASS(config=Game)
class ADSCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

	ADSCharacter();

	virtual FGenericTeamId GetGenericTeamId() const { return FGenericTeamId(100); }

	ADSWeapon* GetWeapon() const { return WeaponInstance; }
	
	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

protected:

	void PreInitializeComponents() override;

	void BeginPlay() override;

	void OnHealthChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(float NewPercentage);
	
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDSInputAbilitySettings> PlayerGameplayAbilitiesDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> InitialAttributes;

	TObjectPtr<UDSBaseCharacterAttributeSet> BaseCharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADSWeapon> WeaponClass;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<ADSWeapon> WeaponInstance;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> WeaponOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditDefaultsOnly)
	bool bAllowDead = true;

};

