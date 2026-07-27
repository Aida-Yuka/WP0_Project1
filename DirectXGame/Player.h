#pragma once

#define NOMINMAX
#include "KamataEngine.h"
#include "MapChipField.h"

struct PlayerPos {
	int x;
	int y;
};

class Player {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="position">位置</param>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// メンバ変数のポインタ
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// カメラ
	KamataEngine::Camera* camera_ = nullptr;
	// テクスチャモデル
	uint32_t textureHandle_ = 0u;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;
};