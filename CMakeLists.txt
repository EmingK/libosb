#
# libosb
#
# osu! storyboard manipulation library
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(libosb)

SET(LIBOSB_SRC
  src/libosb/sprite.cc
  src/libosb/event.cc
)

SET(OSBTEST_SRC
  src/osbtest/main.cc
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/libosb/include)

ADD_LIBRARY(osb ${LIBOSB_SRC})
ADD_EXECUTABLE(osb_test ${OSBTEST_SRC})

SET_PROPERTY(
  TARGET osb osb_test
  PROPERTY CXX_STANDARD 11
)
SET_PROPERTY(
  TARGET osb osb_test
  PROPERTY CXX_STANDARD_REQUIRED ON
)

ADD_DEPENDENCIES(osb_test
  osb
)
TARGET_LINK_LIBRARIES(osb_test
  osb
)