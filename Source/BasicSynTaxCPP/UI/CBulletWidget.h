#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CBulletWidget.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCBulletWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bShoot;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Shooting();

	UFUNCTION(BlueprintImplementableEvent)
		void Reload();

public:
	FORCEINLINE bool IsShoot() { return bShoot; }
};
