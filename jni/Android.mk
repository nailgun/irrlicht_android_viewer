LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
LOCAL_MODULE    := irrlicht_viewer
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv1_CM

LOCAL_STATIC_LIBRARIES := android_native_app_glue irrlicht

include $(BUILD_SHARED_LIBRARY)

IRRLICHT_COMPILE_CONFIG_DIR := $(LOCAL_PATH)/irrlicht
$(call import-module,android/native_app_glue)
$(call import-module,irrlicht)
