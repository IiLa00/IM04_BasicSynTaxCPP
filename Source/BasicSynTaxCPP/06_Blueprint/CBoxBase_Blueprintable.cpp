#include "CBoxBase_Blueprintable.h"
#include "BasicSyntaxCPP.h"
#include "Characters/CPlayer.h"

void ACBoxBase_Blueprintable::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Blueprintable::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase_Blueprintable::EndOverlap);
}

void ACBoxBase_Blueprintable::ResetBodyColor_Implementation()
{
	ACPlayer* Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(Player)	
		Player->SetBodyColor(FLinearColor(0.45098f, 0.403922f, 0.360784f), FLinearColor(0.45098f, 0.403922f, 0.360784f));
}

void ACBoxBase_Blueprintable::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ChangeBodyColor(FLinearColor(0.27f,0.12f,0.7f));
}

void ACBoxBase_Blueprintable::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ResetBodyColor();
}