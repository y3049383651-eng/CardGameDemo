#include "configs/loaders/LevelConfigLoader.h"

#include <vector>
#include "cocos2d.h"
#include "base/CCData.h"
#include "platform/CCFileUtils.h"
#include "configs/LevelConfig.h"
#include "json/document.h"

namespace
{
bool parseCardArray(const rapidjson::Value& arrayValue, std::vector<LevelCardConfig>* outCards)
{
    if (!arrayValue.IsArray() || !outCards)
        return false;

    std::vector<LevelCardConfig> cards;
    cards.reserve(arrayValue.Size());

    for (rapidjson::SizeType i = 0; i < arrayValue.Size(); ++i)
    {
        const rapidjson::Value& cardValue = arrayValue[i];
        if (!cardValue.IsObject() || !cardValue.HasMember("CardFace") || !cardValue.HasMember("CardSuit"))
            return false;

        if (!cardValue["CardFace"].IsInt() || !cardValue["CardSuit"].IsInt())
            return false;

        LevelCardConfig cardConfig;
        cardConfig.face = cardValue["CardFace"].GetInt();
        cardConfig.suit = cardValue["CardSuit"].GetInt();

        if (cardValue.HasMember("Position") && cardValue["Position"].IsObject())
        {
            const rapidjson::Value& positionValue = cardValue["Position"];
            if (positionValue.HasMember("x") && positionValue["x"].IsNumber())
                cardConfig.position.x = positionValue["x"].GetFloat();

            if (positionValue.HasMember("y") && positionValue["y"].IsNumber())
                cardConfig.position.y = positionValue["y"].GetFloat();
        }

        cards.push_back(cardConfig);
    }

    *outCards = cards;
    return true;
}
}

bool LevelConfigLoader::loadFromFile(const std::string& filePath, LevelConfig* outConfig)
{
    if (!outConfig)
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - outConfig is null");
        return false;
    }

    cocos2d::Data fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
    if (fileData.isNull() || fileData.getSize() == 0)
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - failed to read file '%s' (isNull=%d, size=%zu)",
            filePath.c_str(), fileData.isNull(), fileData.getSize());
        return false;
    }

    std::string jsonText(reinterpret_cast<const char*>(fileData.getBytes()), fileData.getSize());

    // Strip UTF-8 BOM if present to avoid RapidJSON parse error at offset 0
    if (jsonText.size() >= 3 &&
        static_cast<unsigned char>(jsonText[0]) == 0xEF &&
        static_cast<unsigned char>(jsonText[1]) == 0xBB &&
        static_cast<unsigned char>(jsonText[2]) == 0xBF)
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - detected UTF-8 BOM in '%s', stripping it", filePath.c_str());
        jsonText.erase(0, 3);
    }

    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if (document.HasParseError() || !document.IsObject())
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - JSON parse error (hasError=%d, isObject=%d) file='%s'",
            document.HasParseError(), document.IsObject(), filePath.c_str());
        if (document.HasParseError())
            cocos2d::log("  parse error offset: %zu", document.GetErrorOffset());
        cocos2d::log("  jsonText (start): %s", jsonText.c_str());
        return false;
    }

    if (!document.HasMember("Playfield") || !document.HasMember("Stack"))
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - missing required member(s) in '%s' (HasPlayfield=%d, HasStack=%d)",
            filePath.c_str(), document.HasMember("Playfield"), document.HasMember("Stack"));
        return false;
    }

    std::vector<LevelCardConfig> playfieldCards;
    std::vector<LevelCardConfig> stackCards;
    if (!parseCardArray(document["Playfield"], &playfieldCards))
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - failed to parse Playfield array in '%s'", filePath.c_str());
        return false;
    }

    if (!parseCardArray(document["Stack"], &stackCards))
    {
        cocos2d::log("LevelConfigLoader::loadFromFile - failed to parse Stack array in '%s'", filePath.c_str());
        return false;
    }

    outConfig->setPlayfieldCards(playfieldCards);
    outConfig->setStackCards(stackCards);
    return true;
}
