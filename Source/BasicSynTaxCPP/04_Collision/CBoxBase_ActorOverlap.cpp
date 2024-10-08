#include "CBoxBase_ActorOverlap.h"
#include "Utilities/CLog.h"

void ACBoxBase_ActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_ActorOverlap::BeginOverlap);
}

void ACBoxBase_ActorOverlap::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	PrintLine();

	CLog::Print(OtherActor->GetName() + " is overlapped");
}
