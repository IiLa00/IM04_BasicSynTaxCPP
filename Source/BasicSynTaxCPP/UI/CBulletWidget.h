#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CBulletWidget.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCBulletWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Shooting();

	UFUNCTION(BlueprintImplementableEvent)
		void Reload();
};
