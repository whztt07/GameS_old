// TestServerGameS.cpp: главный файл проекта.

#include "stdafx.h"
#include "Form1.h"

using namespace TestServerGameS;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Form1^ form = gcnew Form1();
	// Создание главного окна и его запуск
	Application::Run(form);
	return 0;
}
