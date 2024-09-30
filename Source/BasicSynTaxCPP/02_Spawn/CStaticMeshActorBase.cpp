

#include "CStaticMeshActorBase.h"

ACStaticMeshActorBase::ACStaticMeshActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshpComp");
	RootComponent = MeshComp;

}

void ACStaticMeshActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACStaticMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

