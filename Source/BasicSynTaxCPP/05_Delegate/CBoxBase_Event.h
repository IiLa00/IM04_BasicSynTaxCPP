#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Event.generated.h"


UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_Event : public ACBoxBase
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(ACBoxBase_Event,FBoxEvent,int32);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBoxEvent OnBoxEvent;
};
