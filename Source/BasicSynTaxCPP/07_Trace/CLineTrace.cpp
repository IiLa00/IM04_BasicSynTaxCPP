#include "CLineTrace.h"
#include "BasicSyntaxCPP.h"
#include "Components/TextRenderComponent.h"
#include "CVertex.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootSceneComp");
	CHelpers::CreateSceneComponent(this, &TextRenderComp, "TextRenderComp");

	TextRenderComp->SetRelativeLocation(FVector(0, 0, 20));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->SetTextRenderColor(FColor::Blue);
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	TextRenderComp->SetText(GetName());
}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACVertex::StaticClass(), Actors);
	if (Actors.Num() < 1) return;

	Vertices[0] = Cast<ACVertex>(Actors[0]);
	Vertices[1] = Cast<ACVertex>(Actors[1]);

	OnLineTraceHit.AddDynamic(this, &ACLineTrace::LineTraceHit);
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Start = Vertices[0]->GetActorLocation();
	FVector End = Vertices[1]->GetActorLocation();

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Vertices[0]);
	IgnoreActors.Add(Vertices[1]);

	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingleByProfile
	(
		GetWorld(), 
		Start, 
		End, 
		"Pawn", 
		false, 
		IgnoreActors, 
		EDrawDebugTrace::ForOneFrame, 
		Hit, 
		true
	);

	if (Hit.bBlockingHit == false) return;

	OnLineTraceHit.Broadcast(Hit.GetActor(), FLinearColor::Red);


}

void ACLineTrace::LineTraceHit(AActor* InActor, FLinearColor InColor)
{
	TextRenderComp->SetTextRenderColor(InColor.ToFColor(true));
	TextRenderComp->SetText(InActor->GetName());
}

