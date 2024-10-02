#include "CLog.h"

void CLog::Print(int32 Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key,Duration,Color,FString::FromInt(Value));
}

void CLog::Print(float Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::SanitizeFloat(Value));
}

void CLog::Print(const FString& Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Value);
}

void CLog::Print(const FVector& Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Value.ToString());
}

void CLog::Print(const FRotator& Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Value.ToString());
}
