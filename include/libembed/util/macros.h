/**
 * @file macros.h
 * @author Gabriel Heinzer
 * @brief Various utility macro definitions.
 */

#ifndef LIBEMBED_UTIL_MACROS_H_
#define LIBEMBED_UTIL_MACROS_H_

#define __LIBEMBED_CONCAT2_INTERNAL(a, b) a##b

/**
 * @brief Performs a preprocessor token pasting concatenation with two symbols.
 * 
 */
#define LIBEMBED_CONCAT2(a, b) __LIBEMBED_CONCAT2_INTERNAL(a, b)
/**
 * @brief Performs a preprocessor token pasting concatenation with three symbols.
 * 
 */
#define LIBEMBED_CONCAT3(a, b, c) LIBEMBED_CONCAT2(a, LIBEMBED_CONCAT2(b, c))

/**
 * @brief Performs a preprocessor stringification.
 * 
 */
#define LIBEMBED_STRINGIFY_(a) #a

/**
 * @brief Performs a preprocessor stringification.
 * 
 */
#define LIBEMBED_STRINGIFY(a) LIBEMBED_STRINGIFY_(a)

#endif /* LIBEMBED_UTIL_MACROS_H_ */