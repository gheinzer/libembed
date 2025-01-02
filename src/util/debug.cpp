#include <libembed/util/debug.h>

#if LIBEMBED_CONFIG_ENABLE_DEBUGGING == true

static void __dummy_write(std::string _) { };
void (*embed::debug::writeStringPtr)(std::string) = __dummy_write;

static void __printDebug(std::string level, std::string message, std::string functionName) {
    int paddingLength = LIBEMBED_CONFIG_DEBUG_FUNCTION_NAME_MAXLEN - functionName.length();
    if(paddingLength < 0) paddingLength = 1;
    std::string padding(paddingLength, ' ');
    embed::debug::writeStringPtr(
        "[" + level + "]\t" +
        functionName + "()" + padding +
        message + "\r\n"
    );
}

void embed::debug::info(std::string message, std::string functionName) {
    __printDebug("INFO", message, functionName);
}

void embed::debug::trace(std::string message, std::string functionName) {
    __printDebug("TRACE", message, functionName);
}

#endif