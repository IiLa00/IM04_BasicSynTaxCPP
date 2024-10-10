#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPointLight.generated.h"

class UPointLightComponent;

UCLASS()
class BASICSYNTAXCPP_API ACPointLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPointLight();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UPointLightComponent* LightComp1;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UPointLightComponent* LightComp2;

private:
	UFUNCTION()
		void On();

	UFUNCTION()
		void Off();

	FString OnRandomColor(FLinearColor InColor);


};
