#!/bin/sh
INSTALL_DIR=/data/local/tmp/test_aes_wb
adb push cmake_build/main $INSTALL_DIR
adb push cmake_build/testing $INSTALL_DIR
adb push my_plaintext_file $INSTALL_DIR
adb shell $INSTALL_DIR/main --use-key 000102030405060708090A0B0C0D0E0F --create-table $INSTALL_DIR/aes_inst1
adb shell $INSTALL_DIR/main --decrypt=0 --load-tables $INSTALL_DIR/aes_inst1 --input-files $INSTALL_DIR/my_plaintext_file --out-file $INSTALL_DIR/my_encrypted_file
adb shell $INSTALL_DIR/main --decrypt=1 --load-tables $INSTALL_DIR/aes_inst1 --input-files $INSTALL_DIR/my_encrypted_file --out-file $INSTALL_DIR/my_decrypted_file
adb shell $INSTALL_DIR/testing
