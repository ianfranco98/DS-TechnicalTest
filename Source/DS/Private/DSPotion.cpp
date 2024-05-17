#include "DSPotion.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameplayEffect.h>
#include <DSAbilitySystemGlobals.h>


ADSPotion::ADSPotion()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionCollision"));
	SetRootComponent(SphereComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComp);
}

void ADSPotion::Interact(AActor* InteractionInstigator)
{
	TScriptInterface<IAbilitySystemInterface> InstigatorInterface(InteractionInstigator);
	UAbilitySystemComponent* InstigatorASC = InstigatorInterface->GetAbilitySystemComponent();

	if (!InstigatorInterface || !InstigatorASC || !ensure(PotionGE.Get()))
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = InstigatorASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = InstigatorASC->MakeOutgoingSpec(PotionGE, 1, EffectContext);

	InstigatorASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());

	Destroy();
}

