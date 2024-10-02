#pragma once

#include "CoreMinimal.h"

class BASICSYNTAXCPP_API CLog
{
public:
	static void Print(int32 Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(float Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(const FString& Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(const FVector& Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(const FRotator& Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
};
