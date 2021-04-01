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
	struct VbeInfoBlock
	{
		unsigned char 	VbeSignature[4];
		unsigned short	VbeVersion;
		unsigned long	OemStrPtr;
		unsigned char	Capabilities[4];
		unsigned long	VideoModePtr;
		unsigned short	TotalMemory;
		unsigned short	OemSoftwareRev;
		unsigned long	OemVendorNamePtr;
		unsigned long	OemProductNamePtr;
		unsigned long	OemProductRevPtr;
		unsigned char	Reserved[222];
		unsigned char	OemData[256];
	}__attribute__( ( packed ) );

	long dosBuffer;
	dosBuffer = __tb & 0xFFFFF;

	__dpmi_regs r;
	r.x.ax = 0x4F00;
    r.x.es = ( dosBuffer>>4 ) & 0xFFFF;
    r.x.di = dosBuffer & 0xF;
	__dpmi_int( 0x10, &r );

	VbeInfoBlock vbeInfoBlock;

	dosmemget( dosBuffer, sizeof( VbeInfoBlock ), &vbeInfoBlock );	

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

	__djgpp_nearptr_enable();
	unsigned long segment = ( vbeInfoBlock.VideoModePtr & 0xFFFF0000 ) >> 12;
	unsigned long offset = vbeInfoBlock.VideoModePtr & 0x0000FFFF;
	unsigned long final = segment + offset + __djgpp_conventional_base; 
	printf("seg:%p, off:%p, linear:%p, final:%p\n", segment, offset, segment+offset, final );
	getchar();

	
	uint16_t* mode = (uint16_t*)final;
	printf( "modeptr %p\n", mode );
	unsigned int i = 0;
	while( mode[i] != 0xFFFF )
	{
		printf("Mode %i: %X\n", i, mode[i] );
		uint16_t newMode = mode[i];

		struct ModeInfoBlock
		{
			unsigned short	ModeAttributes;
			unsigned char	WinAAttributes;
			unsigned char	WinBAttributes;
			unsigned short	WinGranularity;
			unsigned short	WinSize;
			unsigned short	WinASegment;
			unsigned short	WinBSegment;
			unsigned long	WinFuncPtr;
			unsigned short	BytesPerScanLine;
			unsigned short	XResolution;
			unsigned short	YResolution;
			unsigned char	XCharSize;
			unsigned char	YCharSize;
			unsigned char	NumberOfPlanes;
			unsigned char	BitsPerPixel;
			unsigned char	NumberOfBanks;
			unsigned char	MemoryModel;
			unsigned char	BankSize;
			unsigned char	NumberOfImagesPages;
			unsigned char	Reserved1;
			unsigned char	RedMaskSize;
			unsigned char	RedFieldPosition;
			unsigned char	GreenMaskSize;
			unsigned char	GreenFieldPosition;
			unsigned char	BlueMaskSize;
			unsigned char	BlueFieldPosition;
			unsigned char	RsvdMaskSize;
			unsigned char	RsvdFieldPosition;
			unsigned char 	DirectColorModeInfo;
			unsigned long	PhysBasePtr;
			unsigned long	OffScreenMemOffset;
			unsigned char	Reserved2[206];
		}__attribute__( ( packed ) );

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
		
		vector<DisplayMode> modes;
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
	getchar();
	__djgpp_nearptr_disable();

	//Get Old Mode:
	r.x.ax = 0x4F03;
	__dpmi_int( 0x10, &r );
	oldMode = r.x.bx;

	printf( "oldMode: %x \n", oldMode );

}
vector<DisplayMode> GraphicsEngineVESA::GetAvailableDisplayModes()
{
	vector<DisplayMode> modes;
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