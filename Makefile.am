AM_DEFAULT_SOURCE_EXT = .cpp

sbin_PROGRAMS = phosphor-cable-state-manager 

phosphor_cable_state_manager_SOURCES = \
	cable_state_manager.cpp \
	cable_state_manager_main.cpp 


generic_cxxflags = \
	$(SYSTEMD_CFLAGS) \
	$(PHOSPHOR_DBUS_INTERFACES_CFLAGS) \
	$(SDBUSPLUS_CFLAGS) \
	$(PHOSPHOR_LOGGING_CFLAGS)

generic_ldflags = \
	$(SYSTEMD_LIBS) \
	$(PHOSPHOR_DBUS_INTERFACES_LIBS) \
	$(SDBUSPLUS_LIBS) \
	$(PHOSPHOR_LOGGING_LIBS)


phosphor_cable_state_manager_CXXFLAGS = $(generic_cxxflags)
phosphor_cable_state_manager_LDFLAGS = $(generic_ldflags)