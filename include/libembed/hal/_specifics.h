#ifndef LIBEMBED_HAL_SPECIFICS_H_
#define LIBEMBED_HAL_SPECIFICS_H_

#define __SPECIFICS_CONCAT2(a, b) a##b
#define __SPECIFICS_CONCAT3(a, b, c) a##b##c

#define __FORALLPINS_FPORT(function, port) \
    function(port, 0); \
    function(port, 1); \
    function(port, 2); \
    function(port, 3); \
    function(port, 4); \
    function(port, 5); \
    function(port, 6); \
    function(port, 7); \
    function(port, 8); \
    function(port, 9); \
    function(port, 10); \
    function(port, 11); \
    function(port, 12); \
    function(port, 13); \
    function(port, 14); \
    function(port, 15);

#ifdef STM32G0

    #define __FORALLPORTS_PS(prefix, suffix) \
        __SPECIFICS_CONCAT3(prefix, A, suffix); \
        __SPECIFICS_CONCAT3(prefix, B, suffix); \
        __SPECIFICS_CONCAT3(prefix, C, suffix); \
        __SPECIFICS_CONCAT3(prefix, D, suffix)

    #define __FORALLPORTS_F(function) \
        function(A); \
        function(B); \
        function(C); \
        function(D)

#endif /* STM32G0 */ 

#ifdef STM32F4

    #define __FORALLPORTS_PS(prefix, suffix) \
        __SPECIFICS_CONCAT3(prefix, A, suffix); \
        __SPECIFICS_CONCAT3(prefix, B, suffix); \
        __SPECIFICS_CONCAT3(prefix, C, suffix); \
        __SPECIFICS_CONCAT3(prefix, D, suffix); \
        __SPECIFICS_CONCAT3(prefix, E, suffix); \
        __SPECIFICS_CONCAT3(prefix, F, suffix); \
        __SPECIFICS_CONCAT3(prefix, G, suffix); \
        __SPECIFICS_CONCAT3(prefix, H, suffix)

    #define __FORALLPORTS_F(function) \
        function(A); \
        function(B); \
        function(C); \
        function(D); \
        function(E); \
        function(F); \
        function(G); \
        function(H)

#endif /* STM32F4 */ 

#endif /* LIBEMBED_HAL_SPECIFICS_H_ */