AC_PREREQ([2.69])
AC_INIT([phosphor-cable-manager], [1.0], [https://github.com/openbmc/phosphor-cable-manager/issues])
AC_LANG([C++])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

# Checks for programs
AC_PROG_CXX
AC_PROG_INSTALL #Checks/sets the install variable to be used
AC_PROG_MAKE_SET

# Check for libraries	
PKG_CHECK_MODULES([SYSTEMD], [libsystemd >= 221])
PKG_CHECK_MODULES([PHOSPHOR_DBUS_INTERFACES], [phosphor-dbus-interfaces])
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus])	

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_17([noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# Checks for library functions
LT_INIT # Removes WARNING: unrecognized options: --with-libtool-sysroot

AC_ARG_VAR(CABLE_BUSNAME, [The Host Dbus busname to own])
AS_IF([test "x$CABLE_BUSNAME" == "x"], [CABLE_BUSNAME="xyz.openbmc_project.Cables.Cable"])
AC_DEFINE_UNQUOTED([CABLE_BUSNAME], ["$CABLE_BUSNAME"], [The Host DBus busname to own])

AC_ARG_VAR(CABLE_OBJPATH, [The host state manager Dbus root])
AS_IF([test "x$CABLE_OBJPATH" == "x"], [CABLE_OBJPATH="/xyz/openbmc_project/cables/cable"])
AC_DEFINE_UNQUOTED([CABLE_OBJPATH], ["$CABLE_OBJPATH"], [The host state manager Dbus root])

# Check for header files.
AC_CHECK_HEADER(systemd/sd-bus.h, ,[AC_MSG_ERROR([Could not find systemd/sd-bus.h...systemd development package required])])
AC_CHECK_HEADER(sdbusplus/server.hpp, ,[AC_MSG_ERROR([Could not find sdbusplus/server.hpp...openbmc/sdbusplus package required])])
AC_CHECK_HEADER(phosphor-logging/log.hpp, ,[AC_MSG_ERROR([Could not find phosphor-logging/log.hpp...openbmc/phosphor-logging package required])])

AC_ARG_VAR(CLASS_VERSION, [Class version to register with Cereal])
AS_IF([test "x$CLASS_VERSION" == "x"], [CLASS_VERSION=1])
AC_DEFINE_UNQUOTED([CLASS_VERSION], [$CLASS_VERSION], [Class version to register with Cereal])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
