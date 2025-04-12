#-------------------------------------------------
#
# QwtLibrary configuration file
#
#-------------------------------------------------

# QWT_VER = 5.2.3
QWT_VER = 6.3.0

contains(QWT_VER,^5\\..*\\..*) {
  VER_SFX = 5
  UNIX_SFX = -qt4
} else {
  VER_SFX =
  UNIX_SFX =
}

unix {
  QWT_PATH = /usr
  QWT_INC_PATH = $${QWT_PATH}/include/qwt$${UNIX_SFX}
  QWT_LIB = qwt$${UNIX_SFX}
}

win32 {
  win32-x-g++ {
    QWT_PATH = /usr/qwt$${VER_SFX}-win
  } else {
    QWT_PATH = $${PWD}
  }
  QWT_INC_PATH = $${QWT_PATH}/include
  CONFIG(debug,debug|release) {
    DEBUG_SFX = d
  } else {
    DEBUG_SFX =
  }
  QWT_LIB = qwt$${DEBUG_SFX}$${VER_SFX}
}

INCLUDEPATH += $${QWT_INC_PATH}
DEPENDPATH += $${QWT_INC_PATH}
LIBS += -L$${QWT_PATH}/lib -l$${QWT_LIB}

qwt.path = $${DESTDIR}
qwt.files = $${PWD}/lib/$${QWT_LIB}.dll

INSTALLS += qwt

