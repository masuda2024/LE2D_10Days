#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Line.h"
#include "Vector2.h"
#include <cstring>
#include <ctime> // time()

const char kWindowTitle[] = "2061_線押し陣取り";

const int WL = 0;
const int WR = 1280;
const int WT = 0;
const int WB = 720;

enum Scene {
    TITLE,
    CREDIT,
    TUTORIAL1,
    TUTORIAL2,
    GAME,
    CLEAR,
    OVER
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Novice::Initialize(kWindowTitle, WR, WB);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };


#pragma region 初期化
    int scene = TITLE;




    //＝＝＝ランダム生成＝＝＝
    /*
    unsigned int currentTime = static_cast<int>(time(nullptr));
    srand(currentTime);

    //ダブルアタック
    float PosXA = static_cast<float>(rand() % WR);
    float PosYA = static_cast<float>(rand() % -10);

    //追尾弾
    float PosXB = static_cast<float>(rand() % WR);
    float PosYB = static_cast<float>(rand() % -10);
    */

    


    



    Player player;
    Enemy enemy;
    Line line;

   



    const int kMaxPlayerBullets = 8;
    PlayerBullet playerBullets[kMaxPlayerBullets];

    const int kMaxEnemyBullets = 8;
    EnemyBullet enemyBullets[kMaxEnemyBullets];

    int playerBulletCooldown = 0;
    int enemyBulletCooldown = 0;

    int isGameOver = false;
    int isGameClear = false;
#pragma endregion

#pragma region テクスチャ
    //タイトル
    int TitleBack = Novice::LoadTexture("Resource/Title/TitleBack.png");
    int Title1 = Novice::LoadTexture("Resource/Title/TitleFont1.png");
    int Title2 = Novice::LoadTexture("Resource/Title/TitleFont2.png");
    int Title3 = Novice::LoadTexture("Resource/Title/WarningColor.png");
    int TitleUI = Novice::LoadTexture("Resource/Title/TitleUI.png");
    //クレジット
    int Credit = Novice::LoadTexture("Resource/Credit/Credit.png");
    //チュートリアル
    int Tutorial1= Novice::LoadTexture("Resource/Tutorial/Tutorial1.png");
    int Tutorial2 = Novice::LoadTexture("Resource/Tutorial/Tutorial2.png");
    int PlayerTex = Novice::LoadTexture("Resource/Player/Tank.png");
    //クリア、オーバー画面
    int Clear= Novice::LoadTexture("Resource/Scene/Clear.png");
    int Over = Novice::LoadTexture("Resource/Scene/Over.png");
    //ゲーム画面の地面
    int Ground= Novice::LoadTexture("Resource/Scene/Ground.png");
    //アイテム
    int _doubleAttack= Novice::LoadTexture("Resource/Items/doubleAttack.png");
    int _follow = Novice::LoadTexture("Resource/Items/follow.png");




#pragma endregion
    // Springin
    // https://www.springin.org/

#pragma region BGM_SE
    
    //=====SE=====//
     
     
    //Springin/戦闘-3/発砲1
    int firing1 = Novice::LoadAudio("Resource/Source/SE/Firing1.mp3");

    //Springin/ボタン・システム-1/決定2
    int decision2 = Novice::LoadAudio("Resource/Source/SE/Decision2.mp3");
    
    //Springin/ボタン・システム-1/決定5
    int decision5 = Novice::LoadAudio("Resource/Source/SE/Decision5.mp3");

    //Springin/ボタン・システム-1/決定11
    int decision11 = Novice::LoadAudio("Resource/Source/SE/Decision11.mp3");

    //Springin/戦闘-3/金属叩き
    int metalHammer = Novice::LoadAudio("Resource/Source/SE/MetalHammer.mp3");

    //Springin/ボタン・システム-1/出題1
    int question1 = Novice::LoadAudio("Resource/Source/SE/Question1.mp3");
    
    //Springin/ボタン・システム-2/不正解2
    int incorrectAnswer2 = Novice::LoadAudio("Resource/Source/SE/IncorrectAnswer2.mp3");

    //=====BGM=====//

    //BGM
    int playHandle = -1;
    
    
    //Springin/BGM-1/ゆったりDIY2
    int yuttariDIY2 = Novice::LoadAudio("Resource/Source/SE/YuttariDIY2.mp3");

    //Springin/BGM-1/RPGバトル1
    int RPGbattle= Novice::LoadAudio("Resource/Source/SE/RPG_Battle1.mp3");

    


