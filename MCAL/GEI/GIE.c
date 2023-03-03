#include "GEI.h"

void GIE_Enable(void)
{
	
	SET_BIT( SREG , GIE_BIT);

}

void GIE_Disable(void)
{
	
	CLEAR_BIT( SREG , GIE_BIT);
	
}