// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 * Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1( TComponent * Owner ) : TForm( Owner )
{
}
// ---------------------------------------------------------------------------
typedef struct
{
	double h, v;
} Tp;

#define max 1000
Tp arr[ max ];
double X_vals[ max ];
double Y_vals[ max ];

long modd( long i )
{
	return ( ( i + max ) % max );
}

void step( void )
{
	static long first = 1;
	if ( first )
	{
		first = 0;
		memset( arr, 0, sizeof( arr ) );

		for ( long i = 0; i < max; i++ )
		{
			arr[ i ].h = 0.0;
			if ( i > max / 4 )
			{
				if ( ( i - max / 4 ) / 100.0 < 3.1415 )
				{
					arr[ i ].h = sin( ( i - max / 4 ) / 100.0 );
				}
			}
		}

	}
	else
	{
		for ( long i = 0; i < max; i++ )
		{
			arr[ i ].h = arr[ i ].h + arr[ i ].v;
			arr[ i ].v = arr[ i ].v - 0.0000001 * ( arr[ i ].h - ( arr[ modd( i + 1 ) ].h * 0.5 + arr[ modd( i - 1 ) ].h * 0.5 ) );
		}
		arr[ 0 ].h = 0;
		arr[ max - 1 ].h = 0;
	}

}

#define save_frames_ENABLED 1

void __fastcall TForm1::Timer1Timer( TObject * Sender )
{
	static long first = 1;
	//
	for ( long speed = 0; speed < 10000; speed++ )
	{
		step( );
	}

	if ( first )
	{
		// int __fastcall AddArray(const double *XValues, const int XValues_High, const double *YValues, const int YValues_High)/* overload */;
		for ( long i = 0; i < max; i++ )
		{
			X_vals[ i ] = 1.0 * i;
			Y_vals[ i ] = arr[ i ].h;
		}
		Series1->AddArray( X_vals, max, Y_vals, max );
	}
	else
	{
		for ( long i = 0; i < max; i++ )
		{
			Y_vals[ i ] = arr[ i ].h;
		}
		Series1->Clear( );
		Series1->AddArray( X_vals, max, Y_vals, max );

        #ifdef save_frames_ENABLED
		{
			static long frame_number = 0;
			frame_number++ ;
			Chart1->SaveToBitmapFile( Application->ExeName + IntToStr( ( __int64 )frame_number ) + ".bmp" );
		}
        #endif
	}
	first = 0;
}
// ---------------------------------------------------------------------------
