#include "CSpotLights.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CBoxBase_Multicast.h"

ACSpotLights::ACSpotLights()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));

	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i + 1));

		LightComps[i] = CreateDefaultSubobject<USpotLightComponent>(FName(SubObjectName));
		LightComps[i]->SetupAttachment(RootComponent);
		LightComps[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		LightComps[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		LightComps[i]->Intensity = 1e+5f;
		LightComps[i]->OuterConeAngle = 25.f;

	}

}

void ACSpotLights::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Multicast::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		ACBoxBase_Multicast* Box = Cast<ACBoxBase_Multicast>(Actors[0]);

		if (Box)
		{
			Box->OnBoxMulticast.AddUObject(this, &ACSpotLights::Spot);
		}
	}
}

void ACSpotLights::Spot(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		LightComps[i]->SetLightColor(FLinearColor::White);
	}
	LightComps[InIndex]->SetLightColor(InColor);
}

