set(INCLUDE_DIR include)
set(SRC_DIR src)

set(SOURCES 
    ${SRC_DIR}/Graphics.cpp
    ${SRC_DIR}/Input.cpp
    ${SRC_DIR}/InputEvent.cpp
    ${SRC_DIR}/Menu.cpp
    ${SRC_DIR}/MenuAPI.cpp
    ${SRC_DIR}/MenuFactory.cpp
    ${SRC_DIR}/Utility.cpp
    ${SRC_DIR}/Window.cpp
    ${SRC_DIR}/Json/json.cpp
    ${SRC_DIR}/MenuItems/DrawArea.cpp
    ${SRC_DIR}/MenuItems/MenuItem.cpp
    ${SRC_DIR}/MenuItems/ProgressBar.cpp
    ${SRC_DIR}/MenuItems/Sprite.cpp
    ${SRC_DIR}/MenuItems/TextLabel.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/Graphics.h
    ${INCLUDE_DIR}/Input.h
    ${INCLUDE_DIR}/InputEvent.h
    ${INCLUDE_DIR}/Menu.h
    ${INCLUDE_DIR}/MenuAPI.h
    ${INCLUDE_DIR}/MenuFactory.h
    ${INCLUDE_DIR}/Utility.h
    ${INCLUDE_DIR}/Window.h
    ${INCLUDE_DIR}/Json/json.h
    ${INCLUDE_DIR}/MenuItems/Button.h
    ${INCLUDE_DIR}/MenuItems/Checkbox.h
    ${INCLUDE_DIR}/MenuItems/CheckboxList.h
    ${INCLUDE_DIR}/MenuItems/DrawArea.h
    ${INCLUDE_DIR}/MenuItems/InputField.h
    ${INCLUDE_DIR}/MenuItems/InputFieldPassword.h
    ${INCLUDE_DIR}/MenuItems/List.h
    ${INCLUDE_DIR}/MenuItems/MenuItem.h
    ${INCLUDE_DIR}/MenuItems/ProgressBar.h
    ${INCLUDE_DIR}/MenuItems/Sprite.h
    ${INCLUDE_DIR}/MenuItems/TextLabel.h
)

add_library(MenuSystem ${SOURCES} ${HEADERS})
target_compile_features(MenuSystem PUBLIC cxx_std_17)
target_include_directories(MenuSystem PUBLIC include include/Json include/MenuItems src src/Json src/MenuItems)