#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "DSGameplayTagAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnNotified, const AActor* NotifyOwner, const FGameplayTag& Tag, bool bTagActive);

UCLASS()
class DS_API UDSGameplayTagAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FGameplayTag GetGameplayTag() const { return Tag; }

	FOnNotified OnNotified;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayTag)
	FGameplayTag Tag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayTag)
	bool bTagActive = true;
};
