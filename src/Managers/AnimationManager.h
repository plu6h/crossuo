﻿// MIT License
// Copyright (C) August 2016 Hotride

#pragma once

#include <stdint.h>
#include <unordered_map>
#include <deque>
#include <vector>
#include <xuocore/mulstruct.h> // AnimationSelector
#include "../Globals.h"        // ANIMATION_GROUPS

class CTargetGump;
class CGameCharacter;
struct CTextureAnimationDirection;

static const int MAX_LAYER_DIRECTIONS = 8;
static const float UPPER_BODY_RATIO = 0.35f;
static const float MID_BODY_RATIO = 0.60f;
static const float LOWER_BODY_RATIO = 0.94f;

struct CEquipConvData
{
    uint16_t Graphic = 0;
    uint16_t Gump = 0;
    uint16_t Color = 0;
};

typedef std::unordered_map<uint16_t, CEquipConvData> EQUIP_CONV_DATA_MAP;
typedef std::unordered_map<uint16_t, EQUIP_CONV_DATA_MAP> EQUIP_CONV_BODY_MAP;

class CAnimationManager
{
public:
    uint16_t Color = 0;
    AnimationSelector SelectAnim;

    //protected:
    size_t m_AddressIdx[6];
    size_t m_SizeIdx[6];
    EQUIP_CONV_BODY_MAP m_EquipConv;
    std::vector<std::pair<uint16_t, uint8_t>> m_GroupReplaces[2];

private:
    int m_CharacterFrameHeight = 0;

    static void PrepareTargetAttackGump(
        CTargetGump &gump,
        int drawX,
        int drawY,
        uint16_t targetColor,
        int per,
        CGameCharacter &obj);

    int m_CharacterFrameStartY = 0;
    int m_StartCharacterWaistY = 0;
    int m_StartCharacterKneesY = 0;
    int m_StartCharacterFeetY = 0;
    int m_Sitting = 0;
    bool m_UseBlending = false;

    CEquipConvData *m_EquipConvItem{ nullptr };

    static const int USED_LAYER_COUNT = 23;
    static const int m_UsedLayers[MAX_LAYER_DIRECTIONS][USED_LAYER_COUNT];
    std::deque<CTextureAnimationDirection *> m_UsedAnimList;

    bool TestPixels(
        class CGameObject *obj,
        int x,
        int y,
        bool mirror,
        uint8_t &frameIndex,
        uint16_t id = 0x0000);

    void FixSittingDirection(uint8_t &layerDirection, bool &mirror, int &x, int &y);
    void Draw(class CGameObject *obj, int x, int y, bool mirror, uint8_t &frameIndex, int id = 0);
    void DrawIntoFrameBuffer(class CGameCharacter *obj, int x, int y);

    bool DrawEquippedLayers(
        bool selection,
        class CGameObject *obj,
        int drawX,
        int drawY,
        bool mirror,
        uint8_t layerDir,
        uint8_t animIndex,
        int lightOffset);

    bool IsCovered(int layer, class CGameObject *owner);
    bool m_Transform = false;

    uint16_t m_CharacterLayerGraphic[25];
    uint16_t m_CharacterLayerAnimID[25];

    uint8_t GetObjectNewAnimationType_0(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_1_2(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_3(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_4(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_5(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_6_14(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_7(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_8(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_9_10(CGameCharacter *obj, uint16_t action, uint8_t mode);
    uint8_t GetObjectNewAnimationType_11(CGameCharacter *obj, uint16_t action, uint8_t mode);

    bool IsReplacedObjectAnimation(uint8_t anim, uint16_t v13) const;

public:
    CAnimationManager();
    ~CAnimationManager();
    void ClearUnusedTextures(uint32_t ticks);
    void Init();

    EQUIP_CONV_BODY_MAP &GetEquipConv() { return m_EquipConv; }
    void InitIndexReplaces(uint32_t *verdata);
    void UpdateAnimationAddressTable();
    void Load(uint32_t *verdata);
    void GetAnimDirection(uint8_t &dir, bool &mirror);
    void GetSittingAnimDirection(uint8_t &dir, bool &mirror, int &x, int &y);
    void DrawCharacter(class CGameCharacter *obj, int x, int y);
    bool CharacterPixelsInXY(class CGameCharacter *obj, int x, int y);
    void DrawCorpse(class CGameItem *obj, int x, int y);
    bool CorpsePixelsInXY(class CGameItem *obj, int x, int y);
    uint8_t GetDieGroupIndex(uint16_t id, bool second);
    ANIMATION_GROUPS GetGroupIndex(uint16_t id) const;
    bool AnimationExists(uint16_t graphic, uint8_t group);
    uint8_t CorrectAnimationGroupServer(
        ANIMATION_GROUPS_TYPE type, ANIMATION_FLAGS flags, uint16_t v13) const;

    AnimationFrameInfo GetAnimationDimensions(
        uint8_t frameIndex, uint16_t id, uint8_t dir, uint8_t animGroup, bool isCorpse);

    AnimationFrameInfo GetAnimationDimensions(
        class CGameObject *obj,
        uint8_t frameIndex = 0xFF,
        uint8_t defaultDirection = 0,
        uint8_t defaultGroup = 0);

    struct DRAW_FRAME_INFORMATION
    CollectFrameInformation(class CGameObject *gameObject, bool checkLayers = true);

    uint8_t GetReplacedObjectAnimation(CGameCharacter *obj, uint16_t index);

    uint8_t
    GetObjectNewAnimation(CGameCharacter *obj, uint16_t type, uint16_t action, uint8_t mode);

    CTextureAnimationDirection &
    ExecuteAnimation(uint8_t group, uint8_t direction, uint16_t graphic);
};

extern CAnimationManager g_AnimationManager;
