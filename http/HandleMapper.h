#pragma once
#ifndef HANDLEMAPPER_H
#define HANDLEMAPPER_H
#include <unordered_map>
#include <string>
#include <functional>
#include "../mysql/SQLConnPool.h"
#include "../mysql/SQLConnection.h"

typedef std::unordered_map<std::string, std::string> kvMap;
typedef std::unordered_map<std::string, std::function<void(const kvMap&, std::string&)>> funcMapper;
/**
 * @brief handle函数 
 **/
void login(const kvMap& data, std::string& res);

extern funcMapper POST_HANDLES;
#endif