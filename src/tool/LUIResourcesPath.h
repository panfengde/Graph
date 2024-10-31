//
// Created by 潘峰 on 2023/9/5.
//

#ifndef LUI_LUIRESOURCESPATH_H
#define LUI_LUIRESOURCESPATH_H

#include <fstream>

namespace fs = std::filesystem;

std::string getLUIResourcesPath();

std::string getExecutablePath();

#endif //LUI_LUIRESOURCESPATH_H
