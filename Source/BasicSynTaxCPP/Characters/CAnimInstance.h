#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		float Speed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		float Direction;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
		bool bEquipped;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
		bool bAiming;
	
};
