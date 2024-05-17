#pragma once

#include "CoreMinimal.h"
#include "DSCharacter.h"
#include "DSPlayableCharacter.generated.h"


class UCameraComponent;
class UGameplayAbility;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;

UCLASS()
class DS_API ADSPlayableCharacter : public ADSCharacter
{
	GENERATED_BODY()

public:

	ADSPlayableCharacter();

	FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(1); }

	// note: AI enemies are always hostile to player.
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override { return ETeamAttitude::Hostile; }

	void PossessedBy(AController* NewController) override;

protected:

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnAbilityInputPressed(int32 InputID);
	void OnAbilityInputReleased(int32 InputID);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;
	
};
