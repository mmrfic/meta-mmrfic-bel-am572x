DESCRIPTION = "Testing communication protocols"
PRIORITY = "optional"
SECTION = "protocols"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
SRC_URI = "file://i2c_test.c"
SRC_URI +="file://uart_test.c"
SRC_URI +="file://gpio_test.c" 
SRC_URI +="file://spi_test.c"
S = "${WORKDIR}"
do_compile() {
${CC} ${CFLAGS} ${LDFLAGS} i2c_test.c -o i2c_test
${CC} ${CFLAGS} ${LDFLAGS} uart_test.c -o uart_test
${CC} ${CFLAGS} ${LDFLAGS} gpio_test.c -o gpio_test
${CC} ${CFLAGS} ${LDFLAGS} spi_test.c -o spi_test
}
do_install() {
install -d ${D}${bindir}
install -m 0755 ${WORKDIR}/i2c_test ${D}${bindir}
install -m 0755 ${WORKDIR}/uart_test ${D}${bindir}
install -m 0755 ${WORKDIR}/gpio_test ${D}${bindir}
install -m 0755 ${WORKDIR}/spi_test ${D}${bindir}
}

