﻿#include "GameMap.h"

using namespace Define;

GameMap::GameMap(const char* filePath)
{
    LoadMap(filePath);
}

GameMap::~GameMap()
{
    delete mMap;
}

void GameMap::LoadMap(const char* filePath)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = this->GetWidth();
    r.bottom = this->GetHeight();

    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        const Tmx::Tileset *tileset = mMap->GetTileset(i);

        Sprite* sprite = new Sprite(tileset->GetImage()->GetSource().c_str(), RECT(), 0, 0, 0xff000000);

        mListTileset.insert(std::pair<int, Sprite*>(i, sprite));
    }
    LoadMap1Animation();
}

bool GameMap::isContain(RECT rect1, RECT rect2)
{
    if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
    {
        return false;
    }

    return true;
}

Tmx::Map* GameMap::GetMap()
{
    return mMap;
}

int GameMap::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
    return mMap->GetTileHeight();
}

void GameMap::LoadMap1Animation()
{
    float tpf = 0.1f;
    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::BigGear1, new Animation(PATH_ANIMATION_BIG_GEAR_1, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::BigGear2, new Animation(PATH_ANIMATION_BIG_GEAR_2, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::BigGear3, new Animation(PATH_ANIMATION_BIG_GEAR_3, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::BigGear4, new Animation(PATH_ANIMATION_BIG_GEAR_4, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::SmallGear, new Animation(PATH_ANIMATION_SMALL_GEAR, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Chain1, new Animation(PATH_ANIMATION_CHAIN_1, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Chain2, new Animation(PATH_ANIMATION_CHAIN_2, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Chain3, new Animation(PATH_ANIMATION_CHAIN_3, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Chain4, new Animation(PATH_ANIMATION_CHAIN_4, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall1, new Animation(PATH_ANIMATION_WATERFALL_1, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall2, new Animation(PATH_ANIMATION_WATERFALL_2, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall3, new Animation(PATH_ANIMATION_WATERFALL_3, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall4, new Animation(PATH_ANIMATION_WATERFALL_4, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall5, new Animation(PATH_ANIMATION_WATERFALL_5, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall6, new Animation(PATH_ANIMATION_WATERFALL_6, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall7, new Animation(PATH_ANIMATION_WATERFALL_7, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall8, new Animation(PATH_ANIMATION_WATERFALL_8, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall9, new Animation(PATH_ANIMATION_WATERFALL_9, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall10, new Animation(PATH_ANIMATION_WATERFALL_10, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall11, new Animation(PATH_ANIMATION_WATERFALL_11, 4, 1, 4, tpf, 0xff000000)));

    mListAnimation.insert(std::pair<int, Animation*>
        (TypeAniMap1::Waterfall12, new Animation(PATH_ANIMATION_WATERFALL_12, 4, 1, 4, tpf, 0xff000000)));
}

void GameMap::DrawAnimation(const Tmx::TileLayer *layer, D3DXVECTOR2 trans)
{
    RECT sourceRECT;

    int tileWidth = mMap->GetTileWidth();
    int tileHeight = mMap->GetTileHeight();

    for (size_t m = 0; m < layer->GetHeight(); m++)
    {
        for (size_t n = 0; n < layer->GetWidth(); n++)
        {
            int tilesetIndex = layer->GetTileTilesetIndex(n, m);

            if (tilesetIndex != -1)
            {
                int tileID = layer->GetTileId(n, m);

                //wchar_t buffer[256];
                //wsprintfW(buffer, L"%d, %d, %d", tileID);
                //MessageBoxW(nullptr, buffer, buffer, MB_OK);

                D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                if (mCamera != NULL)
                {
                    RECT objRECT;
                    objRECT.left = position.x - tileWidth / 2;
                    objRECT.top = position.y - tileHeight / 2;
                    objRECT.right = objRECT.left + tileWidth;
                    objRECT.bottom = objRECT.top + tileHeight;
                    
                    //neu nam ngoai camera thi khong Draw
                    if (isContain(objRECT, mCamera->GetBound()) == false)
                        continue;
                        
                }
                mListAnimation[(TypeAniMap1)(tileID + 1)]->Draw(position, RECT(), D3DXVECTOR2(), trans);
            }
        }
    }
}

void GameMap::Draw()
{
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
                                    mCamera->GetHeight() / 2 - mCamera->GetPosition().y);


    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

        if (layer->GetName() == "ani")
        {
            DrawAnimation(layer, trans);
        }

        if (!layer->IsVisible())
        {
            continue;
        }

        RECT sourceRECT;

        int tileWidth = mMap->GetTileWidth();
        int tileHeight = mMap->GetTileHeight();

        for (size_t m = 0; m < layer->GetHeight(); m++)
        {
            for (size_t n = 0; n < layer->GetWidth(); n++)
            {
                int tilesetIndex = layer->GetTileTilesetIndex(n, m);

                if (tilesetIndex != -1)
                {
                    const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);

                    int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                    int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

                    Sprite* sprite = mListTileset[layer->GetTileTilesetIndex(n, m)];

                    //tile index
                    int tileID = layer->GetTileId(n, m);

                    int y = tileID / tileSetWidth;
                    int x = tileID - y * tileSetWidth;

                    sourceRECT.top = y * tileHeight;
                    sourceRECT.bottom = sourceRECT.top + tileHeight;
                    sourceRECT.left = x * tileWidth;
                    sourceRECT.right = sourceRECT.left + tileWidth;

                    //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                    //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                    D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                    if (mCamera != NULL)
                    {
                        RECT objRECT;
                        objRECT.left = position.x - tileWidth / 2;
                        objRECT.top = position.y - tileHeight / 2;
                        objRECT.right = objRECT.left + tileWidth;
                        objRECT.bottom = objRECT.top + tileHeight;

                        //neu nam ngoai camera thi khong Draw
                        if (isContain(objRECT, mCamera->GetBound()) == false)
                            continue;
                    }

                    sprite->SetWidth(tileWidth);
                    sprite->SetHeight(tileHeight);

                    sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
                }
            }
        }
    }    
}

void GameMap::SetCamera(Camera * camera)
{
    this->mCamera = camera;
}

void GameMap::Update(float dt)
{
    map<int, Animation*>::iterator i;
    for (i = mListAnimation.begin(); i != mListAnimation.end(); i++) {
        (*i).second->Update(dt);
    }
}
