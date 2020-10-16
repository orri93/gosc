macro (gosc_get_properties)
  get_target_property(gosc_include_directories gosc
    INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(gosc_compile_definitions gosc
    INTERFACE_COMPILE_DEFINITIONS)
  set(gosc_target gosc)
  if (BUILD_WITH_EMSCRIPTEN)
    get_target_property(gosc_wasm_library gosc RESOURCE)
  endif ()
  get_target_property(gosc_source gosc SOURCES)
  get_target_property(gosc_source_dir gosc SOURCE_DIR)
  list(TRANSFORM gosc_source PREPEND "${gosc_source_dir}/")
endmacro (gosc_get_properties)
