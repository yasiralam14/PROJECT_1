add_test( [==[Scenario: cv::Mat img serialization]==] [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/build/tests/MyProject_test]==] [==[Scenario: cv::Mat img serialization]==]  )
set_tests_properties( [==[Scenario: cv::Mat img serialization]==] PROPERTIES WORKING_DIRECTORY [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/tests]==])
add_test( [==[Scenario: cv::Mat SIFT serialization]==] [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/build/tests/MyProject_test]==] [==[Scenario: cv::Mat SIFT serialization]==]  )
set_tests_properties( [==[Scenario: cv::Mat SIFT serialization]==] PROPERTIES WORKING_DIRECTORY [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/tests]==])
add_test( [==[Compute SIFTS from dataset and serialize]==] [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/build/tests/MyProject_test]==] [==[Compute SIFTS from dataset and serialize]==]  )
set_tests_properties( [==[Compute SIFTS from dataset and serialize]==] PROPERTIES WORKING_DIRECTORY [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/tests]==])
add_test( [==[Deserialize SIFTS from binary dataset]==] [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/build/tests/MyProject_test]==] [==[Deserialize SIFTS from binary dataset]==]  )
set_tests_properties( [==[Deserialize SIFTS from binary dataset]==] PROPERTIES WORKING_DIRECTORY [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/tests]==])
add_test( [==[Check for consistency while r/w datasets]==] [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/build/tests/MyProject_test]==] [==[Check for consistency while r/w datasets]==]  )
set_tests_properties( [==[Check for consistency while r/w datasets]==] PROPERTIES WORKING_DIRECTORY [==[/home/ubuntu/Modern_C_for_vision/C++/serialization/tests]==])
set( MyProject_test_TESTS [==[Scenario: cv::Mat img serialization]==] [==[Scenario: cv::Mat SIFT serialization]==] [==[Compute SIFTS from dataset and serialize]==] [==[Deserialize SIFTS from binary dataset]==] [==[Check for consistency while r/w datasets]==])
