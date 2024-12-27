/**
 * @file macros.h
 * @author Gabriel Heinzer
 * @brief Various utility macro definitions.
 */

#ifndef LIBEMBED_UTIL_MACROS_H_
#define LIBEMBED_UTIL_MACROS_H_

/**
 * @brief Performs a preprocessor token pasting concatenation with two symbols.
 * 
 */
#define LIBEMBED_CONCAT2(a, b) a##b
/**
 * @brief Performs a preprocessor token pasting concatenation with three symbols.
 * 
 */
#define LIBEMBED_CONCAT3(a, b, c) a##b##c

#endif /* LIBEMBED_UTIL_MACROS_H_ */