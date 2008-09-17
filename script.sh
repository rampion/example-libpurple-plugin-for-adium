#Make this change for every new version of libpurple in Adium source
/usr/bin/install_name_tool -change "@executable_path/../Frameworks/libpurple.framework/Versions/0.4.1/libpurple" "@executable_path/../Frameworks/libpurple.framework/libpurple" "$TARGET_BUILD_DIR/$TARGET_NAME.$WRAPPER_EXTENSION/Contents/MacOS/$TARGET_NAME"
