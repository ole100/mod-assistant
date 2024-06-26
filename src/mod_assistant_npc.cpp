#include "mod_assistant.h"

bool Assistant::OnGossipHello(Player* player, Creature* creature)
{
    ClearGossipMenuFor(player);

    if (HeirloomsEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "传家宝", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM);

    if (GlyphsEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "雕文", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GLYPH);

    if (GemsEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "宝石", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM);

    if (ContainersEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "背包", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_CONTAINER);

    if (UtilitiesEnabled)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "角色修改", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES);

    if (CanUnlockFlightPaths(player))
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "解锁飞行点", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS);

    if (HasValidProfession(player))
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "专业直升", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_PROFESSIONS);

    SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    return true;
}

bool Assistant::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;

    if (action == 1)
    {
        OnGossipHello(player, creature);
    }
    else if (action == ASSISTANT_GOSSIP_HEIRLOOM)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "武器", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "装备", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "寒冷飞行", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_HEIRLOOM + 3);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_HEIRLOOM + 1 && action <= ASSISTANT_GOSSIP_HEIRLOOM + 3)
    {
        uint32 id = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_HEIRLOOM + 1:
            id = ASSISTANT_VENDOR_HEIRLOOM_WEAPON;
            break;
        case ASSISTANT_GOSSIP_HEIRLOOM + 2:
            id = ASSISTANT_VENDOR_HEIRLOOM_ARMOR;
            break;
        case ASSISTANT_GOSSIP_HEIRLOOM + 3:
            id = ASSISTANT_VENDOR_HEIRLOOM_OTHER;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), id);
    }
    else if (action == ASSISTANT_GOSSIP_GLYPH)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "大雕文", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GLYPH + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "小雕文", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GLYPH + 2);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_GLYPH + 1 && action <= ASSISTANT_GOSSIP_GLYPH + 2)
    {
        bool major = true;

        if (action == ASSISTANT_GOSSIP_GLYPH + 2)
            major = false;

        uint32 id = 0;

        switch (player->getClass())
        {
        case CLASS_WARRIOR:
            id = GLYPH_WARRIOR;
            break;
        case CLASS_PALADIN:
            id = GLYPH_PALADIN;
            break;
        case CLASS_HUNTER:
            id = GLYPH_HUNTER;
            break;
        case CLASS_ROGUE:
            id = GLYPH_ROGUE;
            break;
        case CLASS_PRIEST:
            id = GLYPH_PRIEST;
            break;
        case CLASS_DEATH_KNIGHT:
            id = GLYPH_DEATH_KNIGHT;
            break;
        case CLASS_SHAMAN:
            id = GLYPH_SHAMAN;
            break;
        case CLASS_MAGE:
            id = GLYPH_MAGE;
            break;
        case CLASS_WARLOCK:
            id = GLYPH_WARLOCK;
            break;
        case CLASS_DRUID:
            id = GLYPH_DRUID;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), GetGlyphId(id, major));
    }
    else if (action == ASSISTANT_GOSSIP_GEM)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "多彩", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "红色", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "蓝色", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 3);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "黄色", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 4);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "紫色", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 5);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "绿色", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 6);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "橙色", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_GEM + 7);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_GEM + 1 && action <= ASSISTANT_GOSSIP_GEM + 7)
    {
        uint32 id = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_GEM + 1:
            id = ASSISTANT_VENDOR_GEM;
            break;
        case ASSISTANT_GOSSIP_GEM + 2:
            id = ASSISTANT_VENDOR_GEM + 1;
            break;
        case ASSISTANT_GOSSIP_GEM + 3:
            id = ASSISTANT_VENDOR_GEM + 2;
            break;
        case ASSISTANT_GOSSIP_GEM + 4:
            id = ASSISTANT_VENDOR_GEM + 3;
            break;
        case ASSISTANT_GOSSIP_GEM + 5:
            id = ASSISTANT_VENDOR_GEM + 4;
            break;
        case ASSISTANT_GOSSIP_GEM + 6:
            id = ASSISTANT_VENDOR_GEM + 5;
            break;
        case ASSISTANT_GOSSIP_GEM + 7:
            id = ASSISTANT_VENDOR_GEM + 6;
            break;
        }

        player->GetSession()->SendListInventory(creature->GetGUID(), id);
    }
    else if (action == ASSISTANT_GOSSIP_CONTAINER)
    {
        player->GetSession()->SendListInventory(creature->GetGUID(), ASSISTANT_VENDOR_CONTAINER);
    }
    else if (action == ASSISTANT_GOSSIP_UTILITIES)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "改名", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 1, "要继续吗?", NameChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "改外观", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 2, "要继续吗?", CustomizeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "改种族", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 3, "要继续吗?", RaceChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "改阵营", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 4, "要继续吗?", FactionChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_UTILITIES + 1 && action <= ASSISTANT_GOSSIP_UTILITIES + 4)
    {
        ClearGossipMenuFor(player);

        AtLoginFlags flag = AT_LOGIN_NONE;
        uint32 cost = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_UTILITIES + 1:
            flag = AT_LOGIN_RENAME;
            cost = NameChangeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 2:
            flag = AT_LOGIN_CUSTOMIZE;
            cost = CustomizeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 3:
            flag = AT_LOGIN_CHANGE_RACE;
            cost = RaceChangeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 4:
            flag = AT_LOGIN_CHANGE_FACTION;
            cost = FactionChangeCost;
            break;
        }

        SetLoginFlag(player, flag, cost);
        CloseGossipMenuFor(player);
    }
    else if (action == ASSISTANT_GOSSIP_FLIGHT_PATHS)
    {
        ClearGossipMenuFor(player);

        if (FlightPathsEnabled[EXPANSION_CLASSIC] && player->GetLevel() >= FlightPathsRequiredLevel[EXPANSION_CLASSIC] && HasAvailableFlightPaths(player, EXPANSION_CLASSIC))
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "地球", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS + 1, "要继续吗?", FlightPathsCost[EXPANSION_CLASSIC], false);

        if (FlightPathsEnabled[EXPANSION_THE_BURNING_CRUSADE] && player->GetLevel() >= FlightPathsRequiredLevel[EXPANSION_THE_BURNING_CRUSADE]  && HasAvailableFlightPaths(player, EXPANSION_THE_BURNING_CRUSADE))
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "外域", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS + 2, "要继续吗?", FlightPathsCost[EXPANSION_THE_BURNING_CRUSADE], false);

        if (FlightPathsEnabled[EXPANSION_WRATH_OF_THE_LICH_KING] && player->GetLevel() >= FlightPathsRequiredLevel[EXPANSION_WRATH_OF_THE_LICH_KING] && HasAvailableFlightPaths(player, EXPANSION_WRATH_OF_THE_LICH_KING))
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "诺森德", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_FLIGHT_PATHS + 3, "要继续吗?", FlightPathsCost[EXPANSION_WRATH_OF_THE_LICH_KING], false);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_FLIGHT_PATHS + 1 && action <= ASSISTANT_GOSSIP_FLIGHT_PATHS + 3)
    {
        ClearGossipMenuFor(player);

        uint8 expansion = EXPANSION_CLASSIC;

        if (action == ASSISTANT_GOSSIP_FLIGHT_PATHS + 2)
            expansion = EXPANSION_THE_BURNING_CRUSADE;
        else if (action == ASSISTANT_GOSSIP_FLIGHT_PATHS + 3)
            expansion = EXPANSION_WRATH_OF_THE_LICH_KING;

        UnlockFlightPaths(player, expansion);
        OnGossipSelect(player, creature, GOSSIP_SENDER_MAIN, 1);
    }
    else if (action == ASSISTANT_GOSSIP_PROFESSIONS)
    {
        ClearGossipMenuFor(player);
        ListProfession(player, SKILL_FIRST_AID);
        ListProfession(player, SKILL_BLACKSMITHING);
        ListProfession(player, SKILL_LEATHERWORKING);
        ListProfession(player, SKILL_ALCHEMY);
        ListProfession(player, SKILL_HERBALISM);
        ListProfession(player, SKILL_COOKING);
        ListProfession(player, SKILL_MINING);
        ListProfession(player, SKILL_TAILORING);
        ListProfession(player, SKILL_ENGINEERING);
        ListProfession(player, SKILL_ENCHANTING);
        ListProfession(player, SKILL_FISHING);
        ListProfession(player, SKILL_SKINNING);
        ListProfession(player, SKILL_INSCRIPTION);
        ListProfession(player, SKILL_JEWELCRAFTING);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "上一页", GOSSIP_SENDER_MAIN, 1);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_PROFESSIONS + 1 && action <= ASSISTANT_GOSSIP_PROFESSIONS + 14)
    {
        ClearGossipMenuFor(player);

        uint32 skill = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_PROFESSIONS + 1:
            skill = SKILL_FIRST_AID;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 2:
            skill = SKILL_BLACKSMITHING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 3:
            skill = SKILL_LEATHERWORKING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 4:
            skill = SKILL_ALCHEMY;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 5:
            skill = SKILL_HERBALISM;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 6:
            skill = SKILL_COOKING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 7:
            skill = SKILL_MINING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 8:
            skill = SKILL_TAILORING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 9:
            skill = SKILL_ENGINEERING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 10:
            skill = SKILL_ENCHANTING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 11:
            skill = SKILL_FISHING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 12:
            skill = SKILL_SKINNING;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 13:
            skill = SKILL_INSCRIPTION;
            break;
        case ASSISTANT_GOSSIP_PROFESSIONS + 14:
            skill = SKILL_JEWELCRAFTING;
            break;
        }

        SetProfession(player, skill);
        OnGossipSelect(player, creature, GOSSIP_SENDER_MAIN, 1);
    }

    return true;
}
