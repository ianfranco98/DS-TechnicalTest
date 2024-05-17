#include "DSCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameplayEffect.h"

#include "DSAbilitySystemGlobals.h"
#include "DSBaseCharacterAttributeSet.h"
#include "DSWeapon.h"
#include "InputAbilitySettings.h"

ADSCharacter::ADSCharacter()
{
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);

	if (GetMesh())
	{
		WeaponOffset = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponOffset"));
		WeaponOffset->SetupAttachment(GetMesh(), FName("hand_r"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No mesh found for weapon offset!"));
	}

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void ADSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerGameplayAbilitiesDataAsset)
	{
		const TSet<FGameplayInputAbilityInfo>& InputAbilities = PlayerGameplayAbilitiesDataAsset->GetInputAbilities();
		constexpr int32 AbilityLevel = 1;

		for (const FGameplayInputAbilityInfo& It : InputAbilities)
		{
			if (It.IsValid())
			{
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(It.GameplayAbilityClass, AbilityLevel, It.InputID);
				AbilitySpec.bActivateOnce = 0;
				AbilitySystemComp->GiveAbility(AbilitySpec);
			}
		}
	}

	AbilitySystemComp->InitAbilityActorInfo(this, this);
	
	if (InitialAttributes)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComp->MakeOutgoingSpec(InitialAttributes, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}

	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(UDSBaseCharacterAttributeSet::GetHealthAttribute()).AddUObject(
		this, &ADSCharacter::OnHealthChanged);
}

void ADSCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	const float Health = Data.NewValue;
	const float MaxHealth = BaseCharacterAttributeSet->GetMaxHealth();

	if (Health <= 0.0f && bAllowDead)
	{
		WeaponInstance->Destroy();
		Destroy();
	}
	else
	{
		UpdateHealthBar(Health / MaxHealth);
	}
}

void ADSCharacter::PreInitializeComponents()
{
	BaseCharacterAttributeSet = NewObject<UDSBaseCharacterAttributeSet>(this, TEXT("BaseCharacterAttributeSet"));

	if (WeaponClass && WeaponOffset)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		WeaponInstance = GetWorld()->SpawnActor<ADSWeapon>(WeaponClass, SpawnParams);
		WeaponInstance->AttachToComponent(WeaponOffset, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon class or weapon offset found!"));
	}

	Super::PreInitializeComponents();
}
