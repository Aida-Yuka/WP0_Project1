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
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw();

	// カメラの毎フレーム追従
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// 速度加算
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	// メンバ変数のポインタ
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	// マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false; // 天井
		bool landing = false; // 着陸
		bool hitWall = false; // 壁にぶつかった
		KamataEngine::Vector3 move = {};
	};

	// ①移動入力
	void InputMove();

	// ②マップ衝突判定
	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	// ③判定結果を反映して移動させる
	void CheckMapMove(const CollisionMapInfo& info);

	// ④天井に接触している場合
	void CheckMapCeiling(const CollisionMapInfo& info);

	// ⑤壁に接触している場合
	void CheckMapWall(const CollisionMapInfo& info);

	// ⑥接地状態の切り替え処理
	void CheckMapLanding(const CollisionMapInfo& info);

	// ⑦旋回制御
	void AnimateTurn();

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	// AABBを取得
	AABB GetAABB();

	// 衝突応答
	void OnCollision(const Enemy* enemy);

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

	// 通常行動更新
	void BehaviorRootUpdate();

	// 攻撃行動更新
	void BehaviorAttackUpdate();

	// 通常行動初期化
	void BehaviorRootInitialize();

	// 攻撃行動初期化
	void BehaviorAttackInitialize();

	// 攻撃フェーズ(型)
	enum class AttackPhase {
		kReservoir, // 溜め
		kRush,      // 突進
		kAfterglow, // 余韻
	};

	// 現在の攻撃フェーズ(変数)
	AttackPhase attackPhase_ = AttackPhase::kReservoir;

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

	// 加速度
	static inline const float kAcceleration = 0.1f;

	static inline const float kAttenuation = 0.1f;

	static inline const float kLimitRunSpeed = 0.3f;

	static inline const float kAttenuationWall = 0.3f;

	// 向いている向き
	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回性能<秒>
	static inline const float kTimeTurn = 0.3f;

	// 設置状態フラグ
	bool onGround_ = true;

	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.5f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 0.8f;

	// キャラクターの当たり判定
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kDepth = 0.8f;

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

	// 攻撃ギミックの経過時間カウンター
	uint32_t attackParameter_ = 0;

	// 溜め動作時間
	float reservoirTime_ = 1.0f;

	// 突進動作時間
	float rushTime_ = 5.0f;

	// 余韻動作時間
	float afterglowTime_ = 1.0f;

	// 攻撃の時間
	float attackTime_ = reservoirTime_ + rushTime_ + afterglowTime_;

	// プレイヤーが右向きか
	int isPlayerRight = true;
};