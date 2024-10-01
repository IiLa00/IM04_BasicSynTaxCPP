

#include "CSpawner.h"
#include "CStaticMeshActorBase.h"

ACSpawner::ACSpawner()
{

}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < (int32)EStaticMeshAssetType::Max; i++)
	{
		FTransform TM;

		StaticMeshBased[i] = GetWorld()->SpawnActor<ACStaticMeshActorBase>(StaticMeshBasedClasses[i], TM);
		
		FVector Location = StaticMeshBased[i]->GetActorLocation();
		StaticMeshBased[i]->SetActorLocation(FVector(Location.X, Location.Y + 200 * i, Location.Z));
	}
	
}



