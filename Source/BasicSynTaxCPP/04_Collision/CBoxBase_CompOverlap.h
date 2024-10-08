#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_CompOverlap.generated.h"

class UPointLightComponent;

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_CompOverlap : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_CompOverlap();
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UPointLightComponent* PointLightComp;
	
};
