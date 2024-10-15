#include "CBoxBase_Event.h"
#include "Kismet/KismetMathLibrary.h"

void ACBoxBase_Event::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Event::BeginOverlap);
}

void ACBoxBase_Event::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	OnBoxEvent.Broadcast(UKismetMathLibrary::RandomIntegerInRange(0, 2));

}
