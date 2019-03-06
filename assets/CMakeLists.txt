# ------------------------------------------------------------------------------
# Assets (audio): copy audio to CMake binary output directory
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ASSETS_AUDIO ${CMAKE_SOURCE_DIR}/assets/audio/*)
foreach(asset_audio ${ASSETS_AUDIO})
    #message(${asset_audio})
    file(COPY ${asset_audio} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/audio)
endforeach(asset_audio)

# ------------------------------------------------------------------------------
# Assets (images): copy assets to CMake binary output directory
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ASSETS_IMAGES ${CMAKE_SOURCE_DIR}/assets/images/*)
foreach(asset_image ${ASSETS_IMAGES})
    #message(${asset_image})
    file(COPY ${asset_image} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)
endforeach(asset_image)

# ------------------------------------------------------------------------------
# Assets (shaders): copy shaders to CMake binary output directory
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ASSETS_SHADERS ${CMAKE_SOURCE_DIR}/assets/shaders/*)
foreach(asset_shader ${ASSETS_SHADERS})
    #message(${asset_shader})
    file(COPY ${asset_shader} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
endforeach(asset_shader)

# ------------------------------------------------------------------------------
# Assets (textures): copy textures to CMake binary output directory
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ASSETS_TEXTURES ${CMAKE_SOURCE_DIR}/assets/textures/*)
foreach(asset_texture ${ASSETS_TEXTURES})
    #message(${asset_texture})
    file(COPY ${asset_texture} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textures)
endforeach(asset_texture)