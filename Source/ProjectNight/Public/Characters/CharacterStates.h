
#pragma once

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_MoveForward UMETA(DisplayName = "MoveForward"),
	EMS_CircleRight UMETA(DisplayName = "CircleRight"), // Circling movement will be added in upcoming versions
	EMS_CircleLeft UMETA(DisplayName = "CircleLeft")
};