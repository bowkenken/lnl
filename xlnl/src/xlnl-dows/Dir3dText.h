#pragma once

#ifndef DIR3D_TEXT_H
#define DIR3D_TEXT_H

#include <d3d9.h>
#include <d3dx9.h>
#include <d3d9types.h>
#include <windows.h>
#include <atlbase.h>

class CDir3dText
{
protected:
	CComPtr<ID3DXFont> m_pFont;
	CComPtr<ID3DXSprite> m_pSprite;

public:
	CDir3dText(void);
	~CDir3dText(void);

	bool Create( LOGFONT *fontDesc );

	bool Begin();
	bool End();
	bool Draw(
		long x, long y, D3DCOLOR color, const char *str
	);
};

#endif // DIR3D_TEXT_H
