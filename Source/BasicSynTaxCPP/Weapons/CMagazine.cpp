#include "CMagazine.h"
#include "BasicSyntaxCPP.h"

ACMagazine::ACMagazine()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent<UStaticMeshComponent>(this, &MeshComp, "MeshComp");

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/magazine/SM_AR4_Mag_Empty");
	MeshComp->SetStaticMesh(MeshAsset);

}

void ACMagazine::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMagazine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

