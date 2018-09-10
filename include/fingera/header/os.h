/**
 * @brief 通过预定义宏识别编译目标操作系统
 * FINGERA_OS_ANDROID
 * FINGERA_OS_IOS
 * FINGERA_OS_OSX
 * FINGERA_OS_LINUX
 * FINGERA_OS_WINDOWS
 * FINGERA_OS 当前系统 如果未识别定义0
 *
 * @file os.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-10
 */
#ifndef _FINGERA_HEADER_OS_H_
#define _FINGERA_HEADER_OS_H_

#define FINGERA_OS_ANDROID 1
#define FINGERA_OS_IOS 2
#define FINGERA_OS_OSX 3
#define FINGERA_OS_LINUX 4
#define FINGERA_OS_WINDOWS 5

#if defined(__ANDROID__)
#define FINGERA_OS FINGERA_OS_ANDROID

#elif defined(__APPLE__) && defined(__MACH__)
#if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#define FINGERA_OS FINGERA_OS_IOS
#else
#define FINGERA_OS FINGERA_OS_OSX
#endif

#elif defined(linux) || defined(__linux)
#define FINGERA_OS FINGERA_OS_LINUX

#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
    defined(__TOS_WIN__) || defined(__WINDOWS__)
#define FINGERA_OS FINGERA_OS_WINDOWS

#else
#define FINGERA_OS 0
#warning 没有识别目标操作系统

#endif

#endif  // _FINGERA_HEADER_OS_H_