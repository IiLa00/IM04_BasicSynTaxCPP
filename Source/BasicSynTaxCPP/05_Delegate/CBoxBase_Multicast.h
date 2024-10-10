#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Multicast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FBoxMulticast,int32,FLinearColor);

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_Multicast : public ACBoxBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBoxMulticast OnBoxMulticast;

};
