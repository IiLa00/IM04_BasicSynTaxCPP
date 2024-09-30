#include "CStaticMeshActor_Cone.h"

ACStaticMeshActor_Cone::ACStaticMeshActor_Cone()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Cone.SM_Cone'"));

	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}