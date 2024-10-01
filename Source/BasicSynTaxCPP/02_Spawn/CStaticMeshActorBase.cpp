#include "CStaticMeshActorBase.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMeshActorBase::ACStaticMeshActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshpComp");
	RootComponent = MeshComp;

}

void ACStaticMeshActorBase::BeginPlay()
{
	Super::BeginPlay();

	StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/StaticMeshes/MI_StaticMesh.MI_StaticMesh'"));

	UMaterialInstanceDynamic::Create(,);
	
}

void ACStaticMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

