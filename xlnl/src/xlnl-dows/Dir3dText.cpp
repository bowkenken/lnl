#include "StdAfx.h"
#include "Dir3d.h"
#include "Dir3dText.h"
#include "../GlobalVar.h"

#define USE_SPRITE	0
#define USE_SPRITE_ARG	0

CDir3dText::CDir3dText(void)
{
	m_pFont = NULL;
	m_pSprite = NULL;
}

CDir3dText::~CDir3dText(void)
{
#if 0
//@@@
	if( m_pFont != NULL )
		delete m_pFont;
	m_pFont = NULL;

	if( m_pSprite != NULL )
		delete m_pSprite;
	m_pSprite = NULL;
#endif
}

bool CDir3dText::Create( LOGFONT *fontDesc )
{
	HRESULT result = D3DXCreateFontIndirect(
			g_Dir3d.pDir3dDevice, fontDesc, &m_pFont );
	if( FAILED( result ) )
		return false;

#if USE_SPRITE
	result = D3DXCreateSprite(
			g_Dir3d.pDir3dDevice, &m_pSprite );
	if( FAILED( result ) )
		return false;
#endif // USE_SPRITE

	return true;
}

bool CDir3dText::Begin()
{
#if USE_SPRITE
	if( m_pFont == NULL )
		return false;
	if( m_pSprite == NULL )
		return false;

# if USE_SPRITE_ARG
	HRESULT result = m_pSprite->Begin(
			(D3DXSPRITE_ALPHABLEND
			| D3DXSPRITE_SORT_TEXTURE) );
# else // USE_SPRITE_ARG
	HRESULT result = m_pSprite->Begin();
# endif // USE_SPRITE_ARG

	if( FAILED( result ) )
		return false;
#endif // USE_SPRITE

	return true;
}

bool CDir3dText::End()
{
#if USE_SPRITE
	if( m_pFont == NULL )
		return false;
	if( m_pSprite == NULL )
		return false;

	HRESULT result = m_pSprite->End();
	if( FAILED( result ) )
		return false;
#endif // USE_SPRITE

	return true;
}

bool CDir3dText::Draw(
	long x, long y, D3DCOLOR color, const char *str
)
{
	if( m_pFont == NULL )
		return false;
#if USE_SPRITE
	if( m_pSprite == NULL )
		return false;
#endif // USE_SPRITE

	if( str == NULL )
		return false;

	RECT rc;
	rc.left = x;
	rc.top = y;
	rc.right = 0;
	rc.bottom = 0;

	g_Dir3d.BeginDraw();

#if USE_SPRITE
	HRESULT result = m_pFont->DrawText(
			m_pSprite, str, -1, &rc, DT_NOCLIP, color );
#else // USE_SPRITE
	HRESULT result = m_pFont->DrawText(
			str, -1, &rc, DT_LEFT, color );
#endif // USE_SPRITE

	g_Dir3d.EndDraw();

	if( FAILED( result ) )
		return false;

	return true;
}
