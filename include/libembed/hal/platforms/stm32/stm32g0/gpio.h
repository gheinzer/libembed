#define __FORALLPORTS_PS(prefix, suffix) \
    LIBEMBED_CONCAT3(prefix, A, suffix); \
    LIBEMBED_CONCAT3(prefix, B, suffix); \
    LIBEMBED_CONCAT3(prefix, C, suffix); \
    LIBEMBED_CONCAT3(prefix, D, suffix)

#define __FORALLPORTS_F(function) \
    function(A); \
    function(B); \
    function(C); \
    function(D)