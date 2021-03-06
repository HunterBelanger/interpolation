#include "catch.hpp"
#include "interpolation.hpp"

#include "dimwits.hpp"

#include "range/v3/view/take.hpp"

using namespace njoy::interpolation;
using namespace dimwits;

SCENARIO("The LinearLogarithmic interpolant computes the correct integral",
         "[interpolant], [LinearLogarithmic]"){
  std::vector<double> xValues{ 1E-2, 1, 10 };
  auto f1 = []( double x ){ return 13.2 * std::log(3.2*x); };
  auto f2 = []( double x ){ return -5.6 * std::log(2.4*x); };
  auto F1 = [](double x){return 13.2*x*(std::log(3.2*x)-1.);};
  auto F2 = [](double x){return -5.6*x*(std::log(2.4*x)-1.);};

  auto avg =
    []( double xLeft, double xRight ){ return 0.5 * ( xLeft + xRight ); };

  auto excessiveError =
    []( double reference, double trial ){
    auto error = std::abs( (trial - reference)
			   / ( ( reference != 0 ) ? reference : 1.0 ) );
    return error > 1E-15; };

  auto iterator = xValues.begin();
  auto last = std::prev( xValues.end() );
  do {
    double xLeft = *iterator, xRight = *( ++iterator );
    double y1Left = f1( xLeft ), y1Right = f1( xRight );
    double y2Left = f2( xLeft ), y2Right = f2( xRight );
    double xBar = avg( xLeft, xRight );
    double xLow = xLeft, xHi = xRight;

    REQUIRE( not excessiveError( F1(xBar) - F1(xLow),
                                 LinearLogarithmic::integrate
                                 ( xLow, xBar, xLeft, xRight, y1Left, y1Right ) ) );
    REQUIRE( not excessiveError( F2(xBar) - F2(xLow),
                                 LinearLogarithmic::integrate
                                 ( xLow, xBar, xLeft, xRight, y2Left, y2Right ) ) );

    REQUIRE( not excessiveError( F1(xHi) - F1(xBar),
                                 LinearLogarithmic::integrate
                                 ( xBar, xHi, xLeft, xRight, y1Left, y1Right ) ) );
    REQUIRE( not excessiveError( F2(xHi) - F2(xBar),
                                 LinearLogarithmic::integrate
                                 ( xBar, xHi, xLeft, xRight, y2Left, y2Right ) ) );
  } while( iterator != last );
}

SCENARIO("The LinearLogarithmic interpolant integration is compatible with units",
         "[interpolant], [LinearLogarithmic]"){
  std::vector< double > xValues{ 1E-2, 1, 10 };
  auto f1 = []( auto x ){ return 13.2 * std::log(3.2 * x.value) * barn; };
  auto f2 = []( auto x ){ return -5.6 * std::log(2.4 * x.value) * barn; };
  auto F1 = []( auto x ){return 13.2*x.value*(std::log(3.2*x.value)-1.) * barn * electronVolts;};
  auto F2 = []( auto x ){return -5.6*x.value*(std::log(2.4*x.value)-1.) * barn * electronVolts;};
 
  auto avg = []( auto xLeft, auto xRight ) { return 0.5 * ( xLeft + xRight ); };

  auto excessiveError =
    []( auto reference, auto trial ){
    auto error = std::abs( (trial - reference).value
			   / ( ( reference.value != 0 ) ?
			       reference.value : 1.0 ) );
    return error > 1E-15; };

  auto units = xValues |
    ranges::view::take( xValues.size() - 1 ) |
    ranges::view::transform( []( auto arg ){ return arg * electronVolts; } );

  auto iterator = units.begin();
  auto last = units.end();
  do {
    auto xLeft = *iterator, xRight = *( ++iterator );
    auto y1Left = f1( xLeft ), y1Right = f1( xRight );
    auto y2Left = f2( xLeft ), y2Right = f2( xRight );
    auto xBar = avg( xLeft, xRight );
    auto xLow = xLeft, xHi = xRight;

    REQUIRE( not excessiveError( F2(xBar) - F2(xLow),
                                 LinearLogarithmic::integrate
                                 ( xLow, xBar, xLeft, xRight, y2Left, y2Right ) ) );

    REQUIRE( not excessiveError( F1(xHi) - F1(xBar),
                                 LinearLogarithmic::integrate
                                 ( xBar, xHi, xLeft, xRight, y1Left, y1Right ) ) );
  } while( iterator != last );
}