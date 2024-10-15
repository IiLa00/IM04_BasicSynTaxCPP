#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpotLights.generated.h"

class USpotLightComponent;

UCLASS()
class BASICSYNTAXCPP_API ACSpotLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpotLights();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* RootSceneComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USpotLightComponent* LightComps[3];

private:
	void Spot(int32 InIndex, FLinearColor InColor);

};
