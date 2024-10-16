#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

class UTextRenderComponent;
class ACVertex;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceHit, AActor*, InActor, FLinearColor, InColor);

UCLASS()
class BASICSYNTAXCPP_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UTextRenderComponent* TextRenderComp;

public:
	UPROPERTY(BlueprintAssignable)
		FLineTraceHit OnLineTraceHit;

private:
	UFUNCTION()
		void LineTraceHit(AActor* InActor, FLinearColor InColor);

private:
	ACVertex* Vertices[2];

};
