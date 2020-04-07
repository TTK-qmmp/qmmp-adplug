
HEADERS += decoderadplugfactory.h \
           decoder_adplug.h \
           adplughelper.h \
           adplugmetadatamodel.h \
           magic.h

SOURCES += decoderadplugfactory.cpp \
           decoder_adplug.cpp \
           adplughelper.cpp \
           adplugmetadatamodel.cpp \
           magic.cpp

CONFIG += warn_on plugin link_pkgconfig c++11

TEMPLATE = lib

QMAKE_CLEAN += lib$${TARGET}.so

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += qmmp libadplug

  QMMP_PREFIX = $$system(pkg-config qmmp --variable=prefix)
  PLUGIN_DIR = $$system(pkg-config qmmp --variable=plugindir)/Input
  LOCAL_INCLUDES = $${QMMP_PREFIX}/include
  LOCAL_INCLUDES -= $$QMAKE_DEFAULT_INCDIRS
  INCLUDEPATH += $$LOCAL_INCLUDES

  plugin.path = $${PLUGIN_DIR}
  plugin.files = lib$${TARGET}.so
  INSTALLS += plugin
}

win32 {
    LIBS += -L. -lqmmp -ladplug -lbinio
}
