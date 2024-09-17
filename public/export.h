//
// Created by summer on 2024/9/14.
//

#ifndef EXPORT_H
#define EXPORT_H

#if defined _WIN32
#if defined(PUBLIC_TOOLS_EXPORTS)
#define PUBLIC_TOOLS_API __declspec(dllexport)
#else
#define PUBLIC_TOOLS_API __declspec(dllimport)
#endif
#else
#define PUBLIC_TOOLS_API
#endif

#endif //EXPORT_H
