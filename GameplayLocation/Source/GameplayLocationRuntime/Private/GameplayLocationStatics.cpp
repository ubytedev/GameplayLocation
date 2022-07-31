// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#include "GameplayLocationStatics.h"
#include "GameplayLocationSettings.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameplayLocationManager, Log, All)

bool UGameplayLocationStatics::ResolvesGameplayLocation(const TSoftClassPtr<UObject> Class, const FGameplayTagContainer GameplayTags)
{
	const UGameplayLocationSettings* Settings = GetDefault<UGameplayLocationSettings>();
	check(Settings)

	if (!GameplayTags.IsEmpty())
	{
		for (const UClass* ClassItr = Class->ClassWithin; ClassItr; ClassItr = ClassItr->GetSuperClass())
		{
			if (const FGameplayLocationConfig* Config = Settings->ConfigMap.Find(ClassItr))
			{
				TArray<FGameplayTag> TagArray;
				for (const FGameplayTag& GroupTag : Config->ImplementedGroups)
				{
					if (!GameplayTags.HasTag(GroupTag) || GameplayTags.HasTagExact(GroupTag))
					{
						return false;
					}
				}

				return true;
			}
		}
	}
	
	return false;
}

bool UGameplayLocationStatics::ResolvesGameplayLocationDescendants(const TSoftClassPtr<> Class,
	const FGameplayTagContainer GameplayTags)
{
	const UGameplayLocationSettings* Settings = GetDefault<UGameplayLocationSettings>();
	check(Settings)

	if (const FGameplayLocationConfig* Config = Settings->ConfigMap.Find(Class))
	{
		return GameplayTags.HasAllExact(Config->ImplementedGroups);
	}

	return false;
}

FGameplayLocation UGameplayLocationStatics::K2_MakeOutgoingGameplayLocation(
	const TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTag GameplayTag)
{
	return FGameplayLocation(GameplayLocationQuerier, GameplayTag);
}

FGameplayLocationContainer UGameplayLocationStatics::K2_MakeOutgoingGameplayLocationContainer(
	const TScriptInterface<IGameplayLocationQuerier> GameplayLocationQuerier, FGameplayTagContainer GameplayTags)
{
	return FGameplayLocationContainer(GameplayLocationQuerier, GameplayTags);
}

FVector UGameplayLocationStatics::ResolveGameplayLocation(const FGameplayLocation& GameplayLocation)
{
	if (GameplayLocation.IsValid())
	{
		return GameplayLocation.Get();
	}
	
	UE_VLOG_UELOG(GetDefault<UGameplayLocationStatics>(), LogGameplayLocationManager, Error, TEXT("%s failed. Provided GameplayLocation is invalid."), __FUNCTIONW__);
	return FVector();
}

TArray<FVector> UGameplayLocationStatics::ResolveGameplayLocationContainer(
	const FGameplayLocationContainer& GameplayLocationContainer)
{
	if (GameplayLocationContainer.IsValid())
	{
		return GameplayLocationContainer.Get();
	}

	UE_VLOG_UELOG(GetDefault<UGameplayLocationStatics>(), LogGameplayLocationManager, Error, TEXT("%s failed. Provided GameplayLocationContainer is invalid."), __FUNCTIONW__);
	return TArray<FVector>();
}

bool UGameplayLocationStatics::IsValid_GameplayLocation(const FGameplayLocation& GameplayLocation)
{
	return GameplayLocation.IsValid();
}

