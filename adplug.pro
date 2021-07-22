include(../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/adplug

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

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    PKGCONFIG += libadplug
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libadplug.so
}

win32 {
    LIBS += -ladplug -lbinio
}
