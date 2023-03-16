FILESEXTRAPATHS_prepend_am572x-bel-mmrfic := "${THISDIR}/am572x:"

SRC_URI += " \
	file://0001-add-mmrfic-dts-Makefile.patch \
	file://0002-am572x-bel-mmrfic-defconfig.patch \
	file://0003-Added-dts-for-mmrfic-carrier-board.patch \
	file://0004-Disabling-peripherals-using-gpio-spi.patch \
"
