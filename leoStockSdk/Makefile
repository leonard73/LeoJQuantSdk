LEO_STOCK_SDK_SOURCE_PATH:=source
LEO_STOCK_SDK_INCLUDE_PATH:=include
LEO_STOCK_SDK_UINT_TEST_PATH:=unitTest
compile_cc:=g++
compile_flag:=-lcurl -lstdc++
sdk_cource_files:=  $(LEO_STOCK_SDK_SOURCE_PATH)/controller.cpp\
					$(LEO_STOCK_SDK_SOURCE_PATH)/strDecode.cpp
sdk_include_path:=$(LEO_STOCK_SDK_INCLUDE_PATH)
test_all_source:=$(LEO_STOCK_SDK_UINT_TEST_PATH)/000_testall.cpp
test_all_exe:=unitTest/000_testall
build:
		$(compile_cc) $(sdk_cource_files) $(test_all_source) -o $(test_all_exe) $(compile_flag) -I$(sdk_include_path)
run:
		./$(test_all_exe)
clean:
		rm -rf $(test_all_exe)