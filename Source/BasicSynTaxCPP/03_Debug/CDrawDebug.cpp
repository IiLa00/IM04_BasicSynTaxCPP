#include "CDrawDebug.h"
#include "DrawDebugHelpers.h"

ACDrawDebug::ACDrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	TargetLocations1 = FVector(0, 0, 0);
	TargetLocations2 = FVector(600, 0, 0);
	TargetLocations3 = FVector(0, 600, 0);
	TargetLocations4 = FVector(600, 600, 0);
	TargetLocations5 = FVector(0, 700, 0);
	TargetLocations6 = FVector(600, 700, 0);
	
}

void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();

	FVector WorldLocation = GetActorLocation() + TargetLocations1;
	Box = FBox(FVector(-50,-100,-50), FVector(50, 100, 50));

	DrawDebugBox(GetWorld(), WorldLocation + Box.GetCenter(), Box.GetExtent(), FColor::Orange, true);
	
}

void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WorldLocations[0]= GetActorLocation() + TargetLocations1;
	WorldLocations[1] = GetActorLocation() + TargetLocations2;
	WorldLocations[2] = GetActorLocation() + TargetLocations3;
	WorldLocations[3] = GetActorLocation() + TargetLocations4;
	WorldLocations[4] = GetActorLocation() + TargetLocations5;
	WorldLocations[5] = GetActorLocation() + TargetLocations6;

	DrawDebugSolidBox(GetWorld(), WorldLocations[1] + Box.GetCenter(), Box.GetExtent(), FColor::Purple);
	DrawDebugPoint(GetWorld(), WorldLocations[2], 30.f, FColor::Red);
	DrawDebugSphere(GetWorld(), WorldLocations[3], 100,30,FColor::Emerald);
	DrawDebugCircle(GetWorld(), WorldLocations[4], 100, 30, FColor::Cyan);
	// DrawDebugString(GetWorld(), WorldLocations[5], GetName(), NULL, FColor::Red);

	FVector ArrowStart = WorldLocations[1];
	FVector ArrowEnd = WorldLocations[4];
	DrawDebugDirectionalArrow(GetWorld(), ArrowStart, ArrowEnd, 200, FColor::Black,false,-1.f,0,10);
}

