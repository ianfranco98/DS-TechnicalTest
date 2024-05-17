#include "DSWeapon.h"

#include "AbilitySystemComponent.h"
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameplayEffect.h>
#include <DSCharacter.h>
#include <DSAbilitySystemGlobals.h>

ADSWeapon::ADSWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComp);
}

void ADSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	ADSCharacter* InstigatorCharacter = GetOwner<ADSCharacter>();
	InstigatorCharacter->GetCapsuleComponent()->IgnoreActorWhenMoving(this, true);
	CapsuleComp->IgnoreActorWhenMoving(InstigatorCharacter, true);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ADSWeapon::OnBeginOverlap);
}

void ADSWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const bool bActorAlreadyDamaged = DamagedActors.FindByKey(OtherActor) != nullptr;

	if (!bIsAttacking || OtherActor == Owner || bActorAlreadyDamaged || CurrentAttackType == FGameplayTag::EmptyTag)
	{
		return;
	}

	ADSCharacter* DSCharacter = Cast<ADSCharacter>(OtherActor);
	if (DSCharacter)
	{
		UAbilitySystemComponent* ASC = DSCharacter->GetAbilitySystemComponent();

		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle NewHandle = ASC->MakeOutgoingSpec(DamageGE, 1, EffectContext);

		const FGameplayTag& DamageMagnitudeTag = UDSAbilitySystemGlobals::GetGlobalGameplayTags().DamageMagnitude;
		const float DamageValue = WeaponDamageTypes.FindChecked(CurrentAttackType);

		NewHandle.Data.Get()->SetSetByCallerMagnitude(DamageMagnitudeTag, -DamageValue);

		const FActiveGameplayEffectHandle& ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		if (ActiveGEHandle.WasSuccessfullyApplied())
		{
			DamagedActors.Add(OtherActor);
		}
	}
}

void ADSWeapon::StartAttack(const FGameplayTag& AttackType)
{
	bIsAttacking = true;
	CurrentAttackType = AttackType;
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ADSWeapon::StopAttack()
{
	bIsAttacking = false;
	DamagedActors.Empty();
	CurrentAttackType = FGameplayTag::EmptyTag;
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

