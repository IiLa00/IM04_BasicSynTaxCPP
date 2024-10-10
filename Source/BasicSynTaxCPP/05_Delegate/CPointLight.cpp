#include "CPointLight.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CBoxBase_Delegate.h"

ACPointLight::ACPointLight()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootSceneComp = RootSceneComp;

	LightComp1 = CreateDefaultSubobject<UPointLightComponent>("LightComp1");
	LightComp1->SetupAttachment(RootSceneComp);

	LightComp2 = CreateDefaultSubobject<UPointLightComponent>("LightComp2");
	LightComp2->SetupAttachment(RootSceneComp);

	LightComp1->Intensity = 1e+4f;
	LightComp1->AttenuationRadius = 200.f;
	LightComp1->LightColor = FColor(255, 128, 0);

	LightComp2->Intensity = 1e+4f;
	LightComp2->AttenuationRadius = 200.f;
	LightComp2->LightColor = FColor(255, 128, 0);
	LightComp2->SetRelativeLocation(FVector(0, 200, 0));
}

void ACPointLight::BeginPlay()
{
	Super::BeginPlay();

	LightComp1->SetVisibility(false);
	LightComp2->SetVisibility(false);
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACBoxBase_Delegate::StaticClass(), Actors);

	if (Actors.Num() < 1)
		return;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACBoxBase_Delegate::StaticClass(), Actors);
	ACBoxBase_Delegate* Box = Cast<ACBoxBase_Delegate>(Actors[0]);

	if (Box)
	{
		Box->OnBoxBeginOverlap.BindUFunction(this,"On");
		Box->OnBoxEndOverlap.BindUFunction(this, "Off");

		Box->OnRetValOverlap.BindUObject(this, &ACPointLight::OnRandomColor);
	}



	
}

void ACPointLight::On()
{
	LightComp1->SetVisibility(true);
	//LightComp2->SetVisibility(true);
}

void ACPointLight::Off()
{
	LightComp1->SetVisibility(false);
	LightComp2->SetVisibility(false);
}

FString ACPointLight::OnRandomColor(FLinearColor InColor)
{
	LightComp2->SetVisibility(true);
	LightComp2->SetLightColor(InColor);

	return InColor.ToString();
}



