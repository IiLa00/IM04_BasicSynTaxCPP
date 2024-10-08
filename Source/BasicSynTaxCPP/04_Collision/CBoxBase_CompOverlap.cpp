#include "CBoxBase_CompOverlap.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

ACBoxBase_CompOverlap::ACBoxBase_CompOverlap()
{
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>("PointLightComp");
	PointLightComp->SetupAttachment(RootSceneComp);

	PointLightComp->SetLightColor(FLinearColor::Green);
}

void ACBoxBase_CompOverlap::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ACBoxBase_CompOverlap::BeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACBoxBase_CompOverlap::EndOverlap);

	PointLightComp->SetVisibility(false);
}

void ACBoxBase_CompOverlap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLightComp->SetVisibility(true);
}

void ACBoxBase_CompOverlap::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLightComp->SetVisibility(false);
}