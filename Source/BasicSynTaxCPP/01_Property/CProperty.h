
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

protected:
	UPROPERTY(EditInstanceOnly, Category = "Numeric", BlueprintReadOnly)
		int32 NumA = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Numeric", BlueprintReadOnly)
		int32 NumB;

	UPROPERTY(EditAnywhere, Category = "Numeric", BlueprintReadWrite)
		int32 NumC = 30;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Real")
		float RealA = 1.11f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Real")
		float RealB = 2.22f;

	UPROPERTY(VisibleAnywhere, Category = "Real")
		float RealC = 3.33f;

	UPROPERTY(EditAnywhere, Category = "MyActor")
		AActor* OtherActor;

};
