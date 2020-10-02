macro (gosc_get_properties)
  get_target_property(gosc_include_directories gosc
    INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(gosc_compile_definitions gosc
    INTERFACE_COMPILE_DEFINITIONS)
  set(gosc_target gosc)
  if (BUILD_WITH_EMSCRIPTEN)
    get_target_property(gosc_wasm_library gosc RESOURCE)
  endif ()
endmacro (gosc_get_properties)
