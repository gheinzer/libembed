def appendToEnv(environment):
    defines = []
    defines.append(("LIBEMBED_PLATFORM", environment["PIOPLATFORM"]))
    boardName = str(environment["BOARD"]).strip()
    defines.append(("LIBEMBED_BOARD", boardName))
    defines.append(f"LIBEMBED_BOARD_{boardName.upper()}")
    defines.append(("LIBEMBED_FRAMEWORK", environment["PIOFRAMEWORK"]))

    flags = []
    flags.append("-std=c++17")
    flags.append("-fexceptions")

    environment.Append(
        CPPDEFINES=list(environment.get("CPPDEFINES", [])) + defines,
        CXXFLAGS=list(environment.get("CCFLAGS", [])) + flags
    )

appendToEnv(DefaultEnvironment())

Import("env", "projenv")
appendToEnv(env)
appendToEnv(projenv)