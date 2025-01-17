project(hesiod)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# --- sources
file(GLOB_RECURSE HESIOD_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
     
if(HESIOD_ENABLE_GENERATE_NODE_SNAPSHOT)
  set(HESIOD_SOURCES ${HESIOD_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/generate_node_snapshot/generate_node_snapshot.cpp
  )
endif(HESIOD_ENABLE_GENERATE_NODE_SNAPSHOT)

add_executable(${PROJECT_NAME} ${HESIOD_SOURCES})

set(HESIOD_INCLUDE
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${PROJECT_SOURCE_DIR}/external/macro-logger
)

if(HESIOD_ENABLE_GENERATE_NODE_SNAPSHOT)
  set(HESIOD_INCLUDE ${HESIOD_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/generate_node_snapshot
  )
endif(HESIOD_ENABLE_GENERATE_NODE_SNAPSHOT)

if(HESIOD_ENABLE_GENERATE_NODE_SNAPSHOT)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_GENERATE_NODE_SNAPSHOT=1)
endif(HESIOD_ENABLE_GENERATE_NODE_SNAPSHOT)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE ${HESIOD_INCLUDE})
			     
# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    highmap
    gnode
    glfw
    OpenGL::GL
    GLEW::GLEW
    GLUT::GLUT
    ImGui::ImGui
    ImCandy::ImCandy
    ImGuiNodeEditor::ImGuiNodeEditor
    ImGuiFileDialog::ImGuiFileDialog
    nlohmann_json::nlohmann_json
)
