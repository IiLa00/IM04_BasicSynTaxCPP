#include "CBullet.h"
#include "BasicSyntaxCPP.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACBullet::ACBullet()
{
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");
	CHelpers::CreateActorComponent(this, &MoveComp, "MoveComp");

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/StaticMeshes/SM_Sphere");
	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetRelativeScale3D(FVector(1.f, 0.025f, 0.025f));

	UMaterial* MaterialAsset;
	CHelpers::GetAsset(&MaterialAsset, "/Game/StaticMeshes/M_Emissive");
	MeshComp->SetMaterial(0, MaterialAsset);
	MeshComp->SetCollisionProfileName("NoCollision");

	MoveComp->InitialSpeed = 20000.f;
	MoveComp->MaxSpeed = 20000.f;
	MoveComp->ProjectileGravityScale = 0.f;
	
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.f);
}

