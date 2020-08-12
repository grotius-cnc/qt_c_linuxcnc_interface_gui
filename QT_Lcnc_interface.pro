QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    display/opengl.cpp \
    display/variable.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    display/display.h \
    display/opengl.h \
    display/variable.h \
    gcode/parse_gcode.h \
    hal/halsection.h \
    keyboard/keyboard.h \
    lcnc/disable_adaptive_feed.h \
    lcnc/enable_adaptive_feed.h \
    lcnc/estop.h \
    lcnc/estop_reset.h \
    lcnc/get_position.h \
    lcnc/halcommand/get_command.h \
    lcnc/halcommand/send_command.h \
    lcnc/halcommand/set_adaptive_feed.h \
    lcnc/halcommand/set_feed_override.h \
    lcnc/halcommand/set_flood_off.h \
    lcnc/halcommand/set_flood_on.h \
    lcnc/halcommand/set_home_x.h \
    lcnc/halcommand/set_jog_speed.h \
    lcnc/halcommand/set_lube_off.h \
    lcnc/halcommand/set_lube_on.h \
    lcnc/halcommand/set_max_velocity.h \
    lcnc/halcommand/set_mode_joint.h \
    lcnc/halcommand/set_mode_teleop.h \
    lcnc/halcommand/set_rapid_override.h \
    lcnc/halcommand/set_scale_max_velocity.h \
    lcnc/halcommand/set_spindle_decrease.h \
    lcnc/halcommand/set_spindle_increase.h \
    lcnc/halcommand/set_spindle_override.h \
    lcnc/home.h \
    lcnc/estop.h \
    lcnc/estop_reset.h \
    lcnc/get_position.h \
    lcnc/home.h \
    lcnc/maxvel.h \
    lcnc/mdi.h \
    lcnc/mode_auto.h \
    lcnc/mode_manual.h \
    lcnc/mode_mdi.h \
    lcnc/nml/config.h \
    lcnc/nml/disable_adaptive_feed.h \
    lcnc/nml/enable_adaptive_feed.h \
    lcnc/nml/estop.h \
    lcnc/nml/estop_reset.h \
    lcnc/nml/feed_override.h \
    lcnc/nml/hal_pin_test.h \
    lcnc/nml/home_all.h \
    lcnc/nml/home_x.h \
    lcnc/nml/jog.h \
    lcnc/nml/jog_speed.h \
    lcnc/nml/maxvel.h \
    lcnc/nml/mdi.h \
    lcnc/nml/mode_auto.h \
    lcnc/nml/mode_manual.h \
    lcnc/nml/mode_mdi.h \
    lcnc/nml/open_file.h \
    lcnc/nml/pause.h \
    lcnc/nml/reload_file.h \
    lcnc/nml/reset_interpreter.h \
    lcnc/nml/resume.h \
    lcnc/nml/run_backward.h \
    lcnc/nml/run_forward.h \
    lcnc/nml/spindle_off.h \
    lcnc/nml/spindle_on.h \
    lcnc/nml/spindle_stop.h \
    lcnc/nml/state_off.h \
    lcnc/nml/state_on.h \
    lcnc/nml/status/get_message_status.h \
    lcnc/nml/status/get_position.h \
    lcnc/nml/status/update_status.h \
    lcnc/nml/step.h \
    lcnc/nml/stop.h \
    lcnc/nml/unhome.h \
    lcnc/open_file.h \
    lcnc/pause.h \
    lcnc/reset_interpreter.h \
    lcnc/resume.h \
    lcnc/run_backward.h \
    lcnc/run_forward.h \
    lcnc/spindle_off.h \
    lcnc/spindle_on.h \
    lcnc/spindle_stop.h \
    lcnc/state_off.h \
    lcnc/state_on.h \
    lcnc/step.h \
    lcnc/stop.h \
    lcnc/unhome.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

INCLUDEPATH += /home/user/linuxcnc/include \
               /home/user/linuxcnc/src/hal/utils

LIBS += -Iinclude -Isrc/emc/rs274ngc -Llib -lnml -llinuxcnc  -llinuxcnchal -llinuxcncini -DULAPI -lposemath
LIBS += -lGLU


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    info.txt

RESOURCES += \
    icons/icons.qrc
