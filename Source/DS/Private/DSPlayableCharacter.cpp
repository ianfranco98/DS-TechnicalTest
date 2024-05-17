#include "DSPlayableCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "InputAbilitySettings.h"
#include "DSAbilitySystemGlobals.h"


ADSPlayableCharacter::ADSPlayableCharacter() : Super()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	// note: -1.0f means instant rotation. This give us a worse movement feel,
	// but instead, we gain more responsiveness when we dodge and attack.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, -1.0f, 0.0f);

	// The player can't die for demonstration purposes.
	bAllowDead = false;
}

void ADSPlayableCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADSPlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (PlayerGameplayAbilitiesDataAsset)
		{
			const TSet<FGameplayInputAbilityInfo>& InputAbilities = PlayerGameplayAbilitiesDataAsset->GetInputAbilities();
			for (const auto& It : InputAbilities)
			{
				if (It.IsValid())
				{
					const UInputAction* InputAction = It.InputAction;
					const int32 InputID = It.InputID;

					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ADSPlayableCharacter::OnAbilityInputPressed, InputID);
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ADSPlayableCharacter::OnAbilityInputReleased, InputID);
				}
			}
		}

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADSPlayableCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADSPlayableCharacter::Look);
	}
}

void ADSPlayableCharacter::OnAbilityInputPressed(int32 InputID)
{
	if (AbilitySystemComp)
	{
		AbilitySystemComp->AbilityLocalInputPressed(InputID);
	}
}

void ADSPlayableCharacter::OnAbilityInputReleased(int32 InputID)
{
	if (AbilitySystemComp)
	{
		AbilitySystemComp->AbilityLocalInputReleased(InputID);
	}
}

void ADSPlayableCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const bool bBlockMovement = GetAbilitySystemComponent()->GetTagCount(UDSAbilitySystemGlobals::GetGlobalGameplayTags().ActionsBlocked) > 0;

	if (!bBlockMovement && Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADSPlayableCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
