# meta-mmrfic-bel-am572x

A BSP layer modified for the custom hardware.

## conf

Contains machine level configuration changes for custom board

## recipes-bsp

U-boot modifications

## recipes-core

Target to include PLL and other test binaries in rootfs

## recipes-kernel

Changes made to kernel DTS

## recipes-test

Source file for UART test, i2c test, spi test

## recipes-utilities

Source file for PLL startup script

## docs

### user-manual.txt

Contains build steps for installation of Code composer studio, RTOS and Linux SDK,
Also contains build and run instruciton for: DSP code, using Code composer studio to build DSP examples, eMMC flashing, webcam instructions

### build-manual.txt

Contains build instruction for phytec BSP build and adding custom layer to phytec build

### test-procedure.txt

Contains instructions to test the BSP