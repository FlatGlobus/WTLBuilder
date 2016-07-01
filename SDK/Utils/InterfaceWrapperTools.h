/********************************************************************
*
* Copyright (C) 2001 Sven Wiegand
* 
* This file is free software; you can redistribute it and/or
* modify, but leave the headers intact and do not remove any 
* copyrights from the source.
*
* If you have further questions, suggestions or bug fixes, please
* let me know
*
*    sven.wiegand@web.de
*
********************************************************************/

#ifndef __INTERFACEWRAPPERTOOLS_H__
#define __INTERFACEWRAPPERTOOLS_H__

#define GETTHIS(AggregatingClass, InterfaceImpl) \
	AggregatingClass	*pThis = \
		((AggregatingClass*)((BYTE*)this - offsetof(AggregatingClass, InterfaceImpl))); \


#endif //__INTERFACEWRAPPERSTOOLS_H__