#include "CameraController.h"
#include "KamataEngine.h"
#include "Player.h"
#include <cmath>

using namespace KamataEngine;
//using namespace MathUtility;

void CameraController::Intialize(/*Camera* camera*/)
{
	/// インゲームの初期化処理///

	// 引数として受け取ったデータをメンバ変数に記録する
	// camera_ = camera;

	// カメラの初期化
	camera_.Initialize();
}

void CameraController::Update()
{
	// 行列を更新する
	camera_.UpdateMatrix();
}