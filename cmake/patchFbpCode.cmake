# Utility file used to patch some widgets that are not supported
# by wxFormBuilder natively.
#
# Usage example for patching files at configure-time:
#
# execute_process(COMMAND ${CMAKE_COMMAND} -DTARGET_FILE=${CMAKE_CURRENT_SOURCE_DIR}/wxtexample.cpp -P${WXT_PATCH_FBP})

if(NOT DEFINED TARGET_FILE)
	message(FATAL_ERROR "Target file must be specified via -DTARGET_FILE=path")
endif()

message("Patching fbp project at \"${TARGET_FILE}\"")

file(READ "${TARGET_FILE}" FILE_CONTENTS)
string(REPLACE "wxStaticBox(" "wxt::StaticBox(" FILE_CONTENTS "${FILE_CONTENTS}")
file(WRITE "${TARGET_FILE}" "${FILE_CONTENTS}")