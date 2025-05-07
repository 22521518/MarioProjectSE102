#pragma once
#include <stdexcept>       

#include "GameParser.h"
#include "TxtGameParser.h"
#include "JsonGameParser.h"

using namespace std;

class GameParserFactory : public IGameParser {
public:

    void _ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath) override;
    FileGameConfig _ParseGameConfigFile(const string& filename) override;
    FilePlaySceneConfig _ParsePlaySceneFile(const string& filename) override;

    static unique_ptr<IGameParser> Create(const string& filename);
};