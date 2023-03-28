#pragma once

#include "Component.h"
#include "Include.h"

BEGIN(Engine)

class  CTransform : public CComponent
{
private:
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform();

public:
	const _matrix*		Get_WorldMatrixPointer() { return &m_matWorld; }
	void				Get_Info(INFO eType, _vec3* pInfo)
	{
		memcpy(pInfo, &m_matWorld.m[eType][0], sizeof(_vec3));
	}
	const _vec3& Get_Scale()
	{
		return m_vScale;
	}

	void Set_Pos(const _float& x, const _float& y, const _float& z)
	{	
		m_vInfo[INFO_POS] = { x,y,z };
	}

	void				Move_Pos(_vec3* pDir, const _float& fTimeDelta, const _float& fSpeed)
	{
		m_vInfo[INFO_POS] += *D3DXVec3Normalize(pDir, pDir) * fSpeed * fTimeDelta;
	}

	void		Rotation(ROTATION eRot, const _float& fAngle)
	{
		*(((_float*)&m_vAngle) + eRot) += fAngle;
	}

	void			Chase_Target(const _vec3* pTargetPos, const _float& fSpeed, const _float& fTimeDelta);
	const _matrix*	Compute_Lookattarget(const _vec3* pTargetPos);

public:
	HRESULT		Ready_Transform(void);
	virtual		_int	Update_Component(const _float& fTimeDelta);
	virtual		void	LateUpdate_Component(void);

public:
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vScale;

	//float		m_fScale[3];

	_vec3		m_vAngle;
	_matrix		m_matWorld;

public:
	static CTransform*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);

private:
	virtual void	Free(void) override;

};
END