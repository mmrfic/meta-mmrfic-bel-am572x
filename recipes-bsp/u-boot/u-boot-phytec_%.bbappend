FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://0001-am572x-bel-mmrfic-defconfig.patch        	\
	file://0002-Added-dts-entry-for-mmrfic.patch 	\
	file://0003-am572x-bel-mmrfic-includes.patch 	\
	file://0004-Added-makefile-for-mmrfic.patch 	\
	file://0005-Added-Kconfig-for-mmrfic.patch 	\
	file://0006-board-changes-for-mmrfic.patch  	\
"
