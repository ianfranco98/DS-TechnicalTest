#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSInteractableInterface.h"
#include "DSPotion.generated.h"

class USphereComponent;
class UGameplayEffect;
class UStaticMeshComponent;

UCLASS()
class DS_API ADSPotion : public AActor, public IDSInteractableInterface
{
	GENERATED_BODY()
	
public:	
	
	ADSPotion();

	void Interact(AActor* InteractionInstigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> PotionGE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComp;

};
