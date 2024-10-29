#include "CGameInfoWidget.h"
#include "BasicSyntaxCPP.h"
#include "Components/TextBlock.h"

void UCGameInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CLog::Print(AutoFireText->GetName());
}

void UCGameInfoWidget::EnableAutoFire_Implementation()
{
	AutoFireText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
}

void UCGameInfoWidget::DisableAutoFire_Implementation()
{
	AutoFireText->SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.f)));
}
