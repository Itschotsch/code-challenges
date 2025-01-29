#define CHECK_TASK_ONE      true
#define CHECK_TASK_TWO      true
#define CHECK_TASK_THREE    true
#define CHECK_TASK_FOUR     true

#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>

/**
 * -- TASK 1 --
 * This escape function returns a false return value if there is more than one character to escape in the input string.
 * Find the bug(s) and fix it.
 */
auto escape(
        const std::string& _value ) -> std::string {
    std::string value;
    const char* escapeList = R"str(\' ")str";
    auto index = _value.find_first_of( escapeList );
    if ( index == std::string::npos ) {
        value.assign( _value );
    } else {
        char escapeChar = '\\';
        auto offset = std::size_t();
        while ( index != std::string::npos ) {
            value.append( _value.substr( offset, index - offset ));
            value.push_back( escapeChar );
            value.push_back( _value[ index ] );
            offset = index + 1;
            index = _value.find_first_of( escapeList, offset );
        }
        value.append( _value.substr( offset ));
    }
    return value;
}

/**
 * -- TASK 2 --
 * Optimize the Color class. Add and/or change functions, classes or variables as you like.
 */
class Color {
    public:
        Color(
            unsigned char _r,
            unsigned char _g,
            unsigned char _b
        ) {
            r = _r;
            g = _g;
            b = _b;
        } ;

        ~Color() = default;

        auto operator==( const Color& rhs ) -> bool {
            return this->r == rhs.r && this->g == rhs.g && this->b == rhs.b;
        };

        int r;
        int g;
        int b;
};

auto is_black(
        auto const& _color ) -> bool {
    return Color(0, 0, 0) == _color;
}

/**
 * -- TASK 3 --
 * Create a function named "max" with two given variables, the greater one being the return value.
 * Allow only numerical types. The variables to be compared always have the same numerical type.
 */
/*
 * Your function.
 */
template <typename N, typename = std::enable_if_t<std::is_arithmetic_v<N>>>
N max(N a, N b) {
    return a > b ? a : b;
}

/**
 * -- TASK 4 --
 * Initialize 'randomCharacter' with a range of [a-z0-9] in the constructor.
 */
class SecretGenerator {
    public:
        /*
         * Replace this constructor.
         */
        SecretGenerator() {
            this->randomCharacter = []() -> char {
                // According to https://simple.wikipedia.org/wiki/File:ASCII-Table-wide.svg, a-z is 97-122 and 0-9 is 48-57.
                // That's 26 + 10 = 36.
                char r = rand() % 36;
                // Now split it up:
                if ( r < 26 ) {
                    return 'a' + r;
                } else {
                    return '0' + r - 26;
                }
            };
        }

        [[nodiscard]] auto generate(
                size_t _length ) const -> std::string {
            std::string secret( _length, 0 );
            std::generate_n( secret.begin(), _length, this->randomCharacter );
            return secret;
        }

    private:
        std::function<char()> randomCharacter;
};

/**
 * Assertion tests.
 */
auto main() -> int {
    // Assertion tests for task 1
#if CHECK_TASK_ONE
    assert( escape("'")                == "\\'" );
    assert( escape("no_escaping")      == "no_escaping" );
    assert( escape("some escaping")    == "some\\ escaping" );
    assert( escape("'wrong escaping'") == "\\'wrong\\ escaping\\'" );

    std::cout << "Test CHECK_TASK_ONE passed." << std::endl;
#endif

    // Assertion tests for task 2
#if CHECK_TASK_TWO
    auto black = Color( 0,   0,  0 );
    auto red   = Color( 0, 255,  0 );
    auto blue  = Color( 0,   0,255 );

    assert(  is_black( black ));
    assert( !is_black( red ));
    assert( !is_black( blue ));

    std::cout << "Test CHECK_TASK_TWO passed." << std::endl;
#endif

    // Assertion tests for task 3
#if CHECK_TASK_THREE
    u_int64_t uInt64X = size_t();
    u_int64_t uInt64Y = UINT64_MAX;
    int intX = 60*60;
    int intY = 360/60;
    float floatX = M_PI;
    float floatY = 3.141592;

    assert( max( uInt64X, uInt64Y ) == uInt64Y );
    assert( max( intX,    intY )    == intX );
    assert( max( floatX,  floatY )  == floatX );

    std::cout << "Test CHECK_TASK_THREE passed." << std::endl;
#endif

    // Assertion tests for task 4
#if CHECK_TASK_FOUR
    SecretGenerator sg = SecretGenerator();
    std::string secret1 = sg.generate(10);
    std::string secret2 = sg.generate(10);

    assert(  secret1.size() == 10 );
    assert( !secret1.empty() );
    assert(  secret1 != secret2 );

    std::cout << "Test CHECK_TASK_FOUR passed." << std::endl;
#endif

    return 0;
}
