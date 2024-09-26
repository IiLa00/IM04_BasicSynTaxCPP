

#include "CProperty.h"

ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();

	GLog->Log("Hello Wolrd!");
	
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

