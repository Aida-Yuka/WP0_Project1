#pragma once
#include "MapChipField.h"
#include "Player.h"
#include "Fade.h"
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
	KamataEngine::Model* modelPlayerTurn_ = nullptr;
	KamataEngine::Model* modelEnemyTurn_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_ = nullptr;

	// 表示ブロックの生成
	void GenerateBlocks();

	// 終了フラグのgetter
	bool IsFinished() const { return finished_; }

	// 終了フラグ
	bool finished_ = false;

	//ターンモデルの表示
	void isTurnDisplay();

	// ターンモデルの表示時間
	float turnDisplayTime_ = 60.0f;
	
	// ターンモデルが表示されているか
	bool isTurnDisplay_ = true;

private:
	// ゲームのフェーズ
	enum class Phase {
		//kFadeIn,    // フェードイン
		//kPlay,      // ゲームプレイ
		//kDeath,     // デス演出
		//kPauseMenu, // ポーズメニュー
		//kFadeOut,   // フェードアウト
		kPlayerTurn,//プレイヤーターン
		kEnemyTurn, //エネミーターン
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

	// フェード
	Fade* fade_ = nullptr;
};