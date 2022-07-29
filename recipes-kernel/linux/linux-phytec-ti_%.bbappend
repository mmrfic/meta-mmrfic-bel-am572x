FILESEXTRAPATHS_prepend_am572x := "${THISDIR}/${PN}/am572x:"

SRC_URI += " \
	file://0001-add-mmrfic-dts-Makefile.patch \
	file://0002-am572x-bel-mmrfic-defconfig.patch \
	file://0003-Added-dts-for-mmrfic-carrier-board.patch \
"
