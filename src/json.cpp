#include "../include/json.hpp"
#include <fstream>
#include <sstream>

std::string JSON::Serialize() const
{
    rapidjson::StringBuffer ss;
    rapidjson::Writer<rapidjson::StringBuffer> writer(ss);		// Can also use Writer for condensed formatting
    if (Serialize(&writer))
        return ss.GetString();
    return "";
}

bool JSON::Deserialize(const std::string& s)
{
    rapidjson::Document doc;
    if (!InitDocument(s, doc))
        return false;

    Deserialize(doc);

    return true;
}

bool JSON::DeserializeFromFile(const std::string& filePath)
{
    std::ifstream f(filePath);
    std::stringstream buffer;
    buffer << f.rdbuf();
    f.close();

    return Deserialize(buffer.str());
}

bool JSON::SerializeToFile(const std::string& filePath)
{
    std::ofstream f(filePath);
    std::string s = Serialize();
    f << s;
    f.flush();
    f.close();

    return true;
}

bool JSON::InitDocument(const std::string& s, rapidjson::Document& doc)
{
    if (s.empty())
        return false;

    std::string validJson(s);

    return !doc.Parse(validJson.c_str()).HasParseError() ? true : false;
}