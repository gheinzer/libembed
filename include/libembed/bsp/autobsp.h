/**
 * @file autobsp.h
 * @author Gabriel Heinzer
 * @brief Automatically includes the appropriate BSP for the specified board.
 */

#include <libembed/util/macros.h>

#ifndef LIBEMBED_BSP_AUTOBSP_H_
#define LIBEMBED_BSP_AUTOBSP_H_

#define __LIBEMBED_BOARD_HEADER_NAME LIBEMBED_STRINGIFY(LIBEMBED_BOARD.h)

#if __has_include(__LIBEMBED_BOARD_HEADER_NAME)
    #include __LIBEMBED_BOARD_HEADER_NAME
#else
    #warning This board does not seem to have a matching BSP. Please refer to the documentation for a list of supported boards.
#endif

#undef __LIBEMBED_BOARD_HEADER_NAME

/**
 * @brief BSP (board support package) for the board you are currently building for.
 * 
 */
namespace embed::board { }

#endif /* LIBEMBED_BSP_AUTOBSP_H_ */