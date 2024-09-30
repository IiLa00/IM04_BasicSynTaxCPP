#include "CStaticMeshActor_Cube.h"

ACStaticMeshActor_Cube::ACStaticMeshActor_Cube()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'"));

	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}