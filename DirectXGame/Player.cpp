#include "Player.h"
#include "MapChipField.h"
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

struct WorldTransform_ {
	Vector3 translation_; // 位置
	Vector3 rotation_;    // 回転
	Vector3 scale_;       // スケール
};

float EaseOut(float start, float end, float t) {
	// tを0～1にクランプ
	t = std::clamp(t, 0.0f, 1.0f);

	// Cubicのeaseout
	float ease = 1.0f - powf(1.0f - t, 3.0f);

	// start→endに補間
	return start + (end - start) * ease;
}

float EaseIn(float start, float end, float t) {
	// tを0～1にクランプ
	t = std::clamp(t, 0.0f, 1.0f);

	// Cubicのease-in
	float ease = t * t * t;

	// start→endに補間
	return start + (end - start) * ease;
}

// ①
void Player::InputMove()
{
	//移動操作
	if (Input::GetInstance()->TriggerKey(DIK_RIGHT)) {
		if (mapPosition_.x < 10.0f) {
			mapPosition_.x += 1.0f;
		}

	} else if (Input::GetInstance()->TriggerKey(DIK_LEFT)) {
		if (mapPosition_.x > 0.0f) {
			mapPosition_.x -= 1.0f;
		}

	} else if (Input::GetInstance()->TriggerKey(DIK_UP)) {
		if (mapPosition_.y > 0.0f) {
			mapPosition_.y -= 1.0f;
		}

	} else if (Input::GetInstance()->TriggerKey(DIK_DOWN)) {
		if (mapPosition_.y < 10.0f) {
			mapPosition_.y += 1.0f;
		}
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position, const Vector2& mapPosition) {
	/// インゲームの初期化処理///

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	//マス座標
	this->mapPosition_ = mapPosition;

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	this->isDead_ = false;
}

void Player::Update() {
	/// インゲームの更新処理 ///

	InputMove();

	// マス座標 → ワールド座標
	worldTransform_.translation_.x = mapPosition_.x * kBlockSize;
	worldTransform_.translation_.y = mapPosition_.y * kBlockSize;

	// 行列更新
	worldTransform_.TransferMatrix();
}

void Player::Draw() {
	/// 描画処理///

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_);
}