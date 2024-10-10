#include "CBall.h"

ACBall::ACBall()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i+1));

		MeshComps[i]=CreateDefaultSubobject<UStaticMeshComponent>(FName(SubObjectName));

	}

}

void ACBall::BeginPlay()
{
	Super::BeginPlay();
	
}


