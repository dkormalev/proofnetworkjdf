cmake_minimum_required(VERSION 3.12.0)
project(ProofNetworkJdfTest LANGUAGES CXX)

proof_add_target_sources(network-jdf_tests
    cutblock_test.cpp
    jdfdocument_test.cpp
    foldingparams_test.cpp
    resourcelinkpool_test.cpp
    knowndevicesquery_test.cpp
    jmfdocument_test.cpp
    knowndevicesresponse_test.cpp
    jdfhelpers_test.cpp
)
proof_add_target_resources(network-jdf_tests tests_resources.qrc)

proof_add_test(network-jdf_tests
    PROOF_LIBS NetworkJdf
)
