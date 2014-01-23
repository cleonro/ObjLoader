#pragma once
//#include "Shader.h"
#include "ui_ShaderWidget.h"
#include <QFileDialog>

class OShader;

class OShaderWidget : public QDialog
{
	Q_OBJECT

public:
	OShaderWidget(QWidget* parent = NULL);
	~OShaderWidget();

protected slots:
	void LoadVertexFile();
	void SaveVertexFile();
	void CompileVertex();
	void LoadFragmentFile();
	void SaveFragmentFile();
	void CompileFragment();
	void LoadShaders();
	void LinkProgram();
	void UseProgram();
	void ClearGL();
	void Clean();

protected:
	void LoadFile(int type);	//type = 1, vertex shader
								//type = 2, fragment shader
	void SaveFile(int type);

	Ui_ShaderEditor ui_;
	OShader*			shader_;
};
