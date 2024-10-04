
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawDebug.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACDrawDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDrawDebug();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
		FVector TargetLocations1;

	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
		FVector TargetLocations2;

	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
		FVector TargetLocations3;

	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
		FVector TargetLocations4;

	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
		FVector TargetLocations5;

	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
		FVector TargetLocations6;

	FBox Box;
	FVector WorldLocations[6];
	
};
