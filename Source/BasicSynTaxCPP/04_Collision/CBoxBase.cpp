#include "CBoxBase.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACBoxBase::ACBoxBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootSceneComp = RootSceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootSceneComp);
	BoxComp->SetHiddenInGame(false); 
	BoxComp->SetRelativeScale3D(FVector(3));

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(RootSceneComp);
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->TextRenderColor = FColor::Red;
	TextRenderComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComp->Text = FText::FromString(GetName());
}

void ACBoxBase::BeginPlay()
{
	Super::BeginPlay();
}



