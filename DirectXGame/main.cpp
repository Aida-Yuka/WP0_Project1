#include <Windows.h>
#include "KamataEngine.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_01_アイダ_ユウカ_AL3");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// InguiManagerインスタンスの取得
	// ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	// メインループ
	while (true)
	{
		// エンジンの更新
		if (KamataEngine::Update())
		{
			break;
		}

		// 描画開始
		dxCommon->PreDraw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
