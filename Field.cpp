#include "Field.h"
#include <DxLib.h>
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Bird.h"
#include "TANK.h"
#include "Engine/CsvReader.h"
#include"Enemy.h"
std::vector<Platform> Field::platforms;

Field::Field(GameObject* scene)
    : GameObject(scene), hImage(-1), hPlatformImage(-1), Map(nullptr), width(0), height(0)
{
    hImage = LoadGraph("Assets/bgchar.png");
    assert(hImage > 0);

    hPlatformImage = LoadGraph("Assets/TANK.png");
    assert(hPlatformImage > 0);
}

Field::~Field()
{
    if (hImage > 0)
    {
        DeleteGraph(hImage);
    }
    if (hPlatformImage > 0)
    {
        DeleteGraph(hPlatformImage);
    }
    if (Map != nullptr)
    {
        delete[] Map;
    }
}

void Field::Reset()
{
    if (Map != nullptr)
    {
        delete[] Map;
        Map = nullptr;
    }
    CsvReader csv;
    bool ret = csv.Load("Assets/stage1.csv");
    assert(ret);
    width = csv.GetWidth(0);
    height = csv.GetHeight();
    Map = new int[width * height];

    for (int h = 0; h < height; h++)
    {
        if (csv.GetString(0, h) == "")
        {
            height = h;
            break;
        }
        for (int w = 0; w < width; w++)
        {
            Map[h * width + w] = csv.GetInt(w, h);
        }
    }

    platforms.clear();

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            switch (csv.GetInt(w, h + height + 1))
            {
            case 0:
            {
                Player* pplayer = GetParent()->FindGameObject<Player>();
                pplayer->SetPosition(w * 32, h * 32);
            }
            break;
            case 1:
            {
                Enemy* penemy = Instantiate<Enemy>(GetParent());
                penemy->SetPosition(w * 32, h * 32);
            }
            break;
            case 2:
            {
                Bird* pbird = Instantiate<Bird>(GetParent());
                pbird->SetPosition(w * 32, h * 32);
            }
            break;
            case 3:
            {
                XMFLOAT3 position(w * 32.0f, h * 32.0f, 0.0f);
                platforms.push_back(Platform(position, true, 180)); // 初期寿命を180フレームに設定
            }
            break;
            }
        }
    }
}

void Field::Update()
{
    if (CheckHitKey(KEY_INPUT_R))
        Reset();

    if (CheckHitKey(KEY_INPUT_T))
        TogglePlatforms();

    for (auto it = platforms.begin(); it != platforms.end(); )
    {
        it->DecreaseLifetime();
        if (it->IsExpired())
        {
            it = platforms.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Field::Draw()
{
    int scroll = 0;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr)
    {
        scroll = cam->GetValue();
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int chip = Map[y * width + x];
            DrawRectGraph(x * 32 - scroll, y * 32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hImage, TRUE);
        }
    }

    for (auto& platform : platforms)
    {
        if (platform.IsActive())
        {
            int px = (int)platform.position.x - scroll;
            int py = (int)platform.position.y;
            DrawGraph(px, py, hPlatformImage, TRUE);
        }
    }
}

int Field::CollisionRight(int x, int y)
{
    if (IsWallBlock(x, y) || IsPlatformBlock(x, y))
    {
        return x % 32 + 1;
    }
    else
        return 0;
}

int Field::CollisionLight(int x, int y)
{
    if (IsWallBlock(x, y) || IsPlatformBlock(x, y))
    {
        return x % 32 + 1;
    }
    else
        return 0;
}

int Field::CollisionDown(int x, int y)
{
    if (IsWallBlock(x, y) || IsPlatformBlock(x, y))
    {
        return y % 32 + 1;
    }
    else
        return 0;
}

bool Field::IsWallBlock(int x, int y)
{
    int chipX = x / 32;
    int chipY = y / 32;
    switch (Map[chipY * width + chipX])
    {
    case 16:
    case 17:
    case 18:
    case 19:
    case 32:
    case 33:
    case 34:
    case 35:
        return true;
    }
    return false;
}

bool Field::IsPlatformBlock(int x, int y)
{
    for (const auto& platform : platforms)
    {
        if (platform.IsColliding(x, y))
        {
            return true;
        }
    }
    return false;
}

void Field::AddPlatform(XMFLOAT3 position)
{
    platforms.push_back(Platform(position, true, 180)); // 足場の寿命を180フレームに設定
}

void Field::TogglePlatforms()
{
    for (auto& platform : platforms)
    {
        platform.ToggleActive();
    }
}
