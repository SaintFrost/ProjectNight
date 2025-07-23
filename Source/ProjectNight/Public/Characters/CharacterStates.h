
#pragma once

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_MoveForward UMETA(DisplayName = "MoveForward"),
	EMS_CircleRight UMETA(DisplayName = "CircleRight"), // Circling movement will be added in upcoming versions
	EMS_CircleLeft UMETA(DisplayName = "CircleLeft")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking")
};