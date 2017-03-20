#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "dimwits.hpp"
#include "interpolation.hpp"

using namespace njoy::interpolation;
using namespace dimwits;


SCENARIO("An interpolation table can be constructed"
	 " such that the left interval throws"){
  GIVEN("an x- and y-grid"){

    std::vector< double > xGrid{1.0, 2.0, 3.0};
    std::vector< double > yGrid{3.0, 5.0, 7.0};

    Table< table::Type< LinearLinear,
			table::search::Binary,
			table::discontinuity::TakeLeft, 
			std::vector< double >,
			std::vector< double > >,
	   table::left::interval::IsRuntimeConstant >
      myTable( 10.0, njoy::utility::copy(xGrid), njoy::utility::copy(yGrid) );

    THEN("the table can be evaluated in the center interval"){
      REQUIRE( 6.0 == myTable( 2.5 ) );
      REQUIRE( 6.0 == myTable( 2.5, myTable.search() ) );
    }

    THEN("the table will throw in the left interval"){
      REQUIRE( 10.0 == myTable( 0.0 ) );
      REQUIRE( 10.0 == myTable( 0.0, myTable.search() ) );
    }
  }
}