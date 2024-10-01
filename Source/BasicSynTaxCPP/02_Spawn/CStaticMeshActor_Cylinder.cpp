#include "CStaticMeshActor_Cylinder.h"

ACStaticMeshActor_Cylinder::ACStaticMeshActor_Cylinder()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("/Game/StaticMeshes/SM_Cylinder"));

	if(SMAsset.Succeeded())
		MeshComp->SetStaticMesh(SMAsset.Object);
}
