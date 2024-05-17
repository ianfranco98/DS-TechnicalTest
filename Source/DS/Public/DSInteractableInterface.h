#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DSInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDSInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DS_API IDSInteractableInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void Interact(AActor* InteractionInstigator) = 0;
};
