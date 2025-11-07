HEADERS += decoderadplugfactory.h \
           decoder_adplug.h \
           adplughelper.h \
           adplugmetadatamodel.h \
           settingsdialog.h

SOURCES += decoderadplugfactory.cpp \
           decoder_adplug.cpp \
           adplughelper.cpp \
           adplugmetadatamodel.cpp \
           settingsdialog.cpp

FORMS += settingsdialog.ui

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/adplug

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
        PKGCONFIG += adplug
    }

    win32{
        LIBS += -ladplug -lbinio
    }
}else{
    QT += widgets
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        equals(QT_MAJOR_VERSION, 5){
            QMMP_PKG = qmmp-1
        }else:equals(QT_MAJOR_VERSION, 6){
            QMMP_PKG = qmmp
        }else{
            error("Unsupported Qt version: 5 or 6 is required")
        }
        
        PKGCONFIG += $${QMMP_PKG} adplug

        PLUGIN_DIR = $$system(pkg-config $${QMMP_PKG} --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config $${QMMP_PKG} --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