#pragma endregion
    while (Novice::ProcessMessage() == 0)
    {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        switch (scene) {
        case TITLE:
#pragma region タイトル
            //	音を鳴らす
            if (Novice::IsPlayingAudio(playHandle) == 0 || playHandle == -1) {
                playHandle = Novice::PlayAudio(yuttariDIY2, 0, 0.3f);
                break;
            }
            isGameClear = false;
            isGameOver = false;
            
            
            //描画
            Novice::DrawSprite(
                0, 0, TitleBack,
                1.0f, 1.0f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                100, 100, Title1,
                1.5f, 1.5f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                800, 400, Title2,
                1.5f, 1.5f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                0, 350, Title3,
                1.0f, 1.0f, 0.0f,
                WHITE
            );

            Novice::DrawSprite(
                354, 500, TitleUI,
                2.0f, 2.0f, 0.0f,
                WHITE
            );



            //ゲーム
            if (keys[DIK_SPACE]) {
                Novice::StopAudio(playHandle);
                Novice::PlayAudio(decision11, 0, 0.3f);
                scene = GAME;
                break;
            }
            //クレジット
            if (preKeys[DIK_C]) {
                Novice::StopAudio(playHandle);
                Novice::PlayAudio(decision2, 0, 0.3f);
                scene = CREDIT;
                break;
            }
            //チュートリアル
            if (preKeys[DIK_T]) {
                Novice::StopAudio(playHandle);
                Novice::PlayAudio(decision2, 0, 0.3f);
                scene = TUTORIAL1;
                break;
            }
            break;
#pragma endregion
        case CREDIT:
#pragma region クレジット
            //	音を鳴らす
            if (Novice::IsPlayingAudio(playHandle) == 0 || playHandle == -1) {
                playHandle = Novice::PlayAudio(yuttariDIY2, 0, 0.3f);
                break;
            }
            //描画
            Novice::DrawSprite(
                0, 0, Credit,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            if (preKeys[DIK_E]) {
                Novice::StopAudio(playHandle);
                Novice::PlayAudio(decision5, 0, 0.3f);
                scene = TITLE;
                break;
            }
            break;

#pragma endregion
        case TUTORIAL1:
#pragma region チュートリアル1  
            //	音を鳴らす
            if (Novice::IsPlayingAudio(playHandle) == 0 || playHandle == -1) {
                playHandle = Novice::PlayAudio(yuttariDIY2, 0, 0.3f);
                break;
            }
            //描画
            Novice::DrawSprite(
                0, 0, Tutorial1,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            Novice::DrawSprite(
                225,410, PlayerTex,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
   
            if (preKeys[DIK_E]) {
                Novice::StopAudio(playHandle);
                Novice::PlayAudio(decision5, 0, 0.3f);
                scene = TITLE;
                break;
            }

            if (preKeys[DIK_D]) {
                Novice::PlayAudio(decision2, 0, 0.3f);
                scene = TUTORIAL2;
                break;
            }


            break;
#pragma endregion
        case TUTORIAL2:
#pragma region チュートリアル2  
            //描画
            Novice::DrawSprite(
                0, 0, Tutorial2,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            Novice::DrawSprite(
                140, 430, _doubleAttack,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            Novice::DrawSprite(
                140, 530, _follow,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            if (preKeys[DIK_E]) {
                Novice::StopAudio(playHandle);
                Novice::PlayAudio(decision5, 0, 0.3f);
                scene = TITLE;
                break;
            }
            if (preKeys[DIK_A]) {
                Novice::PlayAudio(decision2, 0, 0.3f);
                scene = TUTORIAL1;
                break;
            }
            break;
#pragma endregion
        case GAME:
#pragma region ゲーム   
           
            //	音を鳴らす
            if (Novice::IsPlayingAudio(playHandle) == 0 || playHandle == -1) {
                playHandle = Novice::PlayAudio(RPGbattle, 0, 0.5f);
                break;
            }
            
            //地面
            Novice::DrawSprite(
                0, 0,
                Ground,
                1.0f, 1.0f, 0.0f,
                WHITE
            );



       

        // プレイヤー移動
        player.Move(WL, WR, WT, WB, keys);

        // 敵移動
        enemy.Move(WL, WR, player.GetPos(), playerBullets, kMaxPlayerBullets);

        // プレイヤー弾発射
        if (playerBulletCooldown > 0) playerBulletCooldown--;
        if (keys[DIK_SPACE] && playerBulletCooldown <= 0){
            Novice::PlayAudio(firing1, 0, 0.3f);
            for (int i = 0; i < kMaxPlayerBullets; i++){
                if (!playerBullets[i].IsShot()){
                    playerBullets[i].Shoot(player.GetPos());
                    playerBulletCooldown = 10;
                    break;
                }
            }
        }

        // プレイヤー弾更新
        for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Update();

        // 敵弾発射
        if (enemyBulletCooldown > 0) {
            enemyBulletCooldown--;
        };

        if (enemyBulletCooldown <= 0){
            for (int i = 0; i < kMaxEnemyBullets; i++){
                if (!enemyBullets[i].IsShot()){
                    Novice::PlayAudio(firing1, 0, 0.3f);
                    enemyBullets[i].Shoot(enemy.GetPos());
                    enemyBulletCooldown = 30; // 敵のクールタイム
                    break;
                }
            }
        }

        //敵弾
        for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Update();

        //被弾判定
        for (int i = 0; i < kMaxPlayerBullets; i++) {
            if (playerBullets[i].IsShot()) {
                // Enemy判定
                if (enemy.CheckHit(playerBullets[i].GetPos(), playerBullets[i].GetRadius())) {
                    Novice::PlayAudio(metalHammer, 0, 0.3f);
                    playerBullets[i].SetShot(false);

                    line.LineEnemyHit();
                }
            }
        }
        for (int i = 0; i < kMaxEnemyBullets; i++) {
            if (enemyBullets[i].IsShot()) {
                // Player判定
                if (player.CheckHit(enemyBullets[i].GetPos(), enemyBullets[i].GetRadius())) {
                    Novice::PlayAudio(metalHammer, 0, 0.3f);
                    enemyBullets[i].SetShot(false);

                    line.LinePlayerHit();
                }
            }
        }

        //被弾タイマー更新 ======
        player.Update();
        enemy.Update();



        if (line.CheckHitPlayer(player)) {
            Novice::StopAudio(playHandle);
            isGameOver = true;  //負け
            Novice::PlayAudio(incorrectAnswer2, 0, 0.3f);
            scene = OVER;
        }
        if (line.CheckHitEnemy(enemy)) {
            Novice::StopAudio(playHandle);
            isGameClear = true; //勝利
            Novice::PlayAudio(question1, 0, 0.3f);
            scene = CLEAR;
        }



        //描画
        player.Draw();
        enemy.Draw();
        line.Draw();

        for (int i = 0; i < kMaxPlayerBullets; i++) playerBullets[i].Draw();
        for (int i = 0; i < kMaxEnemyBullets; i++) enemyBullets[i].Draw();

        break;

#pragma endregion 
        case CLEAR:
#pragma region クリア
           Novice::DrawSprite(
                0, 0, 
                Clear,
                1.0f, 1.0f,0.0f,
                WHITE
            );
            if (preKeys[DIK_E]) {
                Novice::PlayAudio(decision2, 0, 0.3f);
                isGameClear = false;

                //元の位置に戻す
                player.Initialize();
                enemy.Initialize();
                line.Initialize();
                playerBullets[kMaxPlayerBullets].Initialize();
                enemyBullets[kMaxEnemyBullets].Initialize();
                
                scene = TITLE;
                break;
            }
            break;

#pragma endregion
        case OVER:
#pragma region オーバー
            Novice::DrawSprite(
                0, 0,
                Over,
                1.0f, 1.0f, 0.0f,
                WHITE
            );
            if (preKeys[DIK_E]) {
                Novice::PlayAudio(decision2, 0, 0.3f);
                isGameOver = false;
                //元の位置に戻す
                player.Initialize();
                enemy.Initialize();
                line.Initialize();
                playerBullets[kMaxPlayerBullets].Initialize();
                enemyBullets[kMaxEnemyBullets].Initialize();

                scene = TITLE;
                break;
            }
            break;
#pragma endregion
        }

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) break;
    }

    Novice::Finalize();
    return 0;
}
