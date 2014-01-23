#pragma once
#include "Shader.h"
#include "AppBaseState.h"

class OAppTestShader : public OAppBaseState
{
	friend class OAppManager;

public:
	virtual void Init(void* data);
	virtual void Update(void* data = NULL);
	virtual void Update2(void* data = NULL);
	virtual void Draw();

	virtual void* GetDataForInput();
	
protected:
	static OAppTestShader& GetInstance();

	OAppTestShader();
	~OAppTestShader();

	void InitShader();

	OShader shader_;
};

