//GraphicsEngineVESA.cpp
#include "GraphicsEngineVESA.h"

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

	short* mode = (short*)( ( vbeInfoBlock.VideoModePtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.VideoModePtr & 0xFFFF );
	mode = mode + __djgpp_conventional_base;
	printf( "modeptr %p", (short*)mode );
	unsigned int i = 0;
	while( *mode != -1 )
	{
		printf("Mode %i: %X\n", i, *(short*)mode + __djgpp_conventional_base );
		i++;
	}
	getchar();

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