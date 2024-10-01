#include "CStaticMeshActor_Sphere.h"

ACStaticMeshActor_Sphere::ACStaticMeshActor_Sphere()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));

	if(SMAsset.Succeeded())
		MeshComp->SetStaticMesh(SMAsset.Object);
}
