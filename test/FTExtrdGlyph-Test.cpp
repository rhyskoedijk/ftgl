#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTExtrdGlyph.h"

extern void buildGLContext();

class FTExtrdGlyphTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTExtrdGlyphTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTExtrdGlyphTest() : CppUnit::TestCase( "FTExtrdGlyph Test")
        {
        }
        
        FTExtrdGlyphTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTExtrdGlyphTest()
        {
        }
        
        void testConstructor()
        {
            FT_Library   library;
            FT_Face      face;
            
            FT_Error error = FT_Init_FreeType( &library);
            assert(!error);
            error = FT_New_Face( library, FONT_FILE, 0, &face);
            assert(!error);
            
            FT_Set_Char_Size( face, 0L, FONT_POINT_SIZE * 64, RESOLUTION, RESOLUTION);
            
            error = FT_Load_Char( face, CHARACTER_CODE_A, FT_LOAD_DEFAULT);
            assert( !error);
            
            buildGLContext();
        
            FTExtrdGlyph* extrudedGlyph = new FTExtrdGlyph( face->glyph, 0.0f);            
            CPPUNIT_ASSERT( extrudedGlyph->Error() == 0);
        
            FT_Done_Face( face);
            FT_Done_FreeType( library);
            
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTExtrdGlyphTest);

