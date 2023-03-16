inherit systemd

DESCRIPTION = "Program the PLL during boot"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "pll.service"

SRC_URI = "file://pll-startup.c"
SRC_URI +="file://pll.service"

S = "${WORKDIR}"

do_compile() {
        ${CC} ${CFLAGS} ${LDFLAGS} pll-startup.c -o pll-startup
}

do_install() {
	install -d ${D}${bindir}
	install -d ${D}/${systemd_system_unitdir}

        install -m 0755 ${WORKDIR}/pll-startup ${D}${bindir}
	install -m 0644 ${WORKDIR}/pll.service ${D}/${systemd_system_unitdir}
}

FILES_${PN} += " \
	${binddir}/pll-startup \
	${systemd_system_unitdir}/pll.service \
"
