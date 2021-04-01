//GraphicsEngineVESA.cpp
#include "GraphicsEngineVESA.h"
#include "GameEngine.h"

GraphicsEngineVESA::GraphicsEngineVESA( GameEngine* engine ) : GraphicsEngine( engine )
{
	//seems like there is nothing to do
	screenPadding 	= 64;
	//__djgpp_nearptr_enable();
	backBuffer 		= NULL;
	screenMemory 	= NULL;
	flip 			= false;

	InitGraphics();
}
GraphicsEngineVESA::~GraphicsEngineVESA()
{
	BackToTextMode();

	//__djgpp_nearptr_disable(); better call that in engine proper
}
void GraphicsEngineVESA::InitGraphics()
{

	//Get Graphics Card Infos----------------------------------
	long dosBuffer;
	dosBuffer = __tb & 0xFFFFF;

	__dpmi_regs r;
	r.x.ax = 0x4F00;
    r.x.es = ( dosBuffer>>4 ) & 0xFFFF;
    r.x.di = dosBuffer & 0xF;
	__dpmi_int( 0x10, &r );

	dosmemget( dosBuffer, sizeof( VbeInfoBlock ), &vbeInfoBlock );
	//---------------------------------------------------------	

	long mode_ptr; 
	printf( "VBE Signature: %s\n", vbeInfoBlock.VbeSignature );
	printf( "VBE Version: %hu \n", vbeInfoBlock.VbeVersion );
	mode_ptr = ( ( vbeInfoBlock.OemStrPtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemStrPtr & 0xFFFF );
	printf( "OEM String: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
	printf( "Capabilities: %li \n", ( long )vbeInfoBlock.Capabilities );
	printf( "VideoModes Ptr: %p \n", ( void* )vbeInfoBlock.VideoModePtr );
	printf( "total Memory: %hu \n", vbeInfoBlock.TotalMemory );
	printf( "software rev: %hu \n", vbeInfoBlock.OemSoftwareRev );
	mode_ptr = ( ( vbeInfoBlock.OemVendorNamePtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemVendorNamePtr & 0xFFFF );
	printf( "Vendor Name: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
	mode_ptr = ( ( vbeInfoBlock.OemProductNamePtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemProductNamePtr & 0xFFFF );
	printf( "Product Name: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
	mode_ptr = ( ( vbeInfoBlock.OemProductRevPtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemProductRevPtr & 0xFFFF );
	printf( "Product Rev: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
	getchar();
	



	//Get Old Mode:
	r.x.ax = 0x4F03;
	__dpmi_int( 0x10, &r );
	oldMode = r.x.bx;

	printf( "oldMode: %x \n", oldMode );




	vector<DisplayMode> modes = GetAvailableDisplayModes();
    for( unsigned int i = 0; i < modes.size(); i++ )
    {
        engine->debug->PrintString( "%s\n", modes[i].name.c_str() );
    }

}
vector<DisplayMode> GraphicsEngineVESA::GetAvailableDisplayModes()
{
	vector<DisplayMode> modes;

	long dosBuffer;
	dosBuffer = __tb & 0xFFFFF;

	__djgpp_nearptr_enable();
	unsigned long segment = ( vbeInfoBlock.VideoModePtr & 0xFFFF0000 ) >> 12;
	unsigned long offset = vbeInfoBlock.VideoModePtr & 0x0000FFFF;
	unsigned long final = segment + offset + __djgpp_conventional_base; 
	printf("seg:%p, off:%p, linear:%p, final:%p\n", segment, offset, segment+offset, final );
	getchar();


	__dpmi_regs r;
	
	uint16_t* mode = (uint16_t*)final;
	printf( "modeptr %p\n", mode );
	unsigned int i = 0;
	while( mode[i] != 0xFFFF )
	{
		printf("Mode %i: %X\n", i, mode[i] );
		uint16_t newMode = mode[i];

		dosBuffer = __tb & 0xFFFFF;

		r.x.ax = 0x4F01;
		r.x.cx = newMode;
	    r.x.es = ( dosBuffer>>4 ) & 0xFFFF;
	    r.x.di = dosBuffer & 0xF;
		__dpmi_int( 0x10, &r );

		ModeInfoBlock modeInfoBlock;

		dosmemget( dosBuffer, sizeof( ModeInfoBlock ), &modeInfoBlock );

		printf( "ModeAttributes: %u \n", 	modeInfoBlock.ModeAttributes 		);
		printf( "WinSize: %u \n", 			modeInfoBlock.WinSize 				);
		printf( "WinFuncPtr: %p \n", 		( void* )modeInfoBlock.WinFuncPtr 	);
		printf( "BytesPerScanline: %u \n", 	modeInfoBlock.BytesPerScanLine 		);
		printf( "XResolution: %hu \n", 		modeInfoBlock.XResolution 			);
		printf( "YResolution: %hu \n", 		modeInfoBlock.YResolution 			);
		printf( "XCharSize: %hu \n", 		modeInfoBlock.XCharSize 			);
		printf( "YCharSize: %hu \n", 		modeInfoBlock.YCharSize 			);
		printf( "NumberOfPlanes: %hu \n", 	modeInfoBlock.NumberOfPlanes 		);
		printf( "BitsPerPixel: %hu \n", 	modeInfoBlock.BitsPerPixel 			);
		printf( "NumberOfBanks: %hu \n", 	modeInfoBlock.NumberOfBanks 		);
		printf( "MemoryModel: %hu \n", 		modeInfoBlock.MemoryModel 			);
		printf( "BankSize: %hu \n", 		modeInfoBlock.BankSize 				);
		printf( "PhysBasePtr: %p \n", 		( void* )modeInfoBlock.PhysBasePtr 	);
		printf( "ModeAttributes: %u \n", 	modeInfoBlock.ModeAttributes 		);
		
		
		DisplayMode gMode;
		gMode.name.clear();
	    gMode.width = modeInfoBlock.XResolution;
		gMode.height = modeInfoBlock.YResolution;
		gMode.colorDepth = modeInfoBlock.BitsPerPixel;
		gMode.name.append( engine->text->SPrintString( "%X", mode[i] ) );
		engine->text->PrintString( "%s\n", gMode.name.c_str() );
        modes.push_back( gMode );

		i++;
		getchar();
	}
	__djgpp_nearptr_disable();

	return modes;
}
void GraphicsEngineVESA::SetDisplayMode( DisplayMode mode )
{
	
}
void GraphicsEngineVESA::SetFullScreen( bool fullScreen )
{
	
}
unsigned int GraphicsEngineVESA::GetScreenWidth()
{
	//
	return screenWidth;	
}
unsigned int GraphicsEngineVESA::GetScreenHeight()
{
	//
	return screenHeight;
}
void GraphicsEngineVESA::Update()
{
	
}
void GraphicsEngineVESA::Clear()
{
	
}
void GraphicsEngineVESA::Flip()
{
	
}
void GraphicsEngineVESA::DrawPixel( Vector2D pos, unsigned char color )
{
	
}

void GraphicsEngineVESA::BackToTextMode()
{

}