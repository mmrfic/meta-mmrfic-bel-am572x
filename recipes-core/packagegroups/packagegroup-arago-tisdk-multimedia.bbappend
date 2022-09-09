ACCEL_FW_append_am57x9 = " \
	${@bb.utils.contains('MACHINE_FEATURES', 'mmip', 'ipumm-fw', '', d)} \
"

ACCEL_FW_append_am57x8 = " \
	${@bb.utils.contains('MACHINE_FEATURES', 'mmip', 'ipumm-fw', '', d)} \
"

ACCEL_FW_append_am57xx = " \
        ${@bb.utils.contains('MACHINE_FEATURES', 'mmip', 'ipumm-fw', '', d)} \
"

