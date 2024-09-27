

#include "CStaticMeshActorBase.h"

ACStaticMeshActorBase::ACStaticMeshActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACStaticMeshActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACStaticMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

