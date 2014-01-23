#include "ShaderWidget.h"
#include "Shader.h"
//#include <QFileDialog>
#include <fstream>

OShaderWidget::OShaderWidget(QWidget* parent) : QDialog(parent)
{
	ui_.setupUi(this);
	shader_ = new OShader;
}

OShaderWidget::~OShaderWidget()
{
	delete shader_;
}

void OShaderWidget::LoadFile(int type)
{
	QPlainTextEdit* txt = NULL;
	switch(type) {
		case 1:
			txt = ui_.vertexShaderEdit;
			break;
		case 2:
			txt = ui_.fragmentShaderEdit;
			break;
		default:
			break;
	}
	if(txt == NULL) {
		return;
	}
	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open shader source"), 
														app_path, tr("Shader (*.shd)"));
	if(file_name.isEmpty()) {
		return;
	}
	std::fstream fl(file_name.toLatin1().data(), std::ios::in);
	int sz = 0;
	fl.seekg(0, std::ios::end);
	sz = fl.tellg();
	fl.seekg(0);
	char* buffer = new char[sz + 1];
	buffer[sz] = '\0';
	fl.read(buffer, sz);

 	txt->setPlainText(QString(buffer));

	delete [] buffer;
	fl.close();
}

void OShaderWidget::SaveFile(int type)
{
	QPlainTextEdit* txt = NULL;
	switch(type) {
		case 1:
			txt = ui_.vertexShaderEdit;
			break;
		case 2:
			txt = ui_.fragmentShaderEdit;
			break;
		default:
			break;
	}
	if(txt == NULL) {
		return;
	}

	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getSaveFileName(this, tr("Save shader"), 
														app_path, tr("Shader (*.shd)"));
	if(file_name.isEmpty()) {
		return;
	}

	std::ofstream fl(file_name.toLatin1().data(), std::ios::out);
	QString buffer = txt->toPlainText();
// 	int sz = buffer.length();
// 	fl.write(buffer.toLatin1().data(), sz);
	fl<<buffer.toLatin1().data();
	fl.close();
}

void OShaderWidget::LoadVertexFile()
{
	LoadFile(1);
}

void OShaderWidget::SaveVertexFile()
{
	SaveFile(1);
}

void OShaderWidget::CompileVertex()
{
	QString str = ui_.vertexShaderEdit->toPlainText();
	shader_->LoadShaderString(str.toLatin1().data(), 1);
	shader_->CompileShader(1);
	char* log = shader_->ShaderInfoLog(1);
	ui_.log->appendPlainText(log);
	delete [] log;
}

void OShaderWidget::LoadFragmentFile()
{
	LoadFile(2);
}

void OShaderWidget::SaveFragmentFile()
{
	SaveFile(2);
}

void OShaderWidget::CompileFragment()
{
	QString str = ui_.fragmentShaderEdit->toPlainText();
	shader_->LoadShaderString(str.toLatin1().data(), 2);
	shader_->CompileShader(2);
	char* log = shader_->ShaderInfoLog(2);
	ui_.log->appendPlainText(log);
	delete [] log;
}

void OShaderWidget::LoadShaders()
{
	shader_->LoadShaders();
	char* log = shader_->ProgramInfoLog();
	ui_.log->appendPlainText(log);
	delete [] log;
}

void OShaderWidget::LinkProgram()
{
	shader_->Link();
	char* log = shader_->ProgramInfoLog();
	ui_.log->appendPlainText(log);
	delete [] log;
}

void OShaderWidget::UseProgram()
{

}

void OShaderWidget::ClearGL()
{

}

void OShaderWidget::Clean()
{
	ui_.vertexShaderEdit->clear();
	ui_.fragmentShaderEdit->clear();
	ui_.log->clear();
}
