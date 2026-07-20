#pragma once
#include "MapChipField.h"
#include "Player.h"
#include <vector>

using namespace KamataEngine;

class GameScene {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// フェーズの切り替え
	void ChangePhase();

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelBlock_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_ = nullptr;

	// 表示ブロックの生成
	void GenerateBlocks();

private:
	// ゲームのフェーズ
	enum class Phase {
		kPlayer,
		kEnemy,
	};

	// ゲームの現在フェーズ
	Phase phase_;

	// プレイヤー
	Player* player_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// ブロック用のワールドトランスフォーム
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	// カメラ
	KamataEngine::Camera camera_;
};