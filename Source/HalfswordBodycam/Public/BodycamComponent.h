#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "BodycamComponent.generated.h"

/**
 * Chest-mounted bodycam component for Halfsword
 * Attaches a camera to the character's chest and renders to a texture
 */
UCLASS(ClassGroup = (Bodycam), meta = (BlueprintSpawnableComponent))
class HALFSWORDCAMERA_API UBodycamComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBodycamComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Enable/Disable bodycam
	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	void EnableBodycam();

	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	void DisableBodycam();

	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	bool IsBodycamEnabled() const { return bIsEnabled; }

	// Get the bodycam camera component
	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	class USceneComponent* GetBodycamMountPoint() const { return BodycamMountPoint; }

	// Adjust bodycam position on chest
	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	void SetBodycamPosition(FVector RelativeLocation);

	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	void SetBodycamRotation(FRotator RelativeRotation);

	// Get render target for UI display
	UFUNCTION(BlueprintCallable, Category = "Bodycam")
	class UTextureRenderTarget2D* GetRenderTarget() const { return RenderTarget; }

protected:
	// The mount point on the chest (attach to character mesh)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bodycam")
	class USceneComponent* BodycamMountPoint;

	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bodycam")
	class USceneComponent* BodycamCamera;

	// Render target for bodycam feed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bodycam")
	class UTextureRenderTarget2D* RenderTarget;

	// Capture component for rendering to texture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bodycam")
	class USceneCaptureComponent2D* CaptureComponent;

	// Whether bodycam is active
	UPROPERTY(BlueprintReadOnly, Category = "Bodycam")
	bool bIsEnabled;

	// Bodycam resolution
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bodycam")
	FIntPoint CameraResolution;

	// Socket name on character mesh to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bodycam")
	FName AttachSocketName;

	// Default relative position offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bodycam")
	FVector LocationOffset;

	// Default relative rotation offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bodycam")
	FRotator RotationOffset;

	// Field of view for bodycam
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bodycam", meta = (ClampMin = "1.0", ClampMax = "179.0"))
	float FieldOfView;

private:
	void InitializeBodycam();
	void CreateRenderTarget();
	void SetupCaptureComponent();
};
