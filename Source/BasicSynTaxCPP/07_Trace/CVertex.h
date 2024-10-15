#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertex.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	ACVertex();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* MeshComp;
};
