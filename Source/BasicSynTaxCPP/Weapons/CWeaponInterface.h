#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CWeaponInterface.generated.h"

class ACAR4;

UINTERFACE(MinimalAPI)
class UCWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class BASICSYNTAXCPP_API ICWeaponInterface
{
	GENERATED_BODY()

public:
	virtual ACAR4* GetWeapon() = 0;
	virtual void GetAimRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) = 0;

	virtual void OnTarget() {};
	virtual void OffTarget() {};
};
