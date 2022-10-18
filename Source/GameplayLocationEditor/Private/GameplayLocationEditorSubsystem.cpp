// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#include "GameplayLocationEditorSubsystem.h"
#include "GameplayLocationSettings.h"
#include "ISettingsModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, GameplayLocationEditor);

#define LOCTEXT_NAMESPACE "UGameplayLocationEditorSubsystem"

void UGameplayLocationEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Gameplay Location",
			LOCTEXT("GameplayLocationSettingsName", "Gameplay Location"),
			LOCTEXT("GameplayLocationSettingsNameDesc", "Gameplay Location Settings"),
			GetMutableDefault<UGameplayLocationSettings>()
			);
	}
}

void UGameplayLocationEditorSubsystem::Deinitialize()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Gameplay Location");
	}
}

#undef LOCTEXT_NAMESPACE
