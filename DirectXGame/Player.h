#pragma once

#define NOMINMAX
#include "KamataEngine.h"
#include "MyMath.h"

//
enum class LRDirection {
	kRight,
	kLeft,
};

// 角
enum Corner {
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // 要素数
};

class MapChipField;
class Enemy;

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="position">初期位置</param>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position,const KamataEngine::Vector2& mapPosition);

	void Update();

	void Draw();

	// カメラの毎フレーム追従
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// 速度加算
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	// メンバ変数のポインタ
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	// ①移動入力
	void InputMove();

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	// 死亡フラグのgetter
	bool IsDead() const { return isDead_; }

	// 振る舞い
	enum class Behavior {
		kRoot,    // 通常攻撃
		kAttack,  // 攻撃中
		kUnknown, // 変更リクエストがない
	};

	// 振る舞い
	Behavior behavior_ = Behavior::kRoot;

	// 次の振る舞いリクエスト
	Behavior behaviorRequest_ = Behavior::kUnknown;

	//// 攻撃フェーズ(型)
	//enum class AttackPhase {
	//	kReservoir, // 溜め
	//	kRush,      // 突進
	//	kAfterglow, // 余韻
	//};

	//// 現在の攻撃フェーズ(変数)
	//AttackPhase attackPhase_ = AttackPhase::kReservoir;

	// SRPGマップでの座標
	KamataEngine::Vector2 mapPosition_ = {0.0f, 0.0f};

	//SRPGマップの本来の座標
	const float kBlockSize = 5.0f;

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 自キャラ
	// Player* player_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// 速度
	KamataEngine::Vector3 velocity_ = {};

	// 向いている向き
	LRDirection lrDirection_ = LRDirection::kRight;

	// 設置状態フラグ
	bool onGround_ = true;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// 空白
	static inline const float kBlank = 1;

	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.8f;

	// 微小な数値
	static inline const float kGroundSearchHeight = 0.5f;

	// 死亡フラグ
	bool isDead_ = false;
};