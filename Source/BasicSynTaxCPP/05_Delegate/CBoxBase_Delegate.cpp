#include "CBoxBase_Delegate.h"
#include "Utilities/CLog.h"

void ACBoxBase_Delegate::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Delegate::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase_Delegate::EndOverlap);
}

void ACBoxBase_Delegate::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OnBoxBeginOverlap.IsBound())
		OnBoxBeginOverlap.Execute();

	if (OnRetValOverlap.IsBound())
	{
		FLinearColor RandomColor = FLinearColor::MakeRandomColor();
		RandomColor.A = 1.f;

		FString Str = OnRetValOverlap.Execute(RandomColor);

		CLog::Print(Str, -1, 2.f, RandomColor.ToFColor(true));
	}
	
}

void ACBoxBase_Delegate::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnBoxEndOverlap.IsBound())
		OnBoxEndOverlap.Execute();
}
