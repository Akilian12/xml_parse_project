#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define BENCHMARK_ADVANCED
#include <iostream>
#include <catch2/catch.hpp>
#include <libxml++/libxml++.h>
#include <libxml/parser.h>
#include <tinyxml2.h>
#include <pugixml.hpp>

TEST_CASE("libxml++", "[benchmark]") {
    BENCHMARK_ADVANCED("Deserialization")(Catch::Benchmark::Chronometer meter)
    {
        meter.measure([] {
            xmlpp::DomParser parser;
            parser.parse_file("../big.xml");
            parser.get_document();
        });
    };

    xmlpp::DomParser parser;
    parser.parse_file("../big.xml");
    xmlpp::Document* document = parser.get_document();
    BENCHMARK_ADVANCED("Serialization")(Catch::Benchmark::Chronometer meter)
    {
        meter.measure([&document] {
            document->write_to_file("../lib.xml");
        });
    };
    //delete document;
}

TEST_CASE("pugixml", "[benchmark]") {
    BENCHMARK_ADVANCED("Deserialization")(Catch::Benchmark::Chronometer meter)
    {
        meter.measure([] {
            pugi::xml_document doc;
            doc.load_file("../big.xml");
            doc.reset();
        });
    };

    pugi::xml_document doc;
    doc.load_file("../big.xml");
    BENCHMARK_ADVANCED("Serialization")(Catch::Benchmark::Chronometer meter)
    {
        meter.measure([&doc] {
            doc.save_file("../pugi.xml");
        });
    };
    doc.reset();
}

TEST_CASE("tinyxml", "[benchmark]") {
    BENCHMARK_ADVANCED("Deserialization")(Catch::Benchmark::Chronometer meter)
    {
        meter.measure([] {
            tinyxml2::XMLDocument doc;
            doc.LoadFile( "../big.xml" );
            doc.Clear();
        });
    };

    tinyxml2::XMLDocument document;
    document.LoadFile( "../big.xml" );
    BENCHMARK_ADVANCED("Serialization")(Catch::Benchmark::Chronometer meter)
    {
        meter.measure([&document] {
            document.SaveFile("../tiny.xml");
        });
    };
    document.Clear();
}