//
// Created by marcos on 3/5/20.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <thread>

TEST_CASE("Example Test") {
    system("rm exampleServer.out exampleClient.out");
    std::thread server (system,"./server 8080 > exampleServer.out");
    sleep(1);
    std::thread client (system,"./client localhost 8080 example.in > exampleClient.out");
    client.join();
    server.join();
    REQUIRE(!system("diff exampleServerMati.out exampleServer.out"));
    REQUIRE(!system("diff exampleClientMati.out exampleClient.out"));
}

TEST_CASE("Example Stdin Test") {
    system("rm exampleServer.out exampleClient.out");
    std::thread server (system,"./server 8080 > exampleServer.out");
    sleep(1);
    std::thread client (system,"./client localhost 8080 < example.in > exampleClient.out");
    client.join();
    server.join();
    REQUIRE(!system("diff exampleServerMati.out exampleServer.out"));
    REQUIRE(!system("diff exampleClientMati.out exampleClient.out"));
}

TEST_CASE("ManyCalls Test") {
    system("rm manyCallsServer.out manyCallsClient.out");
    std::thread server (system,"./server 8080 > manyCallsServer.out");
    sleep(1);
    std::thread client (system,"./client localhost 8080 manyCalls.in > manyCallsClient.out");
    client.join();
    server.join();
    REQUIRE(!system("diff manyCallsServerMati.out manyCallsServer.out"));
    REQUIRE(!system("diff manyCallsClientMati.out manyCallsClient.out"));
}

TEST_CASE("ManyCalls Stdin Test") {
    system("rm manyCallsServer.out manyCallsClient.out");
    std::thread server (system,"./server 8080 > manyCallsServer.out");
    sleep(1);
    std::thread client (system,"./client localhost 8080 < manyCalls.in > manyCallsClient.out");
    client.join();
    server.join();
    REQUIRE(!system("diff manyCallsServerMati.out manyCallsServer.out"));
    REQUIRE(!system("diff manyCallsClientMati.out manyCallsClient.out"));
}

TEST_CASE("Params Test") {
    system("rm paramsServer.out paramsClient.out");
    std::thread server (system,"./server 8080 > paramsServer.out");
    sleep(1);
    std::thread client (system,"./client localhost 8080 params.in > paramsClient.out");
    client.join();
    server.join();
    REQUIRE(!system("diff paramsServerMati.out paramsServer.out"));
    REQUIRE(!system("diff paramsClientMati.out paramsClient.out"));
}

TEST_CASE("Params Stdin Test") {
    system("rm paramsServer.out paramsClient.out");
    std::thread server (system,"./server 8080 > paramsServer.out");
    sleep(1);
    std::thread client (system,"./client localhost 8080 < params.in > paramsClient.out");
    client.join();
    server.join();
    REQUIRE(!system("diff paramsServerMati.out paramsServer.out"));
    REQUIRE(!system("diff paramsClientMati.out paramsClient.out"));
}



