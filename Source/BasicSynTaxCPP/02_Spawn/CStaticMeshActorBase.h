
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMeshActorBase.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACStaticMeshActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMeshActorBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* MeshComp;
	

};
