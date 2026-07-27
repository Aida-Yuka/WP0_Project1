#include "Player.h"
#include "MapChipField.h"
#include "cassert"
#include <algorithm>
#include <Numbers>

using namespace KamataEngine;
//using namespace MathUtility;

Player::~Player() {}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position)
{
	// NULLポインタチェック
	assert(model);
	assert(camera);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() {
	model_->Draw(worldTransform_, *camera_);
}