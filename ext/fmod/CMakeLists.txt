add_library (fmod SHARED IMPORTED GLOBAL)

if (WIN32)
    if (${BUILD_X64})
        set_target_properties(fmod PROPERTIES
            IMPORTED_LOCATION_DEBUG   ${CMAKE_CURRENT_LIST_DIR}/lib/x64/fmodL.dll
            IMPORTED_IMPLIB_DEBUG     ${CMAKE_CURRENT_LIST_DIR}/lib/x64/fmodL_vc.lib  
            IMPORTED_LOCATION         ${CMAKE_CURRENT_LIST_DIR}/lib/x64/fmod.dll
            IMPORTED_IMPLIB           ${CMAKE_CURRENT_LIST_DIR}/lib/x64/fmod_vc.lib  
        )
    else()
        set_target_properties(fmod PROPERTIES
            IMPORTED_LOCATION_DEBUG   ${CMAKE_CURRENT_LIST_DIR}/lib/x86/fmodL.dll
            IMPORTED_IMPLIB_DEBUG     ${CMAKE_CURRENT_LIST_DIR}/lib/x86/fmodL_vc.lib  
            IMPORTED_LOCATION         ${CMAKE_CURRENT_LIST_DIR}/lib/x86/fmod.dll
            IMPORTED_IMPLIB           ${CMAKE_CURRENT_LIST_DIR}/lib/x86/fmod_vc.lib  
        )
    endif()
elseif (LINUX)

endif()

target_include_directories(fmod INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
