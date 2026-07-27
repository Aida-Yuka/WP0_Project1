#pragma once
#include "KamataEngine.h"

// 前方宣言
class Player;

/// <summary>
/// カメラコントローラー
/// </summary>
class CameraController {
public:
	void Intialize(/*Camera* camera*/);

	void Update();

	const KamataEngine::Camera& GetViewProjection() const { return camera_; }

private:
	KamataEngine::Camera camera_;
};