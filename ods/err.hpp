/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef MTL_ERR_HPP_
#define MTL_ERR_HPP_

#include <errno.h>
#include <cstdio>
#include <QDebug>

#ifndef SRC_FILE_NAME
#define SRC_FILE_NAME __FILE__
#endif

#ifdef __unix__
	#define MTL_COLOR_BLUE		"\x1B[34m"
	#define MTL_COLOR_DEFAULT	"\x1B[0m"
	#define MTL_COLOR_GREEN		"\x1B[32m"
	#define MTL_COLOR_RED		"\e[0;91m"
#else
	#define MTL_COLOR_BLUE		""
	#define MTL_COLOR_DEFAULT	""
	#define MTL_COLOR_GREEN		""
	#define MTL_COLOR_RED		""
#endif

#if defined(QODS_SILENT)
#define mtl_line(fmt, args...) do {} while (0)
#elif defined(_MSC_VER)
#define mtl_line(fmt, ...) fprintf(stdout, \
	"%s[%s %s %.3d] " fmt "%s\n", MTL_COLOR_BLUE, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, __VA_ARGS__, MTL_COLOR_DEFAULT)
#else
#define mtl_line(fmt, args...) fprintf(stdout, \
	"%s[%s %s %.3d] " fmt "%s\n", MTL_COLOR_BLUE, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, ##args, MTL_COLOR_DEFAULT)
#endif

#if defined(QODS_SILENT)
#define mtl_warn(fmt, args...) do {} while (0)
#elif defined(_MSC_VER)
#define mtl_warn(fmt, ...) fprintf(stderr, \
	"%s[Warning %s %s %.3d] " fmt "%s\n", MTL_COLOR_RED, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, __VA_ARGS__, MTL_COLOR_DEFAULT)
#else
#define mtl_warn(fmt, args...) fprintf(stderr, \
	"%s[Warning %s %s %.3d] " fmt "%s\n", MTL_COLOR_RED, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, ##args, MTL_COLOR_DEFAULT)
#endif

#if defined(QODS_SILENT)
#define mtl_status(status) do {} while (0)
#else
#define mtl_status(status) fprintf (stderr, "%s[%s %s %.3d] %s%s\n", \
	MTL_COLOR_RED, SRC_FILE_NAME, \
	__LINE__, __FUNCTION__, strerror(status), MTL_COLOR_DEFAULT)
#endif

#define mtl_errno fprintf (stderr, "[%s %.3d] %m\n", __LINE__, __FUNCTION__)

#define mtl_qline(qstr) qDebug().nospace() << MTL_COLOR_BLUE << "[" << \
	SRC_FILE_NAME << ' ' << __FUNCTION__ << ' ' << __LINE__ << "] " << \
	qstr << MTL_COLOR_DEFAULT

#define NO_ASSIGN_COPY_MOVE(TypeName)	\
	TypeName(const TypeName&) = delete;		\
	void operator=(const TypeName&) = delete; \
	TypeName(TypeName&&) = delete;

#define NO_MOVE(TypeName)	\
	TypeName(TypeName&&) = delete;

#endif
