#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Delegate.generated.h"

DECLARE_DELEGATE(FBoxOverlap);

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_Delegate : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
