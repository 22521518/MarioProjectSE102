#include "GameParserFactory.h"
#include "debug.h"

void GameParserFactory::_ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath)
{
    auto parser = GameParserFactory::Create(assetPath);
    DebugOut(L"loading file %s", assetPath.c_str());
    parser->_ParseSection_ASSET(config, assetPath);
}

FileGameConfig GameParserFactory::_ParseGameConfigFile(const string& filename)
{
    auto parser = GameParserFactory::Create(filename);
    FileGameConfig config = parser->_ParseGameConfigFile(filename);
    return config;
}

FilePlaySceneConfig GameParserFactory::_ParsePlaySceneFile(const string& filename)
{
    auto parser = GameParserFactory::Create(filename);
    FilePlaySceneConfig config = parser->_ParsePlaySceneFile(filename);
    return config;
}

unique_ptr<IGameParser> GameParserFactory::Create(const string& filename)
{
    auto pos = filename.rfind('.');
    string ext = (pos != string::npos) ? filename.substr(pos) : "";
    if (ext == ".json")
        return make_unique<JsonGameParser>();
    else if (ext == ".txt")
        return make_unique<TxtGameParser>();
    else
        throw runtime_error("Invalid valid file. Do not support the extension: " + ext);
}