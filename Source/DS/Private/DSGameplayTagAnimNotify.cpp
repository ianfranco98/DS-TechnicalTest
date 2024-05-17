#include "DSGameplayTagAnimNotify.h"


void UDSGameplayTagAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnNotified.Broadcast(MeshComp->GetOwner(), Tag, bTagActive);
}