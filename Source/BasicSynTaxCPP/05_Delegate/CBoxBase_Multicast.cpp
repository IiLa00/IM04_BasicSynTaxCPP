#include "CBoxBase_Multicast.h"
#include "Kismet/KismetMathLibrary.h"

void ACBoxBase_Multicast::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Multicast::BeginOverlap);
}

void ACBoxBase_Multicast::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	RandomColor.A = 1.0f;

	OnBoxMulticast.Broadcast(RandomIndex, RandomColor);
}