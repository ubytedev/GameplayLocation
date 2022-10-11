// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "GameplayLocationEditorSubsystem.generated.h"

/** Editor subsystem responsible for (un)registering the Gameplay Location settings area in Project Settings */
UCLASS()
class UGameplayLocationEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
