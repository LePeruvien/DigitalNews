# - Try to find the Xalan xml library
# Once done this will define
#
#  XALAN_FOUND - system has the Xalan library
#  XALAN_INCLUDE_DIR - the Xalan include directory
#  XALAN_LIBRARIES - The libraries needed to use Xalan

IF (NOT XALAN_FOUND)
  IF (WIN32)
    SET (xalan_libs "Xalan-C_1")
  ELSE()
    SET (xalan_libs "xalan-c")
  ENDIF()

    # if we didn't find in externals, look in system include path
    FIND_PATH (XALAN_INCLUDE_DIR NAMES xalanc/XPath/XObjectFactory.hpp )
    FIND_LIBRARY (XALAN_LIBRARIES NAMES ${xalan_libs})

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Xalan DEFAULT_MSG
    XALAN_LIBRARIES 
    XALAN_INCLUDE_DIR
  )

  IF (XALAN_FOUND)
    IF (WIN32)
      STRING(REPLACE "Xalan-C_1" "Xalan-C_1D" XALAN_DEBUG_LIBRARIES "${XALAN_LIBRARIES}")
      set (XALAN_LIBRARIES optimized ${XALAN_LIBRARIES} debug ${XALAN_DEBUG_LIBRARIES})
    ELSE()
      STRING(REPLACE "xalan-c" "xalanMsg" XALAN_EXTRA_LIBRARIES "${XALAN_LIBRARIES}")
      set (XALAN_LIBRARIES ${XALAN_LIBRARIES} ${XALAN_EXTRA_LIBRARIES})
    ENDIF()
  ENDIF()
  MARK_AS_ADVANCED(XALAN_INCLUDE_DIR XALAN_LIBRARIES)
ENDIF()

