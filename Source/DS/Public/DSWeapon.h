#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "DSWeapon.generated.h"

class UCapsuleComponent;
class UGameplayEffect;
class UStaticMeshComponent;

UCLASS()
class DS_API ADSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ADSWeapon();

	void StartAttack(const FGameplayTag& AttackType);

	void StopAttack();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageGE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, float> WeaponDamageTypes;

	UPROPERTY(Transient)
	bool bIsAttacking = false;

private:

	UPROPERTY(Transient)
	FGameplayTag CurrentAttackType;

	UPROPERTY(Transient)
	TArray<AActor*> DamagedActors;

};
