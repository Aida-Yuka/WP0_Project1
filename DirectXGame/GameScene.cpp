#include "GameScene.h"
#include "MapChipField.h"
#include "Player.h"

void GameScene::GenerateBlocks() {
	// ＝＝＝ブロック配置の初期化＝＝＝//
	// 要素数
	uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVirtical();     // 縦
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal(); // 横

	/// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(kNumBlockVirtical);

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		// 1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			/*/模様の処理
			if ((i + j) % 2 == 0)
			{
			    continue;
			}*/

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

// デストラクタ
GameScene::~GameScene() {
	delete player_;
	delete modelBlock_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

// 初期化
void GameScene::Initialize() {
	// プレイヤーフェーズからの開始
	phase_ = Phase::kPlayer;

	// 3Dモデルの生成
	model_ = Model::CreateFromOBJ("player", true);
	modelBlock_ = Model::CreateFromOBJ("block");

	// マップチップフィールドの設定
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	GenerateBlocks();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(5, 18);

	// プレイヤーの生成
	player_ = new Player();

	// プレイヤーの初期化
	player_->Initialize(model_, &camera_, playerPosition);

	// マップチップデータのセット
	player_->SetMapChipField(mapChipField_);

	assert(model_);
	assert(modelBlock_);
}

// 更新
void GameScene::Update() {
	switch (phase_) {
	// プレイヤーフェーズ
	case Phase::kPlayer:

		// プレイヤーの更新
		player_->Update();

		break;
	// エネミーフェイズ
	case Phase::kEnemy:

		break;
	}
}

// フェーズの切り替え
void GameScene::ChangePhase() {
	switch (phase_) {
		// プレイヤーフェーズ
	case Phase::kPlayer:

		// プレイヤーの操作が終わったらエネミーフェイズに切り替え
		// if(プレイヤーの移動が終わったら)
		//{
		// 演出何か入れる
		//
		// phase_=Phase::kEnemy;
		//}

		break;
		// エネミーフェイズ
	case Phase::kEnemy:

		// エネミーの操作が終わったらプレイヤーフェイズに切り替え
		// if(エネミーの移動が終わったら)
		//{
		// 演出何か入れる
		//
		// phase_=Phase::kPlayer;
		//}

		break;
	}
}

// 描画
void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	/*DirectXCommon* dxCommon = DirectXCommon::GetInstance();*/

	// 3Dモデル描画前処理
	Model::PreDraw(/*dxCommon->GetCommandList()*/);

	////プレイヤーの描画
	// player_->Draw();

	//// ブロックの描画
	// for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
	//	for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
	//		if (!worldTransformBlock)
	//			continue;

	//		modelBlock_->Draw(*worldTransformBlock, camera_);
	//	}
	//}

	// 3Dモデル描画後処理
	Model::PostDraw();
}