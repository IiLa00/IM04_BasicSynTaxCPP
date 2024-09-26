
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACProperty : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
