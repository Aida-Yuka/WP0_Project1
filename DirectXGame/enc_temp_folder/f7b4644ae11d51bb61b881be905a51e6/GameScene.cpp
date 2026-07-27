#include "GameScene.h"
#include "MapChipField.h"
#include "Player.h"
#include "MyMath.h"

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
			////模様の処理
			//if ((i + j) % 2 == 0)
			//{
			//    continue;
			//}

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	int count = 0;

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (worldTransformBlocks_[i][j] != nullptr) {
				count++;
			}
		}
	}

	printf("Block Count = %d\n", count);
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
	phase_ = Phase::kPlayerTurn;

	// 3Dモデルの生成
	model_ = Model::CreateFromOBJ("player", true);
	modelBlock_ = Model::CreateFromOBJ("block");
	modelPlayerTurn_ = Model::CreateFromOBJ("playerTurn", true);
	modelEnemyTurn_ = Model::CreateFromOBJ("enemyTurn", true);

	// マップチップフィールドの設定
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	GenerateBlocks();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(5, 18);

	// カメラの初期化
	camera_.Initialize();

	// プレイヤーの生成
	player_ = new Player();

	// プレイヤーの初期化
	player_->Initialize(model_, &camera_, playerPosition);

	// マップチップデータのセット
	player_->SetMapChipField(mapChipField_);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 表示メニュー
	worldTransform_.translation_;

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}
}

// 更新
void GameScene::Update()
{
	// ターンを表示するか
	if (isTurnDisplay_) {
		turnDisplayTime_ -= 1.0f;
		if (turnDisplayTime_ <= 0.0f) {
			isTurnDisplay_ = false;
			turnDisplayTime_ = 60.0f;
		}
	}

	switch (phase_) {
	// プレイヤーフェーズ
	case Phase::kPlayerTurn:
		break;
	// エネミーフェイズ
	case Phase::kEnemyTurn:

		break;
	}

	/// ＝＝＝共通の処理＝＝＝

	// フェーズの切り替え
	ChangePhase();

	// 自キャラの更新
	player_->Update();

	// ビュープロジェクション行列の転送
	camera_.TransferMatrix();
}

// フェーズの切り替え
void GameScene::ChangePhase()
{
	switch (phase_)
	{
	//プレイヤーフェーズ
	case Phase::kPlayerTurn:

		// プレイヤーの操作が終わったらエネミーフェイズに切り替え
		// if(プレイヤーの移動が終わったら)
		//{
		// 演出何か入れる
		// ↓今だけ
		if (Input::GetInstance()->PushKey(DIK_2))
		{
			//ターンモデルを表示する
			isTurnDisplay_ = true;
			//プレイヤーターンからエネミーターンに切り替え
			phase_ = Phase::kEnemyTurn;
		}

		break;
	//エネミーフェイズ
	case Phase::kEnemyTurn:

		// エネミーの操作が終わったらプレイヤーフェイズに切り替え
		// if(エネミーの移動が終わったら)
		//{
		// 演出何か入れる
		// ↓今だけ
		if (Input::GetInstance()->PushKey(DIK_2))
		{
			//エネミーターンからプレイヤーターンに切り替え
			phase_ = Phase::kPlayerTurn;
		}

		break;
	}
}

// 描画
void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	/*DirectXCommon* dxCommon = DirectXCommon::GetInstance();*/

	// 3Dモデル描画前処理
	Model::PreDraw(/*dxCommon->GetCommandList()*/);

	//プレイヤーの描画
	player_->Draw();

	// ブロックの描画
	 for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		 for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			 if (!worldTransformBlock)
				 continue;

			 modelBlock_->Draw(*worldTransformBlock, camera_);
		 }
	 }

	 //ターンモデルの描画
	 if (isTurnDisplay_)
	 {
		 switch (phase_) {
		 case Phase::kPlayerTurn:
			 modelPlayerTurn_->Draw(worldTransform_, camera_);
			 break;

		 case Phase::kEnemyTurn:
			 modelEnemyTurn_->Draw(worldTransform_, camera_);
			 break;
		 }
	 }

	// 3Dモデル描画後処理
	Model::PostDraw();
}